#include <stdio.h>
#include "task2_3.h"

int main()
{
    int choiceUserOperation = 1; //переменная для хранения выбора операции 
    int count = 0; //кол-во введённых чисел
    
    //Массив операций с указателями на функции 
    Operation operations[] = {
        {1, "Сложение", addition},
        {2, "Вычитание", subtraction},
        {3, "Умножение", multiplication},
        {4, "Деление", division}
    };


    while(choiceUserOperation!=0)
    {   
        displayMenu();
        scanf("%d", &choiceUserOperation);

        if(choiceUserOperation==0)
        {
            break;
        }

        printf("Введите количество значений до 4-х: ");
        scanf("%d", &count);


        //Проверка контроля пользователя
        if(count<1 || count>4)
        {
            printf("Превышение лимита \n");
            continue;
        }

        //Массив для хранения ввода значений пользователем
        double inputValuesUser[count];
        for(int i = 0; i<count; i++)
        {
            printf("Введите значения: ");
            scanf("%lf", &inputValuesUser[i]);
        }

        //Проверка деления на ноль 
        if(choiceUserOperation == 4)
        {
            int flagZero = 0; // 0(false) - нулей пока не найдено
            for(int i = 1; i<count; i++)
            {
                if(inputValuesUser[i]==0)
                {
                    printf("Ошибка: деление на ноль\n");
                    flagZero = 1;
                    break;
                }
            }
            if(flagZero) continue; //пропускаем выполнение операции если есть ноль
        }

        //Использование указателя на функцию через switch case
        funcOperation selectedFunc = NULL;

        switch(choiceUserOperation)
        {
            //Сложение 
            case 1:
            selectedFunc = addition;
            break;

            //Вычитание
            case 2:
            selectedFunc = subtraction;
            break;

            //Умножение
            case 3:
            selectedFunc = multiplication;
            break;

            //Деление 
            case 4:
            selectedFunc = division;
            break;

            default:
            printf("Неверная операция\n");
            continue;
        }

        //Вызов функции через указатель 
        double result = callVariadicFunc(selectedFunc, count, inputValuesUser);
        printf("Результат: %f\n", result);
    }

    return 0;
}
























/* ТО, ЧТО БЫЛО
#include <stdio.h>
#include "task2_3.h"

int main()
{
    int choiceUserOperation = 1; //переменная для хранения выбора операции 
    int count = 0; //кол-во введённых чисел
    
    
    while(choiceUserOperation!=0)
    {   
        displayMenu();
        scanf("%d", &choiceUserOperation);

        if(choiceUserOperation==0)
        {
            break;
        }

        printf("Введите количество значений до 4-х: ");
        scanf("%d", &count);


        //Проверка контроля пользователя
        if(count<1 || count>4)
        {
            printf("Превышение лимита \n");
            continue;
        }

        //Массив для хранения ввода значений пользователем
        double inputValuesUser[count];
        for(int i = 0; i<count; i++)
        {
            printf("Введите значения: ");
            scanf("%lf", &inputValuesUser[i]);
        }

        switch(choiceUserOperation)
        {
            //Сложение
            

            //Вычитание



            //Умножение



            //Деление
        }*/

        /* Функция указателя (функция указатель должна ссылаться на switch case менюшку)
        1 - +,
        2- -,
        3 - *
        4 - /
        {*operation, 'sum'}

        {sum, '+',
        div, '/'}
        
        
        
        */










        /*
        switch (choiceUserOperation)
        {
            //Сложение
            case 1:
            if(count==2)
            {
                printf("%f", addition(count, inputValuesUser[0], inputValuesUser[1]));
            }
            if(count==3)
            {
                printf("%f", addition(count, inputValuesUser[0], inputValuesUser[1], inputValuesUser[2]));
            }
            if(count==4)
            {
                printf("%f", addition(count, inputValuesUser[0], inputValuesUser[1], inputValuesUser[2], inputValuesUser[3]));
            }
            break;

            //Вычитание
            case 2:
            if(count==2)
            {
                printf("%f", subtraction(count, inputValuesUser[0], inputValuesUser[1]));
            }
            if(count==3)
            {
                printf("%f", subtraction(count, inputValuesUser[0], inputValuesUser[1], inputValuesUser[2]));
            }
            if(count==4)
            {
                printf("%f", subtraction(count, inputValuesUser[0], inputValuesUser[1], inputValuesUser[2], inputValuesUser[3]));
            }
            break;

            //Умножение
            case 3:
            if(count==2)
            {
                printf("%f", multiplication(count, inputValuesUser[0], inputValuesUser[1]));
            }
            if(count==3)
            {
                printf("%f", multiplication(count, inputValuesUser[0], inputValuesUser[1], inputValuesUser[2]));
            }
            if(count==4)
            {
                printf("%f", multiplication(count, inputValuesUser[0], inputValuesUser[1], inputValuesUser[2], inputValuesUser[3]));
            }
            break;

            //Деление
            case 4:
            if(count==2)
            {
                printf("%f", division(count, inputValuesUser[0], inputValuesUser[1]));
            }
            if(count==3)
            {
                printf("%f", division(count, inputValuesUser[0], inputValuesUser[1], inputValuesUser[2]));
            }
            if(count==4)
            {
                printf("%f", division(count, inputValuesUser[0], inputValuesUser[1], inputValuesUser[2], inputValuesUser[3]));
            }
            break;
            
            //Выход
            //case 0:
            //break;*/
        //}
    //}
//}



