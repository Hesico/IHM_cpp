#include "sensortensao.h"
#include <iostream>

using namespace std;

SensorTensao::SensorTensao(const string &path, const vector<string> &h) : SensorEletrico::SensorEletrico(path, h)
{
    this->unidade = "V"; // atribuição de volt para unidade padrão dos sensores de tensão
}

SensorTensao::~SensorTensao()
{
    this->file.close();
}