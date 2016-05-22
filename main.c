#include "file.h"
#define NBFILE 9
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
        if(stationd >0 && stationd<5 || (stationd==0 && stationa<5) || (stationd==5 && stationa>5)||(stationd==6 && stationa<6))
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
        else if(stationd==6 && stationa>6)
        {
            addPassager(fl[7],p);
        }
        else if(stationd==7)
        {
            addPassager(fl[8],p);
        }
    }
    afficheFilePassager(fl[5 ]);
    return 0;
}
