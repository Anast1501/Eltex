#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <network.h>

int main(int argc, char* argv[])
{
    //Проверка кол-ва аргументов
    if(argc!=4)
    {
        printf("Использование: %s <IP-адрес шлюза> <маска подсети> <кол-во пакетов>\n", argv[0]);
        printf("Пример: %s 192.168.1.1 255.255.255.0 100\n", argv[0]);
        return 1;
    }

    //Объявление переменных для хранения входных параметров
    uint32_t ipAdress = transformIP (argv[1]);
    uint32_t mask = transformIP(argv[2]);
    int N = atoi(argv[3]);
    srand(time(NULL));
    int countPacket = 0;
    //Прогон каждого пакета
    for(int i = 0; i<N; i++)
    {
        uint32_t generatedIP = generateAdress();
        if(checkNetwork(ipAdress, generatedIP, mask)==1)
        {
            countPacket++;
        }
    }

    printf("Кол-во пакетов папавшую в нашу подсеть: %d\n", countPacket);

    double prosent = (countPacket*100.0)/N;
    printf("%.4f%%\n", prosent);

    return 0;
}
