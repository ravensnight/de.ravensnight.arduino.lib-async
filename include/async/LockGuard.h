#ifndef __LockGuard_h__
#define __LockGuard_h__

#include <async/Mutex.h>

namespace ravensnight::async {

    class LockGuard {

        private:
            Lockable* _mtx;

        public:

            LockGuard(Lockable* mtx);
            ~LockGuard();
    };

    #define acquirelock(lockable) const ravensnight::async::LockGuard __lockguard(&lockable)
}

#endif // __LockGuard_h__