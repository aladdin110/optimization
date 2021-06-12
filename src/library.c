#include "library.h"

double preciser(double x) {
    int a =(int) (x * 10000) - ((int) (x * 1000)) * 10;

    int terme_1 = (int)x;
    double terme_2 = ((int) (x * 1000)) - terme_1 * 1000;
    if (a >= 5) terme_2++;

    return terme_1 + terme_2*0.001;
}



// Remarque : le calcule des sommes et produits est fait en respectant la convention :
    /*
    * Soit I un ensemble fini, et (xi)i∈I une famille de nombres complexes.
    * Si I est vide, on convient que ∑xi = 0 pour i dans I et ∏xi = 1.
    * */



#pragma region les donnees
double beta[10] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 , 0.1, 0.1};
double k[10] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
double p[10] = {0.1, 0.2, 0.3, 0.15, 0.1 , 0.25, 0.05, 0.27, 0.12, 0.18};
double r[10] = {0.8, 0.6, 0.7, 0.9, 0.85, 0.65, 0.75, 0.95, 0.85, 0.92};
#define n 10
int d = 1;
int cp = 1;
int cI = 2;

double andes = 0.95; // an**des
#pragma endregion

#pragma region 1.1) T(i)
// Remarque : chaque fonction retourne un vecteur de taille 9.
// Remarque : i doit etre dans l'intervalle [1,9].
//vecteur alpha
double *alpha(double rtilde[10], double *vect_alpha) {
    int i;
    for (i = 0; i < n-1; i++) {
        vect_alpha[i] = r[i+1]*(rtilde[i+1]-rtilde[i]) + p[i+1]*(r[i+1]-rtilde[i+1]);
    }
    return vect_alpha;
}

//vecteur E
double *E(double alpha[10], double ptilde[10], double dtilde[10], double rtilde[10], double *vect_E) {
    int i;
    for (i = 0; i < n-1; i++) {
        double nominateur = alpha[i]*ptilde[i] * (alpha[i]*(ptilde[i] + rtilde[i])*dtilde[i] - k[i] * rtilde[i] * r[i + 1] * (rtilde[i + 1] - rtilde[i]));
        double denominateur = rtilde[i] * (ptilde[i] + rtilde[i]) * p[i + 1] * (r[i + 1] - rtilde[i + 1]) * (k[i] * r[i + 1] * (rtilde[i + 1] - rtilde[i]) - dtilde[i] * alpha[i]);
        vect_E[i] = nominateur / denominateur;
    }
    return vect_E;
}

//vecteur D
double *D(double ptilde[10], double dtilde[10], double rtilde[10], double alpha[10], double *vect_D) {
    int i;
    for (i = 0; i < n-1; i++) {
        double nominateur = ptilde[i]*dtilde[i];
        double denominateur = rtilde[i] * (k[i] * ((r[i + 1] * (rtilde[i + 1] - rtilde[i])) / alpha[i]) - dtilde[i]);
        vect_D[i] = nominateur / denominateur;
    }
    return vect_D;
}

//vecteur C
double *C(double ptilde[10], double dtilde[10], double rtilde[10], double alpha[10], double *vect_C) {
    int i;
    for (i = 0; i < n-1; i++) {
        double nominateur = ((k[i]-dtilde[i])*r[i+1]*(rtilde[i+1]-rtilde[i])-dtilde[i]*p[i+1]*(r[i+1]-rtilde[i+1])) * dtilde[i]*alpha[i] * (dtilde[i]*(ptilde[i]+rtilde[i])-k[i]*rtilde[i]);
        double dominateur = pow(dtilde[i]*(ptilde[i]+rtilde[i])*alpha[i]-k[i]*rtilde[i]*r[i+1]*(rtilde[i+1]-rtilde[i]),2);
        vect_C[i] = nominateur/dominateur;
    }
    return vect_C;
}

//vecteur B
double *B(double ptilde[10], double rtilde[10], double dtilde[10], double alpha[10], double *vect_B) {
    int i;
    for (i = 0; i < n-1; i++) {
        double nominateur = k[i]*p[i+1]*(r[i+1]-rtilde[i+1]);
        double denominateur = ((rtilde[i] + ptilde[i]) * alpha[i]) - ((k[i] * rtilde[i] * r[i + 1] * (rtilde[i + 1] - rtilde[i])) / dtilde[i]);
        vect_B[i] = nominateur / denominateur;
    }
    return vect_B;
}

