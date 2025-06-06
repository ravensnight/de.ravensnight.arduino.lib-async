#include <async/Mutex.h>
#include <Logger.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

    Mutex::Mutex(const char* name) {
        _name = name;
    }

    Mutex::~Mutex() {        
    }

    void Mutex::lock() {
        // Logger::debug("Mutex::lock(%s) - waiting... ", _name);
        _mtx.lock();
        // Logger::debug("Mutex::lock(%s) - locked", _name);
    }

    void Mutex::unlock() {
        _mtx.unlock();
        // Logger::debug("Mutex::unlock(%s) - unlocked", _name);
    }
}

