#include <async/RepeatedJob.h>

using namespace ravensnight::async;

RepeatedJob::RepeatedJob(uint32_t delayInMS) {
    _ticksDelay = pdMS_TO_TICKS( delayInMS );
}

void RepeatedJob::run() {
    while (1) {
        vTaskDelay(_ticksDelay);
        execute();
    }
}
