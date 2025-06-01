#ifndef __Job_h__
#define  __Job_h__

#include <Arduino.h>

namespace ravensnight::async {
    
    class Job {
        public:
            virtual void run() = 0;
    };

}

#endif //  __Runnable_h__