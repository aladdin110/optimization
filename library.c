//
// Created by aladdin on 3/20/21.
//

#include <stdio.h>
void printdata(double data[4][10]) {
    int i,j;
    for (i=0; i<4; i++) {
        for (j=1; j<10; j++) {
            printf("%f\t",data[i][j]);
        }
        printf("%f\n",data[i][j]);
    }
}

//function that calculate N
double Ni(double data[4][10], int i, int d) {
    //calculer le produit de rj/rj+pj, j varie de 1 jusqu'a i-1
    int j;
    double produit = 1,rj,pj;
    for (j=1; j<=i-1 ; j++) {
        rj = data[3][j];
        pj = data[2][j];
        produit = produit*(rj/(rj+pj));
    }

    //calculer ((ri+pi)/(ri*ki))*d
    double ri = data[3][i];
    double pi = data[2][i];
    double ki = data[1][i];
    double fraction = ((ri+pi)/(ri*ki))*d;

    //comparaison
    if (fraction > produit) {
        return fraction;
    }else {
        return produit;
    }
}

//function that calculate M
double Mi(double data[4][10], int i, double andes, int n) {
    //calculer le produit de rj+pj/rj, j varie de 1 jusqu'a i-1
    int j;
    double produit = 1,rj,pj;
    for (j=i; j<=n ; j++) {
        rj = data[3][j];
        pj = data[2][j];
        produit = produit*((rj+pj)/rj);
    }
    printf("le produit : %f\n",produit);

    if (produit*andes > 1) {
        return 1;
    }else {
        return produit*andes;
    }
}

//function that calculate ai
double ai(double data[4][10], double M, double N, int n, double andes, int d, int i) {
    N = Ni(data,i,d);
    M = Mi(data,i,andes,n);
    double ri = data[3][i];
    double pi = data[2][i];
    double nominateur = ((1-M)/M)*ri;
    double denominateur = (ri*(1-N/N))+pi;

    return nominateur/denominateur;
}

//function that calculate bi
double bi(double data[4][10], double N, int d, int i) {
    N = Ni(data,i,d);
    double ri = data[3][i];
    double pi = data[2][i];
    double nominateur = pi*ri;
    double denominateur = (ri*(1-N/N))+pi;

    return nominateur/denominateur;
}

//function that calculate ci
double ci(double data[4][10], double M, double N, int n, double andes, int d, int i) {
    N = Ni(data,i,d);
    M = Mi(data,i,andes,n);
    double ri = data[3][i];
    double pi = data[2][i];
    double nominateur = ((1-N)/N)*ri;
    double denominateur = (ri*(1-M/M))+pi;

    return nominateur/denominateur;
}

//function that calculate ei
double ei(double data[4][10], double M, int n, double andes, int i) {
    M = Mi(data,i,andes,n);
    double ri = data[3][i];
    double pi = data[2][i];
    double nominateur = pi*ri;
    double denominateur = (ri*(1-M/M))+pi;

    return nominateur/denominateur;
}

//funtction that returns landai
int landai(int landa[], int i) {
    return landa[i];
}

//function that calculate qi
double qi(double data[4][10],int landa[], int i) {
    int landai_1 = landai(landa, i-1);
    double betai = data[0][i];
    if ( i == 1){
        return data[0][1];
    }else {
        return (1-landai_1)*(qi(data, landa, i-1))*(1+betai) + betai;
    }
}
