//
// Created by huacheng on 1/12/22.
//

#ifndef EOSTOOL_TEST_H
#define EOSTOOL_TEST_H
#include <stdio.h>
#include "eos_state.h"

int test_tillotson(FILE * output, const char *);
int test_aneos(FILE * output, const char * aname, int correct);

void test_pressure(struct ANEOSTable * _a,FILE * output,char * fmt, int lines);
void generate_aneos(const char * aname, int correct, const char * cname, const char *comment);
#endif //EOSTOOL_TEST_H
