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

int calculNbTours(circuit_t circuit){
    int nbTours = 300 / circuit.longueur;
    if (nbTours * circuit.longueur < 300) nbTours++;
    return  nbTours ;
}

circuit_t afficheMenuCircuit2022(circuit_t *tabCircuits, int nbCircuits){
    int i;
    int choix;
    circuit_t circuitChoisi;
    int nbTours;
    //printf("tabCircuits = %x\n",tabCircuits);

    printf("MENU\n====\n");
    for (i=0 ; i<nbCircuits ; i++){
        //printf("%d\n",i);
        //printf("%d - %-42s %2.3f km\n",i,tabCircuits[i].nom,tabCircuits[i].longueur);
        //nbTours = calculNbTours(tabCircuits[i]);

        /*printf("%2d:%-35s %5.3f km %2d tours Total %7.3f km\n",i+1,tabCircuits[i].nom,tabCircuits[i].longueur,
               nbTours,tabCircuits[i].longueur*nbTours);*/
        printf("%2d : %-35s %5.3f km \n",i+1,tabCircuits[i].nom,tabCircuits[i].longueur);

    }
    printf("Quel est le numéro du circuit que vous voulez choisir : ");
    scanf("%d",&choix);
    choix--;
    memcpy( &circuitChoisi , &(tabCircuits[choix]),sizeof(circuit_t));
    nbTours = calculNbTours(circuitChoisi);

    printf("Vous avez choisi : %s. Ce circuit fait %.3f km. Il comprendra donc %d tours afin qu'au total les voitures effectuent %.3f km\n",
           circuitChoisi.nom,
           circuitChoisi.longueur,
           nbTours,
           circuitChoisi.longueur*nbTours);

    return circuitChoisi;
}

int calculNbCircuits (int annee) {// si annee = 0 on compte tous les circuits, sinon on compte uniquement les circuits de l'année passée en paramètres
    int nbCircuits = 0;
    int anneeLue;
    char string[NB_MAX_CAR_LIGNE_FICHIER];
    char *ch1;
    FILE *f = fopen(NOM_FICH_CIRCUITS,"rt");


    if (f==NULL){
        printf("Problème d'ouverture du fichier %s\n",NOM_FICH_CIRCUITS);
        exit(-1);
    }
    fgets(string,NB_MAX_CAR_LIGNE_FICHIER,f); // on passe la première ligne de titre
    fgets(string,NB_MAX_CAR_LIGNE_FICHIER,f); // on passe la deuxième ligne de titre
    while(fgets(string,NB_MAX_CAR_LIGNE_FICHIER,f)>0){
        ch1 = strtok(string,SEPARATEUR_FICH_CSV); // on passe le nom du circuit
        //if (DEBUG == 1) printf("nom = %s - ",ch1);
        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la colonne type
        //if (DEBUG == 1) printf("type = %s - ",ch1);
        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la colonne direction
        //if (DEBUG == 1) printf("direction = %s - ",ch1);
        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la colonne localisation
        //if (DEBUG == 1) printf("localisation = %s - ",ch1);
        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la colonne pays
        //if (DEBUG == 1) printf("pays = %s - ",ch1);
        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la longueur en km
        //if (DEBUG == 1) printf("km = %s - ",ch1);
        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la longueur en miles
        //if (DEBUG == 1) printf("miles = %s - ",ch1);
        anneeLue = atoi (ch1 = strtok(NULL,SEPARATEUR_FICH_CSV));
        //if (DEBUG == 1) printf("------\nAnnée lue = %s \n ",ch1);
        //if (DEBUG == 1) printf("%s : %d\n", string, anneeLue);
        if (annee == 0 || annee == anneeLue){
           nbCircuits++;
           //if (DEBUG == 1) printf("%s : %d\n", string, anneeLue);
        }
    }
    //if (DEBUG == 4) printf("dans comptage nb circuits = %d\n",nbCircuits);
    fclose(f);
    //if (DEBUG == 3) printf("------------------------\n");
    return nbCircuits;
}

void initCircuit(circuit_t **tabCircuits, int nbCircuits, int annee){ // cette fonction charge tous les circuits en MC // si annee = 0 on charge tous les circuits, sinon on charge uniquement les circuits de l'année passée en paramètres
    char string[NB_MAX_CAR_LIGNE_FICHIER];
    char *ch1;
    int nb = 0;
    float longueur;
    int anneeLue;
    char *nomCircuit;

    FILE *f = fopen(NOM_FICH_CIRCUITS,"rt");
    if (f==NULL){
        printf("Problème d'ouverture du fichier %s\n",NOM_FICH_CIRCUITS);
        exit(-1);
    }

    *tabCircuits = (circuit_t *) malloc (nbCircuits * sizeof(circuit_t));

    fgets(string,NB_MAX_CAR_LIGNE_FICHIER,f); // on passe la première ligne de titre
    fgets(string,NB_MAX_CAR_LIGNE_FICHIER,f); // on passe la deuxième ligne de titre
    while(fgets(string,NB_MAX_CAR_LIGNE_FICHIER,f)>0){
        //printf("on a lu dans le fichier %s\n",string);
        nomCircuit = strtok(string,SEPARATEUR_FICH_CSV);

        strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la colonne type
        strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la colonne direction
        strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la colonne location
        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la colonne pays

        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV);
        longueur = atof(ch1);
        strtok(NULL,SEPARATEUR_FICH_CSV); // on passe la longueur en miles
        //tabCircuits[i].longueur = atof(ch1);
        ch1 = strtok(NULL,SEPARATEUR_FICH_CSV);

        anneeLue = atoi(ch1);
        //if (DEBUG == 3) printf("ici4%s : Année lue = %d\n", string, anneeLue);
        //TODO
        if (annee == 0 || annee == anneeLue){
            strcpy((*tabCircuits)[nb].nom , nomCircuit);
            (*tabCircuits)[nb].longueur = longueur;
            //if (DEBUG == 4) printf("Dans la fonction init on vient d'ajouter à tabCircuits à l'indice : %d - Nom : %s longueur : %f km\n\n",nb,(*tabCircuits)[nb].nom,(*tabCircuits)[nb].longueur);
            nb++;


        }

    }

    fclose(f);

}
