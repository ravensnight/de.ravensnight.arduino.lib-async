#include <async/WeakLock.h>
#include <async/LoggerConfig.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

    WeakLock::WeakLock(const char* name) {
        _name = name;
    }

    void WeakLock::lock() {
        if (_locked) {
            _logger.warn("WeakLock::lock - %s already locked!", _name);
        }
        
        _locked = true;
    }

    bool WeakLock::isLocked() {
        return _locked;
    }

    void WeakLock::unlock() {
        _locked = false;
    }

    ClassLogger WeakLock::_logger(LC_ASYNC);
}