
 ## Memoria Descriptiva 
Mi proyecto sobre el control de temperatura de una cámara frigorífica se manejará con las siguientes instrucciones: Habrá una temperatura configurada como Tconfig, un DeltaT y una temperatura TS que es la temperatura leída por un sensor. Esa temperatura podrá variar una cantidad DeltaT tal que Tconfig-DeltaT<TS<Tconfig+DeltaT. Cuando la temperatura TS<Tconfig-DeltaT, se habilitarán varias entradas de aire al exterior, considerando una temperatura ambiente en el aire. En caso de que la temperatura no se regule en un cierto tiempo programable, sonará una alarma para avisar por falta de calor. Si la temperatura TS retoma un valor mayor a Tconfig-DeltaT, entonces las entradas de aire se cierra.En caso de que la temperatura TS exceda a Tconfig+DeltaT, se habilitarán extractores de calor, un sistema de refrigeración aparte del que ya contiene la cámara frigorífica. Al igual que con las entradas de aire, si la temperatura no se regula en un cierto tiempo, se habilitará otra alarma

## Diagrama de Estados 
[!text](image https://ibb.co/VqKjkKc)


### main.c
```c
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
int main()
{
    int *deltat,*to,*tconfig,op;
    estados_t estado=espera;
    datos_t config;
    system("pause");
    printf("Desea Ingresar los Datos De las variables? 1-si, 0-no");
    scanf("%d",&op);
    if(op)
    crear();
    config=f_inicio();
    deltat=&config.DeltaT;
    to=&config.To;
    tconfig=&config.Tconfig;
    estados_t (*fsm[])(int*,int*,int*)={f_espera,f_enfriar,f_calentar,f_alarma};
        while(1)
            estado=(*fsm[estado])(deltat ,to,tconfig);
        return 0;
}
```
#### funciones.c
``` c
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
int Ts;
estados_t f_espera(int *tconfig, int *to, int *deltat)
{
    estados_t est;
    Ts=rand()%11;
    printf("Estado: Espera. \n Nueva Temperatura Medida :%d",Ts);
    system("pause");
     srand(time(NULL));
    if(Ts>=*to+*deltat)
    {
        est=enfriar;
        return est;
    }
    if(Ts<=*to-*deltat)
    {
        est=calentar;
    return est;
}
if (Ts<*to+*deltat && Ts>*to-*deltat)
    {est=espera;
return est;
}
}
estados_t f_enfriar (int *tconfig, int *to, int *deltat)
{
    int minutos=0,segundos=0;
    estados_t est;
    printf("||Refrigeracion activa||\n");
    while(minutos<*tconfig && Ts>=*to+*deltat)
    {
    srand(time(NULL));
    Ts=rand()%11;
    segundos=60;
    printf("\n Nueva temperatura medida: %d",Ts);
    if(segundos==60 && Ts>=*to+*deltat)
    {
        segundos=0;
        minutos++;
    }
    else
    {
        est=espera;
        return est;
    }
    }
    if(minutos==*tconfig)
    {
        est=alarma;
        return est;
    }
    }
    estados_t f_calentar(int *tconfig, int *to, int *deltat)
    {
    int minutos=0;
    int segundos=0;
    estados_t est;
    printf(" Estado: Calentar.\n Temperatura medida :%d\n",Ts);
    printf("\n||Ventilación Activada|| \n");
    while(minutos<*tconfig && Ts>*to+*deltat)
    {
    srand(time(NULL));
    Ts=rand()%11;
    segundos=60;
    printf(" \n Nueva temperatura medida: %d",Ts);
    if(Ts>=*to+*deltat)
        minutos++;
    else
    {
        est=espera;
    return est;
}
    }
    if(minutos==*tconfig)
        {
            printf("\n Tiempo limite superado");
            est=alarma;
        return est;
        }
    }
    estados_t f_alarma(int *tconfig, int *to, int *deltat)
    {
        estados_t est;
        printf("Estado: Alarma.\n Temperatura medida : %d \n",Ts);
        printf("|Alarma encendida| \n");
        Ts=*to;
        est=espera;
        return est;

    }
    datos_t f_inicio(void)
{
    FILE *fp;
    datos_t bf;
    if((fp=fopen("config.txt","rt"))==NULL)
    {
        printf("Error al abrir el archivo \n");
        return;
    }
    fread(&bf,sizeof(datos_t),1,fp);
    fclose(fp);
    return bf;
}

crear(void)
{
 FILE *fp;
 datos_t bf;
 if((fp=fopen("config.txt","at"))==NULL)
 {
     printf("Error al crear el archivo \n");
     return;
 }
 printf("Ingrese el Valor De las Variables \n");
 printf("DeltaT:");
 scanf("%d", &bf.DeltaT);
 printf("\n Tconfig :");
 scanf("%d", &bf.Tconfig);
 printf("\n To:");
 scanf("%d",&bf.To);
 fwrite(&bf,sizeof(datos_t),1,fp);
 fclose(fp);
 }
```
###### lib.h
``` c
 #include <stdio.h>
#include <stdlib.h>
typedef enum
{
    espera=0,
    enfriar=1,
    calentar=2,
    alarma=3
} estados_t;

typedef struct
{
    int DeltaT;
    int To;
    int Tconfig;
} datos_t;
datos_t f_inicio(void);
void crear(void);
estados_t f_espera(int *tconfig, int *to, int *deltat);
estados_t f_enfriar(int *tconfig, int *to, int *deltat);
estados_t f_calentar(int *tconfig, int *to, int *deltat);
estados_t f_alarma (int *tconfig, int *to, int *deltat);
```
