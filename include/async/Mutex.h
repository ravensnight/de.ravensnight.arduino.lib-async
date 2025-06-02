#ifndef __Mutex_h__
#define __Mutex_h__

#include <Arduino.h>
#include <mutex>

namespace ravensnight::async {

    class Mutex {

        private:

            const char* _name;
            uint16_t _counter;
            std::mutex _mtx;

        public:

            Mutex(const char* name);
            ~Mutex();
     
            void lock();
            void unlock();
    };
}

#endif // __Mutex_h__