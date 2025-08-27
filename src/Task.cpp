#include <async/Task.h>
#include <async/LockGuard.h>

namespace ravensnight::async
{

    void __task_runner(void *param)
    {
        Runnable *runnable = (Runnable*)param;
        runnable->run();
    }

    Task::Task(const char *name, uint8_t priority, uint32_t stackSize) : _mutex(name)
    {
        _name = name;
        _stackSize = stackSize;
        _priority = priority;
        _handle = 0;
    }

    void Task::start(Runnable* runnable)
    {
        acquirelock(_mutex);
        if (_handle == 0)
        {
            xTaskCreate(&__task_runner, _name, _stackSize, runnable, 2, &_handle);
        }
    }

    void Task::kill()
    {
        acquirelock(_mutex);
        if (_handle != 0)
        {
            vTaskDelete(_handle);
            _handle = 0;
        }
    }

}