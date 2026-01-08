#include <async/Mutex.h>
#include <async/LoggerConfig.h>

using namespace ravensnight::logging;

namespace ravensnight::async {
    Logger Mutex::_logger(LC_ASYNC);

    Mutex::Mutex(const char* name) {
        _name = name;
        _counter = 0;
    }

    Mutex::~Mutex() {        
    }

    void Mutex::lock() {
        _counter++;
        if (_counter > 1) {
            _logger.warn("Mutex try lock %s - %d", _name, _counter);
        }
        _mtx.lock();
        _logger.trace("Mutex lock(%s) - locked", _name);
    }

    void Mutex::unlock() {
        _mtx.unlock();
        _logger.trace("Mutex unlock(%s) - unlocked", _name);
        _counter--;
    }


}

