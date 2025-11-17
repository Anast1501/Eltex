#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "permission.h"

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        HelpUser();
        return 0;
    }
    
    if(argc == 2)
    {
        struct stat file_name;
        if(stat(argv[1], &file_name)==0)
        {
            DisplayInfoFile(argv[1]);
            return 0;
        }
        
        if(strlen(argv[1])==3)
        {
            IntToBits(argv[1]);
            return 0;
        }
        else if(strlen(argv[1])==9)
        {
            CharToBits(argv[1]);
            return 0;
        }
        else{
            printf("Ошибка: неверные аргументы\n");
            HelpUser();
            return 1;
        }
    }
    
    //Обработка модификации прав доступа (argc >= 3)
    if(argc >= 3)
    {
        struct stat file_stat;
        if(stat(argv[1], &file_stat) != 0)
        {
            perror("Ошибка при получении информации о файле");
            return 1;
        }
        
        mode_t original_mode = file_stat.st_mode & 0777; // Только права доступа
        mode_t modified_mode = original_mode;
        
        //Применение всех переданных модификаций
        for (int i = 2; i < argc; i++) {
            modified_mode = ApplyModification(modified_mode, argv[i]);
        }
        
        //Отображение результата модификации
        printf("Результат модификации прав доступа для файла: %s\n", argv[1]);
        printf("==================================================\n");
        
        char mod_str[100] = "";
        for (int i = 2; i < argc; i++) {
            if (i > 2) strcat(mod_str, " ");
            strcat(mod_str, argv[i]);
        }
        
        DisplayModifiedRights(original_mode, modified_mode, mod_str);
        
        return 0;
    }
    
    return 0;
}
































































