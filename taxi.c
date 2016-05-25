#include "dmse.h"

void *threadTaxi(void *fl)
{
        int idTaxi=fl;
        int sortieTube;
        while(1)
        {
            if((sortieTube = open (nomTube, O_RDONLY)) == -1)
            {
                fprintf(stderr, "Impossible d'ouvrir la sortie du tube nommé.\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                Passager *p=(Passager*)malloc(sizeof(Passager));
                read(sortieTube,(Passager*)p,TAILLE_MESSAGE);
                usleep(10);
                printf("taxi#{%d} : passager {%d} est rendu a la station {%d}\n",idTaxi,p->id,p->stationA);
                free(p);
            }

        }
    pthread_exit(NULL);
}

