/**
 * 
 * \brief Programme pour générer et jouer une grille de Sudoku.
 * 
 * \author ROSELIER Lisa
 * 
 * \version 1.0
 * 
 * \date 03 décembre 2023
 * 
 * Ce programme permet de générer une grille de sudoku a partir 
 * d'un fichier puis d'y jouer en la complétant jusqu'à ce qu'elle 
 * soit pleine.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * 
 * \def N 
 * 
 * \brief Taille maximale d’un coté de carré de sudoku.
 * 
*/
#define N 3

/**
 * 
 * \def TAILLE
 * 
 * \brief Taille maximale d'un coté d'une grille de sudoku.
 * 
*/
#define TAILLE 9

/**
 * 
 * \typedef tGrille
 * 
 * \brief type tableau de TAILLE colonne(s) et TAILLE lignes(s). 
 * 
 * Le type tGrille sert a modeliser la grille de sudoku sous forme de 
 * tableau.
*/
typedef int tGrille[TAILLE][TAILLE]; 

void chargerGrille(tGrille g);
void ligne(); // utilisé dans afficherGrille()
void numeroColonne(); // utilisé dans afficherGrille()
void afficherGrille(tGrille g);
void saisir(int * val);
bool possible(tGrille g, int nbLigne, int nbColonne, int v); 
int sommeTotale(); //utilisé pour savoir si la grille est pleine ou non
int sommeGrille(tGrille g); //utilisé pour savoir si la grille est pleine ou non

/**
 * 
 * \fn int main()
 * 
 * \brief Programme principal.
 * 
 * \return Code de sortie du programme (0 : sortie normale).
 * 
 * Le pogramme princiaple traite quelques fontions et procédure 
 * servant au fonctionnement du jeu : 
 * Il charge la grille de sudoku, l'affiche, demande les coordonées 
 * de la case a jouer, vérifie si elle n'est pas pleine, demande la 
 * valeur a insérer, verifie qu'il est possible de l'insérer et repart de 
 * l'affichage de la grille jusqu'à quelle soit pleine.
*/
int main(){
    tGrille grille1;
    int numLigne, numColonne, valeur, somme, sommeT;
    chargerGrille(grille1);
    sommeT = sommeTotale();
    somme = sommeGrille(grille1);
    while (somme != sommeT){
        afficherGrille(grille1);
        printf("Indices de la case ? ");
        saisir(&numLigne);
        saisir(&numColonne);
        numLigne = numLigne - 1;
        numColonne = numColonne - 1; // lorsqu'ils sont saisi par le joueur ils peuvent être entre 1 et 9 alors que les indices de grilles sont entre 0 et 8 (d'ou le -1)
        if (grille1[numLigne][numColonne] != 0){
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        }else{
            printf("Valeur à insérer ? ");
            saisir(&valeur);
            
            if(possible(grille1, numLigne, numColonne, valeur)){
                grille1[numLigne][numColonne] = valeur;
                somme = somme + valeur;
            }
        }
        
    }
    printf("Grille pleine, fin de partie");
    return EXIT_SUCCESS;
}

/**
 * 
 * \fn void chargerGrille(tGrille g)
 * 
 * \brief Procédure qui charge la grille.
 * 
 * \param g : paramètre de sortie de type tGrille qui représente la grille du jeu.
 * 
 * Demande le fichier a charger et remplie le tableau g passé en 
 * paramètre.
*/
void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}

/**
 * 
 * \fn void numeroColonne()
 * 
 * \brief Procédure qui affiche les numéros de colonnes.
 * 
 * La procédure numeroColonne créee la première ligne qui sert de numérotation des 
 * colonnes de la grille. Elle les calcules en foction de la taille N de la grille. 
 * Cette procédure est utilisée dans afficherGrille(tGrille g).
*/
void numeroColonne(){
    int i, j, nb = 1;
    printf("      ");
    for(i=0; i<N; i++){ // répète N fois un 'bloc' de N colonne
        for(j=0; j<N; j++){ // numérote un 'bloc' de N colonne
            printf(" %d ", nb);
            nb++;
        }
        printf(" ");
    }
    printf("\n");
}

