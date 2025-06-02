#include <async/LockGuard.h>

#include <Logger.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

    LockGuard::LockGuard(Mutex& mtx) {
        //Logger::debug("LockGuard::LockGuard - lock");
        _mtx = &mtx;
        _mtx->lock();
    }

    LockGuard::~LockGuard() {
        //Logger::debug("LockGuard::~LockGuard - unlock");
        _mtx->unlock();
    }

}