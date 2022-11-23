#include <iostream>
#include <cstring>
#include "headers/MessageQueueProxy.h"

int main (int argc, char **argv) {

    name_t messenger_name;
    strcpy(messenger_name, argv[1]);

    MessageQueueProxy::init();

    auto proxy_instance = MessageQueueProxy::get_instance();
    if (proxy_instance->contains_messenger_name(messenger_name)){
        std::cout << "Мессенджер с таким именем уже существует!" << std::endl;
    } else {
        proxy_instance->add_messenger_name(messenger_name);
    }

    bool is_running = true;
    while (is_running){
        std::cout << "1. Вывести список процессов-мессенджеров" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Ваш выбор:";

        int input_flag;
        std::cin >> input_flag;

        switch (input_flag) {
            case 1:
                proxy_instance->print_messengers_names();
                break;
            case 0:
                is_running = false;
                break;
            default:
                std::cout << "Неправильный ввод! Повторите операцию." << std::endl;
        }
    }

    proxy_instance->remove_messenger_name(messenger_name);
}