/**
 * 
 * \fn void ligne()
 * 
 * \brief Procédure qui qffiche les lignes séparant les lignes de carrées.
 * 
 * La procédure ligne créee les lignes composées de "-" et de "+" 
 * qui servent a séparer les lignes de carrées.
 * Cette procédure est utilisée dans afficherGrille(tGrille g).
*/
void ligne(){
    int i, j;
    printf("     ");
    for(i=0; i<N; i++){ // répète N fois un 'bloc' de N colonne
        printf("+");
        for(j=0; j<3*N; j++){ // délimite un 'bloc' de N colonne
            printf("-");
        }
    }
    printf("+\n");
}

/**
 * 
 * \fn void afficherGrille(tGrille g)
 * 
 * \brief Procédure qui qffiche les lignes séparant les lignes de carrées.
 * 
 * \param g : paramètre d'entrée de type tGrille qui représente la grille du jeu.
 * 
 * La procédure afficherGrille affiche la grille entière du jeu.
 * Cette procédure est utilise les procédures ligne() et numeroColonne().
*/
void afficherGrille(tGrille g){
    int x1, x2, y1, y2, nb = 1;
    numeroColonne();
    for(x1=0; x1<N; x1++){ // représente l'index de ligne des 3 carrée 
        ligne();
        for(x2=0; x2<N; x2++){ // représente l'index de ligne d'un carré 
            printf("  %d  ", nb);
            nb = nb + 1;
            for(y1=0 ; y1<N ; y1++){ // représente l'index de colonne des 3 carrée
                printf("|");
                for(y2=0; y2<N; y2++){ // représente l'index de colonne d'un carrée
                    if(g[x1*N + x2][y1*N + y2] == 0){
                        printf(" . ");
                    } else {
                        printf(" %d ", g[x1*N + x2][y1*N + y2]);
                    }
                }
            }
            printf("|\n");
        }
    }
    ligne();
}

/**
 * 
 * \fn void saisir(int * val)
 * 
 * \brief Procédure chargée de lire au clavier une valeur.
 * 
 * \param val : paramètre de sortie de type entier qui représente la valeur a saisir.
 * 
 * Cette procédure demande une valeur a insérer et vérifie qu'elle 
 * soit comprise entre 1 et la taille TAILLE de la grille.
*/
void saisir(int * val){ 
    char chaine[2];
    //printf("Entrez une valeur entière comprise entre 1 et %d: ", N*N);
    scanf("%s", chaine);
    sscanf(chaine, "%d", val);
    if(chaine[1] != 0){ //si la chaine de caractère a + de 2 valeurs, la saisie est forcément mauvaise car une valeur entre 1 et 9 ne comporte qu'un caractère
    //(sauf si TAILLE comporte 2 chiffres) et cela sert a régler pb de saisi d'un entier suivi de caractère (ex : "1test"), la variable val prendra pour valeur 1
    //alors que la saisie est fausse
        *val = 0;
    }
    while((*val <1) || (*val > N*N)){
        printf("Erreur\n");
        printf("Entrez une valeur entière comprise entre 1 et %d: \n", N*N);
        scanf("%s", chaine);
        sscanf(chaine, "%d", val);
        if(chaine[1] != 0){
            *val = 0;
        }
    }
}