//vecteur A
double *A(double ptilde[10], double rtilde[10], double alpha[10], double dtilde[10], double *vect_A) {
    int i;
    for (i = 0; i < n-1; i++) {
        double nominateur = k[i]*ptilde[i];
        double denominateur = pow(ptilde[i] + rtilde[i], 2) - ((k[i] * rtilde[i] * r[i + 1] * (rtilde[i] + ptilde[i]) * (rtilde[i + 1] - rtilde[i])) / (dtilde[i] * alpha[i]));
        vect_A[i] = nominateur / denominateur;
    }
    return vect_A;
}

//vecteur T.  Remarque : juste les coordonnes d'indice entre 1 et 9, le n-eme cordonne est dans la partie 1.2)
double *T(double A[10], double B[10], double C[10], double D[10], double E[10], double *vect_T) {
    int i;
    for (i = 0; i < n-1; i++) {
        vect_T[i] = A[i] - B[i] - C[i] * log(D[i] - E[i]); // log : logaritmique neperien.
    }
    return vect_T;
}

#pragma endregion

#pragma region 1.2) T(n)
//RHOn
double RHOn(double rtilde[10], double dtilde[10], double ptilde[10]) {
    double nominateur = rtilde[n-1]*(k[n-1] - (dtilde[n-1]/andes));
    double denominateur = ptilde[n - 1] * (dtilde[n - 1] / andes);
    return nominateur / denominateur;
}

//MUn
double MUn(double ptilde[10], double dtilde[10]) {
    double denominateur = k[n-1] - (dtilde[n-1] / andes);
    return ptilde[n-1]/denominateur;

}

//coordonne n-eme de T
double Tn(double ptilde[10],double MUn, double rtilde[10], double RHOn) {
    double terme1 = cp*(k[n-1]*((andes*(ptilde[n-1]+rtilde[n-1])-rtilde[n-1]) / ((ptilde[n-1]+rtilde[n-1]) * (1 - RHOn) * ptilde[n-1])));
    double terme2 = (((ptilde[n-1]+rtilde[n-1])*(1-andes)) / (MUn*pow(1 - RHOn,2)*ptilde[n-1])) - (1/(MUn*(1-RHOn)));
    double terme3 = log((1/RHOn)*(1-((1-RHOn)/((1-andes)*((ptilde[n-1]+rtilde[n-1])/ptilde[n-1])))));
    return terme1 + terme2 * terme3;

}

#pragma endregion

