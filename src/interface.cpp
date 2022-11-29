
//Nome: Aarão de Sousa Rodrigues  Matrícula: 201669054B
//Nome: Elias Lopes Oliveira  Matrícula: 201769014B
//Nome: Henrique Silva Coutinho  Matricula: 201769014A
//Nome: Matheus Taninho Reinh  Matrícula: 201769021B

#include <iostream>
#include "sensorvazao.h"
#include "sensortensao.h"
#include "sensorcorrente.h"
#include "interface.h"
#include <vector>

using namespace std;



void Interface::imprimeVolume(SensorVazao &v1, SensorVazao &v2, const string &hora)
{
    cout << "Volume do reservatorio em " << hora << " h: " << v1.somaVazao(hora) - v2.somaVazao(hora) * 1000 << " L" << endl;
    //Metodo utilizado para calculo do volume do reservatorio
    //Faz a subtração de todo liquido que entrou (soma das vazões de entrada) 
    //e todo o líquido que saiu (soma da vazão de saída)
}

int Interface::getNumHorariosEnvolvidos(const string &hora)
{
    //Método utilizado para obter a quantidade de segundos que se passaram do tempo inicial 
    //até um tempo determinado
    //Pegamos os segundos totais do tempo designado e subtraimos os segundos do tempo inicial
    int segundosTotais = 0;
    segundosTotais += stod(hora.substr(0, 2)) * 3600;
    segundosTotais += stod(hora.substr(3, 5)) * 60;
    segundosTotais += stod(hora.substr(6, 8));
    return (segundosTotais - 65335);
}

int Interface::getNumAmostrasEnvolvidas(const string hora, SensorEletrico &sensor)
{
    //Método utilizado para localizar a primeira amostra de determiando horário
    //Pegamos os segundos totais de determinado horario, subtraimos do horário inicial
    //e multilplicamos pela frequencia de amostragem. Assim obtemos a amostra incial 
    //do tempo desejado.

    int segundosTotais = 0;
    segundosTotais += stod(hora.substr(0, 2)) * 3600;
    segundosTotais += stod(hora.substr(3, 5)) * 60;
    segundosTotais += stod(hora.substr(6, 8));
    return (segundosTotais - 65335) * sensor.getFreqAmostragem();
}
double Interface::potenciaAtiva(const string hora, SensorTensao &sensorTensao1, SensorCorrente &sensorCorrente1, const int n)
{
    //Método utilizado para cálculo da potência ativa
    //Pegamos a amostra inicial de determinado horario e fazemos o calculo para
    //a potencia ativa com n amostras por segundo.
    double potenciaAtiva = 0;
    double m;

    int n2 = this->getNumAmostrasEnvolvidas(hora, sensorTensao1);
    for (int i = 1; i < n - 1; i++)
    {
        potenciaAtiva = potenciaAtiva + (sensorTensao1.getDado(n2 + i, m) * sensorCorrente1.getDado(n2 + i, m)) / n;
    }
    return potenciaAtiva;
}

double Interface::energia(const string hora, SensorTensao &sensorTensao1, SensorCorrente &sensorCorrente1, const int n)
{
int segundos = this->getNumHorariosEnvolvidos(hora);
double energia = 0;

for (int i = 0; i < segundos; i++)
{
    energia = energia + this->potenciaAtiva(hora,sensorTensao1,sensorCorrente1,n);
}

return energia/(3600*1000);



}


