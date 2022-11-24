#ifndef MESSENGER_H
#define MESSENGER_H

#include "NamesArray.h"
#include <list>

struct message_t {
    char text[100] {};
    name_t sender_name {};

    message_t() = default;

    message_t(const message_t& copy);
};

class Messenger {
public:
    explicit Messenger(name_t name);

    const name_t & get_name() const;

    bool send(name_t const &receiver_name, message_t &message);

    std::list<message_t> receive ();

    ~Messenger();
private:
    struct message_buf_t{
        long receiver_hash {};
        message_t message {};

        message_buf_t() = default;

        message_buf_t(long type, const message_t &message);
    };

    static const size_t MESSAGE_SIZE = sizeof(message_buf_t) - sizeof(long);

    name_t name {};
};

#endif //MESSENGER_H
