#include <async/Service.h>
#include <async/LoggerConfig.h>
#include <async/LockGuard.h>

using namespace ravensnight::async;
using namespace ravensnight::logging;

Service::Service(const char *name) : 
    _task(name),
    _runnable(RefType::owned) {
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

    if (_runnable.isNULL()) {
        _runnable = createRunnable();
        if (!_runnable.isNULL()) {
            _task.start(_runnable.get(), getPriority(), getStackSize());
        } else {
            _logger.error("Service::install - createRunnable returned NULL.");
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
    if (!_runnable.isNULL()) {
        _task.kill();
        _runnable.clear();
    }

    postUninstall();
}

ClassLogger Service::_logger(LC_ASYNC);