/* ЗАДАНИЕ 3.1 ПУНКТ 3 (ВСЁ ВМЕСТЕ)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Функция для преобразования битов прав доступа в буквенное представление
void BitsToLetters(mode_t mode, char *letters)
{
    // Права для владельца
    letters[0] = (mode & S_IRUSR) ? 'r' : '-';
    letters[1] = (mode & S_IWUSR) ? 'w' : '-';
    letters[2] = (mode & S_IXUSR) ? 'x' : '-';

    // Права для группы
    letters[3] = (mode & S_IRGRP) ? 'r' : '-';
    letters[4] = (mode & S_IWGRP) ? 'w' : '-';
    letters[5] = (mode & S_IXGRP) ? 'x' : '-';

    // Права для остальных
    letters[6] = (mode & S_IROTH) ? 'r' : '-';
    letters[7] = (mode & S_IWOTH) ? 'w' : '-';
    letters[8] = (mode & S_IXOTH) ? 'x' : '-';

    letters[9] = '\0'; 
}

// Функция для преобразования битов прав доступа в цифровое представление
void BitsToDigital(mode_t mode, char *digit)
{
    // Восьмеричная нотация (4, 2, 1 - вес битов прав доступа в восьмеричной системе)
    int user = ((mode & S_IRUSR) ? 4 : 0) + ((mode & S_IWUSR) ? 2 : 0) + ((mode & S_IXUSR) ? 1 : 0);
    int group = ((mode & S_IRGRP) ? 4 : 0) + ((mode & S_IWGRP) ? 2 : 0) + ((mode & S_IXGRP) ? 1 : 0);
    int other = ((mode & S_IROTH) ? 4 : 0) + ((mode & S_IWOTH) ? 2 : 0) + ((mode & S_IXOTH) ? 1 : 0);

    sprintf(digit, "%d%d%d", user, group, other);
}

// Функция для вывода битового представления прав доступа для файлов
void PrintBits(mode_t mode)
{
    printf("Битовое представление: ");
    for(int i = 8; i>=0; i--)
    {
        int bit = (mode >> i) & 1;
        printf("%d", bit);
        if(i == 6 || i == 3) {
            printf(" ");
        }
    }
    printf("\n");
}

// Функция отображения информации о файле
void DisplayInfoFile(const char *filename)
{
    struct stat file_stat;

    // Получение информации о файле
    if(stat(filename, &file_stat)==-1)
    {
        perror("Ошибка при получении информации о файле");
        return;
    }

    printf("Информация о файле: %s\n", filename);
    printf("\n");

    // Буквенное представление 
    char letters[10];
    BitsToLetters(file_stat.st_mode, letters);
    printf("Буквенное представление: %s\n", letters);

    // Цифровое представление
    char digital[4];
    BitsToDigital(file_stat.st_mode, digital);
    printf("Цифровое представление: %s\n", digital);

    // Битовое представление
    PrintBits(file_stat.st_mode & 0777);
}

// Функция для применения модификации прав доступа (аналогично chmod)
// Функция для применения модификации прав доступа (аналогично chmod)
mode_t ApplyModification(mode_t current_mode, const char *modification)
{
    mode_t new_mode = current_mode;
    
    // Копируем строку для безопасной работы
    char *mod_str = strdup(modification);
    if (!mod_str) {
        printf("Ошибка памяти\n");
        return current_mode;
    }
    
    // Разбираем строку модификации (например: "u+r", "g-w", "o=x")
    char who_part[10] = "";
    char op = '\0';
    char perms_part[10] = "";
    
    // Парсим строку: who op perms
    int i = 0, j = 0;
    
    // Читаем who часть (u, g, o, a)
    while (mod_str[i] != '\0' && mod_str[i] != '+' && mod_str[i] != '-' && mod_str[i] != '=') {
        who_part[j++] = mod_str[i++];
    }
    who_part[j] = '\0';
    
    // Читаем операцию
    if (mod_str[i] != '\0') {
        op = mod_str[i++];
    } else {
        printf("Ошибка: отсутствует операция в '%s'\n", modification);
        free(mod_str);
        return current_mode;
    }
    
    // Читаем права
    j = 0;
    while (mod_str[i] != '\0') {
        perms_part[j++] = mod_str[i++];
    }
    perms_part[j] = '\0';
    
    if (strlen(perms_part) == 0) {
        printf("Ошибка: отсутствуют права в '%s'\n", modification);
        free(mod_str);
        return current_mode;
    }
    
    // Определяем, к кому применяются изменения
    int apply_user = 0, apply_group = 0, apply_other = 0;
    
    if (strlen(who_part) == 0) {
        // Если не указано кому, применяем ко всем
        apply_user = apply_group = apply_other = 1;
    } else {
        for (int k = 0; who_part[k] != '\0'; k++) {
            switch (who_part[k]) {
                case 'u': apply_user = 1; break;
                case 'g': apply_group = 1; break;
                case 'o': apply_other = 1; break;
                case 'a': 
                    apply_user = apply_group = apply_other = 1; 
                    break;
                default:
                    printf("Ошибка: неизвестный идентификатор '%c'\n", who_part[k]);
                    free(mod_str);
                    return current_mode;
            }
        }
    }
    
    // Применяем операцию
    if (op == '+') {
        // Добавление прав
        for (int k = 0; perms_part[k] != '\0'; k++) {
            switch (perms_part[k]) {
                case 'r': 
                    if (apply_user) new_mode |= S_IRUSR;
                    if (apply_group) new_mode |= S_IRGRP;
                    if (apply_other) new_mode |= S_IROTH;
                    break;
                case 'w': 
                    if (apply_user) new_mode |= S_IWUSR;
                    if (apply_group) new_mode |= S_IWGRP;
                    if (apply_other) new_mode |= S_IWOTH;
                    break;
                case 'x': 
                    if (apply_user) new_mode |= S_IXUSR;
                    if (apply_group) new_mode |= S_IXGRP;
                    if (apply_other) new_mode |= S_IXOTH;
                    break;
                default:
                    printf("Ошибка: неизвестное право '%c'\n", perms_part[k]);
                    continue;
            }
        }
    }
    else if (op == '-') {
        // Удаление прав
        for (int k = 0; perms_part[k] != '\0'; k++) {
            switch (perms_part[k]) {
                case 'r': 
                    if (apply_user) new_mode &= ~S_IRUSR;
                    if (apply_group) new_mode &= ~S_IRGRP;
                    if (apply_other) new_mode &= ~S_IROTH;
                    break;
                case 'w': 
                    if (apply_user) new_mode &= ~S_IWUSR;
                    if (apply_group) new_mode &= ~S_IWGRP;
                    if (apply_other) new_mode &= ~S_IWOTH;
                    break;
                case 'x': 
                    if (apply_user) new_mode &= ~S_IXUSR;
                    if (apply_group) new_mode &= ~S_IXGRP;
                    if (apply_other) new_mode &= ~S_IXOTH;
                    break;
                default:
                    printf("Ошибка: неизвестное право '%c'\n", perms_part[k]);
                    continue;
            }
        }
    }
    else if (op == '=') {
        // Установка точных прав
        // Сначала сбрасываем права для указанных категорий
        if (apply_user) new_mode &= ~(S_IRUSR | S_IWUSR | S_IXUSR);
        if (apply_group) new_mode &= ~(S_IRGRP | S_IWGRP | S_IXGRP);
        if (apply_other) new_mode &= ~(S_IROTH | S_IWOTH | S_IXOTH);
        
        // Затем устанавливаем указанные права
        for (int k = 0; perms_part[k] != '\0'; k++) {
            switch (perms_part[k]) {
                case 'r': 
                    if (apply_user) new_mode |= S_IRUSR;
                    if (apply_group) new_mode |= S_IRGRP;
                    if (apply_other) new_mode |= S_IROTH;
                    break;
                case 'w': 
                    if (apply_user) new_mode |= S_IWUSR;
                    if (apply_group) new_mode |= S_IWGRP;
                    if (apply_other) new_mode |= S_IWOTH;
                    break;
                case 'x': 
                    if (apply_user) new_mode |= S_IXUSR;
                    if (apply_group) new_mode |= S_IXGRP;
                    if (apply_other) new_mode |= S_IXOTH;
                    break;
                default:
                    printf("Ошибка: неизвестное право '%c'\n", perms_part[k]);
                    continue;
            }
        }
    }
    else {
        printf("Ошибка: неизвестная операция '%c'\n", op);
    }
    
    free(mod_str);
    return new_mode;
}// Функция для отображения модифицированных прав доступа
void DisplayModifiedRights(mode_t original_mode, mode_t modified_mode, const char *modification)
{
    printf("Модификация: %s\n", modification);
    printf("Исходные права -> Новые права\n");
    printf("==============================\n");
    
    char orig_letters[10], mod_letters[10];
    char orig_digital[4], mod_digital[4];
    
    BitsToLetters(original_mode, orig_letters);
    BitsToLetters(modified_mode, mod_letters);
    BitsToDigital(original_mode, orig_digital);
    BitsToDigital(modified_mode, mod_digital);
    
    printf("Буквенное: %s -> %s\n", orig_letters, mod_letters);
    printf("Цифровое:  %s -> %s\n", orig_digital, mod_digital);
    
    printf("Битовое исходное:  ");
    PrintBits(original_mode);
    printf("Битовое новое:     ");
    PrintBits(modified_mode);
}

// Функция перевода из char->int->битовое представление
void IntToBits(char *simbols)
{
    // Проверка длины символов
    if(strlen(simbols)!=3)
    {
        printf("Ошибка! Неверная длина входной строки \n");
        return;
    }

    mode_t resultTranslate = strtol(simbols, NULL, 8); 
    printf("Битовое представление для %s:  ", simbols);

    // Цикл перевода из восьмеричной в двоичную
    for(int i = 8; i>=0; i--) // перевод из числа в биты с конца
    {
        int bit = (resultTranslate>>i)&1; // сдвигаем и забираем конкретный бит
        printf("%d", bit);
        if(i==6 || i==3)
        {
            printf(" ");
        }
    }
    printf("\n");
}

// Функция перевода из буквенного в битовое представление
void CharToBits(const char *simbols)
{
    // Проверка длины букв + на соответствие букв
    if(strlen(simbols)!=9)
    {
        printf("Ошибка! Неверная длина входной строки \n");
        return;
    }

    // Проверка на наличие нужных букв
    for(int i = 0; i<9; i++)
    {
        if(simbols[i]!='r' && simbols[i]!='w' && simbols[i]!='x' && simbols[i]!='-')
        {
            printf("Ошибка! Неверные введённые буквы (нет таких прав доступа))\n");
            return;
        }
    }
    printf("Битовое представление для %s: ", simbols);
    for(int i = 0; i<9; i++)
    {
        char bykva = simbols[i];
        if(bykva=='r' || bykva=='w' || bykva=='x')
        {
            printf("1");
        }   
        else{
            printf("0");
        }

        if(i==2 || i==5)
        {
            printf(" ");
        }
    }
    printf("\n");
}

void HelpUser()
{
    printf("Если в качестве параметра передать числовой или буквенный вариант, выведется битовая маска\n");
    printf("Если ввести название файла, выведутся права доступа\n");
    printf("Для модификации прав используйте: ./program файл модификация\n");
    printf("Примеры модификаций: u+r, g-w, o=x, a=rwx, u+rw\n");
}

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        HelpUser();
        return 0;
    }
    
    if(argc == 2)
    {
        struct stat file_name;
        if(stat(argv[1], &file_name)==0)
        {
            DisplayInfoFile(argv[1]);
            return 0;
        }
        
        if(strlen(argv[1])==3)
        {
            IntToBits(argv[1]);
            return 0;
        }
        else if(strlen(argv[1])==9)
        {
            CharToBits(argv[1]);
            return 0;
        }
        else{
            printf("Ошибка: неверные аргументы\n");
            HelpUser();
            return 1;
        }
    }
    
    // Обработка модификации прав доступа (argc >= 3)
    if(argc >= 3)
    {
        struct stat file_stat;
        if(stat(argv[1], &file_stat) != 0)
        {
            perror("Ошибка при получении информации о файле");
            return 1;
        }
        
        mode_t original_mode = file_stat.st_mode & 0777; // Только права доступа
        mode_t modified_mode = original_mode;
        
        // Применяем все переданные модификации
        for (int i = 2; i < argc; i++) {
            modified_mode = ApplyModification(modified_mode, argv[i]);
        }
        
        // Отображаем результат модификации
        printf("Результат модификации прав доступа для файла: %s\n", argv[1]);
        printf("==================================================\n");
        
        char mod_str[100] = "";
        for (int i = 2; i < argc; i++) {
            if (i > 2) strcat(mod_str, " ");
            strcat(mod_str, argv[i]);
        }
        
        DisplayModifiedRights(original_mode, modified_mode, mod_str);
        
        return 0;
    }
    
    return 0;
}
*/















