#include <async/Mutex.h>
#include <Logger.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

    Mutex::Mutex(const char* name) {
        _name = name;
        _counter = 0;
    }

    Mutex::~Mutex() {        
    }

    void Mutex::lock() {
        _counter++;
        if (_counter > 1) {
            Logger::warn("Mutex::try lock %s - %d", _name, _counter);
        }
        _mtx.lock();
        // Logger::debug("Mutex::lock(%s) - locked", _name);
    }

    void Mutex::unlock() {
        _mtx.unlock();
        // Logger::debug("Mutex::unlock(%s) - unlocked", _name);
        _counter--;
    }
}

