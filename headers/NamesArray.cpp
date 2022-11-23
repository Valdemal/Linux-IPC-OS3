#include <cstring>
#include "NamesArray.h"

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

long hash(const name_t& name) {
    long hash_val = name[0] - 96;

    for (size_t i = 0; name[i] != '\0'; i++){
        int letter = name[i] - 96;
        hash_val = hash_val * 27 + letter;
    }

    return hash_val;
}
