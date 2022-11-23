#include <iostream>
#include <fcntl.h>
#include <atomic>
#include <sys/mman.h>
#include "MessageQueueProxy.h"

const char *MessageQueueProxy::QUEUE_NAME = ".";

const int MessageQueueProxy::PROJ_ID = 'm';

const char *MessageQueueProxy::SOURCE_FILE_NAME = "_queue_proxy";

sembuf MessageQueueProxy::SEM_LOCK = {0, -1, IPC_NOWAIT};
sembuf MessageQueueProxy::SEM_UNLOCK = {0, 1, IPC_NOWAIT};


MessageQueueProxy *MessageQueueProxy::instance = nullptr;

void MessageQueueProxy::init() {
    int file = open(SOURCE_FILE_NAME, O_RDWR | O_CREAT | O_EXCL, 0666);

    bool need_to_init = false;
    if (file != -1) {
        // Задать размер файла
        ftruncate(file, sizeof(MessageQueueProxy));
        need_to_init = true;
    } else {
        // Иначе просто открыть файл
        file = open(SOURCE_FILE_NAME, O_RDWR, 0666);
    }

     instance = (MessageQueueProxy*) mmap(
            nullptr,sizeof(MessageQueueProxy),
            PROT_READ | PROT_WRITE,MAP_SHARED,file,0
    );

    close(file);

    if (need_to_init){
        auto key = ftok(QUEUE_NAME, PROJ_ID);

        if (key == -1)
            throw std::runtime_error("Ошибка генерации ключа!");

        int queue_id = msgget(key, IPC_CREAT);

        if (queue_id == -1)
            throw std::runtime_error("Ошибка соединения с очередью сообщений!");

        int sem_id = semget(key, 1, IPC_CREAT);

        *instance = MessageQueueProxy(queue_id, sem_id);
    }
}

void MessageQueueProxy::destroy() {
    auto code = msgctl(get_instance()->queue_key, IPC_RMID, nullptr);

    if (code == -1)
        throw std::runtime_error("Ошибка закрытия соединения с очередью сообщений!");

    code = semctl(get_instance()->sem_id, 0, IPC_RMID);
    if (code == -1)
        throw std::runtime_error("Ошибка закрытия соединения с семафором!");

    remove(SOURCE_FILE_NAME);
}

MessageQueueProxy *MessageQueueProxy::get_instance() {
    if (instance == nullptr)
        throw std::runtime_error("Instance is null!");

    return instance;
}

MessageQueueProxy::MessageQueueProxy(int queue_id, int sem_id) : queue_key(queue_id), sem_id(sem_id) {}

void MessageQueueProxy::add_messenger_name(name_t name) {
    // Lock mutex
    semop(sem_id, &SEM_LOCK,1);

    names.push_back(name);

    // Unlock mutex
    semop(sem_id, &SEM_UNLOCK,1);
}

bool MessageQueueProxy::contains_messenger_name(name_t name) const {
    // lock mutex
    semop(sem_id, &SEM_LOCK,1);

    bool is_find = names.find(name) != -1;

    // Unlock mutex
    semop(sem_id, &SEM_UNLOCK,1);

    return is_find;
}

void MessageQueueProxy::remove_messenger_name(name_t name) {
    // Lock mutex
    semop(sem_id, &SEM_LOCK,1);

    int index = names.find(name);

    if (index != -1)
        names.remove(index);

    // Unlock mutex
    semop(sem_id, &SEM_UNLOCK,1);
}

void MessageQueueProxy::print_messengers_names() const {
    // Lock mutex
    semop(sem_id, &SEM_LOCK,1);

    for (size_t i = 0; i < names.size(); i++){
        std::cout << names[i] << std::endl;
    }

    // Unlock mutex
    semop(sem_id, &SEM_UNLOCK,1);
}
