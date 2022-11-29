#include <iostream>
#include "sensorvazao.h"
#include "sensoreletrico.h"
#include "sensortensao.h"
#include "sensorcorrente.h"
#include "interface.h"
#include <vector>

using namespace std;

int main()
{
    //Declaração dos objetidos sensores e seus respectivos headers.
    vector<string> headers = {"Nome do Sensor", "ID do sensor", "Frequencia da rede", "Numero de amostras por segundo", "Horario inicio da coleta", "Total de Amostras"};
    SensorCorrente sensorCorrente1("C:\\Users\\Henrique_2.Henrique-PC\\Desktop\\IHMv6\\IHMv6\\data\\SensorCorrente1.dat", headers);
    SensorTensao sensorTensao1("C:\\Users\\Henrique_2.Henrique-PC\\Desktop\\IHMv6\\IHMv6\\data\\SensorTensao1.dat", headers);
    SensorCorrente sensorCorrente2("C:\\Users\\Henrique_2.Henrique-PC\\Desktop\\IHMv6\\IHMv6\\data\\SensorCorrente2.dat", headers);
    SensorTensao sensorTensao2("C:\\Users\\Henrique_2.Henrique-PC\\Desktop\\IHMv6\\IHMv6\\data\\SensorTensao2.dat", headers);
    vector<string> headers2 = {"Nome do Sensor", "ID do sensor", "Unidade das medicoes", "Numero de amostras por segundo", "Horario inicio da coleta", "Total de Amostras"};
    SensorVazao sensorVazao1("C:\\Users\\Henrique_2.Henrique-PC\\Desktop\\IHMv6\\IHMv6\\data\\SensorVazao1.dat", headers2);
    SensorVazao sensorVazao2("C:\\Users\\Henrique_2.Henrique-PC\\Desktop\\IHMv6\\IHMv6\\data\\SensorVazao2.dat", headers2);

    //Lendo dados de todos os sensores.
    sensorCorrente1.lerDados();
    sensorTensao1.lerDados();
    sensorCorrente2.lerDados();
    sensorTensao2.lerDados();

    sensorVazao1.lerDados();
    sensorVazao2.lerDados();
    // Chamando a interface
    Interface IHM;
    IHM.atendimento(sensorCorrente1, sensorCorrente2, sensorTensao1, sensorTensao2, sensorVazao1, sensorVazao2);

    system("pause");
    return 0;
}