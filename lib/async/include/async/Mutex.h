#ifndef __Mutex_h__
#define __Mutex_h__

#include <Arduino.h>
#include <mutex>

#include <ClassLogger.h>
#include <async/Lockable.h>


using namespace ravensnight::logging;

namespace ravensnight::async {

    class Mutex : public Lockable {

        private:

            static ClassLogger _logger;
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