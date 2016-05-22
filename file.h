#include <stdio.h>s
#include <stdlib.h>
#include <stdbool.h>

typedef struct Passager
{
  int id;
  int stationD;
  int stationA;
  int tpae;
  bool transfert;
  int tpmax;

}Passager;

typedef struct FilePassager
{
    int tailleFIle;
    Passager* ptete;
    Passager* pqueue;

}FilePassager;

Passager* new_Passager(int id,int stationD,int stationA,int tpae,int transfert,int tpmax);
void affichePassager(Passager* p);
FilePassager* new_FilePassager();
void Passager_free(Passager *p);
