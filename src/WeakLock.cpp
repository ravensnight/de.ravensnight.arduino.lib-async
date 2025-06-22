#include <async/WeakLock.h>
#include <Logger.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

    WeakLock::WeakLock(const char* name) {
        _name = name;
    }

    void WeakLock::lock() {
        if (_locked) {
            Logger::warn("WeakLock::lock - %s already locked!", _name);
        }
        
        _locked = true;
    }

    bool WeakLock::isLocked() {
        return _locked;
    }

    void WeakLock::unlock() {
        _locked = false;
    }

}