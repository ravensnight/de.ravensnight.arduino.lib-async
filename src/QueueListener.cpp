#include <async/QueueListener.h>
#include <Logger.h>

using namespace ravensnight::logging;

namespace ravensnight::async {

template <class T>
QueueListener<T>::QueueListener(QueueHandle_t& queue, Receiver<T>& receiver) {
    _receiver = &receiver;
    _queue = &queue;
}

template <class T>
void QueueListener<T>::run() {

    if (_queue == 0) {
        Logger::warn("Queue not created. Return.");
        return;
    }

    QueueMsg msg;
    while (xQueueReceive(*_queue, &msg, portMAX_DELAY)) {

        T& payload = *((T*)msg.ptr);
        _receiver.handle(payload);

        Logger::debug("Handled queue message. Destroy message.");
        free(msg.ptr);  // remove the message after its handled.
    }
}

}