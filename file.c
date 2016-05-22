#include "file.h"
Passager* new_Passager(int id,int stationD,int stationA,int tpae,int transfert,int tpmax)
{
    Passager* p=malloc(sizeof(Passager));
    p->id=id;
    p->stationD=stationD;
    p->stationA=stationA;
    p->tpae=tpae;
    p->transfert=transfert;
    p->tpmax=tpmax;
    p->next=NULL;
    return p;

}
void affichePassager(Passager* p)
{
   printf("# %d %d %d %d %d %d\n",p->id,p->stationD,p->stationA,p->tpae,p->transfert,p->tpmax);

}
void Passager_free(Passager *p)
{
    if (p!=NULL) free(p);
}
FilePassager* new_FilePassager()
{
    return calloc(1,sizeof(FilePassager));
}
void addPassager(FilePassager* fp,Passager* p)
{
    if(fp!=NULL)
    {
        if(fp->tailleFIle==0 && fp->pqueue==NULL && fp->ptete==NULL)
        {
            fp->pqueue=p;fp->ptete=p;
        }
        else
        {
            p->next=fp->pqueue;
            fp->pqueue=p;
        }
        fp->tailleFIle++;
    }

}
void afficheFilePassager(FilePassager* fl)
{
    if(fl!=NULL)
    {
        Passager* actuel =fl->pqueue;
        while(actuel!=NULL)
        {
            affichePassager(actuel);
            actuel=actuel->next;
        }

    }

}
