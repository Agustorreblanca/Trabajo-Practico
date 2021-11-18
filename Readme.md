
 ## Memoria Descriptiva 
Mi proyecto sobre el control de temperatura de una cámara frigorífica se manejará con las siguientes instrucciones: Habrá una temperatura configurada como Tconfig, un DeltaT y una temperatura TS que es la temperatura leída por un sensor. Esa temperatura podrá variar una cantidad DeltaT tal que Tconfig-DeltaT<TS<Tconfig+DeltaT. Cuando la temperatura TS<Tconfig-DeltaT, se habilitarán varias entradas de aire al exterior, considerando una temperatura ambiente en el aire. En caso de que la temperatura no se regule en un cierto tiempo programable, sonará una alarma para avisar por falta de calor. Si la temperatura TS retoma un valor mayor a Tconfig-DeltaT, entonces las entradas de aire se cierra.En caso de que la temperatura TS exceda a Tconfig+DeltaT, se habilitarán extractores de calor, un sistema de refrigeración aparte del que ya contiene la cámara frigorífica. Al igual que con las entradas de aire, si la temperatura no se regula en un cierto tiempo, se habilitará otra alarma

## Diagrama de Estados 
[!text](imagine https://ibb.co/XZLyfjM)


### Código de operación
```c

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
int main()
{

    printf("|||Medicion de temperatura||| \n");
    system("pause \n");
   int minutos=0, segundos=0,Minutos=0, Segundos=0, Ts;
         srand(time(NULL));
        Ts=rand()%15;
        printf("La temperatura medida es : %d grados \n", Ts);
        system("pause");
        while (Minutos<3&&Ts>Tconfig+DeltaT)
        {
            printf("\n Refrigeracion activa \n");
            Segundos=60;
            if(Segundos==60)
            {

                Minutos++;
                Segundos=0;
                Ts=funcionarefri(Ts);
                system("Pause \n");

            }
            printf(">> Tiempo transcurrido: %d minutos << \n", Minutos);

        if(Minutos >=3 && Ts>Tconfig+DeltaT)
        {

            printf("|||||Alarma por Alta temperatura activa|||||");
        }
        if(Minutos<3 && Ts<Tconfig+DeltaT)
        {
            printf("La nueva temperatura es: %d \n", Ts);
            printf("La temperatura se regulo a %d ....", Ts);
        }
        }

        while(minutos<3 && Ts<Tconfig-DeltaT)
        {
            printf("!!!!!!!Filtro de aire activado!!!!!!! \n");
            segundos=60;
            if(segundos==60)
            {
                minutos++;
             segundos=0;
             Ts=tempfiltro(Ts);
            }
            printf("\n Nueva temperatura leida en la camara  ''''%d''''' grado(s) ", Ts );
            printf("\n Tiempo transcurrido : %d   Minuto(s) \n", minutos);
            system("pause");
            if(minutos==3&&Ts<Tconfig-DeltaT)
            {
             printf("||Alarma encendida por falta de calor||");
             system("Pause");
            }
            if (minutos<3&& Ts>Tconfig-DeltaT)
            {
             printf(" \n |||Temperatura regulada a %d grados|||", Ts );
            }

        }

    return 0;
}