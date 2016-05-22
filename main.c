#include "file.h"
#define NBFILE 10
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
        affichePassager(p);
    }
    return 0;
}
