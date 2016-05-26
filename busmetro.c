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
        //Teste si le bus et metro sont à la même station
        if(compteurbus==0 && compteurmetro==NBFILEBUS)
        {
            //Mis en pause du bus en attendant que le metro finisse son tour
            sem_wait(&evt1);
        }
        printf(" ______________________\n|,----.,----.,----.,--.\\ \n||    ||    ||    ||   \\\\ \n|`----'`----'|----||----\\`. \n[            |   -||- __|(| \n[  ,--.      |____||.--.  |\n=-(( `))-----------(( `))==\n   `--'             `--'\n");
         printf("bus station : %d \n",compteurbus);
        debarquement(pbus,BUS,compteurbus,fl);
        embarquement(pbus,BUS,compteurbus,fl);
        compteurbus=(compteurbus+1)%NBFILEBUS;
        sem_post(&evt3);
        sem_wait(&evt1);
    }
    pthread_exit(NULL);
}
void *threadmetro(void *fl)
{

    compteurmetro=NBFILEBUS;
    Passager** pmetro=(Passager**)malloc(CAPMETRO*sizeof(Passager*));
    while(!finProgramme)
    {
        printf("_________\n|  _  |    __\n| | | |____\\/_\n| |_| |       \\ \n| __  |  _  _  |\n|/  \\_|_/ \\/ \\/\n \\__/   \\_/\\_/\n");
        printf("Metro station : %d \n",compteurmetro);
        debarquement(pmetro,METRO,compteurmetro,fl);
        embarquement(pmetro,METRO,compteurmetro,fl);
        //Teste si le bus et metro sont à la même station
        if(compteurbus==0 && compteurmetro==NBFILEBUS)
        {
            //Passe son tour au bus
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
        //Incrémente le temps des passagers
        for(i=0;i<NBFILE;i++)
        {
            FilePassager** fp=fl;
            incrementTempsTransfert(fp[i]);
        }
        //Met fin aux threads et donc au programme lorsque tous les passager on débarqués ou prit un taxi
        if(nbPassager==0)
        {
            printf("NBPASSAGER %d\n",nbPassager);
            finProgramme=true;
            sem_post(&evt1);
            sem_post(&evt2);
        }
        else
        {
            printf("NBPASSAGER %d\n",nbPassager);
            sleep(2);
            sem_post(&evt1);
            sem_post(&evt2);
            sem_wait(&evt3);
            sem_wait(&evt3);
        }

    }
    pthread_exit(NULL);
}
