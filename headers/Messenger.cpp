
#include <cstring>
#include "Messenger.h"
#include "MessageQueueProxy.h"

Messenger::Messenger(char *name) {
    strcpy(this->name, name);

    MessageQueueProxy::init();

    auto proxy_instance = MessageQueueProxy::get_instance();
    if (proxy_instance->contains_messenger(this->name)){
        throw std::runtime_error("Мессенджер с таким" + std::string(name) + "уже существует!");
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
