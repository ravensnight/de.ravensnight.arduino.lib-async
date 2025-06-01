#include <async/Queue.h>
#include <Logger.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

template <class T>
Queue<T>& Queue<T>::operator << (const T& data) {
    push(data);
    return (*this);
}

template <class T> 
Queue<T>::Queue(size_t length) {
    _length = length;
    _queue = 0;
    _ticks = 0;
}

template <class T> 
Queue<T>::Queue(size_t length, uint32_t waitForMS) {
    _length = length;
    _queue = 0;
    _ticks = pdMS_TO_TICKS( waitForMS );
}

template <class T> 
bool Queue<T>::install() {

    if (_queue != 0) {
        Logger::warn("Queue already installed. Skip.");
        return false;
    }

    _queue = xQueueCreate(_length, sizeof( QueueMsg ));
    return (_queue != 0);
}

template <class T> 
QueueHandle_t& Queue<T>::handle() {
    return _queue;
}

template <class T> 
bool Queue<T>::push(const T& element) {
    return push(&element, sizeof( T ));
}

template <class T> 
bool Queue<T>::push(const uint8_t* ptr, size_t len) {
    const std::lock_guard<std::mutex> lock(_mutex);

    if (_queue == 0) {
        Logger::warn("Queue not created. Return.");
        return false;
    }

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

}