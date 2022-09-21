#include <stdio.h>
#include <unistd.h>
#include "test.h"
#include "Tools.h"


int main()
{
    // convert tillotson to aneos
    const char aname[][30] = {
            "../data/gabbro1.aneos",
            "../data/granit2.aneos",
            "../data/gabbro1.tillotson"
    };

    const char comment[] = "original version is iSALE2D/dunite_.aneos";
    GenerateANEOSfTill(aname[0],aname[1],aname[2],comment);

    FILE * fp = fopen(aname[0],"r");
    struct ANEOSTable eos_test;
    LoadANEOS(&eos_test,fp);
    FILE * out = fopen("gabbro1.cs","w");
    test_aneos_data(&eos_test,out,"%12.5e,",ANEOSCSD);
    UnAllocateANEOS(&eos_test);
    fclose(out);
}

int bh__main()
{
    // compare tillotson f90 and c implementation
    const char * _source = "../data/gabbro1.tillotson";
    struct TillotsonTable * eos_source;
    int tillindex = 1;
    FILE * source_fp = fopen(_source,"r");
    get_tilltable(&tillindex,&eos_source);
    LoadTillEOS(eos_source,source_fp);
    tillotson_initialize(&tillindex);

    for(int k=0;k<21;k++)
    {
//        fprintf(stdout,"{Density = %lf}",5.0 + 200.0*k);
        for(int j=0;j<22;j++)
        {
            double kDen = 5.0 + 200.0*k;
            double jTmp = 275.0 + 200.0*j;
            double rPre1 = TillEOSInterpolateTD(eos_source,jTmp,kDen,ANEOSCSD);
            double rPre2 = isale_tillotson_interpolateTD(tillindex,jTmp,kDen,ANEOSCSD);
            fprintf(stdout,"[(SALEc)%13.5e,(isale)%13.5e,%13.5e]",rPre1,rPre2,(rPre1 - rPre2)/(rPre2+1.0e-2));
//            fprintf(stdout,"%13.5e",rPre2);

        }
        fprintf(stdout,"\n");
    }

}

int test_tillotson_main()
{
    FILE * fp = fopen("gabbro.cs.till","w");
    test_tillotson(fp,"../data/gabbro1.tillotson");
    fclose(fp);
}

int l_main()
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
            double rPre2 = ANEOSInterpolateTD(eos_test+1,jTmp,kDen,ANEOSCSD);

            fprintf(stdout,"%13.5e,",rPre2);
        }
        fprintf(stdout,"\n");
    }

    UnAllocateANEOS(eos_test);
    return 0;
}