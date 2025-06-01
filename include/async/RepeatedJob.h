#include <async/Job.h>

namespace ravensnight::async {

    class RepeatedJob : public Job {

        private:

            uint32_t _ticksDelay;

        public:

            RepeatedJob(uint32_t delay);            
            void run();

            virtual void execute() = 0;
    };

}