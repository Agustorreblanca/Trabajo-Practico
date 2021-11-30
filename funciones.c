```c
#include "lib.h"
#include <time.h>
int tempfiltro(int x)
{

    int tempamb;
    srand(time(NULL));
    tempamb=rand()%8;
    printf("Temperatura ambiente : %d \n", tempamb);
    system("pause");
    if(tempamb>=2&&tempamb<8)
    {
        x=x+tempamb;

        return x;
    }
    if(tempamb<2)
    {
        printf("||La temperatura ambiente es muy baja para regular Ts||");


    }

}
int funcionarefri(int x)
{
    int funciona;
    int temprefri=5;

    printf(" \n Chequeo del refrigerador \n");
    srand(time(NULL));
    funciona=rand()%2;
    if(funciona)
    {
        printf("El refrigerador funciona correctamente \n");
        x=x-temprefri;
        return x;
    }

    else
    {
        printf(" \n||No funciona el refrigerador|| \n");
        return  x;
    }


}
```
#####