/* ПЕРВАЯ ЧАСТЬ ЗАДАЧИ 3.1 (1)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


//Функция перевода из char->int->битовое представление
void IntToBits(char *simbols)
{
    //Проверка длины символов
    if(strlen(simbols)!=3)
    {
        printf("Ошибка! Неверная длина входной строки \n");
        return;
    }


    mode_t resultTranslate = 0; 
    resultTranslate = strtol(simbols, NULL, 8);

    //Цикл перевода из восьмеричной в двоичную
    for(int i = 8; i>=0; i--) //перевод из числа в биты с конца
    {
        int bit = (resultTranslate>>i)&1; //сдвигаем и забираем конкретный бит
        printf("%d", bit);
    }
    printf("\n");

    //printf("Ввод значения: %d\n", resultTranslate);
}

//Функция перевода из буквенного в битовое представление
void CharToBits(char *simbols)
{
    //Проверка длины букв + на соответствие букв
    if(strlen(simbols)!=9)
    {
        printf("Ошибка! Неверная длина входной строки \n");
        return;
    }

    //Проверка на наличие нужных букв
    for(int i = 0; i<9; i++)
    {
        if(simbols[i]!='r' && simbols[i]!='w' && simbols[i]!='x' && simbols[i]!='-')
        {
            printf("Ошибка! Неверные введённые буквы (нет таких прав доступа))\n");
            return;
        }
    }


   char bykva;
   //char stroka[] = {'r', 'w', 'x', '-'};  
   for(int i = 0; i<9; i++)
   {
    bykva = simbols[i];
   if(bykva=='r' || bykva=='w' || bykva=='x')
   {
        printf("1");
   }   
   else{
    printf("0");
   }
 }
}



int main(int argc, char *argv[]) //кол-во аргументов, значение аргументов
{

    //printf("Первый входной аргумент %s\n", argv[0]);
    //printf("Первый входной аргумент: %s\n", argv[1]);
    //CharToBits(argv[1]);
   // printf("Второй входной аргумент %s\n", argv[2]);

    if(strlen(argv[1])==3)
    {
        IntToBits(argv[1]);
    }
    else if(strlen(argv[1])==9)
    {
        CharToBits(argv[1]);
    }
    else{
        printf("Ошибка\n");
        return 1;
    }
    return 0;
}
*/



