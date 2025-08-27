#ifndef __Service_h__
#define __Service_h__

#include <async/Runnable.h>
#include <async/Task.h>
#include <async/Mutex.h>

namespace ravensnight::async {

    class Service {

        private:

            Mutex _mutex;
            uint8_t _priority;
            uint32_t _stackSize;

            Runnable* _runnable = 0;
            Task _task;

        protected:

            Service(const char* name);
            ~Service();

            virtual uint8_t getPriority();
            virtual uint32_t getStackSize();
            virtual Runnable* createRunnable();

        public:

            /**
             * Install the service
             */
            bool install();

            /**
             * Remove the service.
             */
            void uninstall();
    };
}

#endif // __Service_h__