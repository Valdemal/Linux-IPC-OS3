
#ifndef NAMES_H
#define NAMES_H


#include <cstddef>

typedef char name_t[80];

class NamesArray {
public:
    NamesArray() = default;

    void push_back(name_t name);

    int find(name_t name) const;

    void remove(size_t index);

    size_t size() const;

    const char* operator [](size_t index) const;
private:
    static const size_t MAX_SIZE = 10;

    name_t values[MAX_SIZE];
    size_t len {0};
};

#endif //NAMES_H
