#include "dmse.h"

int main(int argc, const char * argv[])
{
    if(argc<=1)
    {
        printf("Il manque les passagers!");
        exit(1);
    }
    FILE* passagers=NULL;
    passagers =fopen(argv[1],"r");
    if(passagers==NULL)
    {
        printf("Erreur d'ouverture du fichier");
        exit(1);
    }
    int nbPassager=0;
    int id,stationd,stationa,temps,transfert,tempsmax;
    pid_t pid;
    nomTube=(char*)malloc(sizeof("nepnep.fifo"));
    nomTube="nepnep.fifo";
    FilePassager **fl=(FilePassager**)malloc(NBFILE*sizeof(FilePassager*));
    int i;
    for(i=0;i<NBFILE;i++)
    {
        fl[i]=new_FilePassager();
    }
    fscanf(passagers,"%d\n",&nbPassager);
    printf("Nombre de passager %d\n",nbPassager);
    while((fscanf(passagers,"# %d %d %d %d %d %d\n",&id,&stationd,&stationa,&temps,&transfert,&tempsmax))!=EOF)
    {
        Passager *p=new_Passager(id,stationd,stationa,temps,transfert,tempsmax);
        if(stationd >0 && stationd<5 || (stationd==0 && stationa<5) || (stationd==5 && stationa>5)||(stationd==6 && stationa>6)|| stationa==7)
        {
            addPassager(fl[stationd],p);
        }
        else if(stationd==0 && stationa>=5)
        {
            addPassager(fl[5],p);
        }
        else if(stationd==5 && stationa<5)
        {
            addPassager(fl[0],p);
        }
        else if(stationd==6 && stationa<6)
        {
            addPassager(fl[8],p);
        }
    }
    pid=fork();
    if(pid>0)
    {
        if (mkfifo((nomTube), S_IRWXU | S_IRGRP | S_IWGRP) == -1)
        {
        fprintf(stderr, "Erreur de création du tube\n");
        //exit(EXIT_FAILURE);
        }
        pthread_t busthread,metrothread,verifthread;
        sem_init(&evt1,0,0);
        sem_init(&evt2,0,0);
        sem_init(&evt3,0,0);
        if(pthread_create(&busthread, NULL, threadbus,fl) == -1) {
        perror("pthread_create");
        return EXIT_FAILURE;
        }
        if(pthread_create(&metrothread, NULL, threadmetro,fl) == -1) {
        perror("pthread_create");
        return EXIT_FAILURE;
        }
        if(pthread_create(&verifthread, NULL, threadVerif,fl) == -1) {
        perror("pthread_create");
        return EXIT_FAILURE;
        }
        if (pthread_join(busthread, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
        }
        if (pthread_join(metrothread, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
        }
        if (pthread_join(verifthread, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
        }
    }
    else
    {

    }
    return 0;
}
