#ifndef SENSOR_CORRENTE_H
#define SENSOR_CORRENTE_H

#include "sensoreletrico.h"

class SensorCorrente : public SensorEletrico // definição da classe para sensores de tensão derivada da classe de sensores elétricos
{

public:
    SensorCorrente(const string &, const vector<string> &); // construtor com devidas alterações para sensores de corrente
    ~SensorCorrente();                                      // destrutor da classe
};

#endif