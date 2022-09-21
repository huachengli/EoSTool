//
// Created by huacheng on 9/13/22.
//

#include "Tools.h"

void ANEOSCreateLike(struct ANEOSTable * _target,struct ANEOSTable * _source)
{
    _target->nDen = _source->nDen;
    _target->nTem = _source->nTem;
    AllocateANEOS(_target);
    for(int k=0;k<_target->nTem;++k)
    {
        _target->xTem[k] = _source->xTem[k];
    }
    for(int j=0;j<_target->nDen;++j)
    {
        _target->yDen[j] = _source->yDen[j];
    }
}


void TillStateExt(struct TillotsonTable * _t,double tTem,double tDen,double *eng,double *pres,double *csound)
{
    /*
     * the core code of TillInterpolateTD ..
     */
    double ThermalE = (tTem - _t->TLTref)*_t->TLCv;
    int DI = 0;
    int DJ = _t->nDen - 1;
    while(DI + 1 < DJ)
    {
        int DM = (DI + DJ)/2;
        if(_t->xDen[DM] > tDen)
            DJ = DM;
        else
            DI = DM;
    }

    double Dxl = (_t->xDen[DJ]-tDen)/(_t->xDen[DJ]-_t->xDen[DI]);
    Dxl = Wind(Dxl,0.0,1.0);
    double Dxr = 1.0 - Dxl;
    double LMEng = _t->yEng[DI]*Dxl + _t->yEng[DJ]*Dxr + ThermalE;


    double LMPre,LMCs;
    TillPres(_t,LMEng,tDen,&LMPre,&LMCs);

    *eng = LMEng;
    *pres = LMPre;
    *csound = LMCs;
}
void ANEOSBuildWithTill(struct ANEOSTable * _target,struct TillotsonTable * _source)
{
    _target->Tnorm = _source->TLTref;
    _target->Dnorm = _source->TLRho0;

    double a_temperature,a_pressure,a_csound,a_density,a_energy;
    for(int k=0;k<_target->nDen;++k)
    {
        a_density = _target->yDen[k];
        for(int j=0;j<_target->nTem;++j)
        {
            a_temperature = _target->xTem[j];
            TillStateExt(_source,a_temperature,a_density,
                         &a_energy,&a_pressure,&a_csound);
            _target->Data[j][k][0] = a_density*a_energy;
            _target->Data[j][k][1] = a_pressure;
            _target->Data[j][k][2] = a_csound;
        }
    }

    _target->Pnorm = ANEOSInterpolateTD(_target,_source->TLTref,_source->TLRho0,ANEOSPRE);
}

void GenerateANEOSfTill(const char *_aname,const char * _atype,const char *_source,const char * comment)
{
    // load ANEOS from a existed aneos file
    struct ANEOSTable eos_proto;
    FILE * proto_fp = fopen(_atype,"r");
    LoadANEOS(&eos_proto,proto_fp);

    // create aneos like eos_proto
    struct ANEOSTable eos_target;
    ANEOSCreateLike(&eos_target,&eos_proto);

    // load tillotson
    struct TillotsonTable eos_source;
    FILE * source_fp = fopen(_source,"r");
    LoadTillEOS(&eos_source,source_fp);

    // gerenate aneos
    ANEOSBuildWithTill(&eos_target,&eos_source);

    // write into file
    ANEOSWrite(&eos_target,_aname,comment);

    UnAllocateANEOS(&eos_proto);
    UnAllocateANEOS(&eos_target);
    UnAllocateTillEOS(&eos_source);

}