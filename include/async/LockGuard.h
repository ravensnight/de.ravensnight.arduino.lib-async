#ifndef __LockGuard_h__
#define __LockGuard_h__

#include <async/Mutex.h>

namespace ravensnight::async {

    class LockGuard {

        private:
            Mutex* _mtx;

        public:

            LockGuard(Mutex& mtx);
            ~LockGuard();
    };

    #define synchronized(mutex) const ravensnight::async::LockGuard __lockguard(mutex)
}

#endif // __LockGuard_h__