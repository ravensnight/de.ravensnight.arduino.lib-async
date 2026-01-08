#ifndef __WeakLock_h__
#define __WeakLock_h__

#include <Arduino.h>
#include <Logger.h>
#include <async/Lockable.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

    class WeakLock : public Lockable {
        private:

            static Logger _logger;

            bool _locked;
            const char* _name;

        public:

            WeakLock(const char* name);

            bool isLocked();
            void lock();
            void unlock();
    };

}

#endif // __WeakLock_h__