#ifndef SENSOR_VAZAO_H
#define SENSOR_VAZAO_H

#include <vector>
#include <fstream>
#include "medicao.h"

using namespace std;

class SensorVazao // definição da classe para os sensores de vazão
{
protected:
    vector<Medicao> dados;  // armazenamento de valores e horarios
    vector<string> headers; // armazenamento de informacões do cabeçalho do banco de dados em .dat
    string nomeSensor;
    string id;
    string unidade;
    string horarioInicial;
    int freqA;     // número de amostras por segundo
    int numMed;    // número total de medições
    ifstream file; //objeto que recebe os dados do arquivo .dat

public:
    SensorVazao(const string &, const vector<string> &); //construtor da classe
    ~SensorVazao();                                      // destrutor da classe

    bool abrirArquivo(const string &);      // método para abrir o arquivo .dat
    bool lerDados();                        // método para ler devidamente os dados e armazenar em "dados"
    bool getDado(const string &, double &); // método que encontra e armazena um dado correspondente a uma hora especifica

    string getId();             // método que retorna id
    string getUnidade();        // método que retorna unidade
    string getNomeSensor();     // método que retorna nome do sensor
    string getHorarioInicial(); // método que retorna horario inicial

    int getNumMed();         // método que retorna número de medições
    int getFreqAmostragem(); // método que retorna número de medições por segundo

    double somaVazao(const string &); // método que retorna soma de vazões até determinado horário
    double getVazao(const string &);  // método que retorna vazão de um determinado horário
};

#endif