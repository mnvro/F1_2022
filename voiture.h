#ifndef __VOITURE__
#define __VOITURE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define INFINITE 32000
#define NB_MAX_Voitures 100

//PARAMETRE DE MARGE
//INTERVALLE DE TEMPS POUR LES SECTEURS
#define MIN_TPS_SECTEUR 25.00
#define MAX_TPS_SECTEUR 40.00
#define MIN_TPS_STAND 5000
#define MAX_TPS_STAND 10000

#define NELEMS(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct{
  int pid;
  int num;
  float lastS[3]; // last S1, last S2 et last S3
  float bestTour;
  int nbStand; // elle est au stand
  int out;

}voiture_t;

int getNBVoitures();

void initVoitures(voiture_t *tabVoitures);

void voitureFait1Tour(voiture_t *voiture, int nbTours);

void afficheUneVoiture(voiture_t v);

void afficheTout(voiture_t *tabVoitures);

#endif // __VOITURE__
