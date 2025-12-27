#include <stdio.h>
#include <string.h>
#include "rendezvous.h"
#include "patient.h"
#include "medecin.h"
#include "utils.h"

RendezVous rendezVous[MAX_RDV];
int nbRendezVous = 0;

int creneauLibre(int idMedecin, char* date, char* heure) {
    for (int i = 0; i < nbRendezVous; i++) {
        if (rendezVous[i].idMedecin == idMedecin &&
            strcmp(rendezVous[i].dateRDV, date) == 0 &&
            strcmp(rendezVous[i].heureRDV, heure) == 0) {
            return 0;
        }
    }
    return 1;
}

void creerRendezVous() {
    if (nbRendezVous >= MAX_RDV) {
        printf("\n❌ Limite atteinte!\n");
        return;
    }
    
    RendezVous rdv;
    rdv.id = nbRendezVous + 1;
    
    obtenirDateHeureActuelle(rdv.dateCreation, rdv.heureCreation);
    
    printf("\n=== CRÉATION D'UN RENDEZ-VOUS ===\n");
    printf("📅 Créé le: %s à %s\n\n", rdv.dateCreation, rdv.heureCreation);
    
    afficherPatients();
    printf("\nID patient: ");
    scanf("%d", &rdv.idPatient);
    
    if (!patientExiste(rdv.idPatient)) {
        printf("\n❌ Patient inexistant!\n");
        return;
    }
    
    afficherMedecins();
    printf("\nID médecin: ");
    scanf("%d", &rdv.idMedecin);
    
    if (!medecinExiste(rdv.idMedecin)) {
        printf("\n❌ Médecin inexistant!\n");
        return;
    }
    
    printf("\n--- Planification ---\n");
    printf("Date RDV (JJ/MM/AAAA): ");
    scanf("%s", rdv.dateRDV);
    printf("Heure RDV (HH:MM): ");
    scanf("%s", rdv.heureRDV);
    viderBuffer();
    
    if (!creneauLibre(rdv.idMedecin, rdv.dateRDV, rdv.heureRDV)) {
        printf("\n❌ Créneau occupé!\n");
        return;
    }
    
    printf("Motif: ");
    fgets(rdv.motif, 100, stdin);
    rdv.motif[strcspn(rdv.motif, "\n")] = 0;
    
    rendezVous[nbRendezVous++] = rdv;
    
    printf("\n✅ RDV créé!\n");
    printf("   ID: %d\n", rdv.id);
    printf("   Créé: %s %s\n", rdv.dateCreation, rdv.heureCreation);
    printf("   Prévu: %s %s\n", rdv.dateRDV, rdv.heureRDV);
}

void afficherRendezVous() {
    if (nbRendezVous == 0) {
        printf("\n❌ Aucun RDV.\n");
        return;
    }
    
    printf("\n=== LISTE DES RENDEZ-VOUS (%d) ===\n", nbRendezVous);
    printf("%-3s %-10s %-10s %-11s %-6s %-11s %-6s %-15s\n", 
           "ID", "Patient", "Médecin", "Créé le", "à", "RDV le", "à", "Motif");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < nbRendezVous; i++) {
        char nomPatient[50] = "?";
        char nomMedecin[50] = "?";
        
        for (int j = 0; j < nbPatients; j++) {
            if (patients[j].id == rendezVous[i].idPatient) {
                strcpy(nomPatient, patients[j].nom);
                break;
            }
        }
        
        for (int j = 0; j < nbMedecins; j++) {
            if (medecins[j].id == rendezVous[i].idMedecin) {
                strcpy(nomMedecin, medecins[j].nom);
                break;
            }
        }
        
        printf("%-3d %-10s %-10s %-11s %-6s %-11s %-6s %-15s\n",
               rendezVous[i].id, nomPatient, nomMedecin,
               rendezVous[i].dateCreation, rendezVous[i].heureCreation,
               rendezVous[i].dateRDV, rendezVous[i].heureRDV, 
               rendezVous[i].motif);
    }
}

