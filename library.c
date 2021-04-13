#include <math.h>

// Remarque : le calcule des sommes et produits est fait en respectant la convention :
    /*
    * Soit I un ensemble fini, et (xi)i∈I une famille de nombres complexes.
    * Si I est vide, on convient que ∑xi = 0 pour i dans I et ∏xi = 1.
    * */


#pragma region 1.1) T(i)
// Remarque : chaque fonction prend en parametre l'indice i et retourne le i-eme coordonne de vecteur.
// Remarque : i doit etre dans l'intervalle [1,9].
//vecteur alpha
double alpha(double r[10], double rtilde[10], double p[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    return r[i+1]*(rtilde[i+1]-rtilde[i]) + p[i+1]*(r[i+1]-rtilde[i+1]);
}

//vecteur E
double E(double alpha[10], double ptild[10], double p[10],double dtilde[10], double rtilde[10], double k[10], double r[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    double nominateur = alpha[i]*ptild[i]*(alpha[i]*(ptild[i]+rtilde[i])*dtilde[i] - k[i]*rtilde[i]*r[i+1]*(rtilde[i+1]-rtilde[i]));
    double dominateur = rtilde[i]*(ptild[i]+rtilde[i])*p[i+1]*(r[i+1]-rtilde[i+1])*(k[i]*r[i+1]*(rtilde[i+1]-rtilde[i])-dtilde[i]*alpha[i]);
    return nominateur/dominateur;
}

//vecteur D
double D(double ptilde[10], double dtilde[10], double rtilde[10], double alpha[10],double k[10], double r[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    double nominateur = ptilde[i]*dtilde[i];
    double dominateur = rtilde[i]*(k[i]*((r[i+1]*(rtilde[i+1]-rtilde[i]))/alpha[i])-dtilde[i]);
    return nominateur/dominateur;
}

//vecteur C
double C(double k[10],double ptilde[10], double dtilde[10], double r[10], double rtilde[10], double p[10], double alpha[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    double nominateur = ((k[i]-dtilde[i])*r[i+1]*(rtilde[i+1]-rtilde[i])-dtilde[i]*p[i+1]*(r[i+1]-rtilde[i+1]))*dtilde[i]*alpha[i]*(dtilde[i]*(ptilde[i]+rtilde[i])-k[i]*rtilde[i]);
    double dominateur = pow(dtilde[i]*(ptilde[i]+rtilde[i])*alpha[i]-k[i]*rtilde[i]*r[i+1]*(rtilde[i+1]-rtilde[i]),2);
    return nominateur/dominateur;
}

//vecteur B
double B(double k[10], double ptilde[10],double p[10], double r[10], double rtilde[10], double dtilde[10],double alpha[10], double d[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    double nominateur = k[i]*p[i+1]*(r[i+1]-rtilde[i+1]);
    double dominateur = ((rtilde[i] + ptilde[i]) * alpha[i] - (k[i] * rtilde[i] * r[i + 1] * (rtilde[i + 1] - rtilde[i])) / dtilde[i]);
    return nominateur / dominateur;
}

//vecteur A
double A(double k[10], double ptilde[10], double rtilde[10], double r[10], double alpha[10], double dtilde[10],int i) {
    double nominateur = k[i]*ptilde[i];
    double dominateur = pow(ptilde[i]+rtilde[i], 2) - ((k[i]*rtilde[i]*r[i+1]*(rtilde[i]+ptilde[i])*(rtilde[i+1]-rtilde[i])) / (dtilde[i]*alpha[i]));
    return nominateur / dominateur;
}

//vecteur T.  Remarque : juste les coordonnes d'indice entre 1 et 9, le n-eme cordonne est dans la partie 1.2)
double T(double A[10], double B[10], double C[10], double D[10], double E[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    return A[i] - B[i] - C[i] * log(D[i] - E[i]); // log : logaritmique neperien.
}

#pragma endregion


#pragma region 1.2) T(n)
//coordonne n-eme de T
double Tn(double k[10], double ptilde[10], MUn, double rtilde[10], double RHOn, double cp, double andes, int n) {
    //decrementer n par 1, parceque l'indexation des tableaux commence par 0
    n--;
    double terme1 = cp*(k[n]*((andes*(ptilde[n]+rtilde[n])-rtilde[n]) / ((ptilde[n]+rtilde[n]) * (1 - RHOn) * ptilde[n])));
    double terme2 = (((ptilde[n]+rtilde[n])*(1-andes)) / (MUn*pow(1 - RHOn,2)*ptilde[n]) - 1/(MUn*(1-RHOn))) * log((1/RHOn)*(1-((1-RHOn)/((1-andes)*((ptilde[n]+rtilde[n])/ptilde[n])))));
    return terme1 + terme2;
}

//RHOn
double RHOn(double *rtilde, double *k, double *dtilde, double *ptilde, int n, double andes) {
    //decrementer n par 1, parceque l'indexation des tableaux commence par 0
    n--;
    double nominateur = rtilde[n]*(k[n] - (dtilde[n]/andes));
    double dominateur = ptilde[n]*(dtilde[n]/andes);
    return nominateur / dominateur;
}

//MUn
double MUn(double *ptilde, double *k, double *dtilde, double andes, int n) {
    //decrementer n par 1, parceque l'indexation des tableaux commence par 0
    n--;
    double dominateur = k[n] - (dtilde[n] / andes);
    return ptilde[n]/dominateur;

}


#pragma endregion


#pragma region 1.3) les bornes de ri~
// Remarque : chaque fonction prend en parametre l'indice i et retourne le i-eme coordonne de vecteur.
// Remarque : i doit etre dans l'intervalle [1,10].
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
double ptilde(double p[10], double r[10], double rtilde[10],double a[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    return (((p[i]+r[i])/(a[i-1]*r[i]))-1)*rtilde[i];
}

//vecteur q
double q(double lambda[10], double beta[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    if (i == 1) return 0.1;
    else return (1-lambda[i-1])*q(lambda, beta, i-1)*(1+beta[i]) + beta[i];
}

//vecteur d~
double dtilde(double q[10], double lambda[10], int n, int d, int i) {
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
double borneInf_7(double a[10], double rtilde[10], double b[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    return a[i] * rtilde[i - 1] + b[i];
}

//borne superieur de ri~ definie dans (7)
double borneSup_7(double a[10], double rtide[10], double b[10], int i) {
    //decrementer i par 1, parceque l'indexation des tableaux commence par 0
    i--;
    return a[i]*rtide[i-1] + b[i];
}


#pragma endregion

