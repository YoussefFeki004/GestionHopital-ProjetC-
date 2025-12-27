#include <stdio.h>
#include <string.h>
#include "medecin.h"
#include "utils.h"

Medecin medecins[MAX_MEDECINS];
int nbMedecins = 0;

void ajouterMedecin() {
    if (nbMedecins >= MAX_MEDECINS) {
        printf("\n❌ Limite atteinte!\n");
        return;
    }
    
    Medecin m;
    m.id = nbMedecins + 1;
    
    printf("\n=== AJOUT D'UN MÉDECIN ===\n");
    printf("Nom: ");
    scanf("%s", m.nom);
    printf("Prénom: ");
    scanf("%s", m.prenom);
    printf("Spécialité: ");
    scanf("%s", m.specialite);
    printf("Téléphone: ");
    scanf("%s", m.telephone);
    viderBuffer();
    
    medecins[nbMedecins++] = m;
    printf("\n✅ Médecin ajouté! (ID: %d)\n", m.id);
}

void afficherMedecins() {
    if (nbMedecins == 0) {
        printf("\n❌ Aucun médecin.\n");
        return;
    }
    
    printf("\n=== LISTE DES MÉDECINS (%d) ===\n", nbMedecins);
    printf("%-4s %-12s %-12s %-15s %-12s\n", 
           "ID", "Nom", "Prénom", "Spécialité", "Téléphone");
    printf("----------------------------------------------------------\n");
    
    for (int i = 0; i < nbMedecins; i++) {
        printf("%-4d %-12s %-12s %-15s %-12s\n",
               medecins[i].id, medecins[i].nom, medecins[i].prenom,
               medecins[i].specialite, medecins[i].telephone);
    }
}

void filtrerMedecinsParSpecialite() {
    char specialite[50];
    int trouve = 0;
    
    printf("\n=== FILTRAGE PAR SPÉCIALITÉ ===\n");
    printf("Spécialité: ");
    scanf("%s", specialite);
    viderBuffer();
    
    printf("\n%-4s %-12s %-12s %-15s %-12s\n", 
           "ID", "Nom", "Prénom", "Spécialité", "Téléphone");
    printf("----------------------------------------------------------\n");
    
    for (int i = 0; i < nbMedecins; i++) {
        if (strcasecmp(medecins[i].specialite, specialite) == 0) {
            printf("%-4d %-12s %-12s %-15s %-12s\n",
                   medecins[i].id, medecins[i].nom, medecins[i].prenom,
                   medecins[i].specialite, medecins[i].telephone);
            trouve = 1;
        }
    }
    
    if (!trouve) printf("❌ Aucun résultat.\n");
}

void supprimerMedecin() {
    int id;
    printf("\n=== SUPPRESSION ===\n");
    afficherMedecins();
    printf("\nID à supprimer: ");
    scanf("%d", &id);
    viderBuffer();
    
    for (int i = 0; i < nbMedecins; i++) {
        if (medecins[i].id == id) {
            for (int j = i; j < nbMedecins - 1; j++) {
                medecins[j] = medecins[j + 1];
            }
            nbMedecins--;
            printf("\n✅ Médecin supprimé!\n");
            return;
        }
    }
    printf("\n❌ Médecin introuvable!\n");
}

int medecinExiste(int id) {
    for (int i = 0; i < nbMedecins; i++) {
        if (medecins[i].id == id) return 1;
    }
    return 0;
}

void menuMedecins() {
    int choix;
    
    do {
        clearScreen();
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║         GESTION DES MÉDECINS              ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("\n1. Ajouter\n2. Afficher\n3. Filtrer par spécialité\n");
        printf("4. Supprimer\n0. Retour\n");
        printf("\nChoix: ");
        scanf("%d", &choix);
        viderBuffer();
        
        switch(choix) {
            case 1: ajouterMedecin(); break;
            case 2: afficherMedecins(); break;
            case 3: filtrerMedecinsParSpecialite(); break;
            case 4: supprimerMedecin(); break;
            case 0: break;
            default: printf("\n❌ Choix invalide!\n");
        }
        
        if (choix != 0) pause_ecran();
        
    } while(choix != 0);
}