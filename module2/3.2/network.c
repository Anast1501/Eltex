#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "network.h"

//Функция для генерации
uint32_t generateAdress()
{
    uint32_t generateIP = 0;
    
    for(int i = 0; i<4; i++)
    {
        generateIP = (generateIP<<8) | (rand()%256);

    }
    return generateIP;
}

//Функция проверки в одной ли подсети находятся адреса
int checkNetwork(uint32_t ipOne, uint32_t ipTwo, uint32_t mask)
{   

    if((ipOne & mask) == (ipTwo & mask)) 
    {   
        return 1;
    }
    else{
        return 0;
    }
        
}

//Функция для преобразования строки IP в число
uint32_t transformIP(const char *ipStr)
{
    uint32_t result = 0;
    unsigned int a, b, c, d;

    if(sscanf(ipStr, "%u.%u.%u.%u", &a, &b, &c, &d)==4)
    {
        return (a<<24) | (b<<16) | (c<<8) | d;
    }
    //return 0;
    exit(EXIT_FAILURE);
}