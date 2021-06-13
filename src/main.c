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

/****************************************************************
   Standard callback function to display local solutions
 ****************************************************************/
int  LS_CALLTYPE local_sol_log(pLSmodel pModel,int iLoc, void *cbData)
{
    int iter=0,niter,biter,siter;
    int *nKKT = (int *) cbData, npass=0, nbrn;
    double pfeas=0.0,pobj=0.0;
    double bestobj;
    if (iLoc==LSLOC_LOCAL_OPT)
    {
        if (*nKKT == 0){
            printf(" %5s %11s %11s %11s %10s\n",
                   "Iter","Objective","Infeas","Best","Branches");
        }
        LSgetCallbackInfo(pModel,iLoc,LS_IINFO_MIP_NLP_ITER,&niter);
        LSgetCallbackInfo(pModel,iLoc,LS_IINFO_MIP_SIM_ITER,&siter);
        LSgetCallbackInfo(pModel,iLoc,LS_IINFO_MIP_BAR_ITER,&biter);
        LSgetCallbackInfo(pModel,iLoc,LS_DINFO_POBJ,&pobj);
        LSgetCallbackInfo(pModel,iLoc,LS_DINFO_PINFEAS,&pfeas);
        LSgetCallbackInfo(pModel,iLoc,LS_DINFO_MSW_POBJ,&bestobj);
        LSgetCallbackInfo(pModel,iLoc,LS_IINFO_MIP_BRANCHCOUNT,&nbrn);
        iter = niter+siter+biter;
        printf(" %5d %11.3f %11.3f %11.3f %10d\n",iter,pobj,pfeas,
               bestobj,nbrn);
        (*nKKT)++;
    }
    return 0;
}

/****************************************************************
   Callback function to compute function values
 ****************************************************************/
