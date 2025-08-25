#ifndef __Scheduled_h__
#define __Scheduled_h__

#include <Arduino.h>
#include <async/Runnable.h>

namespace ravensnight::async {

    class Scheduled : public Runnable {

        private:

            uint32_t _ticksDelay;
            
        public:

            Scheduled(uint32_t delay);            
            void run();

            virtual void execute() = 0;
    };

}

#endif // __Scheduled_h__