void afficherRendezVousParMedecin() {
    int idMedecin;
    int trouve = 0;
    
    printf("\n=== RDV PAR MÉDECIN ===\n");
    afficherMedecins();
    printf("\nID médecin: ");
    scanf("%d", &idMedecin);
    viderBuffer();
    
    printf("\n%-3s %-10s %-11s %-6s %-11s %-6s %-15s\n", 
           "ID", "Patient", "Créé le", "à", "RDV le", "à", "Motif");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < nbRendezVous; i++) {
        if (rendezVous[i].idMedecin == idMedecin) {
            char nomPatient[50] = "?";
            for (int j = 0; j < nbPatients; j++) {
                if (patients[j].id == rendezVous[i].idPatient) {
                    strcpy(nomPatient, patients[j].nom);
                    break;
                }
            }
            printf("%-3d %-10s %-11s %-6s %-11s %-6s %-15s\n",
                   rendezVous[i].id, nomPatient,
                   rendezVous[i].dateCreation, rendezVous[i].heureCreation,
                   rendezVous[i].dateRDV, rendezVous[i].heureRDV, 
                   rendezVous[i].motif);
            trouve = 1;
        }
    }
    
    if (!trouve) printf("❌ Aucun RDV pour ce médecin.\n");
}

void afficherRendezVousParDate() {
    char date[11];
    int trouve = 0;
    
    printf("\n=== RDV PAR DATE ===\n");
    printf("Date (JJ/MM/AAAA): ");
    scanf("%s", date);
    viderBuffer();
    
    printf("\n%-3s %-10s %-10s %-6s %-15s\n", 
           "ID", "Patient", "Médecin", "Heure", "Motif");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < nbRendezVous; i++) {
        if (strcmp(rendezVous[i].dateRDV, date) == 0) {
            char nomPatient[50] = "?";
            char nomMedecin[50] = "?";
            
            for (int j = 0; j < nbPatients; j++) {
                if (patients[j].id == rendezVous[i].idPatient) {
                    strcpy(nomPatient, patients[j].nom);
                    break;
                }
            }
            
            for (int j = 0; j < nbMedecins; j++) {
                if (medecins[j].id == rendezVous[i].idMedecin) {
                    strcpy(nomMedecin, medecins[j].nom);
                    break;
                }
            }
            
            printf("%-3d %-10s %-10s %-6s %-15s\n",
                   rendezVous[i].id, nomPatient, nomMedecin,
                   rendezVous[i].heureRDV, rendezVous[i].motif);
            trouve = 1;
        }
    }
    
    if (!trouve) printf("❌ Aucun RDV à cette date.\n");
}

void statistiquesRendezVous() {
    if (nbMedecins == 0 || nbRendezVous == 0) {
        printf("\n❌ Données insuffisantes.\n");
        return;
    }
    
    printf("\n=== STATISTIQUES ===\n");
    printf("%-12s %-15s %-8s\n", "Médecin", "Spécialité", "Nb RDV");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < nbMedecins; i++) {
        int count = 0;
        for (int j = 0; j < nbRendezVous; j++) {
            if (rendezVous[j].idMedecin == medecins[i].id) {
                count++;
            }
        }
        printf("%-12s %-15s %-8d\n", 
               medecins[i].nom, medecins[i].specialite, count);
    }
    
    printf("\nTotal: %d rendez-vous\n", nbRendezVous);
}

void annulerRendezVous() {
    int id;
    printf("\n=== ANNULATION D'UN RDV ===\n");
    afficherRendezVous();
    printf("\nID du RDV à annuler: ");
    scanf("%d", &id);
    viderBuffer();
    
    for (int i = 0; i < nbRendezVous; i++) {
        if (rendezVous[i].id == id) {
            for (int j = i; j < nbRendezVous - 1; j++) {
                rendezVous[j] = rendezVous[j + 1];
            }
            nbRendezVous--;
            printf("\n✅ RDV annulé!\n");
            return;
        }
    }
    printf("\n❌ RDV introuvable!\n");
}

void menuRendezVous() {
    int choix;
    
    do {
        clearScreen();
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║         GESTION DES RENDEZ-VOUS           ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("\n1. Créer un RDV\n2. Afficher tous les RDV\n");
        printf("3. RDV par médecin\n4. RDV par date\n");
        printf("5. Statistiques\n6. Annuler un RDV\n0. Retour\n");
        printf("\nChoix: ");
        scanf("%d", &choix);
        viderBuffer();
        
        switch(choix) {
            case 1: creerRendezVous(); break;
            case 2: afficherRendezVous(); break;
            case 3: afficherRendezVousParMedecin(); break;
            case 4: afficherRendezVousParDate(); break;
            case 5: statistiquesRendezVous(); break;
            case 6: annulerRendezVous(); break;
            case 0: break;
            default: printf("\n❌ Choix invalide!\n");
        }
        
        if (choix != 0) pause_ecran();
        
    } while(choix != 0);
}