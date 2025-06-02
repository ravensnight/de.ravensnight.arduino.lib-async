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

        public:

            QueueListener(Queue<T>& queue, Receiver<T>* receiver) {
                _receiver = receiver;
                _queue = &queue;
            }

            void run() {
                QueueHandle_t& h = _queue->handle();
                if (h == 0) {
                    return;
                }

                QueueMsg msg;
                while (xQueueReceive(h, &msg, portMAX_DELAY)) {

                    T& payload = *((T*)msg.ptr);
                    _receiver->handle(payload);

                    Logger::debug("Handled queue message. Destroy message.");
                    free(msg.ptr);  // remove the message after its handled.
                }
            }
    };

}

#endif //  __QueueListener_h__