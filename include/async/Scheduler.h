#ifndef __Scheduler_h__
#define __Scheduler_h__

#include <Arduino.h>
#include <ClassLogger.h>
#include <list>

#include <async/Runnable.h>
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
            uint16_t    _delayTime = 0;
            Runnable*   _runnable  = 0;
            bool        _deleteOnClose = false;

        public:
            SchedulerEntry(Runnable* runnable, uint16_t delayTimeMS, bool deleteOnClose);
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
            std::list<SchedulerEntry*> _entries;         
            
        protected:
            void tick();
            uint16_t timeSlice();

        public:

            Scheduler(const char* name, uint16_t timeSliceMS);
            ~Scheduler();

            /**
             * Register a single job, which is being called every repeatMS
             */
            void attach(Runnable* job, uint16_t delayTimeMS, bool deleteOnClose);

            /**
             * Service method overrides
             */
            uint8_t getPriority();
            uint32_t getStackSize();
            Runnable* createRunnable();
    };

}


#endif