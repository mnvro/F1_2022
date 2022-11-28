#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define INFINITE 32000
#define NB_MAX_VOtures 100

//PARAMETRE DE MARGE
//INTERVALLE DE TEMPS POUR LES SECTEURS
#define MIN_TPS_SECTEUR 25
#define MAX_TPS_SECTEUR 40
#define MIN_TPS_STAND 5000
#define MAX_TPS_STAND 10000

#define NELEMS(arr) (sizeof(arr) / sizeof(arr[0]))

#define DEBUG_VOITURE 1
#define DEBUG_ALEA 1

int debugVoiture = 1;
int tabPilotes[] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9, -4, -3, -2, -1}; // -x c'est pour garder les meilleures valeurs

typedef struct{
  int pid;
  int num;
  float lastS[3]; // last S1, last S2 et last S3
  float bestTour;
  int nbTours; // le nombre de tours que la voiture a effectués
  int nbStand; // nb de fois que la voiture est allée au stand
  int out; // 1 la voiture est out

}voiture_t;

//int nbVoitures = NELEMS(tabPilotes);
//voiture_t tabVoitures [NB_MAX_VOtures];

void initVoitures(voiture_t tabVoitures [], int *nbVoitures){
  int i,j;
  *nbVoitures = NELEMS(tabPilotes);
  for (i=0 ; i<*nbVoitures  ; i++){
    tabVoitures[i].num = tabPilotes[i];
    for(j=0 ; j<3 ; j++){
      tabVoitures[i].lastS[j] = INFINITE;
    }
    tabVoitures[i].bestTour = INFINITE;
    tabVoitures[i].nbStand = 0;
    tabVoitures[i].out = 0;
    tabVoitures[i].nbTours = 0;
  }
}

int estLeDernierTour(voiture_t voiture, int nbTours){
    return (voiture.nbTours == nbTours);
}

void voitureFait1Tour(voiture_t *voiture, int nbTours){
    int j;
    float alea;
    int stand; // un arret obligatoire pendant la course du dimanche - 2 voire 3 grand max

    int intervalleAlea = (MAX_TPS_SECTEUR - MIN_TPS_SECTEUR) * 1000 ;
    srand(time(NULL)+voiture->num);

    voiture->nbTours++;

    for(j=0 ; j<3 ; j++){
        alea = (
                  ( rand() % ( (int)  intervalleAlea ) )
               ) /1000.0 + MIN_TPS_SECTEUR;
        voiture->lastS[0] = alea;
        //if (debugVoiture) printf("alea = %0.3f (compris entre %d et %d) \n",alea, MIN_TPS_SECTEUR, MAX_TPS_SECTEUR);

        stand = rand() % nbTours;
    }
    if (voiture->nbStand <= 3){ // 3 est le nombre maximum de fois où une voiture devrait aller au stand
      stand = rand() % nbTours; // risque d'aller au stand --> si 0 il doit aller au stand
      if ((estLeDernierTour(*voiture,nbTours)&&(voiture->nbStand == 0))||stand==0) {// c'est le dernier tour et la voiture n'est pas encore allée au stand, elle est obligée d'y aller
          intervalleAlea = (MAX_TPS_STAND - MIN_TPS_STAND) * 1000 ;
          alea = (
                  ( rand() % ( (int)  intervalleAlea ) )
                 ) /1000.0 + MIN_TPS_STAND;
          voiture->lastS[2] += alea;
          if (DEBUG_ALEA) printf("alea au stand = %f\n",alea);

      }
    }



}


