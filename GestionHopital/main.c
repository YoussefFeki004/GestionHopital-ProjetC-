#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "auth.h"
#include "patient.h"
#include "medecin.h"
#include "rendezvous.h"

void afficherMenuPrincipal() {
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║   SYSTÈME DE GESTION D'HÔPITAL 🏥         ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("\nConnecté: %s (%s)\n", utilisateurConnecte, roleConnecte);
    printf("\n┌─────────────────────────────────────────┐\n");
    printf("│  1. Gestion des Patients               │\n");
    printf("│  2. Gestion des Médecins               │\n");
    printf("│  3. Gestion des Rendez-vous            │\n");
    printf("│  4. Sécurité & Utilisateurs            │\n");
    printf("│  0. Déconnexion                        │\n");
    printf("└─────────────────────────────────────────┘\n");
    printf("\nChoix: ");
}

int main() {
    int choix;
    
    // Initialisation du système de sécurité
    initialiserUtilisateurs();
    
    // Authentification obligatoire
    if (!authentifier()) {
        printf("\nFermeture du programme...\n");
        return 1;
    }
    
    // Boucle principale
    do {
        clearScreen();
        afficherMenuPrincipal();
        scanf("%d", &choix);
        viderBuffer();
        
        switch(choix) {
            case 1:
                menuPatients();
                break;
            case 2:
                menuMedecins();
                break;
            case 3:
                menuRendezVous();
                break;
            case 4:
                menuSecurite();
                break;
            case 0:
                printf("\n👋 Déconnexion... Au revoir %s!\n", utilisateurConnecte);
                break;
            default:
                printf("\n❌ Choix invalide!\n");
                pause_ecran();
        }
        
    } while(choix != 0);
    
    return 0;
}