#ifndef AUTH_H
#define AUTH_H

#define MAX_USERS 10

typedef struct {
    char username[30];
    char password[50];
    char role[20]; // "admin" ou "user"
    int actif;
} Utilisateur;

extern Utilisateur utilisateurs[MAX_USERS];
extern int nbUtilisateurs;
extern char utilisateurConnecte[30];
extern char roleConnecte[20];

void initialiserUtilisateurs();
int authentifier();
void ajouterUtilisateur();
void afficherUtilisateurs();
void modifierMotDePasse();
int estAdmin();
void menuSecurite();

#endif