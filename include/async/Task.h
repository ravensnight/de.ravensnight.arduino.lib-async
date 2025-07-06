#ifndef __Task_h__
#define  __Task_h__

#include <Arduino.h>
#include <async/Job.h>

namespace ravensnight::async {

    class Task {

        private: 

            const char* _name;
            uint8_t _priority;
            uint32_t _stackSize;
            Job* _runnable;
            TaskHandle_t _handle;

        public:

            Task(const char* name, uint8_t priority, uint32_t stackSize, Job* runnable);

            void start();
            void kill();
    };

}

#endif //  __Task_h__