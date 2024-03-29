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
void test_aneos_data(struct ANEOSTable * _a,FILE * output,char * fmt,int dataid);
void test_pressure_example();
void generate_aneos(const char * aname, int correct, const char * cname, const char *comment);
void special_scientific_notation(char * dst,unsigned int w,unsigned int d,double num);
void fspecial_scientific_notation(FILE * fp, int w, int d,double num);
void ANEOSWrite_2d(struct ANEOSTable * _t,const char fname[], const char comment[]);

// function from tillotson_eos.f90
void till_print(double*,double*);
void set_v_imp_max(double*);
void till_check(int*);
void get_tilltable(int*,struct TillotsonTable**);
void tillotson_initialize(int*);
void tillotson_rot(int *med,double *ro_in,double *t_in,double *p_out,double *sie_out,double *cs_out);
double isale_tillotson_interpolateTD(int m,double tTem, double tDen,int DataId);
#endif //EOSTOOL_TEST_H