int    CALLBACKTYPE Funcalc8(pLSmodel pModel,void    *pUserData,
                             int      nRow  ,double  *pdX,
                             int      nJDiff,double  dXJBase,
                             double   *pdFuncVal,int  *pReserved)
{
    int i;

    double *vect_N = (double *)malloc(10*sizeof(double));
    for (i = 0; i < 10; i++) {
        vect_N[i] = N(i);
    }

    double *vect_M = (double *)malloc(10* sizeof(double));
    for (i = 0; i < 10; i++) {
        vect_M[i] = M(i);
    }

    double val=0.0;

    double *rtilde = (double *)malloc(10* sizeof(double));
    int *lambda = (int *)malloc(10* sizeof(int));
    for (i = 0; i < 10; i++) {
        rtilde[i] = pdX[i];
        lambda[i] = (int)pdX[10+i];
    }

    int    nerr=0;
    /* compute objective's functional value*/
    if (nRow == -1)
        val = J(rtilde, lambda);
        /* compute constaint 0's functional value */
    else if (nRow == 0) {
        for (i = 10; i < 20; i++) {
            val = val + pdX[i];
        }
        val = val - m;
    }
        /* compute constaint 1's functional value */
    else if (nRow == 1) val = pdX[0] - 0.8;
        /* compute constaint 2's functional value */
    else if (nRow == 2) val = rtilde[1] - b(vect_N, 1);
        /* compute constaint 3's functional value */
    else if (nRow == 3) val = rtilde[2] - b(vect_N, 2);
        /* compute constaint 4's functional value */
    else if (nRow == 4) val = rtilde[3] - b(vect_N, 3);
        /* compute constaint 5's functional value */
    else if (nRow == 5) val = rtilde[4] - b(vect_N, 4);
        /* compute constaint 6's functional value */
    else if (nRow == 6) val = rtilde[5] - b(vect_N, 5);
        /* compute constaint 7's functional value */
    else if (nRow == 7) val = rtilde[6] - b(vect_N, 6);
        /* compute constaint 8's functional value */
    else if (nRow == 8) val = rtilde[7] - b(vect_N, 7);
        /* compute constaint 9's functional value */
    else if (nRow == 9) val = rtilde[8] - b(vect_N, 8);
        /* compute constaint 10's functional value */
    else if (nRow == 10) val = rtilde[9] - b(vect_N, 9);
        /* compute constaint 11's functional value */
    else if (nRow == 11) val = c(vect_M, vect_N, 1)*rtilde[0] - rtilde[1] + e(vect_M, 1);
        /* compute constaint 12's functional value */
    else if (nRow == 12) val = c(vect_M, vect_N, 2)*rtilde[1] - rtilde[2] + e(vect_M, 2);
        /* compute constaint 13's functional value */
    else if (nRow == 13) val = c(vect_M, vect_N, 3)*rtilde[2] - rtilde[3] + e(vect_M, 3);
        /* compute constaint 14's functional value */
    else if (nRow == 14) val = c(vect_M, vect_N, 4)*rtilde[3] - rtilde[4] + e(vect_M, 4);
        /* compute constaint 15's functional value */
    else if (nRow == 15) val = c(vect_M, vect_N, 5)*rtilde[4] - rtilde[5] + e(vect_M, 5);
        /* compute constaint 16's functional value */
    else if (nRow == 16) val = c(vect_M, vect_N, 6)*rtilde[5] - rtilde[6] + e(vect_M, 6);
        /* compute constaint 17's functional value */
    else if (nRow == 17) val = c(vect_M, vect_N, 7)*rtilde[6] - rtilde[7] + e(vect_M, 7);
        /* compute constaint 18's functional value */
    else if (nRow == 18) val = c(vect_M, vect_N, 8)*rtilde[7] - rtilde[8] + e(vect_M, 8);
        /* compute constaint 19's functional value */
    else if (nRow == 19) val = c(vect_M, vect_N, 9)*rtilde[8] - rtilde[9] + e(vect_M, 9);

    *pdFuncVal=val;
    return nerr;
}


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
    int howmany = 0;
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
    nErrorCode = LSloadLPData(pModel, nCons, nVars, LS_MIN, 0.0, objCoeff, rhs, contypes, nAnnz, A_column_index, A_column_length, A_nnz_values, A_row_index, lb, ub);
    APIERRORCHECK;

    nErrorCode=LSloadVarType(pModel,vartypes);
    APIERRORCHECK;

    nErrorCode=LSwriteLINDOFile(pModel,"lpModel.ltx");
    APIERRORCHECK;

    /*****************************************************************
    * Specify the NLP portion of the model.
    *****************************************************************/
    /* The number of nonlinear variables in each column */
    for (i = 0; i < 20; i++) {
        A_column_length[i] = 0;
    }

    /* The indices of the first nonlinear variable in each column */
    for (i = 0; i < 20; i++) {
        A_column_index[i] = 0;
    }

    /* The indices of nonlinear constraints */
    A_row_index[0] = 0;

    /* The indices of variables that are nonlinear in the objective*/
    int *NLobjndx = (int *)malloc(20* sizeof(int));
    for (i = 0; i < 20; i++) {
        NLobjndx[i] = i;
    }

    /* Number nonlinear variables in cost */
    int numNLobj = 20;

    /* Load the nonlinearstructure */
    nErrorCode = LSloadNLPData(pModel, A_column_index, A_column_length, NULL, A_row_index, numNLobj, NLobjndx, NULL);
    APIERRORCHECK;
    /*****************************************************************
    * Set up callback functions
    *****************************************************************/
    /* Install the callback function to call at every local solution */
    nErrorCode=LSsetCallback(pModel,(cbFunc_t) local_sol_log,&howmany);
    APIERRORCHECK;

    /* Set the print level to 1 */
    nErrorCode=LSsetModelIntParameter(pModel,LS_IPARAM_NLP_PRINTLEVEL,1);
    APIERRORCHECK;

    /* Set the NLP prelevel to 0 */
    nErrorCode=LSsetModelIntParameter(pModel,LS_IPARAM_NLP_PRELEVEL,0);
    APIERRORCHECK;

    /* Install the routine that will calculate the function values. */
    nErrorCode=LSsetFuncalc(pModel,(Funcalc_type) Funcalc8,NULL);
    APIERRORCHECK;
    /*****************************************************************
    * Solve the model
    *****************************************************************/
    /* Turn multi-start search on */
    nErrorCode=LSsetModelIntParameter(pModel,LS_IPARAM_NLP_SOLVER,LS_NMETHOD_MSW_GRG);
    APIERRORCHECK;

    /* Set maximum number of local optimizations */
    nErrorCode=LSsetModelIntParameter(pModel,LS_IPARAM_NLP_MAXLOCALSEARCH,5);
    APIERRORCHECK;
    printf("\n\tSolving the MINLP using Multi-Start Approach.\n\n");
    nErrorCode=LSsolveMIP(pModel,NULL);
    APIERRORCHECK;
    {
        double objval, primal[20];
        nErrorCode = LSgetMIPPrimalSolution(pModel, primal);
        nErrorCode = LSgetInfo(pModel, LS_DINFO_MIP_OBJ, &objval);
        if (nErrorCode == LSERR_NO_ERROR)
        {
            printf("\n\n\n");
            printf("obj  = %15.7f \n",objval);
            for (i=0; i<20; i++) printf("x[%d] = %15.7f \n",i,primal[i]);
        }
        else
        {
            printf("Error %d occured\n\n\n",nErrorCode);
        }
    }
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