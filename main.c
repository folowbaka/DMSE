#include "dmse.h"

int main(int argc, const char * argv[])
{
    //Verification d'un fichier passé en argument
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
    int id,stationd,stationa,temps,transfert,tempsmax;
    pid_t pid;
    profit=0;
    finProgramme=false;
    nomTube=(char*)malloc(sizeof("nepnep.fifo"));
    nomTube="nepnep.fifo";
    //Création des files
    FilePassager **fl=(FilePassager**)malloc(NBFILE*sizeof(FilePassager*));
    int i;
    for(i=0;i<NBFILE;i++)
    {
        fl[i]=new_FilePassager();
    }
    //Lecture du fichier contenant les passagers
    fscanf(passagers,"%d\n",&nbPassager);
    printf("Nombre de passager %d\n",nbPassager);
    while((fscanf(passagers,"# %d %d %d %d %d %d\n",&id,&stationd,&stationa,&temps,&transfert,&tempsmax))!=EOF)
    {
        Passager *p=new_Passager(id,stationd,stationa,temps,transfert,tempsmax);
        if(stationd >0 && stationd<5 || (stationd==0 && stationa<5) || (stationd==5 && stationa>5)||(stationd==6 && stationa>6)|| stationd==7)
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
    //Création du pipe nommé
    if (mkfifo((nomTube), S_IRWXU | S_IRGRP | S_IWGRP) == -1)
        {
        fprintf(stderr, "Erreur de création du tube\n");
        exit(EXIT_FAILURE);
        }
    //Création du processus fils
    pid=fork();
    if(pid>0)
    {
        sleep(2);
        pthread_t busthread,metrothread,verifthread;
        compteurmetro=NBFILEBUS;compteurbus=0;
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
        kill(pid,SIGTERM);
        printf("Fin du programme, Profit : %d$\n",profit);
        //Destruction du pipe nommé
        unlink(nomTube);
          for(i=0;i<NBFILE;i++)
        {
            free(fl[i]);
        }
        free(fl);
    }
    else
    {
        pthread_t taxithread1,taxithread2,taxithread3;
         if(pthread_create(&taxithread1, NULL, threadTaxi,1) == -1) {
        perror("pthread_create");
        return EXIT_FAILURE;
        }
        if(pthread_create(&taxithread2, NULL, threadTaxi,2) == -1) {
        perror("pthread_create");
        return EXIT_FAILURE;
        }
        if(pthread_create(&taxithread3, NULL, threadTaxi,3) == -1) {
        perror("pthread_create");
        return EXIT_FAILURE;
        }
        if (pthread_join(taxithread1, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
        }
        if (pthread_join(taxithread2, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
        }
        if (pthread_join(taxithread3, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
        }
    }
    return 0;
}