#pragma region 1.3) les bornes de ri~
// Remarque : tout les fonction retournent un vecteur de taille 10, sauf les fonctions des bornes, ils retournent une valeur reele;
//vecteur N
double N(int i) {
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
double M(int i) {
    // calculer le produit de terme ((rj+pj)/rj)*andes avec j varie de i a n
    double produit = 1;
    int j;
    for (j = i; j < n; j++) {
        produit = produit * ((r[j]+p[j])/r[j]);
    }
    produit = produit * andes;
    //la comparaison
    if (produit < 1) return produit;
    else return 1;
}

//vecteur a
double a(double M[10], double N[10], int i) {
    double nominateur = ((1-M[i])/M[i])*r[i];
    double denominateur = ((1 - N[i]) / N[i]) * r[i] + p[i];
    return nominateur / denominateur;
}

//vecteur b
double b(double N[10], int i) {
    double nominateur = p[i]*r[i];
    double denominateur = ((1 - N[i]) / N[i]) * r[i] + p[i];
    return nominateur / denominateur;
}

//vecteur c
double c(double M[10], double N[10], int i) {
    double nominateur = ((1-N[i])/N[i])*r[i];
    double denominateur = ((1 - M[i]) / M[i]) * r[i] + p[i];
    return nominateur / denominateur;
}

//vecteur e
double e(double M[10], int i) {
    double nominateur = p[i]*r[i];
    double denominateur = ((1 - M[i]) / M[i]) * r[i] + p[i];
    return nominateur / denominateur;
}

//borne inferieur de ri~ definie dans (10)
double borneInf_10(double a[10], double b[10], int i) {
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

//borne superieur de ri~ definie dans (10)  //TODO : a reviser
double borneSup_10(double c[10], double e[10], int i) {
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
double *ptilde(double rtilde[10], double *vect_ptilde) {
    int i = 0;
    vect_ptilde[i] = p[i];
    for (i = 1; i < n; i++) {
        vect_ptilde[i] = rtilde[i]*((p[i]/r[i]) + ((p[i]*(r[i]-rtilde[i])*(r[i]+p[i]))/(pow(r[i],2)*(rtilde[i]-rtilde[i-1]))));
    }
    return vect_ptilde;
}

//vecteur q
double *q(int lambda[10], double *vect_q) {
    int i = 0;
    vect_q[i] = beta[i];

    for (i = 1; i < n; i++) {
        vect_q[i] = (1-lambda[i-1]) * vect_q[i-1] * (1+beta[i]) + beta[i];
    }
    return vect_q;
}

//vecteur d~
double *dtilde(double q[10], int lambda[10], double *vect_dtilde) {
    int i;
    for (i = 0; i < n; i++) {
        //calculer le produit de terme (1+lambdaj*qj), j varie de i a n
        double produit = 1;
        int j;
        for (j = i; j < n; j++) {
            produit = produit*(1 + lambda[j]*q[j]);

        }
        vect_dtilde[i] = d*produit;
    }
    return vect_dtilde;
}

//borne inferieur de ri~ definie dans (7)
double borneInf_7(double a[10], double rtilde[10], double b[10], int i) {
    return a[i] * rtilde[i - 1] + b[i];
}

//borne superieur de ri~ definie dans (7)
double borneSup_7(double a[10], double rtilde[10], double b[10], int i) {
    return a[i] * rtilde[i - 1] + b[i];
}

#pragma endregion

//fonction objective
double J(double *rtilde, int *lambda) {
    int i;
    double *vect_N = (double *)malloc(10*sizeof(double));
    for (i = 0; i < 10; i++) {
        vect_N[i] = N(i);
    }

    double *vect_M = (double *)malloc(10* sizeof(double));
    for (i = 0; i < 10; i++) {
        vect_M[i] = M(i);
    }

    double *vect_a = (double *)malloc(10* sizeof(double));
    for (i = 0; i < 10; i++) {
        vect_a[i] = a(vect_M, vect_N, i);
    }

    double *vect_q = (double *)malloc(10* sizeof(double));
    q(lambda, vect_q);

    double *vect_ptilde = (double *)malloc(10 * sizeof(double));
    ptilde(rtilde, vect_ptilde);

    double *vect_dtilde = (double *)malloc(10* sizeof(double));
    dtilde(vect_q, lambda, vect_dtilde);

    double *vect_alpha = (double *)malloc(9* sizeof(double));
    alpha(rtilde, vect_alpha);

    double *vect_A = (double *)malloc(9*sizeof(double));
    A(vect_ptilde, rtilde, vect_alpha, vect_dtilde, vect_A);

    double *vect_B = (double *)malloc(9* sizeof(double));
    B(vect_ptilde, rtilde, vect_dtilde, vect_alpha, vect_B);

    double *vect_C = (double *)malloc(9* sizeof(double));
    C(vect_ptilde, vect_dtilde, rtilde, vect_alpha, vect_C);

    double *vect_D = (double *)malloc(9*sizeof(double));
    D(vect_ptilde, vect_dtilde, rtilde, vect_alpha, vect_D);

    double *vect_E = (double *)malloc(9* sizeof(double));
    E(vect_alpha, vect_ptilde, vect_dtilde, rtilde, vect_E);

    double *vect_T = (double *)malloc(9*sizeof(double));
    T(vect_A, vect_B, vect_C, vect_D, vect_E, vect_T);

    double terme_MUn = MUn(vect_ptilde, vect_dtilde);
    double terme_RHOn = RHOn(rtilde, vect_dtilde, vect_ptilde);
    double terme_Tn = Tn(vect_ptilde, terme_MUn, rtilde, terme_RHOn);

    double terme_1 = 0, terme_2 = 0;

    for (i = 0; i < n-1; i++) {
        terme_1 += vect_T[i];
        terme_2 += cI*lambda[i]*vect_dtilde[i];
    }

    terme_1 += terme_Tn;
    terme_2 += cI*lambda[n-1] * vect_dtilde[n-1];

    return terme_1 + terme_2;

}