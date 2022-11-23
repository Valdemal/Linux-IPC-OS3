#include <iostream>
#include "headers/MessageQueueProxy.h"
#include "headers/Messenger.h"

int main (int argc, char **argv) {
    Messenger messenger(argv[1]);

    std::cout << "hash " << hash(messenger.get_name()) << std::endl;

    bool is_running = true;
    while (is_running){
        std::cout << "1. Вывести список процессов-мессенджеров" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Ваш выбор:";

        int input_flag;
        std::cin >> input_flag;

        switch (input_flag) {
            case 1:
                MessageQueueProxy::get_instance()->print_messengers_names();
                break;
            case 0:
                is_running = false;
                break;
            default:
                std::cout << "Неправильный ввод! Повторите операцию." << std::endl;
        }
    }
}