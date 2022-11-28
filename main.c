#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h> // pour que sem_init soit reconnu mais ça marche quand même pas
// il faut ajouter -lpthread en ligne de commande pour compiler voir mon PPT pour comment l'ajouter dans code::blocks

#include "gestionCircuits.h"
#include "voiture.h"

#define DEBUG_MAIN 0

int nbCircuits;
circuit_t *tabCircuits;
circuit_t circuitChoisi;
int nbTours;


int nbVoitures;
voiture_t *tabVoitures ;
int annee = 2022;
//int annee = TOUS_LES_CIRCUITS;

//int shmget(key_t key, size_t size, int shmflg);
int resultShmGet;

int shmid_sem;
sem_t *semaphore;
int codeErreur;

int main(){
    int pidPapa = getpid();
    //int pid = getpid();
    int resultFork;
    int i,j; // pour boucle

    system("clear");

    nbCircuits = calculNbCircuits(annee);
    initCircuit(&tabCircuits,nbCircuits,annee);
    nbVoitures = getNBVoitures();
    //tabVoitures = (voiture_t *)malloc(nbVoitures*sizeof(voiture_t));

    /////////////////////////////// Mémoire partagée /////////////////////////////////////////////////
    resultShmGet = shmget(IPC_PRIVATE, nbVoitures*sizeof(voiture_t), 0666 | IPC_CREAT);
    tabVoitures = shmat(resultShmGet, NULL, 0);


    //création et initiation d'un sémaphore en Mémoire partagée //////////////////////////////////////
    shmid_sem = shmget(IPC_PRIVATE, sizeof(sem_t), 0666 | IPC_CREAT);
    semaphore = shmat(shmid_sem, NULL, 0);
    //int sem_init(sem_t *sem, int pshared, unsigned value);
    //If the pshared argument has a non-zero value, then the semaphore is shared between processes
    //The value of the initialized semaphore shall	be  value.
    codeErreur = sem_init(semaphore, 1, 1);

    if (codeErreur != 0){
        printf("Problème avec l'initialisation du sémaphore\n");
        exit(codeErreur);
    }

    circuitChoisi = afficheMenuCircuit2022(tabCircuits,nbCircuits); //TODO aller enlever le circuit choisi qui est pour l'instant hardcodé pour aller plus vite

    afficheUnCircuit(circuitChoisi);
    printf("\n\n");
    nbTours = calculNbTours(circuitChoisi);
    initVoitures(tabVoitures);
    /*if (DEBUG_MAIN){
      for (i=0 ; i<nbVoitures ; i++){
        printf("\nLa voiture %d a été initialisée\n-----------init--------------------\n",i);
        afficheUneVoiture(tabVoitures[i]);
      }
    }*/
    usleep(100000);
    for (i=0 ; i<nbVoitures ; i++){

        if(getpid() == pidPapa){
            resultFork = fork();
            sem_wait(semaphore);
            afficheTout(tabVoitures);
            sem_post(semaphore);
            usleep(100000);

        }
        if (resultFork != 0){ // Je suis dans le fils
          tabVoitures[i].pid = getpid();
          for(j=0 ; j<nbTours ; j++){
            sem_wait(semaphore);
            voitureFait1Tour(&(tabVoitures[i]), nbTours);
            //afficheUneVoiture(tabVoitures[i]);
            sem_post(semaphore);
            usleep(100000);
          }
        }
    }



    if(getpid() == pidPapa){
        afficheTout(tabVoitures);
    }


    shmdt(tabCircuits);
    free(tabCircuits);
    shmdt(semaphore);
    free(semaphore);
}
