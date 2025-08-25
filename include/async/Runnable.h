#ifndef __Runnable_h__
#define  __Runnable_h__

#include <Arduino.h>

namespace ravensnight::async {
    
    class Runnable {
        public:
            virtual void run() = 0;
    };

}

#endif //  __Runnable_h__