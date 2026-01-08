#ifndef __QueueListener_h__
#define __QueueListener_h__

#include <Logger.h>
#include <async/LoggerConfig.h>

#include <async/Runnable.h>
#include <async/Queue.hpp>
#include <async/Mutex.h>

using namespace ravensnight::logging;

namespace ravensnight::async {
    template <class T>
    Logger QueueListener<T>::_logger(LC_ASYNC);

    template <class T>
    class QueueListener : public Runnable {
        private:
            static Logger _logger;

            Receiver<T>* _receiver = 0;
            Queue<T>* _queue = 0;
            bool _useHeap = false;
            Mutex _mutex;

            void runOnStack(QueueHandle_t& h) {
                BaseType_t status;
                T msg2;
                while (true) {
                    status = xQueueReceive(h, &msg2, portMAX_DELAY);
                    if (status != pdPASS) continue;
                    
                    _mutex.lock();
                    _receiver->handle(msg2);
                    _mutex.unlock();
                }
            }

            void runOnHeap(QueueHandle_t& h) {
                BaseType_t status;
                QueueMsg msg1;
                while (true) {

                    status = xQueueReceive(h, &msg1, portMAX_DELAY);
                    if (status != pdPASS) continue;
                    _mutex.lock();

                    T& payload = *((T*)(msg1.ptr));
                    _receiver->handle(payload);

                    _logger.debug("Handled queue message and destroy.");
                    free(msg1.ptr);  // remove the message after its handled.
                    
                    _mutex.unlock();
                }
            }

        public:

            QueueListener(Queue<T>* queue, Receiver<T>* receiver, bool useHeap) : _mutex("QueueListener") {
                _receiver = receiver;
                _queue = queue;
                _useHeap = useHeap;
            }

            void run() {
                QueueHandle_t& h = _queue->handle();
                if (h == 0) {
                    return;
                }

                if (_useHeap) {
                    runOnHeap(h);
                } else {
                    runOnStack(h);
                }
            }
    };

}

#endif //  __QueueListener_h__