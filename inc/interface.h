#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "sensorvazao.h"
#include "sensortensao.h"
#include "sensorcorrente.h"
#include <vector>

class Interface
{
public:
    int getNumHorariosEnvolvidos(const string &hora);
    int getNumAmostrasEnvolvidas(const string, SensorEletrico &);
    double potenciaAtiva(const string, SensorTensao &, SensorCorrente &, const int);
    double energia(const string, SensorTensao &, SensorCorrente &, const int);
    void imprimeVolume(SensorVazao &, SensorVazao &, const string &);
    void atendimento(SensorCorrente &, SensorCorrente &, SensorTensao &, SensorTensao &, SensorVazao &, SensorVazao &);
};

#endif