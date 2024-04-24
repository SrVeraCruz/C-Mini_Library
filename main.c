#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NOEUD{
    int ISBN;
    char *Titre;
    int Stock;
    struct NOEUD *suivant;
};

typedef struct NOEUD LIVRE;

typedef struct{
    LIVRE *debut;
} LSC;

struct client{
    char *Nom;
    char *Contact;
    int CI;
};

typedef struct client CLIENT;

typedef struct {
    CLIENT *p;
    LSC ISBN;
    int Qte;
}VENTE;

typedef struct{
    LIVRE *debut;
} LSC_v;

void initialise(LSC *liste);
void remplir(LIVRE *newLivre, int ISBN, int Stock, char *Titre);
void remplir_client(CLIENT *client, char *Nom, char *tel, int CI);
void ajouterLivre(LSC *liste, int ISBN, int Stock, char *Titre);
void afficher(LIVRE *livre);
void afficherListe(LSC *liste);
LIVRE* chercher(LSC *liste, int ISBN);
int position(LSC *liste, int ISBN);
int quantite(LSC *liste, int ISBN);
void vendre(LSC *liste, int ISBN);
void vendre_2(CLIENT *Client, LIVRE *livre, int Qte, LSC *ISBN, VENTE *Vente);
void supprimerSiVide(LIVRE *livre);
void supprimerToutVide(LSC *liste);

int main()
{
    LSC *liste = (LSC*)malloc(sizeof(LSC));
    initialise(liste);
    LIVRE *post;
    int num, ISBN, Stock, pos, quant;
    char *Titre,titre[20];

    ajouterLivre(liste,1,2,"Matlab");
    ajouterLivre(liste,2,5,"Ruby");
    ajouterLivre(liste,3,2,"Algorithme");
    ajouterLivre(liste,4,3,"Base de Donnes");
    ajouterLivre(liste,5,2,"Programation");
    ajouterLivre(liste,6,1,"Poo");
    ajouterLivre(liste,7,1,"Python");
    ajouterLivre(liste,8,9,"C++");
    ajouterLivre(liste,9,8,"Java");



    do{
        printf("*********************************************\n");
        printf("* Pour ajouter un livre a la Librerie:----1 *\n");
        printf("* Pour chercher la position d'un livre:---2 *\n");
        printf("* Pour savoir la quantite d'un livre:-----3 *\n");
        printf("* Pour vendre un livre:-------------------4 *\n");
        printf("* Pour afficher un livre:-----------------5 *\n");
        printf("* Pour afficher tous les livres:----------6 *\n");
        printf("* Pour supprimir les livres vide:---------7 *\n");
        printf("* Pour annuler:---------------------------0 *\n");
        printf("*********************************************\n");

        printf("Entrer un numero: ");
        scanf("%d", &num);
        printf("*********************************************\n");


        switch(num){
        case 1:
            system("cls");
            printf("Pour ajouter a la Librerie\n\n");
            printf("Entrer la cle primaire: ");
            scanf("%d", &ISBN);
            printf("Entrer la quantite du livre: ");
            scanf("%d", &Stock);
            fflush(stdin);
            printf("Entrer son titre: ");
            gets(titre);
            Titre = (char*)malloc(strlen(titre)+1);
            strcpy(Titre, titre);
            fflush(stdin);
            ajouterLivre(liste,ISBN,Stock,Titre);
            printf("\nAjoute avec succes!!! \n\n");
            break;
        case 2:
            system("cls");
            printf("Pour chercher la position d'un livre:\n\n");
            printf("Entrer id du livre a chercher la position: ");
            scanf("%d", &ISBN);
            pos = position(liste,ISBN);
            if(pos == -1){
                printf("\nLe livre n'existe pas.\n");
            }
            else{
                printf("\nLe livre %d est a la position %d.\n", ISBN, pos);
            }
            printf("\n");
            break;
        case 3:
            system("cls");
            printf("Pour savoir la quantite d'un livre:\n\n");
            printf("Entrer id du livre a chercher la quantite: ");
            scanf("%d", &ISBN);
            quant = quantite(liste,ISBN);
            if(quant == -1){
                printf("\nLe livre n'existe pas.\n");
            }
            else{
                printf("\nLa quantite du livre %d est %d.\n", ISBN, quant);
            }
            printf("\n");
            break;
        case 4:
            system("cls");
            printf("Pour vendre un livre:\n\n");
            printf("Entrer id du livre a vendre: ");
            scanf("%d", &ISBN);
            post = chercher(liste,ISBN);
            if(post == NULL){
                printf("\nLe livre n'existe pas.\n");
                break;
            }
            else{
                vendre(liste,ISBN);
                printf("\nLa quantite du livre %s (ISBN = %d) est %d.\n", post->Titre, post->ISBN, post->Stock);
            }
            printf("\n");
            break;
        case 5:
            system("cls");
            printf("Pour afficher un livre:\n\n");
            printf("Entrer id du afficher: ");
            scanf("%d", &ISBN);
            post = chercher(liste,ISBN);
            if(post == NULL){
                printf("\nLe livre n'existe pas.\n");
            }
            else{
                afficher(post);
            }
            printf("\n");
            break;
        case 6:
            system("cls");
            printf("Pour afficher tout livre:\n\n");
            if(liste->debut == NULL){
                printf("Librerie est vide.");
            }
            else{
                afficherListe(liste);
            }
            printf("\n");
            break;
        case 7:
            system("cls");
            printf("Pour supprimir les livres vides:\n\n");
            supprimerToutVide(liste);
            printf("\nLibrairie mise a jour.\n");
            printf("\n");
            break;
        case 0:
            system("cls");
            printf("*********************************************\n");
            printf("        Vouz avez annule l'operation");
            break;
        default:
            system("cls");
        }
    }while(num != 0);
    printf("\n");
    printf("*********************************************\n");
    printf("*        Merci pour votre attention         *\n");
    printf("*********************************************\n");



    return 0;
}

