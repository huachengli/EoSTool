//
// Created by huacheng on 9/13/22.
//

#ifndef EOSTOOL_TOOLS_H
#define EOSTOOL_TOOLS_H

#include "eos_state.h"

void ANEOSCreateLike(struct ANEOSTable * _target,struct ANEOSTable * _source);
void ANEOSBuildWithTill(struct ANEOSTable * _target,struct TillotsonTable * _source);
void TillStateExt(struct TillotsonTable * _t,double tTem,double tDen,double *eng,double *pres,double *csound);
void GenerateANEOSfTill(const char *_aname,const char * _atype,const char *_source,const char * comment);
#endif //EOSTOOL_TOOLS_H
