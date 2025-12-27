#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "patient.h"
#include "utils.h"

Patient patients[MAX_PATIENTS];
int nbPatients = 0;

void ajouterPatient() {
    if (nbPatients >= MAX_PATIENTS) {
        printf("\n❌ Nombre maximum de patients atteint!\n");
        return;
    }
    
    Patient p;
    p.id = nbPatients + 1;
    
    printf("\n=== AJOUT D'UN PATIENT ===\n");
    printf("Nom: ");
    scanf("%s", p.nom);
    printf("Prénom: ");
    scanf("%s", p.prenom);
    printf("Âge: ");
    scanf("%d", &p.age);
    viderBuffer();
    printf("Maladie/Motif: ");
    fgets(p.maladie, 100, stdin);
    p.maladie[strcspn(p.maladie, "\n")] = 0;
    printf("Téléphone: ");
    scanf("%s", p.telephone);
    
    patients[nbPatients] = p;
    nbPatients++;
    
    printf("\n✅ Patient ajouté avec succès! (ID: %d)\n", p.id);
}

void afficherPatients() {
    if (nbPatients == 0) {
        printf("\n❌ Aucun patient enregistré.\n");
        return;
    }
    
    printf("\n=== LISTE DES PATIENTS ===\n");
    printf("%-5s %-15s %-15s %-5s %-25s %-15s\n", "ID", "Nom", "Prénom", "Âge", "Maladie", "Téléphone");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < nbPatients; i++) {
        printf("%-5d %-15s %-15s %-5d %-25s %-15s\n",
               patients[i].id, patients[i].nom, patients[i].prenom,
               patients[i].age, patients[i].maladie, patients[i].telephone);
    }
}

void rechercherPatientParNom() {
    char nom[50];
    int trouve = 0;
    
    printf("\n=== RECHERCHE PAR NOM ===\n");
    printf("Entrez le nom: ");
    scanf("%s", nom);
    
    printf("\n%-5s %-15s %-15s %-5s %-25s %-15s\n", "ID", "Nom", "Prénom", "Âge", "Maladie", "Téléphone");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < nbPatients; i++) {
        if (strcasecmp(patients[i].nom, nom) == 0) {
            printf("%-5d %-15s %-15s %-5d %-25s %-15s\n",
                   patients[i].id, patients[i].nom, patients[i].prenom,
                   patients[i].age, patients[i].maladie, patients[i].telephone);
            trouve = 1;
        }
    }
    
    if (!trouve) {
        printf("❌ Aucun patient trouvé avec ce nom.\n");
    }
}

void rechercherPatientParMaladie() {
    char maladie[100];
    int trouve = 0;
    
    printf("\n=== RECHERCHE PAR MALADIE ===\n");
    printf("Entrez la maladie: ");
    viderBuffer();
    fgets(maladie, 100, stdin);
    maladie[strcspn(maladie, "\n")] = 0;
    
    printf("\n%-5s %-15s %-15s %-5s %-25s %-15s\n", "ID", "Nom", "Prénom", "Âge", "Maladie", "Téléphone");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < nbPatients; i++) {
        if (strstr(patients[i].maladie, maladie) != NULL) {
            printf("%-5d %-15s %-15s %-5d %-25s %-15s\n",
                   patients[i].id, patients[i].nom, patients[i].prenom,
                   patients[i].age, patients[i].maladie, patients[i].telephone);
            trouve = 1;
        }
    }
    
    if (!trouve) {
        printf("❌ Aucun patient trouvé avec cette maladie.\n");
    }
}

void trierPatientsParAge() {
    if (nbPatients == 0) {
        printf("\n❌ Aucun patient à trier.\n");
        return;
    }
    
    for (int i = 0; i < nbPatients - 1; i++) {
        for (int j = 0; j < nbPatients - i - 1; j++) {
            if (patients[j].age > patients[j + 1].age) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }
    
    printf("\n✅ Patients triés par âge!\n");
    afficherPatients();
}

void supprimerPatient() {
    int id;
    printf("\n=== SUPPRESSION D'UN PATIENT ===\n");
    afficherPatients();
    printf("\nID du patient à supprimer: ");
    scanf("%d", &id);
    
    for (int i = 0; i < nbPatients; i++) {
        if (patients[i].id == id) {
            for (int j = i; j < nbPatients - 1; j++) {
                patients[j] = patients[j + 1];
            }
            nbPatients--;
            printf("\n✅ Patient supprimé avec succès!\n");
            return;
        }
    }
    
    printf("\n❌ Patient non trouvé!\n");
}

int patientExiste(int id) {
    for (int i = 0; i < nbPatients; i++) {
        if (patients[i].id == id) return 1;
    }
    return 0;
}

void menuPatients() {
    int choix;
    
    do {
        clearScreen();
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║         GESTION DES PATIENTS              ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("\n1. Ajouter un patient\n");
        printf("2. Afficher tous les patients\n");
        printf("3. Rechercher par nom\n");
        printf("4. Rechercher par maladie\n");
        printf("5. Trier par âge\n");
        printf("6. Supprimer un patient\n");
        printf("0. Retour\n");
        printf("\nVotre choix: ");
        scanf("%d", &choix);
        
        switch(choix) {
            case 1: ajouterPatient(); break;
            case 2: afficherPatients(); break;
            case 3: rechercherPatientParNom(); break;
            case 4: rechercherPatientParMaladie(); break;
            case 5: trierPatientsParAge(); break;
            case 6: supprimerPatient(); break;
            case 0: break;
            default: printf("\n❌ Choix invalide!\n");
        }
        
        if (choix != 0) pause_ecran();
        
    } while(choix != 0);
}
