
#include <async/LoggerConfig.h>
#include <async/Scheduler.h>

namespace ravensnight::async {

 /**
  *----------------------------------------------------------------------------
  * Scheduler implementation
  * ----------------------------------------------------------------------------
  */

Scheduler::Scheduler(const char* name, uint16_t timeSliceMS) : Service(name) {
    _timeSlice = timeSliceMS;    
}

Scheduler::~Scheduler() {
    for (SchedulerEntry* e : _entries) {
        delete e;
    }

    _entries.clear();
}

uint16_t Scheduler::timeSlice() {
    return _timeSlice;
}

uint8_t Scheduler::getPriority() {
    return SCHEDULER_PRIORITY;
}

uint32_t Scheduler::getStackSize() {
    return SCHEDULER_STACKSIZE;
}

Runnable* Scheduler::createRunnable() {
    SchedulerTask* t = new SchedulerTask(this);
    return t;
}

void Scheduler::attach(Runnable* job, uint16_t delayTimeMS, bool deleteOnClose) {
    SchedulerEntry* e = new SchedulerEntry(job, delayTimeMS, deleteOnClose);
    _entries.push_back(e);
}

/** 
 * ----------------------------------------------------------------------------
 * SchedulerTask implementation
 * ----------------------------------------------------------------------------
 */

SchedulerTask::SchedulerTask(Scheduler* scheduler) {
    _scheduler = scheduler;
     _ticks = pdMS_TO_TICKS( scheduler->timeSlice() );
}

void SchedulerTask::run() {
    while (1) {
        vTaskDelay(_ticks);
        _scheduler->tick();
    }
}

/** 
 * ----------------------------------------------------------------------------
 * SchedulerEntry implementation
 * ----------------------------------------------------------------------------
 */

SchedulerEntry::SchedulerEntry(Runnable* job, uint16_t delayTimeMS, bool deleteOnClose) {
    _runnable = job;
    _timer = 0;
    _delayTime = delayTimeMS;
    _deleteOnClose = deleteOnClose;
}

SchedulerEntry::~SchedulerEntry() {
    if (_deleteOnClose && (_runnable != 0)) {
        delete _runnable;
        _runnable = 0;
    }
}

void SchedulerEntry::update(uint16_t slice) {
    if (_runnable == 0) return;

    _timer += slice;
    if (_timer >= _delayTime) {
        _runnable->run();
        _timer = 0;
    }
}

ClassLogger Scheduler::_logger(LC_ASYNC);

}