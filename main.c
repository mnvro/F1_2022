#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gestionCircuits.h"
#include "voiture.h"

int nbCircuits;
circuit_t *tabCircuits;
circuit_t circuitChoisi;
int nbTours;


int nbVoitures;
voiture_t tabVoitures [NB_MAX_VOtures];
int annee = 2022;
//int annee = TOUS_LES_CIRCUITS;



int main(){

    nbCircuits = calculNbCircuits(annee);
    initCircuit(&tabCircuits,nbCircuits,annee);

    circuitChoisi = afficheMenuCircuit2022(tabCircuits,nbCircuits);
    nbTours = calculNbTours(circuitChoisi);
    initVoitures(tabVoitures,&nbVoitures);
    voitureFait1Tour(&(tabVoitures[0]), nbTours);



    free(tabCircuits);
}
