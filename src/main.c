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
    if ( nErrorCode == LSERR_NO_VALID_LICENSE) {
        printf( "Invalid License Key!\n");
        exit( 1);
    }
    APIERRORCHECK;

    /*****************************************************************
    * Specify the LP portion of the model.
    *****************************************************************/



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