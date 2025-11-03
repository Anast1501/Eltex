#ifndef TASK2_1_H_
#define TASK2_1_H_


// #define - директива макрос значение
#define MAX_NAME_LEN 50
#define MAX_WORK_LEN 200
#define MAX_POSITION_LEN 100
#define MAX_PHONE_LEN 12
#define MAX_EMAIL_LEN 50
#define MAX_LINK_LEN 100
#define MAX_CONTACTS 100

// Объявление структуры для хранения информации о контакте
typedef struct
{
    char persName[MAX_NAME_LEN];
    char persWork[MAX_WORK_LEN];
    char workPosition[MAX_POSITION_LEN];
    char persPhone[MAX_PHONE_LEN];
    char persEmail[MAX_EMAIL_LEN];
    char persLink[MAX_LINK_LEN];
} Contact; //пользовательский тип данных

//Функции для работы со статическим массивом
void addContact(Contact contactsBook[MAX_CONTACTS], int *countContacts);
void editContact(Contact contactsBook[MAX_CONTACTS], int countContacts);
void deleteContact(Contact contactsBook[MAX_CONTACTS], int *countContacts);
void printContact(Contact contactsBook[MAX_CONTACTS], int countContacts);

int PhoneUnique(Contact contactsBook[], int countContacts, const char *phone);
int EmailUnique(Contact contactsBook[], int countContacts, const char *email);
int LinkUnique(Contact contactsBook[], int countContacts, const char *link);

#endif