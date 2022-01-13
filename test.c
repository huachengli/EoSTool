//
// Created by huacheng on 1/12/22.
//

#include "test.h"

int test_aneos(FILE * output)
{
    // an example for aneos
    struct ANEOSTable eos_test;
    FILE * fp = fopen("../data/granit2.aneos","r");
    LoadANEOS(&eos_test,fp);


    ANEOSInterpolateTD(&eos_test,2000,10000,ANEOSPRE);

    for(int k=0;k<21;k++)
    {
        for(int j=0;j<22;j++)
        {
            double kDen = 200.0 + 200.0*k;
            double jTmp = 275.0 + 200.0*j;
            double rPre = ANEOSInterpolateTD(&eos_test,jTmp,kDen,ANEOSPRE);
            fprintf(output,"%13.5e,",rPre);
        }
        fprintf(output,"\n\n");
    }

    UnAllocateANEOS(&eos_test);
    return 0;
}

int test_tillotson(FILE * output)
{
    struct TillotsonTable eos_test;
    FILE * fp = fopen("../data/granite.tillotson","r");
    LoadTillEOS(&eos_test,fp);

    double check = TillEOSInterpolateTD(&eos_test,1500,300,ANEOSPRE);
    for(int k=0;k<21;k++)
    {
        for(int j=0;j<22;j++)
        {
            double kDen = 200.0 + 200.0*k;
            double jTmp = 275.0 + 200.0*j;
            double rPre = TillEOSInterpolateTD(&eos_test,jTmp,kDen,ANEOSPRE);
            fprintf(output,"%13.5e,",rPre);
        }
        fprintf(output,"\n");
    }

    UnAllocateTillEOS(&eos_test);
    return 0;
}

void test_pressure(struct ANEOSTable * _a,FILE * output,char * fmt, int lines)
{

    fprintf(output,"%d,%d,",_a->nTem,_a->nDen);
    fprintf(output,"\n");

    for(int k=0;k<_a->nTem;++k)
    {
        fprintf(output,fmt,_a->xTem[k]);
    }
    fprintf(output,"\n");

    for(int k=0;k<_a->nDen;++k)
    {
        fprintf(output,fmt,_a->yDen[k]);
    }
    fprintf(output,"\n");

    for(int k=0;k<_a->nTem;++k)
    {
        for(int j=0;j<_a->nDen;++j)
        {
            fprintf(output,fmt,_a->Data[k][j][1]);
        }
        fprintf(output,"\n");
    }
}
