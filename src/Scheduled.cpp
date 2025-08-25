#include <async/Scheduled.h>

using namespace ravensnight::async;

Scheduled::Scheduled(uint32_t delayInMS) {
    _ticksDelay = pdMS_TO_TICKS( delayInMS );
}

void Scheduled::run() {
    while (1) {
        vTaskDelay(_ticksDelay);
        execute();
    }
}
