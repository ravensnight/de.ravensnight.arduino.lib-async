#ifndef __QueueListener_h__
#define  __QueueListener_h__

#include <async/Job.h>
#include <async/Queue.h>

namespace ravensnight::async {

    template <class T>
    class QueueListener : public Job {
        private:
            Receiver<T>* _receiver;
            QueueHandle_t* _queue;

        public:

            QueueListener(QueueHandle_t& queue, Receiver<T>& receiver);
            void run();
    };

}

#endif //  __QueueListener_h__