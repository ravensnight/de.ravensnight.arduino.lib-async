#ifndef __Lockable_h__
#define __Lockable_h__

namespace ravensnight::async {

    class Lockable {

        public:

            virtual void lock() = 0;
            virtual void unlock() = 0;
    };

}


#endif // __Lockable_h__