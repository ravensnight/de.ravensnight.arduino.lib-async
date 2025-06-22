#ifndef __WeakLock_h__
#define __WeakLock_h__

#include <Arduino.h>
#include <async/Lockable.h>

namespace ravensnight::async {

    class WeakLock : public Lockable {
        private:
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