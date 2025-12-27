#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"
#include "utils.h"

Utilisateur utilisateurs[MAX_USERS];
int nbUtilisateurs = 0;
char utilisateurConnecte[30] = "";
char roleConnecte[20] = "";

void initialiserUtilisateurs() {
    // Compte admin par défaut
    strcpy(utilisateurs[0].username, "admin");
    strcpy(utilisateurs[0].password, "admin123");
    strcpy(utilisateurs[0].role, "admin");
    utilisateurs[0].actif = 1;
    
    // Compte utilisateur par défaut
    strcpy(utilisateurs[1].username, "user");
    strcpy(utilisateurs[1].password, "user123");
    strcpy(utilisateurs[1].role, "user");
    utilisateurs[1].actif = 1;
    
    nbUtilisateurs = 2;
}

int authentifier() {
    char username[30];
    char password[50];
    int tentatives = 0;
    
    while (tentatives < 3) {
        clearScreen();
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║        AUTHENTIFICATION REQUISE           ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("\nNom d'utilisateur: ");
        scanf("%s", username);
        printf("Mot de passe: ");
        scanf("%s", password);
        
        for (int i = 0; i < nbUtilisateurs; i++) {
            if (strcmp(utilisateurs[i].username, username) == 0 &&
                strcmp(utilisateurs[i].password, password) == 0 &&
                utilisateurs[i].actif == 1) {
                strcpy(utilisateurConnecte, username);
                strcpy(roleConnecte, utilisateurs[i].role);
                printf("\n✅ Connexion réussie! Bienvenue %s (%s)\n", username, roleConnecte);
                pause_ecran();
                return 1;
            }
        }
        
        tentatives++;
        printf("\n❌ Identifiants incorrects! Tentatives restantes: %d\n", 3 - tentatives);
        if (tentatives < 3) pause_ecran();
    }
    
    printf("\n🔒 Trop de tentatives échouées. Accès bloqué.\n");
    return 0;
}

void ajouterUtilisateur() {
    if (!estAdmin()) {
        printf("\n❌ Accès refusé! Réservé aux administrateurs.\n");
        return;
    }
    
    if (nbUtilisateurs >= MAX_USERS) {
        printf("\n❌ Nombre maximum d'utilisateurs atteint!\n");
        return;
    }
    
    Utilisateur u;
    printf("\n=== AJOUT D'UN UTILISATEUR ===\n");
    printf("Nom d'utilisateur: ");
    scanf("%s", u.username);
    
    // Vérifier si l'utilisateur existe déjà
    for (int i = 0; i < nbUtilisateurs; i++) {
        if (strcmp(utilisateurs[i].username, u.username) == 0) {
            printf("\n❌ Ce nom d'utilisateur existe déjà!\n");
            return;
        }
    }
    
    printf("Mot de passe: ");
    scanf("%s", u.password);
    printf("Rôle (admin/user): ");
    scanf("%s", u.role);
    u.actif = 1;
    
    utilisateurs[nbUtilisateurs] = u;
    nbUtilisateurs++;
    
    printf("\n✅ Utilisateur ajouté avec succès!\n");
}

void afficherUtilisateurs() {
    if (!estAdmin()) {
        printf("\n❌ Accès refusé! Réservé aux administrateurs.\n");
        return;
    }
    
    printf("\n=== LISTE DES UTILISATEURS ===\n");
    printf("%-20s %-15s %-10s\n", "Username", "Rôle", "Statut");
    printf("-----------------------------------------------\n");
    
    for (int i = 0; i < nbUtilisateurs; i++) {
        printf("%-20s %-15s %-10s\n", 
               utilisateurs[i].username, 
               utilisateurs[i].role,
               utilisateurs[i].actif ? "Actif" : "Inactif");
    }
}

void modifierMotDePasse() {
    char ancienMdp[50];
    char nouveauMdp[50];
    char confirmation[50];
    
    printf("\n=== MODIFIER MON MOT DE PASSE ===\n");
    printf("Ancien mot de passe: ");
    scanf("%s", ancienMdp);
    
    for (int i = 0; i < nbUtilisateurs; i++) {
        if (strcmp(utilisateurs[i].username, utilisateurConnecte) == 0) {
            if (strcmp(utilisateurs[i].password, ancienMdp) != 0) {
                printf("\n❌ Ancien mot de passe incorrect!\n");
                return;
            }
            
            printf("Nouveau mot de passe: ");
            scanf("%s", nouveauMdp);
            printf("Confirmer le nouveau mot de passe: ");
            scanf("%s", confirmation);
            
            if (strcmp(nouveauMdp, confirmation) != 0) {
                printf("\n❌ Les mots de passe ne correspondent pas!\n");
                return;
            }
            
            strcpy(utilisateurs[i].password, nouveauMdp);
            printf("\n✅ Mot de passe modifié avec succès!\n");
            return;
        }
    }
}

int estAdmin() {
    return strcmp(roleConnecte, "admin") == 0;
}

void menuSecurite() {
    int choix;
    
    do {
        clearScreen();
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║         GESTION DE LA SÉCURITÉ            ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("\n1. Ajouter un utilisateur (Admin)\n");
        printf("2. Afficher les utilisateurs (Admin)\n");
        printf("3. Modifier mon mot de passe\n");
        printf("0. Retour\n");
        printf("\nVotre choix: ");
        scanf("%d", &choix);
        
        switch(choix) {
            case 1: ajouterUtilisateur(); break;
            case 2: afficherUtilisateurs(); break;
            case 3: modifierMotDePasse(); break;
            case 0: break;
            default: printf("\n❌ Choix invalide!\n");
        }
        
        if (choix != 0) pause_ecran();
        
    } while(choix != 0);
}