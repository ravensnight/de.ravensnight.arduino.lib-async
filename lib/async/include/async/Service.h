#ifndef __Service_h__
#define __Service_h__

#include <Logger.h>
#include <utils/Ref.hpp>
#include <async/Runnable.h>
#include <async/Task.h>

using namespace ravensnight::logging;
using namespace ravensnight::utils;

namespace ravensnight::async {

    class Service {

        private:

            static Logger _logger;

            Ref<Runnable> _runnable;
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