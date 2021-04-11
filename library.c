//
// Created by aladdin on 3/20/21.
//
#include <stdio.h>
// Remarque1 : chaque fonction prend en parametre l'indice i et retourne le i-eme coordonne de vecteur.
// Remarque2 : i doit etre dans l'intervalle [1,10].
// Remarque3 : le calcule des sommes et produits est fait en respectant la convention :
    /*
    * Soit I un ensemble fini, et (xi)i∈I une famille de nombres complexes.
    * Si I est vide, on convient que ∑xi = 0 pour i dans I et ∏xi = 1.
    * */
#pragma region 1.3) les bornes de ri~

//vecteur N
double N(double r[10], double p[10], int d,double k[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    // calculer le produit de terme rj/(rj+pj) avec j varie de 0 a i-1
    double produit = 1;
    //si i dans l'intervalle [1,9]
    int j;
    for (j = 0; j <= i-1; j++) {
        produit = produit * (r[j]/(r[j]+p[j]));
    }

    // calculer l'expression ((ri+pi)/riki)*d
    double expression = ((r[i]+p[i])/r[i]*k[i])*d;

    // la comparaison
    if (produit >= expression) return produit;
    else return expression;
}

//vecteur M
double M(double r[10], double p[10], double andes, int n, int i) {
    //decrementer i et n par 1, parceque l'indexation des tableaux commence par 0
    i--;
    n--;
    // calculer le produit de terme ((rj+pj)/rj)*andes avec j varie de i a n
    double produit = 1;
    int j;
    for (j = i; j <= n; j++) {
        produit = produit * ((r[j]+p[j])/r[j])*andes;
    }

    //la comparaison
    if (produit <= 1) return produit;
    else return 1;
}

//vecteur a
double a(double r[10], double p[10], double M[10], double N [10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    double nominateur = ((1-M[i])/M[i])*r[i];
    double dominateur = ((1-N[i])/N[i])*r[i] + p[i];
    return nominateur/dominateur;
}

//vecteur b
double b(double r[10], double p[10], double M[10], double N [10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    double nominateur = p[i]*r[i];
    double dominateur = ((1-N[i])/N[i])*r[i] + p[i];
    return nominateur/dominateur;
}

//vecteur c
double c(double r[10], double p[10], double M[10], double N [10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    double nominateur = ((1-N[i])/N[i])*r[i];
    double dominateur = ((1-M[i])/M[i])*r[i] + p[i];
    return nominateur/dominateur;
}

//vecteur e
double e(double r[10], double p[10], double M[10], double N [10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    double nominateur = p[i]*r[i];
    double dominateur = ((1-M[i])/M[i])*r[i] + p[i];
    return nominateur/dominateur;
}

//borne inferieur de ri~ definie dans (10)
double borneInf_10(double a[10], double r[10], double b[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    //claculer le produit de terme aj avec j varie de 1 a i
    int j;
    double produit = 1;
    for (j = 1; j <= i; j++) {
        produit = produit * a[j];
    }
    produit = produit * r[0];

    //calculer la 2eme terme de l'expression, j vaire de 1 a i-1
    double sum = 0;
    for (j = 1; j <= i-1; j++) {
        int k;
        //calculer le produit, k varie de i jusqu'a j+1
        double tmp = 1;
        for (k = i; k <= j+1; k++) {
            tmp = tmp * a[k];
        }
        tmp = tmp * b[j];
        sum = sum + tmp;
    }

    // sommer ler 3 termes et retourner la valeur
    return produit + sum + b[i];
}

//borne superieur de ri~ definie dans (10)
double borneSup_10(double c[10], double r[10], double e[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    //claculer le produit de terme cj avec j varie de 1 a i
    int j;
    double produit = 1;
    for (j = 1; j <= i; j++) {
        produit = produit * c[j];
    }
    produit = produit * r[0];

    //calculer la 2eme terme de l'expression, j vaire de 1 c i-1
    double sum = 0;
    for (j = 1; j <= i-1; j++) {
        int k;
        //calculer le produit, k varie de i jusqu'a j+1
        double tmp = 1;
        for (k = i; k <= j+1; k++) {
            tmp = tmp * c[k];
        }
        tmp = tmp * e[j];
        sum = sum + tmp;
    }

    // sommer ler 3 termes et retourner la valeur
    return produit + sum + e[i];
}

//vecteur p~
double ptide(double p[10], double r[10], double rtide[10],double a[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    return (((p[i]+r[i])/(a[i-1]*r[i]))-1)*rtide[i];
}

//vecteur q
double q(double lambda[10], double beta[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    if (i == 1) return 0.1;
    else return (1-lambda[i-1])*q(lambda, beta, i-1)*(1+beta[i]) + beta[i];
}

//vecteur d~
double dtide(double q[10], double lambda[10], int n, int d, int i) {
    //decrementer i et n par 1, parceque l'indexation des tableaux commence par 0
    i--;
    n--;
    //calculer le produit de terme (1+lambdaj*qj), j varie de i a n
    double produit = 1;
    int j;
    for (j = i; j < n; j++) {
        produit = produit*(1 + lambda[j]*q[j]);
    }

    return d*produit;
}

//borne inferieur de ri~ definie dans (7)
double borneInf_7(double a[10], double rtide[10], double b[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    return a[i]*rtide[i-1] + b[i];
}

//borne superieur de ri~ definie dans (7)
double borneSup_7(double a[10], double rtide[10], double b[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    return a[i]*rtide[i-1] + b[i];
}


#pragma endregion

