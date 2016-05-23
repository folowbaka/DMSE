#include <stdio.h>s
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#define NBFILE 9

typedef struct Passager Passager;
struct Passager
{
  int id;
  int stationD;
  int stationA;
  int tpae;
  bool transfert;
  int tpmax;
  Passager* next;

};

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
void addPassager(FilePassager* fp,Passager* p);
void afficheFilePassager(FilePassager* fl);
