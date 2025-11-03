//Реализация функций
#include <stdio.h>
#include <string.h>
#include "task2_1.h"

//Функция проверки уникальности номера телефона
int PhoneUnique(Contact contactsBook[], int countContacts, const char *phone)
{
    for (int i = 0; i<countContacts; i++)
    {
        if(strcmp(contactsBook[i].persPhone, phone)==0)
        {
            return 1; //номер не уникален
        }
    }
    return 0; //номер уникален
}

//Функция проверки уникальности Email
int EmailUnique(Contact contactsBook[], int countContacts, const char *email)
{
    for (int i = 0; i<countContacts; i++)
    {
        if(strcmp(contactsBook[i].persEmail, email)==0)
        {
            return 1; //Email не уникален
        }
    }
    return 0; //Email уникален
}

//Функция проверки уникальности ссылки на соц.сети
int LinkUnique(Contact contactsBook[], int countContacts, const char *link)
{
    for (int i = 0; i<countContacts; i++)
    {
        if(strcmp(contactsBook[i].persLink, link)==0)
        {
            return 1; //номер не уникален
        }
    }
    return 0; //номер уникален
}





//Функция добавление контакта в телефонную книгу
void addContact(Contact contactsBook[], int *countContacts)
{

    //Проверка на переполнение телефонной книги
    if(*countContacts >= MAX_CONTACTS)
    {
        printf("Телефонная книга переполнена");
        return; //выход из функции, если достигнут лимит
    }

    Contact newContact; //создание временной переменной для нового контакта

    //Ввод полей телефонного справочника
    printf("Введите ФИО (Обязательно для заполнения): ");
    fgets(newContact.persName, MAX_NAME_LEN, stdin); //чтение ввода с клавиатуры
    newContact.persName[strcspn(newContact.persName, "\n")] = 0; //удаление символа новой строки

    //Проверка, что имя не пустое
    if(strlen(newContact.persName)==0)
    {
        printf("Укажите ФИО \n");
        return;
    }

    printf("Введите место работы: ");
    fgets(newContact.persWork, MAX_WORK_LEN, stdin);
    newContact.persWork[strcspn(newContact.persWork, "\n")] = 0;

    printf("Введите должность: ");
    fgets(newContact.workPosition, MAX_POSITION_LEN, stdin);
    newContact.workPosition[strcspn(newContact.workPosition, "\n")] = 0;

    printf("Введите номер телефона (Обязательно для заполнения): ");
    fgets(newContact.persPhone, MAX_PHONE_LEN, stdin);
    newContact.persPhone[strcspn(newContact.persPhone, "\n")] = 0;

    
    
    //Проверка, что номер телефона вписан
    if(strlen(newContact.persPhone)==0)
    {
        printf("Укажите номер телефона!\n");
        return;
    }

    //Проверка уникальности номера телефона
    if(PhoneUnique(contactsBook, *countContacts, newContact.persPhone))
    {
        printf("Такой номер телефона уже существует\n");
        return;
    }
    getchar();
    printf("Введите Email: ");
    fgets(newContact.persEmail, MAX_EMAIL_LEN, stdin);
    newContact.persEmail[strcspn(newContact.persEmail, "\n")] = 0;

    printf("Введите ссылку на соц.сети: ");
    fgets(newContact.persLink, MAX_LINK_LEN, stdin);
    newContact.persLink[strcspn(newContact.persLink, "\n")] = 0;

    //Добавление контакта в массив
    contactsBook[*countContacts] = newContact; //копирование данных в основной массив
    (*countContacts)++;
    printf("Контакт успешно добавлен! Всего контактов: %d\n", *countContacts);
}