void initialise(LSC *liste)
{
    liste->debut = NULL;
}

void remplir(LIVRE *newLivre, int ISBN, int Stock, char *Titre)
{
    newLivre->ISBN = ISBN;
    newLivre->Stock = Stock;
    newLivre->Titre = (char*)malloc(strlen(Titre)+1);
    strcpy(newLivre->Titre, Titre);
    newLivre->suivant = NULL;
}

void ajouterLivre(LSC *liste, int ISBN, int Stock, char *Titre)
{
    LIVRE *newLivre = (LIVRE*)malloc(sizeof(LIVRE));
    remplir(newLivre, ISBN, Stock, Titre);

    if (liste->debut == NULL)
    {
        liste->debut = newLivre;
    }

    else
    {
        LIVRE *pos = chercher(liste, newLivre->ISBN);
        if(pos != NULL)
        {
            pos->Stock += newLivre->Stock;
            return;
        }
        if(newLivre->Stock <= 1)
        {
            newLivre->suivant = liste->debut;
            liste->debut = newLivre;
        }
        else
        {
            LIVRE *courant;
            courant = liste->debut;

            while(courant->suivant != NULL)
            {
                courant = courant->suivant;
            }
            courant->suivant = newLivre;
        }
    }
}

void afficher(LIVRE *livre)
{
    printf("ISBN = %d || STOCK = %d || TITRE = %s \n",livre->ISBN, livre->Stock, livre->Titre);
}

void afficherListe(LSC *liste)
{
    LIVRE *courant;
    courant = liste->debut;

    while(courant != NULL)
    {
        afficher(courant);
        courant = courant->suivant;
    }
}

LIVRE* chercher(LSC *liste, int ISBN)
{
    LIVRE *courant = liste->debut;

    while(courant != NULL)
    {
        if(ISBN == courant->ISBN)
        {
            return courant;

        }
        courant = courant->suivant;
    }
    return NULL;
}

int position(LSC *liste, int ISBN)
{
    LIVRE *courant;
    courant = liste->debut;
    int position = 0;

    while(courant != NULL)
    {
        position++;
        if(ISBN == courant->ISBN)
        {
            return position;
        }
        courant = courant->suivant;
    }
    return -1;
}

int quantite(LSC *liste, int ISBN)
{
    LIVRE *position;
    position = chercher(liste, ISBN);

    if(position != NULL)
    {
        return position->Stock;
    }
    return -1;
}

void vendre(LSC *liste, int ISBN)
{
    LIVRE *position;
    position = chercher(liste, ISBN);
    if(position != NULL && position->Stock > 0)
    {
        position->Stock--;
        if(position->Stock == 0)
        {
            supprimerToutVide(liste);
        }
        printf("\nVendu avec succes.\n");
    }
}

void remplir_client(CLIENT *client, char *Nom, char *tel, int CI)
{
    client->Nom = malloc(strlen(Nom)+1);
    client->Contact = malloc(strlen(tel)+1);
    client->CI = CI;

}

void vendre_2(CLIENT *Client, LIVRE *livre, int Qte, LSC *ISBN, VENTE *Vente)
{
    if(livre->Stock >= Qte)
    {
        livre->Stock -= Qte;
        if(livre->Stock == 0)
        {
            supprimerSiVide(livre);
        }

        Vente->Qte += Qte;
        if(ISBN->debut == NULL)
        {
            ISBN->debut = livre;
        }
        else
        {
            LIVRE *courant = ISBN->debut;
            while(courant->suivant != NULL)
            {
                courant = courant->suivant;
            }
            courant->suivant = livre;
        }
        Vente->p = Client;
    }
}

void supprimerSiVide(LIVRE *livre)
{
    if(livre->Stock == 0)
    {
        LIVRE *suprime;
        suprime = livre;
        livre = livre->suivant;
        free(suprime);
    }
}

void supprimerToutVide(LSC *liste)
{
    LIVRE *courant;
    LIVRE *precedent = NULL;
    courant = liste->debut;

    while(courant != NULL)
    {
        if(quantite(liste, courant->ISBN) == 0)
        {
            if(courant == liste->debut)
            {
                liste->debut = courant->suivant;

            }
            else
            {
                precedent->suivant = courant->suivant;
            }
        }
        else
        {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}
