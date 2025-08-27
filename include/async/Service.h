#ifndef __Service_h__
#define __Service_h__

#include <async/Runnable.h>
#include <async/Task.h>

namespace ravensnight::async {

    class Service {

        private:

            Runnable* _runnable = 0;
            Task _task;

        protected:

            Service(const char* name);
            ~Service();

            virtual uint8_t getPriority()  = 0;
            virtual uint32_t getStackSize() = 0;
            virtual Runnable* createRunnable()  = 0;

            virtual bool preInstall();
            virtual void postUninstall();

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