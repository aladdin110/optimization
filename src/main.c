#include "library.h"


/* Define a macro to declare variables for error checking */
#define APIERRORSETUP  \
   int nErrorCode; \
   char cErrorMessage[LS_MAX_ERROR_MESSAGE_LENGTH] \


/* Define a macro to do our error checking */
#define APIERRORCHECK  \
   if (nErrorCode) \
   { \
      if ( pEnv) \
      { \
         LSgetErrorMessage( pEnv, nErrorCode, \
          cErrorMessage); \
         printf("Errorcode=%d:  %s\n", nErrorCode, \
          cErrorMessage); \
      } else {\
         printf( "Fatal Error\n"); \
      } \
      goto Terminate; \
   }                   \

/* Define a macro to display information about the API version */
#define APIVERSION \
{\
    char szVersion[255], szBuild[255];\
    LSgetVersionInfo(szVersion,szBuild);\
    printf("\nLINDO API Version %s built on %s\n",szVersion,szBuild);\
}\



/* main entry point*/
int main() {
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

    double *vect_b = (double *)malloc(10* sizeof(double));
    for (i = 0; i < 10; i++) {
        vect_b[i] = b(vect_N, i);
    }

    double *vect_c = (double *)malloc(10* sizeof(double));
    for (i = 0; i < 10; i++) {
        vect_c[i] = c(vect_M, vect_N, i);
    }

    double *vect_e = (double *)malloc(10* sizeof(double));
    for (i = 0; i < 10; i++) {
        vect_e[i] = e(vect_M, i);
    }








    APIERRORSETUP;

    /* declare an instance of the LINDO environment object */
    pLSenv pEnv;
    /* declare an instance of the LINDO model object */
    pLSmodel pModel;

    char MY_LICENSE_KEY[1024];

    /*****************************************************************
    * Create a model in the environment.
    *****************************************************************/
    nErrorCode = LSloadLicenseString(LINDO_LICENSE, MY_LICENSE_KEY);
    if ( nErrorCode != LSERR_NO_ERROR) {
        printf( "Failed to load license key (error %d)\n",nErrorCode);
        exit( 1);
    }

    APIVERSION;


    pEnv = LScreateEnv ( &nErrorCode, MY_LICENSE_KEY);
    APIERRORCHECK;

    pModel = LScreateModel(pEnv,&nErrorCode);
    APIERRORCHECK;

    /*****************************************************************
    * Specify the LP portion of the model.
    *****************************************************************/
    /*Model dimensions */
    //Number of constraintsin the model
    int nCons = 20;
    //Number of variablesin the model
    int nVars = 20;
    //The number of nonzeros in the constraint matrix
    int nAnnz = 38;

    /*vector containing the nonzero coefficients of the constraint matrix A*/
    double A_nnz_values[38] = {1, vect_c[1],
                               1, -1, vect_c[2],
                               1, -1, vect_c[3],
                               1, -1, vect_c[4],
                               1, -1, vect_c[5],
                               1, -1, vect_c[6],
                               1, -1, vect_c[7],
                               1, -1, vect_c[8],
                               1, -1, vect_c[9],
                               1, -1,
                               1,
                               1,
                               1,
                               1,
                               1,
                               1,
                               1,
                               1,
                               1,
                               1};
    /*vector containing the length of each column*/
    int A_column_length[20] = {2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    /*vector containing the index of the first nonzero in each column*/
    int A_column_index[21] = {0, 2, 5, 8, 11, 14, 17, 20, 23, 26, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38};

    /*vector containing the row indices of the nonzeros in the constraint matrix A*/
    int A_row_index[38] = {1, 11,
                           2, 11, 12,
                           3, 12, 13,
                           4, 13, 14,
                           5, 14, 15,
                           6, 15, 16,
                           7, 16, 17,
                           8, 17, 18,
                           9, 18, 19,
                           10, 19,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0};

    /*vector containing the constraint right-hand side coefficients*/
    double *rhs = (double *)malloc(20 * sizeof(double));
    rhs[0] = m;
    rhs[1] = 0.8;
    for (i = 2; i <= 10; i++) {
        rhs[i] = vect_b[i-1];
    }
    for (i = 11; i < 20; i++) {
        rhs[i] = -vect_e[i-10];
    }

    /* vector containing the type of each constraint*/
    char *contypes = (char *)malloc(20 * sizeof(char));
    contypes[0] = 'E';
    contypes[1] = 'E';
    for (i = 2; i < 20; i++) {
        contypes[i] = 'G';
    }


    /*vector containing the lower bound of each variable*/
    double *lb = (double *)malloc(20 * sizeof(double));
    /*vector containing the upper bound of each variable*/
    double *ub = (double *)malloc(20 * sizeof(double));

    for (i = 0; i < 10; i++) {
        lb[i] = borneInf_10(vect_a, vect_b, i);
        ub[i] = borneSup_10(vect_c, vect_e, i);

        lb[i+10] = 0;
        ub[i+10] = 1;
    }

    /*vector containing the type of each variable*/
    char *vartypes = (char *)malloc(20 * sizeof(char));
    for (i = 0; i < 10; i++) {
        vartypes[i] = 'C';
        vartypes[i+10] = 'I';

    }

    /*vector containing the objective coefficients*/
    double *objCoeff = (double *)malloc(20* sizeof(double));
    for (i = 0; i < 20; i++) {
        objCoeff[i] = 0;
    }


    /* Load in nonzero structure and linear/constant terms*/
    nErrorCode = LSloadLPData(pModel, nCons, nVars, LS_MIN, 0.0,
                              objCoeff, rhs, contypes, nAnnz,
                              A_column_index, A_column_length,
                              A_nnz_values, A_row_index, lb, ub);

    APIERRORCHECK;

    nErrorCode=LSloadVarType(pModel,vartypes);
    APIERRORCHECK;

    nErrorCode=LSwriteLINDOFile(pModel,"lpModel.ltx");
    APIERRORCHECK;

    /*****************************************************************
    * Specify the NLP portion of the model.
    *****************************************************************/


    /*****************************************************************
    * Set up callback functions
    *****************************************************************/

    /*****************************************************************
    * Solve the model
    *****************************************************************/



Terminate:
    /***************************************************************
     *  Terminate : Delete the model & env space
     ***************************************************************/
    nErrorCode = LSdeleteModel( &pModel);
    nErrorCode = LSdeleteEnv( &pEnv);

    /* Wait until user presses the Enter key */
    printf("Press <Enter> ...");
    getchar();
}