#ifndef MESSAGE_QUEUE_PROXY_H
#define MESSAGE_QUEUE_PROXY_H

#include <sys/msg.h>
#include <stdexcept>
#include <sys/sem.h>
#include "names.h"

class MessageQueueProxy {
public:
    static void init();

    static void destroy();

    static MessageQueueProxy* get_instance();

    bool contains_messenger_name(name_t name) const;

    void add_messenger_name(name_t name);

    void remove_messenger_name(name_t name);

    void print_messengers_names() const;

private:
    static const char* QUEUE_NAME;
    static const int PROJ_ID;
    static const char* SOURCE_FILE_NAME;
    static sembuf SEM_LOCK;
    static sembuf SEM_UNLOCK;


    static MessageQueueProxy* instance;


    int queue_key;
    int sem_id;
    NamesArray names {};

    explicit MessageQueueProxy(int queue_id, int sem_id);

};

#endif //MESSAGE_QUEUE_PROXY_H
