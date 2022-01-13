//
// Created by huacheng on 1/12/22.
//

#ifndef EOSTOOL_TEST_H
#define EOSTOOL_TEST_H
#include <stdio.h>
#include "eos_state.h"

int test_tillotson(FILE * output);
int test_aneos(FILE * output);

void test_pressure(struct ANEOSTable * _a,FILE * output,char * fmt, int lines);
#endif //EOSTOOL_TEST_H
