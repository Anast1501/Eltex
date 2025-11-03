#include <stdio.h>
#include <stdarg.h>
#include "task2_3.h"

//Функция сложения чисел
double addition(int countVariable, ...)
{
    double result = 0;
    va_list startVariable; //указатель на начало 
    va_start(startVariable, countVariable);
    for(int i = 0; i<countVariable; i++)
    {
        result += va_arg(startVariable, double);
    }
    va_end(startVariable);
    return result;
}

//Функция вычитания чисел
double subtraction(int countVariable, ...)
{
    va_list startVariable;
    va_start(startVariable, countVariable);
    double result = va_arg(startVariable, double); //вытаскиваем первый элемент из списка
    for(int i = 1; i<countVariable; i++)
    {
        result -= va_arg(startVariable, double);
    }
    va_end(startVariable);
    return result;
}

//Функция умножения чисел
double multiplication(int countVariable, ...)
{
    double result = 1.0;
    va_list startVariable;
    va_start(startVariable, countVariable);
    for(int i = 0; i<countVariable; i++)
    {
        result *= va_arg(startVariable, double);
    }
    va_end(startVariable);
    return result;
}

//Функция деления чисел
double division(int countVariable, ...)
{
    va_list startVariable;
    va_start(startVariable, countVariable);
    double result = va_arg(startVariable, double);
    //Цикл по оставшимся аргументам (делителям)
    for(int i = 1; i<countVariable; i++)
    {
    double divisor = va_arg(startVariable, double);
    //Проверка деления на ноль
    if(divisor == 0)
    {
        printf("Ошибка: деление на ноль\n");
        va_end(startVariable);
        return 0;
    }
    result/=divisor;
    }
    va_end(startVariable);
    return result;
}

void displayMenu()
{
    printf("\n===КАЛЬКУЛЯТОР===\n");
    printf("1. Сложение\n");
    printf("2. Вычитание\n");
    printf("3. Умножение\n");
    printf("4. Деление\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

//Функция получения номера операции от пользователя 
int getNumberOperationUser()
{
    int choiceUserOperation; //переменная для хранения выбора пользователя
    scanf("%d", &choiceUserOperation); //чтение выбора пользователя из входного потока
    return choiceUserOperation; //возврат выбранного номера операции
}