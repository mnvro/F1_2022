#ifndef __GESTION_CIRCUIT__
#define __GESTION_CIRCUIT__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NOM_FICH_CIRCUITS "Tous les circuits de F1.csv"
#define NB_MAX_CAR_CIRCUIT 100 // pour info actuellement le plus long est "Autódromo Internacional do Rio de Janeiro" qui fait 41 caractères
#define NB_MAX_CAR_LIGNE_FICHIER 1000

#define TOUS_LES_CIRCUITS 0 // si on veut charger tous les circuits
#define UNIQUEMENT_CIRCUITS_ANNEE 2022 // si on veut charger uniquement les circuits d'une année précisée
#define SEPARATEUR_FICH_CSV ";" // séparateur dans le fichier csv, normalement "," ou bien ";"

#define DEBUG 4

typedef struct{
    char nom[NB_MAX_CAR_CIRCUIT];
    float longueur; // la longueur en km
}circuit_t;

int calculNbTours(circuit_t circuit);

circuit_t afficheMenuCircuit2022(circuit_t *tabCircuits, int nbCircuits);

int calculNbCircuits (int annee); // si annee = 0 on compte tous les circuits, sinon on compte uniquement les circuits de l'année passée en paramètres

void initCircuit(circuit_t **tabCircuits, int nbCircuits, int annee); // cette fonction charge tous les circuits en MC // si annee = 0 on charge tous les circuits, sinon on charge uniquement les circuits de l'année passée en paramètres

void afficheUnCircuit(circuit_t circuitChoisi);
#endif // __GESTION_CIRCUIT__
