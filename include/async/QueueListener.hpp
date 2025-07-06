#ifndef __QueueListener_h__
#define __QueueListener_h__

#include <Logger.h>

#include <async/Job.h>
#include <async/Queue.hpp>

using namespace ravensnight::logging;

namespace ravensnight::async {

    template <class T>
    class QueueListener : public Job {
        private:
            Receiver<T>* _receiver;
            Queue<T>* _queue;
            bool _useHeap;

        public:

            QueueListener(Queue<T>& queue, Receiver<T>& receiver, bool useHeap) {
                _receiver = &receiver;
                _queue = &queue;
                _useHeap = useHeap;
            }

            void run() {
                QueueHandle_t& h = _queue->handle();
                if (h == 0) {
                    return;
                }

                if (_useHeap) {
                    QueueMsg msg1;
                    while (xQueueReceive(h, &msg1, portMAX_DELAY)) {

                        T& payload = *((T*)(msg1.ptr));
                        _receiver->handle(payload);

                        Logger::debug("Handled queue message. Destroy message.");
                        free(msg1.ptr);  // remove the message after its handled.
                    }
                } else {
                    T msg2;
                    while (xQueueReceive(h, &msg2, portMAX_DELAY)) {
                        _receiver->handle(msg2);
                    }
                }


            }
    };

}

#endif //  __QueueListener_h__