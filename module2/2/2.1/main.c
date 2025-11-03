#include <stdio.h>
#include "task2_1.h"

int main()
{
    // Статический массив структур для хранилища данных в телефонной книге
    Contact contactsBook[MAX_CONTACTS];

    // Количество контактов всего (чтоб посмотреть на счётчик и узнать сколько всего контактов, чтоб можно было найти нужный контакт/инфу в ящике и изментить/редактировать её)
    int countContacts = 0;

    // Переменная для выбора пункта меню
    int numberMenu = 1;

    while (numberMenu != 0)
    {
        // Вызов функции - меню
        printf("\t М Е Н Ю \n");

        printf("Добавление контакта - (1) \n");
        printf("Редактирование контакта - (2) \n");
        printf("Удаление контакта - (3) \n");
        printf("Просмотр списка контактов - (4) \n");
        printf("Завершение программы - (0) \n");
        printf("\n");
        printf("Введите пункт меню: ");
        scanf("%d", &numberMenu);
        getchar();

        switch (numberMenu)
        {
        case 1:
            printf("Добавление контакта \n");
            // вызов функции добавление
            addContact(contactsBook, &countContacts); //&countContacts - передача адреса (изменение значения countContacts (счётчик +1/-1))
            break;

        case 2:
            printf("Редактирование контакта \n");
            // вызов функции редактирование
            editContact(contactsBook, countContacts); // countContacts - передача значения (только читаем переменную countContacts)
            break;

        case 3:
            printf("Удаление контакта \n");
            // вызов функции удаления
            deleteContact(contactsBook, &countContacts);
            break;

        case 4:
            printf("Просмотр списка контактов \n");
            // вызов функции просмотра списка контактов
            printContact(contactsBook, countContacts);
            break;

        case 0:
            printf("Завершение программы \n");
            break;

        default:
            printf("Не существуют данного пункта меню \n");
        }
    }
    return 0;
}


