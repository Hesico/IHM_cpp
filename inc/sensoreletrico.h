#ifndef SENSOR_ELETRICO_H
#define SENSOR_ELETRICO_H

#include <vector>
#include <fstream>
#include "medicao.h"
#include "medicaorms.h"
using namespace std;

class SensorEletrico // definição da classe para sensores elétricos
{
protected:
    vector<Medicao> dados;       // armazenamento de valores e horarios
    vector<MedicaoRms> dadosRMS; // armazenamento de valores RMS calculados e índices de controle
    vector<string> headers;      // armazenamento de informacões do cabeçalho do banco de dados em .dat
    string nomeSensor;
    string id;
    string unidade;
    string horarioInicial;
    int freqA; // número de amostras por segundo
    int freqRede;
    int numMed;    // número total de medições
    ifstream file; //objeto que recebe os dados do arquivo .dat

public:
    SensorEletrico(const string &, const vector<string> &); // construtor da classe
    ~SensorEletrico();                                      // destrutor da classe

    bool abrirArquivo(const string &); // método para abrir o arquivo .dat
    bool lerDados();                   // método para ler devidamente os dados e armazenar em "dados"

    string getId();         // método que retorna id
    string getUnidade();    // método que retorna unidade
    string getNomeSensor(); // método que retorna nome do sensor

    int getNumMed();         // método que retorna número de medições
    int getFreqRede();       // método que retorna frequência da rede
    int getFreqAmostragem(); // método que retorna número de medições por segundo

    double getDado(const int, double &);               // método que retorna um dadoRMS de acordo com um índice de controle
    double rms(const string &, double &, const int n); // método que retorna um valor RMS de acordo com um número de amostras fornecidas
};

#endif