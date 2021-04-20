#include "library.h"

int main() {
    double rtilde[10] = {0.8, 0.65, 0.685, 0.745, 0.769, 0.692, 0.699, 0.82, 0.828, 0.874};
    int lambda[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1};

    double fonction_objective = J(rtilde, lambda);
    printf("J = %lf\n", fonction_objective);



    return 0;
}
