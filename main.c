#include <stdio.h>
#include "test.h"

int main()
{
    test_tillotson(stdout);
    struct ANEOSTable eos_test;
    FILE * fp = fopen("../data/granit2.aneos","r");
    LoadANEOS(&eos_test,fp);
    FILE * out = fopen("granit2.pre","w");

    test_pressure(&eos_test,out,"%12.5e,",20);

    UnAllocateANEOS(&eos_test);
    fclose(out);
    return 0;
}
