#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#define NBFILE 9
#define NBFILEBUS 5
#define CAPBUS 5
#define CAPMETRO 8
#define BUS 1
#define METRO 2

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

sem_t evt1,evt2,evt3;

Passager* new_Passager(int id,int stationD,int stationA,int tpae,int transfert,int tpmax);
void affichePassager(Passager* p);
FilePassager* new_FilePassager();
void Passager_free(Passager *p);
bool FilePassagerVide(FilePassager* fl);
void addPassager(FilePassager* fp,Passager* p);
void incrementTempsTransfert(FilePassager *fl);
void afficheFilePassager(FilePassager* fl);
void *threadbus(void *arg);
void *threadmetro(void *arg);
void *threadVerif(void *fl);
void debarquement(Passager** ptransport,int typeTransport,int station,FilePassager** fl);
void embarquement(Passager** ptransport,int typeTransport,int station,FilePassager** fl);
