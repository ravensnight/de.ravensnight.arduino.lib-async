#include <async/LockGuard.h>

#include <Logger.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

    LockGuard::LockGuard(Lockable* lockable) {
        //Logger::debug("LockGuard::LockGuard - lock");
        _mtx = lockable;
        _mtx->lock();
    }

    LockGuard::~LockGuard() {
        //Logger::debug("LockGuard::~LockGuard - unlock");
        _mtx->unlock();
    }

}