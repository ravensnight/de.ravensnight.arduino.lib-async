#include <Arduino.h>

#include <Logger.h>
#include <async/Service.h>
#include <async/Runnable.h>

using namespace ravensnight::async;
using namespace ravensnight::logging;

class Runner : public Runnable {

    public:
        void run() {
            Logger::debug("Run once.");
        }
};

class Test : public Service {

    public:

        Test() : Service("Test") {            
        }

    protected:
        uint8_t getPriority() {
            return 2;
        }

        uint32_t getStackSize() {
            return 1024;
        }

        Runnable* createRunnable() {
            return new Runner();
        }
};

Test tmp;

void setup() {
    tmp.install();
}

void loop() {
}