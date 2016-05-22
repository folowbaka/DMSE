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
