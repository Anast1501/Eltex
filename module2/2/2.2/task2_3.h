#ifndef TASK2_3_H_
#define TASK2_3_H_

//TODO: Макросы
//#define MAX_OPERATIONS 4 //max кол-во операций
//#define MAX_ARGUMENTS 100 //!!!!!


//Функции калькулятора
double addition(int countVariable, ... );
double subtraction(int countVariable, ...);
double multiplication(int countVariable, ...);
double division(int countVariable, ...);


//Функции для управления калькулятором
void displayMenu(void); //отображение меню операций
int getNumberOperationUser(void); //получения номера операции от пользователя
//double getNumbersUser(double numbers[], int maxCount); //получения массива чисел от пользователя
double* getNumbersUser(int* count); //возвращение динамического массива и кол-во

#endif



/*void displayMenu(void); //показать меню
//void executeOperation(int choiceUserChislo); //выполнить операцию
double chisloUser(const char* chus); //получить число от полььзователя
//double(*getCommandFunction(int index))(int, ...);
//int getCountChisls(void); //получить кол-во чисел
double getUserNumbers(double numbers[], int maxCount); //функция получения массива чисел от пользователя
*/

