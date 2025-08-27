#ifndef __Task_h__
#define  __Task_h__

#include <Arduino.h>
#include <async/Mutex.h>
#include <async/Runnable.h>

namespace ravensnight::async {

    class Task {

        private: 

            Mutex _mutex;
            const char* _name;
            TaskHandle_t _handle;

        public:

            Task(const char* name);

            void start(Runnable* runnable, uint8_t priority, uint32_t stackSize);
            void kill();
    };

}

#endif //  __Task_h__