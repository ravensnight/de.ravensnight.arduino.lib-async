#include <async/Service.h>
#include <async/LockGuard.h>
#include <Logger.h>

using namespace ravensnight::async;
using namespace ravensnight::logging;

Service::Service(const char *name) : _task(name) {
}

Service::~Service()
{
    uninstall();
}

bool Service::preInstall() {
    return true;
}

bool Service::install()
{
    if (!preInstall()) {
        return false;
    }

    if (_runnable == 0) {
        _runnable = createRunnable();
        if (_runnable != 0) {
            _task.start(_runnable, getPriority(), getStackSize());
        } else {
            Logger::error("Service::install - createRunnable returned NULL.");
            return false;
        }

        return true;
    }

    return false;
}

void Service::postUninstall() {
}

void Service::uninstall()
{
    if (_runnable != 0) {
        _task.kill();
        delete _runnable;
        _runnable = 0;
    }

    postUninstall();
}