/**
 * 
 * \fn bool possible(tGrille g, int numL, int numC, int val)
 * 
 * \brief Fonction chargée de vérifier que la valeur saisie est jouable dans la case chosie.
 * 
 * \param g : paramètre d'entrée de type tGrille qui représente la grille du jeu.
 * \param numL : paramètre d'entrée de type entier qui représente le numéro de ligne de la case choisie.
 * \param numC : paramètre d'entrée de type entier qui représente le numéro de colonne de la case choisie.
 * \param val : paramètre d'entrée de type entier représente la valeur saisie.
 * 
 * \return true si la valeur peux être jouée dans la case choisie, false sinon.
 * 
 * Cette fonction vérifie que la valeur saisie est jouable dans la case choisie :
 * elle vérifie que cette valeur n'est pas dans le même bloc (ou carée) que la case,
 * dans la même colonne que la case ou dans la même ligne que la case.
*/
bool possible(tGrille g, int numL, int numC, int val){
    bool result;
    int l, c, q1L, q2L, q1C, q2C; // l et c représente ligne et colonne
    result = true;
    for(l=0; l<TAILLE; l++){
        for(c=0; c<TAILLE; c++){
            if(g[l][c] == val){
                //vérification si la valeur n'est pas dans un bloc 
                q1L = (numL / N);       // les variables q sont des quotient,  elles donnent les coordonnées du bloc de N par N grâce au numéro de ligne et de colonne
                q2L = (l/N);            // ex : une grille de 9 lignes par 9 colonnes est donc composé de 3 bloc par 3 bloc
                q1C = (numC / N);       // dans ce programme, les blocs ont pour coordonnées : bloc(0 à N-1)(0 à N-1)
                q2C = (c/N);            
                if (q1L == q2L && q1C == q2C){ // on vérifie donc que les coordonnées de la case sélectionnée, sont les même que les coordonnées du bloc dans lequel il y a la valeur trouvée afin d'avertir qu'il y a déjà une valeur dans le bloc
                    printf("La valeur %d est déjà présente en colonne %d et en ligne %d. (même bloc)\n", val, c+1, l+1);
                    result = false;
                // vérification si la valeur n'est pas dans une ligne ou une colonne
                } else if(l == numL){
                    printf("La valeur %d est déjà présente en colonne %d et en ligne %d. (même ligne)\n", val, c+1, l+1);
                    result = false;
                } else if(c == numC){
                    printf("La valeur %d est déjà présente en colonne %d et en ligne %d. (même colonne)\n", val, c+1, l+1);
                    result = false;
                }
            }
        }
    }
    return result;
}

/**
 * 
 * \fn int sommeTotale()
 * 
 * \brief Fonction chargée de calculer la somme totale d'une grille de sudoku.
 * 
 * \return la somme totale de la grille.
 * 
 * Cette fonction calcule la somme totale des valeurs d'une grille de 
 * sudoku pleine en les ajoutant entre eux. Elle utilise seulement la 
 * constante TAILLE définie en début de programme.
*/
int sommeTotale(){
    int nb, sT;
    sT = 0;
    for(nb=0; nb<TAILLE; nb++){ // calcul la somme des valeurs d'un 'bloc' rempli (un bloc rempli a forcément toutes les valeur comprise entre 1 et TAILLE)
        sT = sT + (nb+1);
    }
    sT = sT * TAILLE;
    return sT;
}

/**
 * 
 * \fn int sommeTotale()
 * 
 * \brief Fonction chargée de calculer la somme totale d'une grille de sudoku.
 * 
 * \param g : paramètre d'entrée de type tGrille qui représente la grille du jeu.
 * 
 * \return la somme des valeurs de la grille passée en paramètre.
 * 
 * Cette fonction calcule la somme des valeurs de la grille de 
 * sudoku passée en paramètre en les ajoutant entre eux.
 * Cette fonction aide a savoir si la grille est pleine en la comparant 
 * avec las somme totale de la grille.
*/
int sommeGrille(tGrille g){
    int ligne, colonne, somme;
    somme = 0;
    for(ligne = 0; ligne<TAILLE; ligne++){
        for(colonne = 0; colonne<TAILLE; colonne++){
            somme = somme + g[ligne][colonne];
        }
    }
    return somme;
}