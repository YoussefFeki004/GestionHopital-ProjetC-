#ifndef MEDECIN_H
#define MEDECIN_H

#define MAX_MEDECINS 50

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char specialite[50];
    char telephone[15];
} Medecin;

extern Medecin medecins[MAX_MEDECINS];
extern int nbMedecins;

void ajouterMedecin();
void afficherMedecins();
void filtrerMedecinsParSpecialite();
void supprimerMedecin();
int medecinExiste(int id);
void menuMedecins();

#endif
