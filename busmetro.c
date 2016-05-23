#include "dmse.h"
void *threadbus(void *arg)
{
    printf("Nous sommes dans le bus.\n");

    /* Pour enlever le warning */
    (void) arg;
    pthread_exit(NULL);
}
void *threadmetro(void *arg)
{
    printf("Nous sommes dans le metro.\n");

    /* Pour enlever le warning */
    (void) arg;
    pthread_exit(NULL);
}
