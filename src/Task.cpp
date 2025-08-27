#include <async/Task.h>
#include <async/LockGuard.h>

namespace ravensnight::async
{

    void __task_runner(void *param)
    {
        Runnable *runnable = (Runnable*)param;
        runnable->run();
    }

    Task::Task(const char *name)
    {
        _name = name;
        _handle = 0;
    }

    void Task::start(Runnable* runnable, uint8_t priority, uint32_t stackSize)
    {
        if (_handle == 0)
        {
            xTaskCreate(&__task_runner, _name, stackSize, runnable, priority, &_handle);
        }
    }

    void Task::kill()
    {
        if (_handle != 0)
        {
            vTaskDelete(_handle);
            _handle = 0;
        }
    }

}