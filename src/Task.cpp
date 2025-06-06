#include <async/Task.h>

namespace ravensnight::async {

void __task_runner( void* param ) {
    Job* runnable = (Job*)param;
    runnable->run();
}

Task::Task(const char* name, uint8_t priority, uint32_t stackSize, Job* runnable) {
    _runnable = runnable;
    _name = name;
    _stackSize = stackSize;
    _priority = priority;
    _handle = 0;
}

void Task::start() {
    if (_handle == 0) {
        xTaskCreate(&__task_runner, _name, _stackSize, _runnable, 2, &_handle);
    }
}

void Task::kill() {
    if (_handle != 0) {
        vTaskDelete( _handle );
    }
}

}