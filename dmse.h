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

sem_t evt1;
sem_t evt2;
Passager* new_Passager(int id,int stationD,int stationA,int tpae,int transfert,int tpmax);
void affichePassager(Passager* p);
FilePassager* new_FilePassager();
void Passager_free(Passager *p);
void addPassager(FilePassager* fp,Passager* p);
void afficheFilePassager(FilePassager* fl);
void *threadbus(void *arg);
void *threadmetro(void *arg);
