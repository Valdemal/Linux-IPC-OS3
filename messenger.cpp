#include <iostream>
#include "headers/MessageQueueProxy.h"
#include "headers/Messenger.h"

void send_messages_case(Messenger & messenger);

void receive_messages_case(Messenger &messenger);

int main (int argc, char **argv) {
    Messenger messenger(argv[1]);

    std::cout << "hash " << hash(messenger.get_name()) << std::endl;

    bool is_running = true;
    while (is_running){
        std::cout << "1. Вывести список процессов-мессенджеров" << std::endl;
        std::cout << "2. Прочитать сообщения" << std::endl;
        std::cout << "3. Отправить сообщения" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Ваш выбор:";

        int input_flag;
        std::cin >> input_flag;

        switch (input_flag) {
            case 1:
                MessageQueueProxy::get_instance()->print_messengers();
                break;
            case 2:
                receive_messages_case(messenger);
                break;
            case 3:
                send_messages_case(messenger);
                break;
            case 0:
                is_running = false;
                break;
            default:
                std::cout << "Неправильный ввод! Повторите операцию." << std::endl;
        }
    }
}

void send_messages_case(Messenger &messenger) {

    message_t message;
    std::cout << "Введите текст сообщения:" << std::endl;
    std::cin >> message.text;

    size_t receivers_count;
    std::cout << "Введите количество получателей" << std::endl;
    std::cin >> receivers_count;

    for(size_t i = 0; i < receivers_count; i++){

        name_t receiver_name;
        std::cout << "Введите имя " << i + 1 << "-го получателя:" << std::endl;
        std::cin >> receiver_name;

        if (MessageQueueProxy::get_instance()->contains_messenger(receiver_name)){
            start_sending:
            if (messenger.send(receiver_name, message)) {
                std::cout << "Сообщение было успешно получено!" << std::endl;
            } else {
                std::cout << "Произошла ошибка при получении сообщения! Желаете повторить отправку(y/n)?" << std::endl;
                char flag;
                std::cin >> flag;
                if (flag == 'y')
                    goto start_sending;
            }
        } else {
            std::cout << "Мессенджера с именем " << receiver_name << " не существует!" << std::endl;
        }
    }
}

void receive_messages_case(Messenger &messenger) {
    auto received_messages = messenger.receive();

    if (not received_messages.empty()){
        std::cout << "Полученные сообщения:" << std::endl;
        for (const auto &message: received_messages) {
            std::cout << message.sender_name << ": " << message.text << std::endl;
        }
    } else
        std::cout << "Новых сообщений нет." << std::endl;
}
