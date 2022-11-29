#ifndef SENSOR_TENSAO_H
#define SENSOR_TENSAO_H

#include "sensoreletrico.h"

class SensorTensao : public SensorEletrico // definição da classe para sensores de tensão derivada da classe de sensores elétricos
{
public:
    SensorTensao(const string &, const vector<string> &); // construtor com devidas alterações para sensores de tensão
    ~SensorTensao();                                      // destrutor da classe
};

#endif