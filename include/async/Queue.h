#ifndef __Queue_h__
#define __Queue_h__

#include <Arduino.h>
#include <mutex>

namespace ravensnight::async {

    typedef struct {        
        size_t   len;
        uint8_t* ptr;
    } QueueMsg;

    template <class T>
    class Receiver {
        public:
            virtual void handle(const T& msg);
    };

    template <class T>
    class Queue {

        private:
            std::mutex _mutex;
            size_t _length;
            bool _useHeap;
            uint32_t _ticks;
            QueueHandle_t _queue;
            QueueMsg _msg;

            /**
             * Push some element to queue.
             * Note: 
             * This function does create a clone of the given buffer referenced by element.
             * Receiver needs to delete it!
             */
            bool push(const uint8_t* ptr, size_t len);

        public:

            /**
             * Create a new queue with the given length;
             */
            Queue(size_t length);
            Queue(size_t length, uint32_t waitForMS);

            /**
             * Install the queue
             */
            bool install();

            /**
             * Return the queue handle for the receiver task.
             */
            QueueHandle_t& handle();

            /**
             * Push some element to queue.
             * Note: 
             * This function does create a clone of the given buffer. 
             * Receiver needs to delete it!
             */
            bool push(const T& element);            

            /**
             * Queue operator, which does the same as function #push(const T& element)
             */
            Queue& operator << (const T& data);
    };
}


#endif // __Queue_h__