#ifndef PERMISSION_H
#define PERMISSION_H

#include <sys/stat.h>

//Функция для преобразования битов прав доступа в буквенное представление
void BitsToLetters(mode_t mode, char *letters);

//Функция для преобразования битов прав доступа в цифровое представление
void BitsToDigital(mode_t mode, char *digit);

//Функция для вывода битового представления прав доступа для файлов
void PrintBits(mode_t mode);

//Функция отображения информации о файле
void DisplayInfoFile(const char *filename);

//Функция для применения модификации прав доступа (аналогично chmod)
mode_t ApplyModification(mode_t current_mode, const char *modification);

//Функция для отображения модифицированных прав доступа
void DisplayModifiedRights(mode_t original_mode, mode_t modified_mode, const char *modification);

//Функция перевода из char->int->битовое представление
void IntToBits(char *simbols);

//Функция перевода из буквенного в битовое представление
void CharToBits(const char *simbols);

//Функция помощи пользователю
void HelpUser();

#endif