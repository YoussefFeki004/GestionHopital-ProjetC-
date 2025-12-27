#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#define MAX_RDV 200

typedef struct {
    int id;
    int idPatient;
    int idMedecin;
    char dateCreation[11];
    char heureCreation[6];
    char dateRDV[11];
    char heureRDV[6];
    char motif[100];
} RendezVous;

extern RendezVous rendezVous[MAX_RDV];
extern int nbRendezVous;

void creerRendezVous();
void afficherRendezVous();
void afficherRendezVousParMedecin();
void afficherRendezVousParDate();
void statistiquesRendezVous();
void annulerRendezVous();
int creneauLibre(int idMedecin, char* date, char* heure);
void menuRendezVous();

#endif