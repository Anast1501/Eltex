#ifndef TASK2_3_H_
#define TASK2_3_H_

//Тип для указателя на функцию арифметической операции
typedef double(*funcOperation) (int, ...);

//Структура для описания операции
typedef struct
{
    int numberOperation; //номер операции в меню
    const char* nameOperation;
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
double callVariadicFunc(funcOperation func, int count, double values[]);

#endif


