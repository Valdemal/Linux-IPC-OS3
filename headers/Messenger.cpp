
#include <cstring>
#include <iostream>
#include "Messenger.h"
#include "MessageQueueProxy.h"

Messenger::Messenger(char *name) {
    strcpy(this->name, name);

    MessageQueueProxy::init();

    auto proxy_instance = MessageQueueProxy::get_instance();
    if (proxy_instance->contains_messenger(this->name)) {
        throw std::runtime_error("Мессенджер с таким " + std::string(name) + " уже существует!");
    } else {
        proxy_instance->add_messenger(this->name);
    }
}

Messenger::~Messenger() {
    MessageQueueProxy::get_instance()->remove_messenger(name);
}

const name_t &Messenger::get_name() const {
    return name;
}

bool Messenger::send(name_t const &receiver_name, message_t &message) {
    int queue_id = MessageQueueProxy::get_instance()->get_queue_id();
    strcpy(message.sender_name, this->name);
    message_buf_t buf (hash(receiver_name), message);

    int status = msgsnd(queue_id, &buf, MESSAGE_SIZE, 0);

    if (status == -1){
        std::cout << strerror(errno)  << std::endl;
    }

    return status >= 0;
}

std::list<message_t> Messenger::receive() {
    std::list<message_t> received_messages;
    int queue_id = MessageQueueProxy::get_instance()->get_queue_id();
    long receiver_hash = hash(this->name);

    bool has_available_messages;
    do {
        message_buf_t buf;

        // Если сообщение было успешно считано
        has_available_messages = msgrcv(queue_id, &buf, MESSAGE_SIZE, receiver_hash, 0) >= 0;

        if (has_available_messages)
            received_messages.push_back(buf.message);

    } while (has_available_messages);

    return received_messages;
}

Messenger::message_buf_t::message_buf_t(long type, const message_t &message)
        : receiver_hash(type), message(message) {}

message_t::message_t(const message_t &copy) {
    strcpy(this->text, copy.text);
    strcpy(this->sender_name, copy.sender_name);
}
