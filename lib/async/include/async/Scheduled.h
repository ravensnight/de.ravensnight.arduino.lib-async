#ifndef __Scheduled_h__
#define __Scheduled_h__

#include <Arduino.h>

namespace ravensnight::async {

    class Scheduled {

        public:
            virtual void timerExpired(uint16_t timerId, void* param) = 0;
            
    };

}

#endif 