//Функция изменение контакта в телефонной книге
void editContact(Contact contactsBook[], int countContacts)
{

    //Проверка на пустоту телефонной книги
    if(countContacts == 0)
    {
        printf("Телефонная книга пуста\n");
        return;
    }

    //Показ контактов для выбора
    printContact(contactsBook, countContacts);

    //Поиск контакта по номеру телефона
    char searchPhone[MAX_PHONE_LEN]; //создание массива для хранения номера поиска
    printf("Ввод номера телефона для поиска контакта: ");
    fgets(searchPhone, MAX_PHONE_LEN, stdin); //чтение номера телефона для поиска
    searchPhone[strcspn(searchPhone, "\n")] = 0; //удаление символа новой строки
    
    
    //Поиск контакта
    int foundIndexContact = -1; //переменная для хранения индекса найденного контакта (-1 = не найден)
    //Цикл по всем контактам
    for(int i = 0; i<countContacts; i++)
    {
        //Сравнение номеров телефонов
        if(strcmp(contactsBook[i].persPhone, searchPhone)==0)
        {
            foundIndexContact = i; //сохранение индекса найденного контакта
            break; //выход из цикла при нахождении
        }
    }

    //Если контакт не найден
    if(foundIndexContact == -1)
    {
        printf("Контакт не найден");
        return;
    }


    //Отображение найденного контакта
    printf("\nНайден контакт:\n");//код библиотеки
    printf("ФИО: %s\n", contactsBook[foundIndexContact].persName);
    printf("Телефон: %s\n", contactsBook[foundIndexContact].persPhone);
    printf("Место работы: %s\n", contactsBook[foundIndexContact].persWork);
    printf("Должность: %s\n", contactsBook[foundIndexContact].workPosition);
    printf("Email: %s\n", contactsBook[foundIndexContact].persEmail);
    printf("Ссылка на соц.сети: %s\n", contactsBook[foundIndexContact].persLink);


    //Редактирование контакта 
    char tempName[MAX_NAME_LEN]; //временный массив для хранения вводимых данных
    char tempWork[MAX_WORK_LEN];
    char tempPosition[MAX_POSITION_LEN];
    char tempPhone[MAX_PHONE_LEN];
    char tempEmail[MAX_EMAIL_LEN];
    char tempLink[MAX_LINK_LEN];

    getchar();
    printf("Введите новое ФИО: ");
    fgets(tempName, MAX_NAME_LEN, stdin);
    tempName[strcspn(tempName, "\n")] = 0;
    //Если введено не пустое ФИО
    if(strlen(tempName)>0)
    {
        strcpy(contactsBook[foundIndexContact].persName, tempName); //копирование нового ФИО
    }

    printf("Введите новое место работы: ");
    fgets(tempWork, MAX_WORK_LEN, stdin);
    tempWork[strcspn(tempWork, "\n")] = 0;
    //Если введено не пустое место работы
    if(strlen(tempWork)>0)
    {
        strcpy(contactsBook[foundIndexContact].persWork, tempWork); //копирование нового места работы
    }

    printf("Введите новую должность: ");
    fgets(tempPosition, MAX_POSITION_LEN, stdin);
    tempPosition[strcspn(tempPosition, "\n")] = 0;
    //Если введена не пустая должность
    if(strlen(tempPosition)>0)
    {
        strcpy(contactsBook[foundIndexContact].workPosition, tempPosition); //копирование новой должности
    }

    printf("Введите новый номер телефона: ");
    fgets(tempPhone, MAX_PHONE_LEN, stdin);
    tempPhone[strcspn(tempPhone, "\n")] = 0;
    //Если введён не пустой номер телефона
    if(strlen(tempPhone)>0)
    {
        //Проверка уникальности нового/изменённого номера телефона
        if(PhoneUnique(contactsBook, countContacts, tempPhone))
        {
            printf("Этот номер телефона уже существует\n");
        }
        else{
            strcpy(contactsBook[foundIndexContact].persPhone, tempPhone); //копирование нового номера телефона
            printf("Номер телефона успешно изменён\n");
        }
    }

    printf("Введите новый Email: ");
    fgets(tempEmail, MAX_EMAIL_LEN, stdin);
    tempEmail[strcspn(tempEmail, "\n")] = 0;
    //Если введён не пустой Email
    if(strlen(tempEmail)>0)
    {
        //Проверка уникальности нового/изменённого Email
        if(EmailUnique(contactsBook, countContacts, tempEmail))
        {
            printf("Этот Email уже существует\n");
        }
        else{
            strcpy(contactsBook[foundIndexContact].persEmail, tempEmail); //копирование нового Email
            printf("Email успешно изменён\n");
        }
    }

    printf("Введите новую ссылку на соц.сети: ");
    fgets(tempLink, MAX_LINK_LEN, stdin);
    tempLink[strcspn(tempLink, "\n")] = 0;
    //Если введён не пустая ссылка
    if(strlen(tempLink)>0)
    {
        //Проверка уникальности новой/изменённой ссылки на соц.сети 
        if(LinkUnique(contactsBook, countContacts, tempLink))
        {
            printf("Эта ссылка уже существует\n");
        }
        else{
            strcpy(contactsBook[foundIndexContact].persLink, tempLink); //копирование нового номера телефона
            printf("Ссылка успешна изменена\n");
        }
    }
}





    //Функция удаление контакта с телефонной книге
    void deleteContact(Contact contactsBook[], int *countContacts)
    {
        //Проверка  на пустоту телефонной книги
        if(*countContacts == 0)
        {
            printf("Телефонная книга пуста");
            return;
        }

        //Показ контактов для выбора
        printContact(contactsBook, *countContacts);

        //Поиск контакта по номеру телефона
        char searchPhone[MAX_PHONE_LEN]; //создание массива для хранения номера телефона
        printf("Введите номер телефона контакта для удаления: ");
        fgets(searchPhone, MAX_PHONE_LEN, stdin); //чтение номера телефона для поиска
        searchPhone[strcspn(searchPhone, "\n")] = 0; //удаление символа новой строки

        //Поиск контакта
        int foundIndexContact = -1;
        //Цикл по всем контактам
        for(int i = 0; i < *countContacts; i++)
        {
            //Сравнение номеров телефонов
            if(strcmp(contactsBook[i].persPhone, searchPhone) == 0)
            {
                foundIndexContact = i; //сохранение индекса найденного контакта
                break; //выход из цикла при нахождении 
            }
        }

        //Если контакт не найден
        if(foundIndexContact == -1)
        {
            printf("Конктакт с номером телефона '%s' не найден\n", searchPhone);
            return;
        }

        //Показ контактов, которые будут удалены
        printf("\nКонтакт для удаления:\n");
        printf("ФИО: %s\n", contactsBook[foundIndexContact].persName);
        printf("Номер телефона: %s\n", contactsBook[foundIndexContact].persPhone);
        printf("Место работы: %s\n", contactsBook[foundIndexContact].persWork);
        printf("Должность: %s\n", contactsBook[foundIndexContact].workPosition);
    

        //Подтверждение удаления контакта
        char confirmDeleteContact;
        printf("Вы уверены, что хотите удалить данный контакт? (y/n): ");
        scanf("%c", &confirmDeleteContact);
        getchar(); //очистка буфера после scanf

        if(confirmDeleteContact == 'y' || confirmDeleteContact == 'Y')
        {
            //Сдвиг всех контактов после удаляемого на одну позицию влево
            for(int i = foundIndexContact; i < *countContacts-1; i++)
            {
                contactsBook[i] = contactsBook[i+1]; //копирование след.контакта на место текущего
            }

            (*countContacts)--; //уменьшение кол-ва контактов
            printf("Контакт успешно удалён \n");
            //printf("Осталось контактов: %d\n", *countContacts);
        }
        else{
            printf("Удаление отменено\n");
        }
    }




    
    //Функция просмотра списка контактов
    void printContact(Contact contactsBook[], int countContacts)
    {
        if(countContacts == 0)
        {
            printf("Телефонная книга пуста \n");
            return;
        }

        printf("\n=== СПИСОК КОНТАКТОВ (%d) ===\n", countContacts);

        for(int i = 0; i<countContacts; i++)
        {
            printf("\n--- Контакт #%d ---\n", i+1);
            printf("ФИО: %s\n", contactsBook[i].persName);
            printf("Номер телефона: %s\n", contactsBook[i].persPhone);
            printf("Место работы: %s\n", contactsBook[i].persWork);
            printf("Должность: %s\n", contactsBook[i].workPosition);
            printf("Email: %s\n", contactsBook[i].persEmail);
            printf("Ссылка на соц.сети: %s\n", contactsBook[i].persLink);
        }
        printf("\n");
    }