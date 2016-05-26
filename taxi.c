#include "dmse.h"

void *threadTaxi(void *fl)
{
        int idTaxi=fl;
        int sortieTube;
         if((sortieTube = open (nomTube, O_RDONLY)) == -1)
            {
                fprintf(stderr, "Impossible d'ouvrir la sortie du tube nommé.\n");
                exit(EXIT_FAILURE);
            }
        while(1)
        {
                Passager *p=(Passager*)malloc(sizeof(Passager));
                read(sortieTube,(Passager*)p,TAILLE_MESSAGE);
                usleep(10);
                printf("              .----' `-----.\n             //^^^^;;^^^^^^`\\ \n     _______//_____||_____()_\\________ \n    / %d     :      : ___              `\\ \n   |>   ____;      ;  |/\><|   ____   _<)\n  {____/    \\_________________/    \\____}\n       \\ '' /                 \\ '' /\n        '--'                   '--'\n",idTaxi);
                printf("taxi#{%d} : passager {%d} est rendu a la station {%d}\n",idTaxi,p->id,p->stationA);
                free(p);


        }
    pthread_exit(NULL);
}

