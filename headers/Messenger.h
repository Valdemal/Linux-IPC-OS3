#ifndef MESSENGER_H
#define MESSENGER_H

#include "NamesArray.h"


class Messenger {
public:
    explicit Messenger(name_t name);

    const name_t & get_name() const;

    ~Messenger();
private:
    name_t name {};
};

#endif //MESSENGER_H
