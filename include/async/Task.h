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
            uint8_t _priority;
            uint32_t _stackSize;
            TaskHandle_t _handle;

        public:

            Task(const char* name, uint8_t priority, uint32_t stackSize);

            void start(Runnable* runnable);
            void kill();
    };

}

#endif //  __Task_h__