#include <cstring>
#include "names.h"

const char *NamesArray::operator[](size_t index) const {
    return values[index];
}

void NamesArray::push_back(char *name) {
    strcpy(values[len], name);
    len++;
}

int NamesArray::find(char *name) const {
    for (int i = 0; i < len; i++){
        if (strcmp(values[i], name) == 0)
            return i;
    }

    return -1;
}

void NamesArray::remove(size_t index) {
    for (size_t i = index + 1; i < len; i++){
        strcpy(values[i-1], values[i]);
    }
    len--;
}

size_t NamesArray::size() const {
    return len;
}