void Interface::atendimento(SensorCorrente &sensorCorrente1, SensorCorrente &sensorCorrente2, SensorTensao &sensorTensao1, SensorTensao &sensorTensao2, SensorVazao &sensorVazao1, SensorVazao &sensorVazao2)
{
    //Método para o atendimento 

    double m;
    string hora;
    int operacao;
    int atd = 1;
    while (atd == 1)
    {
        cout << " " << endl;
        cout << "Bem vindo ao banco de dados do reservatorio" << endl;
        cout << "1-Vazao do tanque" << endl;
        cout << "2-Volume do reservatorio" << endl;
        cout << "3-Nome do sensor" << endl;
        cout << "4-ID de um sensor" << endl;
        cout << "5-Valor RMS dos sensores eletricos" << endl;
        cout << "6-Potencia de uma bomba" << endl;
        cout << "7-Potencia aparente de uma bomba" << endl;
        cout << "8-Fator de potencia de uma bomba" << endl;
        cout << "9-Energia consumida por uma bomba" << endl;
        cout << "Digite o numero da informacao que deseja obter: ";
        cin >> operacao;
        switch (operacao)
        {
        case 1:
            cout << "Digite o horario(hh:mm:ss): ";
            cin >> hora;
            cout << "Vazao de entrada: " << sensorVazao1.getVazao(hora) << " " << sensorVazao1.getUnidade() << endl;
            cout << "Vazao de saida: " << sensorVazao2.getVazao(hora)*1000 << " " << sensorVazao1.getUnidade() << endl;
            break;
        case 2:
            cout << "Digite o horario(hh:mm:ss): ";
            cin >> hora;
            this->imprimeVolume(sensorVazao1, sensorVazao2, hora);

            break;
        case 3:
            int operacao2;

            cout << "1-Sensor Corrente 1" << endl;
            cout << "2-Sensor Corrente 2" << endl;
            cout << "3-Sensor Tensao 1" << endl;
            cout << "4-Sensor Tensao 2" << endl;
            cout << "5-Sensor Vazao 1" << endl;
            cout << "6-Sensor Vazao 2" << endl;
            cout << "Escolha o sensor: ";
            cin >> operacao2;

            switch (operacao2)
            {
            case 1:
                cout << "Nome: " << sensorCorrente1.getNomeSensor() << endl;
                break;
            case 2:
                cout << "Nome: " << sensorCorrente2.getNomeSensor() << endl;
                break;
            case 3:
                cout << "Nome: " << sensorTensao1.getNomeSensor() << endl;
                break;
            case 4:
                cout << "Nome: " << sensorTensao2.getNomeSensor() << endl;
                break;
            case 5:
                cout << "Nome: " << sensorVazao1.getNomeSensor() << endl;
                break;
            case 6:
                cout << "Nome: " << sensorVazao2.getNomeSensor() << endl;
                break;
            }

            break;
        case 4:
            int operacao3;

            cout << "1-Sensor corrente 1" << endl;
            cout << "2-Sensor corrente 2" << endl;
            cout << "3-Sensor tensao 1" << endl;
            cout << "4-Sensor tensao 2" << endl;
            cout << "5-Sensor vazao 1" << endl;
            cout << "6-Sensor vazao 2" << endl;
            cout << "Escolha o sensor: ";
            cin >> operacao3;

            switch (operacao3)
            {
            case 1:
                cout << "ID: " << sensorCorrente1.getId() << endl;
                break;
            case 2:
                cout << "ID: " << sensorCorrente2.getId() << endl;
                break;
            case 3:
                cout << "ID: " << sensorTensao1.getId() << endl;
                break;
            case 4:
                cout << "ID: " << sensorTensao2.getId() << endl;
                break;
            case 5:
                cout << "ID: " << sensorVazao1.getId() << endl;
                break;
            case 6:
                cout << "ID: " << sensorVazao2.getId() << endl;
                break;
            }

            break;
        case 5:
            int operacao4;

            cout << "1-Sensor corrente 1" << endl;
            cout << "2-Sensor corrente 2" << endl;
            cout << "3-Sensor tensao 1" << endl;
            cout << "4-Sensor tensao 2" << endl;
            cout << "Escolha o sensor: ";
            cin >> operacao4;
            cout << "Digite o instante (hh:mm:ss): ";
            cin >> hora;

            switch (operacao4)
            {
            case 1:
                cout << "Valor RMS Corrente1: " << sensorCorrente1.rms(hora, m, sensorCorrente1.getFreqAmostragem()) <<" A"<< endl;
                break;
            case 2:
                cout << "Valor RMS Corrente2: " << sensorCorrente2.rms(hora, m, sensorCorrente2.getFreqAmostragem()) <<" A"<< endl;
                break;
            case 3:
                cout << "Valor RMS Tensao1: " << sensorTensao1.rms(hora, m, sensorTensao1.getFreqAmostragem()) <<" V"<< endl;
                break;
            case 4:
                cout << "Valor RMS Tensao2: " << sensorTensao2.rms(hora, m, sensorTensao2.getFreqAmostragem()) <<" V"<< endl;
                break;
            }

            break;
        case 6:
            int operacao6;

            cout << "1-Bomba 1" << endl;
            cout << "2-Bomba 2" << endl;
            cout << "Escolha a Bomba: ";
            cin >> operacao6;
            cout << "Digite o horario (hh:mm:ss): ";
            cin >> hora;

            switch (operacao6)
            {
            case 1:
                cout << "Potencia Ativa Bomba 1: " << potenciaAtiva(hora, sensorTensao1, sensorCorrente1, sensorTensao1.getFreqAmostragem()) <<" W"<< endl;
                break;
            case 2:
                cout << "Potencia Ativa Bomba 2: " << potenciaAtiva(hora, sensorTensao2, sensorCorrente2, sensorTensao2.getFreqAmostragem()) <<" W"<< endl;
                break;
            }
            break;

        case 7:
            int operacao7;

            cout << "1-Bomba 1" << endl;
            cout << "2-Bomba 2" << endl;
            cout << "Escolha a Bomba: ";
            cin >> operacao7;
            cout << "Digite o horario (hh:mm:ss): ";
            cin >> hora;

            switch (operacao7)
            {
            case 1:
                cout << "Potencia Aparente da Bomba 1: " << sensorCorrente1.rms(hora, m, sensorCorrente1.getFreqAmostragem()) * sensorTensao1.rms(hora, m, sensorTensao1.getFreqAmostragem()) <<" VA"<< endl;
                break;
            case 2:
                cout << "Potencia Aparente da Bomba 2: " << sensorCorrente2.rms(hora, m, sensorCorrente2.getFreqAmostragem()) * sensorTensao2.rms(hora, m, sensorTensao2.getFreqAmostragem()) <<" VA"<< endl;
                break;
            }
            break;
        case 8:
            int operacao8;

            cout << "1-Bomba 1;" << endl;
            cout << "2-Bomba 2." << endl;
            cout << "Escolha a Bomba: ";
            cin >> operacao8;
            cout << "Digite o horario (hh:mm:ss): ";
            cin >> hora;

            switch (operacao8)
            {
            case 1:
                cout << "Fator de Potencia da Bomba 1: " << (potenciaAtiva(hora, sensorTensao1, sensorCorrente1, sensorTensao1.getFreqAmostragem())) / (sensorCorrente1.rms(hora, m, sensorCorrente1.getFreqAmostragem()) * sensorTensao1.rms(hora, m, sensorTensao1.getFreqAmostragem())) << endl;
                break;
            case 2:
                cout << "Fator de Potencia da Bomba 2: " << (potenciaAtiva(hora, sensorTensao2, sensorCorrente2, sensorTensao2.getFreqAmostragem())) / (sensorCorrente2.rms(hora, m, sensorCorrente2.getFreqAmostragem()) * sensorTensao2.rms(hora, m, sensorTensao2.getFreqAmostragem())) << endl;
                break;
            }
            break;
        case 9:
            int operacao9;

            cout << "1-Bomba 1;" << endl;
            cout << "2-Bomba 2." << endl;
            cout << "Escolha a Bomba: ";
            cin >> operacao9;
            cout << "Digite o horario (hh:mm:ss): ";
            cin >> hora;

            switch (operacao9)
            {
            case 1:
                cout << "Energia consumida pela Bomba 1: " << energia(hora, sensorTensao1, sensorCorrente1, sensorTensao1.getFreqAmostragem()) << endl;
                break;
            case 2:
                cout << "Energia consumida pela Bomba 2: " <<  energia(hora, sensorTensao2, sensorCorrente2, sensorTensao2.getFreqAmostragem()) << endl;
                break;
            }
            break;
        case 10:
            atd = 0;
            break;
        default:
            break;
        }
    }
}
