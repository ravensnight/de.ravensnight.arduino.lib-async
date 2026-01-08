#include <async/LockGuard.h>
#include <async/LoggerConfig.h>

using namespace ravensnight::logging;

namespace ravensnight::async {
    Logger LockGuard::_logger(LC_ASYNC);

    LockGuard::LockGuard(Lockable* lockable) {
        _logger.trace("LockGuard - lock");
        _mtx = lockable;
        _mtx->lock();
    }

    LockGuard::~LockGuard() {
        _logger.trace("LockGuard - unlock");
        _mtx->unlock();
    }

}