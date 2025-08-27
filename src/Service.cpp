#include <async/Service.h>
#include <async/LockGuard.h>

using namespace ravensnight::async;

Service::Service(const char *name) : _task(name), _mutex(name) {
}

Service::~Service()
{
    uninstall();
}

bool Service::install()
{
    acquirelock(_mutex);
    if (_runnable == 0) {
        _runnable = createRunnable();
        _task.start(_runnable, getPriority(), getStackSize());
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
