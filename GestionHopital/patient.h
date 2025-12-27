#ifndef PATIENT_H
#define PATIENT_H

#define MAX_PATIENTS 100

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    int age;
    char maladie[100];
    char telephone[15];
} Patient;

extern Patient patients[MAX_PATIENTS];
extern int nbPatients;

void ajouterPatient();
void afficherPatients();
void rechercherPatientParNom();
void rechercherPatientParMaladie();
void trierPatientsParAge();
void supprimerPatient();
int patientExiste(int id);
void menuPatients();

#endif
