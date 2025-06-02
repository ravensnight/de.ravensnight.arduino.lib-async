#ifndef __Queue_h__
#define __Queue_h__

#include <Arduino.h>
#include <Logger.h>
#include <async/Mutex.h>
#include <async/LockGuard.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

    typedef struct {        
        size_t   len;
        uint8_t* ptr;
    } QueueMsg;

    template <class T>
    class Receiver {
        public:
            virtual void handle(const T& msg) = 0;
    };

    template <class T>
    class Queue {

        private:
            Mutex _mutex;
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
            bool push(const uint8_t* ptr, size_t len) {
                if (_queue == 0) {
                    Logger::warn("Queue not created. Return.");
                    return false;
                }

                synchronized(_mutex);

                _msg.len = len,
                _msg.ptr = (uint8_t*)malloc(len);

                memcpy(_msg.ptr, ptr, len);

                if (xQueueSend(_queue, &_msg, _ticks) != pdPASS) {
                    Logger::error("Failed to send item to task queue.");
                    free(_msg.ptr);
                    _msg.ptr = 0;
                    _msg.len = 0;

                    return false;
                }

                return true;                
            }

        public:

            /**
             * Create a new queue with the given length;
             */
            Queue(size_t length) : _mutex("Queue") {
               _length = length;
                _queue = 0;
                _ticks = 0;
            }

            Queue(size_t length, uint32_t waitForMS) : _mutex("Queue") {
                 _length = length;
                _queue = 0;
                _ticks = pdMS_TO_TICKS( waitForMS );
            }

            /**
             * Install the queue
             */
            bool install() {
                if (_queue != 0) {
                    Logger::warn("Queue already installed. Skip.");
                    return false;
                }

                _queue = xQueueCreate(_length, sizeof( QueueMsg ));
                return (_queue != 0);
            }

            /**
             * Return the queue handle for the receiver task.
             */
            QueueHandle_t& handle() {
                return _queue;
            }

            /**
             * Push some element to queue.
             * Note: 
             * This function does create a clone of the given buffer. 
             * Receiver needs to delete it!
             */
            bool push(const T& element) {
                return push((const uint8_t*)&element, (size_t)sizeof( T ));
            }

            /**
             * Push operator.
             */
            Queue<T>& operator <<(const T& element) {
                push(element);
            }
    };
}


#endif // __Queue_h__