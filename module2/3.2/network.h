#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

//Функция для генерации
uint32_t generateAdress();

//Функция проверки в одной ли подсети находятся адреса
int checkNetwork(uint32_t ipOne, uint32_t ipTwo, uint32_t mask);

//Функция для преобразования строки IP в число
uint32_t transformIP(const char *ipStr);

#endif