#ifndef TASK2_3_H_
#define TASK2_3_H_

//Тип для указателя на функцию арифметической операции
typedef double(*funcOperation)(int, ...);

//Структура для описания операции
typedef struct
{
    int numberOperation; //номер операции в меню
    const char* nameOperation; //название операции
    funcOperation func; //указатель на функцию
} Operation;


//Функции калькулятора
double addition(int countVariable, ... );
double subtraction(int countVariable, ...);
double multiplication(int countVariable, ...);
double division(int countVariable, ...);


//Функции для управления калькулятором
void displayMenu(void); //отображение меню операций
int getNumberOperationUser(void); //получения номера операции от пользователя

#endif



/*void displayMenu(void); //показать меню
//void executeOperation(int choiceUserChislo); //выполнить операцию
double chisloUser(const char* chus); //получить число от полььзователя
//double(*getCommandFunction(int index))(int, ...);
//int getCountChisls(void); //получить кол-во чисел
double getUserNumbers(double numbers[], int maxCount); //функция получения массива чисел от пользователя
*/

