#include <async/Service.h>
#include <async/LockGuard.h>

using namespace ravensnight::async;

Service::Service(const char *name, uint8_t priority, uint32_t stackSize) : _task(name), _mutex(name)
{
    _priority = priority;
    _stackSize = stackSize;
}

Service::~Service()
{
    if (_runnable != 0) {
        _task.kill();

        delete _runnable;
        _runnable = 0;
    }
}

bool Service::install()
{
    acquirelock(_mutex);

    if (_runnable == 0) {
        _runnable = createRunnable();
        _task.start(_runnable, _priority, _stackSize);
        return true;
    }

    return false;
}

void Service::uninstall()
{
    acquirelock(_mutex);

    if (_runnable != 0) {
        _task.kill();
        delete _runnable;
        _runnable = 0;
    }
}
