#include <stdio.h>
#include <unistd.h>
#include "test.h"

int main__()
{
    double test_num = -.100000000000E+11;

    char test_str[30];
    special_scientific_notation(test_str,20,12,test_num);
    printf("%s",test_str);
    return 0;
}


int main()
{

    // an example for aneos
    struct ANEOSTable eos_test[2];
/*

     const char aname[][30] = {
            "../data/granit2.aneos",
            "granite3.aneos"
    };
    const char comment[] = "original version is iSALE2d/granit2.aneos.";
*/


    const char aname[][30] = {
            "../data/dunite_.aneos",
            "dunite3.aneos"
    };
    const char comment[] = "original version is iSALE2D/dunite_.aneos";

    if(!access(aname[1],F_OK|W_OK))
    {
        fprintf(stdout,"overwrite %s\n",aname[1]);
    }

    generate_aneos(aname[0],CONSTSHIFT,aname[1],comment);


    FILE * fp[2] = {
            fopen(aname[0],"r"),
            fopen(aname[1],"r"),
    };

    LoadANEOS(eos_test + 0,fp[0]);
    LoadANEOS(eos_test + 1,fp[1]);


    for(int k=0;k<21;k++)
    {
        for(int j=0;j<22;j++)
        {
            double kDen = 200.0 + 200.0*k;
            double jTmp = 275.0 + 200.0*j;
            double rPre1 = ANEOSInterpolateTD(eos_test+0,jTmp,kDen,ANEOSPRE);
            double rPre2 = ANEOSInterpolateTD(eos_test+1,jTmp,kDen,ANEOSPRE);

            fprintf(stdout,"%13.5e,",rPre2-rPre1);
        }
        fprintf(stdout,"\n");
    }

    UnAllocateANEOS(eos_test);
    return 0;
}
