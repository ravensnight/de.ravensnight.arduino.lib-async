#ifndef __Queue_h__
#define __Queue_h__

#include <Arduino.h>
#include <Logger.h>

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
            size_t _length;
            bool _useHeap;
            uint32_t _ticks;
            QueueHandle_t _queue;

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

                QueueMsg msg = {
                    .len = len,
                    .ptr = (uint8_t*)malloc(len)
                };

                memcpy(msg.ptr, ptr, len);
                if (xQueueSend(_queue, &msg, _ticks) != pdPASS) {
                    Logger::error("Failed to send item to task queue.");
                    free(msg.ptr);
                    msg.ptr = 0;
                    msg.len = 0;

                    return false;
                }

                return true;                
            }

            /**
             * Push some element to queue.
             * Note: 
             * This function sends the msg directly without passing pointers.
             */
            bool pushDirect(const T& msg) {
                if (_queue == 0) {
                    Logger::warn("Queue not created. Return.");
                    return false;
                }

                if (xQueueSend(_queue, &msg, _ticks) != pdPASS) {
                    Logger::error("Failed to send direct item to task queue.");
                    return false;
                }

                return true;                
            }

        public:

            /**
             * Create a new queue with the given length;
             */
            Queue(size_t length, boolean useHeap) {
                _length = length;
                _queue = 0;
                _ticks = 0;
                _useHeap = useHeap;
            }

            Queue(size_t length, boolean useHeap, uint32_t waitForMS) {
                _length = length;                
                _queue = 0;
                _ticks = pdMS_TO_TICKS( waitForMS );
                _useHeap = useHeap;
            }

            /**
             * Install the queue
             */
            bool install() {
                if (_queue != 0) {
                    Logger::info("Queue already installed. Skip.");
                    return true;
                }

                if (_useHeap) {
                    _queue = xQueueCreate(_length, sizeof( QueueMsg ));
                } else {
                    _queue = xQueueCreate(_length, sizeof( T ));
                }
                
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
                if (_useHeap) {
                    return push((const uint8_t*)&element, (size_t)sizeof( T ));
                } else {
                    return pushDirect(element);
                }
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