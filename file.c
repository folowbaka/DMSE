#include "dmse.h"
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
    if(p!=NULL)
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
bool FilePassagerVide(FilePassager* fl)
{
    return fl->tailleFIle==0;
}
//Ajoute un passager en bout de queue de la file
void addPassager(FilePassager* fp,Passager* p)
{
    if(fp!=NULL)
    {
        if(FilePassagerVide(fp))
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
//Retire un passager en bout de tête
Passager* popPassager(FilePassager* fp)
{
    Passager* pr=NULL;
    if(!FilePassagerVide(fp))
    {
        if(fp->tailleFIle==1 && fp->pqueue==fp->ptete)
        {
            pr=fp->pqueue;
            fp->pqueue=NULL;
            fp->ptete=NULL;
        }
        else
        {
            Passager* p=fp->pqueue;
            while(p!=NULL && p->next!=fp->ptete)
            {
                p=p->next;
            }
            pr=fp->ptete;
            fp->ptete=p;fp->ptete->next=NULL;
        }
        fp->tailleFIle--;
    }
    return pr;
}
//Retire le passager passé en paramètre de la file
Passager* popPassagerTaxi(FilePassager* fp,Passager* p)
{
    if(!FilePassagerVide(fp))
    {
        if(fp->tailleFIle==1 && fp->pqueue==fp->ptete)
        {
            fp->pqueue=NULL;
            fp->ptete=NULL;
        }
        else if(p==fp->pqueue)
        {
            fp->pqueue=fp->pqueue->next;
        }
        else
        {
            Passager* ps=fp->pqueue;
            while(ps!=NULL && ps->next!=p)
            {
                ps=ps->next;
            }
            ps->next=p->next;
            if(p==fp->ptete)
            {
                fp->ptete=ps;
            }

        }
        fp->tailleFIle--;
    }
    return p;

}
//Incrémente le temps des passager et appelle un taxi si besoin
void incrementTempsTransfert(FilePassager* fl)
{
         if(fl!=NULL)
    {
        Passager* actuel =fl->pqueue;
        while(actuel!=NULL)
        {
            actuel->tpae++;
            if(actuel->tpae==actuel->tpmax)
            {
                Passager* p=popPassagerTaxi(fl,actuel);
                profit=profit+3;
                nbPassager--;
                printf("verificateur : transfert du passager{%d} vers un taxi\n",p->id);
                ecrirePassager(p);
                usleep(100);
            }
            actuel=actuel->next;
        }

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
