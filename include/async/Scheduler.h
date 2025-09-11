#ifndef __Scheduler_h__
#define __Scheduler_h__

#include <Arduino.h>
#include <ClassLogger.h>
#include <list>

#include <async/Scheduled.h>
#include <async/Service.h>

using namespace ravensnight::logging;

namespace ravensnight::async {
    
    #ifndef SCHEDULER_PRIORITY
        #define SCHEDULER_PRIORITY 4
    #endif

    #ifndef SCHEDULER_STACKSIZE
        #define SCHEDULER_STACKSIZE 2048
    #endif

    /**
     * Scheduler entry, which holds the attached runnable to schedule.
     */
    class SchedulerEntry {
        private:
            uint16_t    _timer = 0;
            uint16_t    _timerId = 0;
            uint16_t    _delayTime = 0;
            Scheduled*  _runnable  = 0;
            bool        _deleteOnClose = false;

        public:
            SchedulerEntry(Scheduled* job, uint16_t timerId, uint16_t delayTimeMS, bool deleteOnClose);
            ~SchedulerEntry();

            void update(uint16_t slice);
    };

    /**
     * The task which runs continously
     */
    class Scheduler;
    class SchedulerTask : public Runnable {

        private:
            TickType_t _ticks;
            Scheduler* _scheduler;

        public:

            SchedulerTask(Scheduler* scheduler);
            void run();
    };

    /**
     * The scheduler service
     */
    class Scheduler : public Service {

        friend class SchedulerTask;

        private:

            static ClassLogger _logger;
            
            uint16_t _timeSlice;
            uint16_t _timerId;
            std::list<SchedulerEntry*> _entries;         
            
        protected:
            void tick();
            uint16_t timeSlice();

        public:

            /**
             * Create the scheduler.
             * @param name the name of the scheduler. This is used to identify the scheduler task
             * @param timeSliceMS the task wait time in milliseconds. This is the minimum resolution of the scheduler.
             */
            Scheduler(const char* name, uint16_t timeSliceMS);
            ~Scheduler();

            /**
             * Register a single job, which is being called every repeatMS
             * @param job the Scheduler Job to be registered with the scheduler
             * @param timerId the unique id of the timer. This is passed to the Scheduled::timeExpired method and may be used to identify the timer, which expired.
             * @param delayTimeMS the time in millis to wait between multiple expiries.
             * @param deleteOnClose tell the scheduler, if the scheduled job shall be deleted on destruction of the scheduler itself.
             */
            void attach(Scheduled* job, uint16_t timerId, uint16_t delayTimeMS, bool deleteOnClose);

            /**
             * Service method overrides
             */
            uint8_t getPriority();
            uint32_t getStackSize();
            Runnable* createRunnable();
    };

}


#endif