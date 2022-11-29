#include "sensorcorrente.h"
#include <iostream>

using namespace std;

SensorCorrente::SensorCorrente(const string &path, const vector<string> &h) : SensorEletrico::SensorEletrico(path, h)
{
    this->unidade = "A"; // atribuição de ampere para unidade padrão dos sensores de corrente
}

SensorCorrente::~SensorCorrente()
{
    this->file.close();
}