/* ЗАДАЧА 3.1 ПУНКТ 2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


//Функция для преобразования битов прав доступа в буквенное представление
void BitsToLetters(mode_t mode, char *letters)
{
    //Права для владельца
    letters[0] = (mode & S_IRUSR) ? 'r' : '-';
    letters[1] = (mode & S_IWUSR) ? 'w' : '-';
    letters[2] = (mode & S_IXUSR) ? 'x' : '-';

    //Права для группы
    letters[3] = (mode & S_IRGRP) ? 'r' : '-';
    letters[4] = (mode & S_IWGRP) ? 'w' : '-';
    letters[5] = (mode & S_IXGRP) ? 'x' : '-';

    //Права для остальных
    letters[6] = (mode & S_IROTH) ? 'r' : '-';
    letters[7] = (mode & S_IWOTH) ? 'w' : '-';
    letters[8] = (mode & S_IXOTH) ? 'x' : '-';

    letters[9] = '\0'; 
}

//Функция для преобразования битов прав доступа в цифровое представление
void BitsToDigital(mode_t mode, char *digit)
{
    //Восьмеричная нотация (4, 2, 1 - вес битов прав доступа в восьмеричной системе)
    int user = ((mode & S_IRUSR) ? 4 : 0) + ((mode & S_IWUSR) ? 2 : 0) + ((mode & S_IXUSR) ? 1 : 0);
    int group = ((mode & S_IRGRP) ? 4 : 0) + ((mode & S_IWGRP) ? 2 : 0) + ((mode & S_IXGRP) ? 1 : 0);
    int other = ((mode & S_IROTH) ? 4 : 0) + ((mode & S_IWOTH) ? 2 : 0) + ((mode & S_IXOTH) ? 1 : 0);

    sprintf(digit, "%d%d%d", user, group, other);
}


//Функция для вывода битового представления прав доступа для файлов
void PrintBits(mode_t mode)
{
    printf("Битовое представление: ");
    for(int i = 8; i>=0; i--)
    {
        int bit = (mode >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}


//Функция отображения информации о файле
void DisplayInfoFile(const char *filename)
{
    struct stat file_stat;

    //Получение информации о файле
    if(stat(filename, &file_stat)==-1)
    {
        perror("Ошибка при получении информации о файле");
        return;
    }

    printf("Информация о файле: %s\n", filename);
    printf("\n");

    //Буквенное представление 
    char letters[10];
    BitsToLetters(file_stat.st_mode, letters);
    printf("Буквенное представление: %s\n", letters);

    //Цифровое представление
    char digital[4];
    BitsToDigital(file_stat.st_mode, digital);
    printf("Цифровое представление: %s\n", digital);

    //Битовое представление
    PrintBits(file_stat.st_mode & 0777);


}



//Функция перевода из char->int->битовое представление
void IntToBits(char *simbols)
{
    //Проверка длины символов
    if(strlen(simbols)!=3)
    {
        printf("Ошибка! Неверная длина входной строки \n");
        return;
    }


    mode_t resultTranslate = strtol(simbols, NULL, 8); 
    printf("Битовое представление для %s:  ", simbols);

    //Цикл перевода из восьмеричной в двоичную
    for(int i = 8; i>=0; i--) //перевод из числа в биты с конца
    {
        int bit = (resultTranslate>>i)&1; //сдвигаем и забираем конкретный бит
        printf("%d", bit);
        if(i==6 || i==3)
        {
            printf(" ");
        }
    }
    printf("\n");

    //printf("Ввод значения: %d\n", resultTranslate);
}

//Функция перевода из буквенного в битовое представление
void CharToBits(const char *simbols)
{
    //Проверка длины букв + на соответствие букв
    if(strlen(simbols)!=9)
    {
        printf("Ошибка! Неверная длина входной строки \n");
        return;
    }

    //Проверка на наличие нужных букв
    for(int i = 0; i<9; i++)
    {
        if(simbols[i]!='r' && simbols[i]!='w' && simbols[i]!='x' && simbols[i]!='-')
        {
            printf("Ошибка! Неверные введённые буквы (нет таких прав доступа))\n");
            return;
        }
    }
    printf("Битовое представление для %s: ", simbols);
    for(int i = 0; i<9; i++)
    {
        char bykva = simbols[i];
   if(bykva=='r' || bykva=='w' || bykva=='x')
   {
        printf("1");
   }   
   else{
    printf("0");
   }

   if(i==2 || i==5)
   {
    printf(" ");
   }
 }
    printf("\n");
}

void HelpUser()
{
    printf("Если в качестве параметра передать числовой или буквенный вариант, выведется битовая маска\n");
    printf("Если ввести название файла, выведутся права доступа\n");

}

int main(int argc, char *argv[]) //кол-во аргументов, значение аргументов
{
    if(argc == 1)
    {
        HelpUser();
    }
    if(argc == 2)
    {
        struct stat file_name;

        if(stat(argv[1], &file_name)==0)
        {
            DisplayInfoFile(argv[1]);
            return 0;
        }
    if(strlen(argv[1])==3)
    {
        IntToBits(argv[1]);
    }
    else if(strlen(argv[1])==9)
    {
        CharToBits(argv[1]);
    }
    else{
        printf("Ошибка\n");
        return 1;
    }
}
    return 0;
}
*/