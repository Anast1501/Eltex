#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "permission.h"

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
        if(i == 6 || i == 3) {
            printf(" ");
        }
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

//Функция для применения модификации прав доступа (аналогично chmod)
mode_t ApplyModification(mode_t current_mode, const char *modification)
{
    mode_t new_mode = current_mode;
    
    char *mod_str = strdup(modification);
    if (!mod_str) {
        printf("Ошибка памяти\n");
        return current_mode;
    }
    
    //Разбираем строку модификации (например: "u+r", "g-w", "o=x")
    char who_part[10] = "";
    char op = '\0';
    char perms_part[10] = "";
    
    int i = 0, j = 0;
    
    //Чтение who часть (u, g, o, a)
    while (mod_str[i] != '\0' && mod_str[i] != '+' && mod_str[i] != '-' && mod_str[i] != '=') {
        who_part[j++] = mod_str[i++];
    }
    who_part[j] = '\0';
    
    //Чтение операцию
    if (mod_str[i] != '\0') {
        op = mod_str[i++];
    } else {
        printf("Ошибка: отсутствует операция в '%s'\n", modification);
        free(mod_str);
        return current_mode;
    }
    
    //Чтение права
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
    
    //Определяем, к кому применяются изменения
    int apply_user = 0, apply_group = 0, apply_other = 0;
    
    if (strlen(who_part) == 0) {
        //Если не указано кому, применяем ко всем
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
    
    //Применение операции
    if (op == '+') {
        //Добавление прав
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
        //Удаление прав
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
        // Установка прав
        if (apply_user) new_mode &= ~(S_IRUSR | S_IWUSR | S_IXUSR);
        if (apply_group) new_mode &= ~(S_IRGRP | S_IWGRP | S_IXGRP);
        if (apply_other) new_mode &= ~(S_IROTH | S_IWOTH | S_IXOTH);
        
        //Устанавливаем указанные права
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
}

//Функция для отображения модифицированных прав доступа
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
    printf("Для модификации прав используйте: ./program файл модификация\n");
    printf("Примеры модификаций: u+r, g-w, o=x, a=rwx, u+rw\n");
}