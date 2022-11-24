/*
Реализовать обмен текстовыми сообщениями между несколькими процессами.
Обеспечить возможность отправки сообщения сразу нескольким адресатам.
Реализовать подтверждение приема сообщения адресатом или, в случае потери сообщения,
повторную его передачу. Очереди сообщений
*/

#include "headers/MessageQueueProxy.h"
#include <iostream>


int main() {
    MessageQueueProxy::init();

    auto proxy_instance = MessageQueueProxy::get_instance();

    std::cout << "Вас приветствует программа для управления мессенджерами. "
                 "Не закрывайте программу, пока запущены мессенджеры!" << std::endl;

    bool is_running = true;
    while (is_running) {
        std::cout << "1. Вывести список процессов-мессенджеров" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Ваш выбор:";

        int input_flag;
        std::cin >> input_flag;

        switch (input_flag) {
            case 1:
                proxy_instance->print_messengers();
                break;
            case 0:
                is_running = false;
                break;
            default:
                std::cout << "Неправильный ввод! Повторите операцию." << std::endl;
        }
    }

    MessageQueueProxy::destroy();
}
