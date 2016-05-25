#include "dmse.h"

void debarquement(Passager** ptransport,int typeTransport,int station,FilePassager** fl)
{
        int i;
        switch(typeTransport)
        {
            case BUS:
            for(i=0;i<CAPBUS;i++)
            {
                if(ptransport[i]!=NULL)
                {
                    if(ptransport[i]->stationA==station || (ptransport[i]->stationA==5 && station==0))
                    {
                        printf("bus : debarque le passager %d\n",ptransport[i]->id);
                        Passager_free(ptransport[i]);
                        ptransport[i]=NULL;
                        nbPassager--;
                    }
                    else if(ptransport[i]->stationA>5 && station==0)
                    {
                        printf("transfert passager {%d} vers station {5}\n",ptransport[i]->id);
                        addPassager(fl[5],ptransport[i]);
                        ptransport[i]=NULL;
                    }
                }
            }
            break;
            case METRO:
            for(i=0;i<CAPMETRO;i++)
            {
                if(ptransport[i]!=NULL)
                {
                    if(ptransport[i]->stationA==station || (ptransport[i]->stationA==6 && station==8) || (ptransport[i]->stationA==0 && station==5))
                    {
                        printf("metro : debarque le passager %d\n",ptransport[i]->id);
                        Passager_free(ptransport[i]);
                        ptransport[i]=NULL;
                        nbPassager--;
                    }
                    else if(ptransport[i]->stationA<5 && station==5)
                    {
                        printf("transfert passager {%d} vers station {5}\n",ptransport[i]->id);
                        addPassager(fl[0],ptransport[i]);
                        ptransport[i]=NULL;
                    }
                }
            }
            break;

        }
}
void embarquement(Passager** ptransport,int typeTransport,int station,FilePassager** fl)
{
    bool transportplein=false;
    while(!FilePassagerVide(fl[station]) && !transportplein)
    {
        int i=0;
        switch(typeTransport)
        {
            case(BUS):
                while(i<CAPBUS && ptransport[i]!=NULL)
                {
                    i++;
                }
                if(i>=CAPBUS)
                {
                    printf("Bus plein\n");
                    transportplein=true;
                }
                else
                {
                    ptransport[i]=popPassager(fl[station]);
                    printf("bus : embarque le passager {%d}\n",ptransport[i]->id);
                    profit++;
                }
            break;
            case(METRO):
                while(i<CAPMETRO && ptransport[i]!=NULL)
                {
                    i++;
                }
                if(i>=CAPMETRO)
                {
                    printf("Metro plein\n");
                    transportplein=true;
                }
                else
                {
                    ptransport[i]=popPassager(fl[station]);
                    printf("metro : embarque le passager {%d}\n",ptransport[i]->id);
                    profit++;
                }
            break;

        }
    }
}
void ecrirePassager(Passager* p)
{
    int entreeTube;
    if((entreeTube = open (nomTube, O_WRONLY)) == -1)
	{
		fprintf(stderr, "Impossible d'ouvrir l'entrée du tube nommé.\n");
		exit(EXIT_FAILURE);
	}
    write(entreeTube,p,TAILLE_MESSAGE);

}
void *threadbus(void *fl)
{
    compteurbus=0;
    int i;
    Passager** pbus=(Passager**)malloc(CAPBUS*sizeof(Passager*));
    while(!finProgramme)
    {
        if(compteurbus==0 && compteurmetro==NBFILEBUS)
        {
            sem_wait(&evt1);
        }
        printf(" ______________________\n|,----.,----.,----.,--.\\ \n||    ||    ||    ||   \\\\ \n|`----'`----'|----||----\\`. \n[            |   -||- __|(| \n[  ,--.      |____||.--.  |\n=-(( `))-----------(( `))==\n   `--'             `--'\n");
         printf("bus station : %d \n",compteurbus);
        debarquement(pbus,BUS,compteurbus,fl);
        embarquement(pbus,BUS,compteurbus,fl);
        for(i=0;i<CAPBUS;i++)
        affichePassager(pbus[i]);
        compteurbus=(compteurbus+1)%NBFILEBUS;
        sem_post(&evt3);
        sem_wait(&evt1);
    }
    pthread_exit(NULL);
}
void *threadmetro(void *fl)
{
int i;
    compteurmetro=NBFILEBUS;
    Passager** pmetro=(Passager**)malloc(CAPMETRO*sizeof(Passager*));
    while(!finProgramme)
    {
        printf("_________\n|  _  |    __\n| | | |____\\/_\n| |_| |       \\ \n| __  |  _  _  |\n|/  \\_|_/ \\/ \\/\n \\__/   \\_/\\_/\n");
        printf("Metro station : %d \n",compteurmetro);
        debarquement(pmetro,METRO,compteurmetro,fl);
        embarquement(pmetro,METRO,compteurmetro,fl);
        for(i=0;i<CAPMETRO;i++)
        affichePassager(pmetro[i]);
        if(compteurbus==0 && compteurmetro==NBFILEBUS)
        {
            sem_post(&evt1);
        }
        compteurmetro++;
        if(compteurmetro==NBFILE){compteurmetro=NBFILEBUS;}
        sem_post(&evt3);
        sem_wait(&evt2);
    }
    pthread_exit(NULL);
}
void *threadVerif(void *fl)
{
    int i;
    sem_wait(&evt3);
    sem_wait(&evt3);
    while(!finProgramme)
    {
        printf("Tour vérif\n");
        for(i=0;i<NBFILE;i++)
        {
            FilePassager** fp=fl;
            incrementTempsTransfert(fp[i]);
        }
        printf("NBPASSAGER %d\n",nbPassager);
        if(nbPassager==0)
        {
            finProgramme=true;
            sem_post(&evt1);
            sem_post(&evt2);
        }
        else
        {
            sleep(2);
            sem_post(&evt1);
            sem_post(&evt2);
            sem_wait(&evt3);
            sem_wait(&evt3);
        }

    }
    pthread_exit(NULL);
}
