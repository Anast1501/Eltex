#include <stdio.h>
#include "task2_3.h"

int main()
{
    int choiceUserOperation=1; //переменная для хранения выбора операции 
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
            //break;
        }
    }
}





    /*printf("===КАЛЬКУЛЯТОР===\n");
    printf("Введите числа\n\n");
    
    while(1) 
    {
        //Отображение меню
        displayMenu();

        //Получение номера операции от пользователя
        choiceUserOperation = getNumberOperationUser();

        //Выход из программы
        if(choiceUserOperation == 0)
        {

        }
    }
}*/
    

/////////////////////
    
    /*printf("Сложение - (1) \n");
        printf("Вычитание - (2) \n");
        printf("Умножение - (3) \n");
        printf("Деление - (4) \n");
        printf("Просмотр списка контактов - (4) \n");
        printf("Завершение программы - (0) \n");
        scanf("%d", &numberMenu);
        getchar();

    switch(choiceUserChislo)
    {
        case 1:
        if()
    }

    //Тестовые вызовы
    printf("%f \n", addition(4, 1.2, 2.0, 3.0, 4.0));
    printf("%f \n", subtraction(3, 100.0, 32.0, 10.9));
    printf("%f \n", multiplication(3, 2.0, 3.0, 4.0));
    printf("%f \n", division(3, 10.0, 5.0, 2.0));

    return 0;*/
