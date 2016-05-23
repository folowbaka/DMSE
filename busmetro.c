#include "dmse.h"

void debarquement(Passager** ptransport,int typeTransport)
{
    switch(typeTransport)
    {
        case BUS:
        break;


    }


}
void *threadbus(void *fl)
{
    int compteurbus=0;
    Passager** pbus=(Passager**)malloc(CAPBUS*sizeof(Passager*));
    while(1)
    {
        printf(" bus station : %d \n",compteurbus);
        compteurbus=(compteurbus+1)%NBFILEBUS;
        sem_post(&evt2);
        sleep(2);
        sem_wait(&evt1);
    }
    pthread_exit(NULL);
}
void *threadmetro(void *fl)
{
    sem_wait(&evt2);
    int compteurmetro=NBFILEBUS;
    Passager** pmetro=(Passager**)malloc(CAPMETRO*sizeof(Passager*));
    while(1)
    {
        printf("Metro station : %d \n",compteurmetro);
        compteurmetro++;
        if(compteurmetro==NBFILE){compteurmetro=NBFILEBUS;}
        sem_post(&evt1);
        sleep(2);
        sem_wait(&evt2);
    }
    pthread_exit(NULL);
}
