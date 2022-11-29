#include <iostream>
#include "sensoreletrico.h"
#include <math.h>

using namespace std;

SensorEletrico::SensorEletrico(const string &path, const vector<string> &h) : nomeSensor("desconhecido"), id("desconhecido"), unidade("desconhecida"), horarioInicial("desconhecido"), numMed(0), freqRede(0), freqA(0)
{
    this->headers.assign(h.begin(), h.end()); //cópia de h para headers
    this->abrirArquivo(path);                 // abrir o arquivo do endereço "path"
}

SensorEletrico::~SensorEletrico()
{
    this->file.close();
}

bool SensorEletrico::abrirArquivo(const string &path)
{
    try // faz tentativa de abrir o arquivo
    {
        this->file.open(path);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n'; // caso não consiga executar as instruções anteriores
    }
    return false;
}

bool SensorEletrico::lerDados()
{
    try
    {
        if (this->file.is_open()) // caso o arquivo esteja aberto, prosseguimos
        {

            string d;
            getline(this->file, d); // toda vez que usar getline leremos uma linha e saltaremos para a próxima no fim
            int n = 0;
            int idx; // variável para controle de posição ao longo do vetor

            vector<string> dadosHeader(this->headers.size()); // inicialização de variável auxiliar com mesmo tamanho que "headers"

            while (n < this->headers.size())
            {
                getline(this->file, d); // armazena linha atual em "d" e salta para próxima linha do "file" no fim da leitura
                idx = d.find(":");      // recebe o índice do primeiro ":" que encontrar em "d"

                // faz comparação do conteúdo do começo de "d" até o índice "idx" com conteúdo na posição "n" de "headers"
                if (d.substr(0, idx) == this->headers[n])
                {
                    // atribui para "dadosHeader[n]" um recorte do conteúdo da string de "d" de "idx" até o fim da string
                    dadosHeader[n] = d.substr(idx + 1, d.length() - idx);
                    n++;
                }
                else
                {
                    return false;
                }
            }

            // atribuição dos dados em "dadosHeader" coletados nas variáveis da nossa classe
            this->nomeSensor = dadosHeader[0];
            this->id = dadosHeader[1];
            this->freqRede = stod(dadosHeader[2]);
            this->freqA = (int)stod(dadosHeader[3]);
            this->horarioInicial = dadosHeader[4];
            this->numMed = stod(dadosHeader[5]); // stod converte string em double

            MedicaoRms m; // declaração variável auxiliar para armazenar dados em dadosRMS
            getline(this->file, d);

            for (int i = 0; i < this->numMed; i++)
            {
                getline(this->file, d, ','); // utilizamos getline agora com o parametro de parada uma virgula, não quebra de linha
                idx = d.find(",");
                m.amostra = i; // amostra recebe o índice "i"
                m.valor = stod(d.substr(idx + 1, d.length() - idx));
                this->dadosRMS.push_back(m); // permite alocação dinamica de dados no tempo de execucao
            }
        }
        else
        {
            return false;
        }
    }
    catch (const std::exception &e)
    {
        // imprime no terminal caso não seja possível executar procedimentos anteriores
        std::cout << "Arquivo corrompido. Erro: " << e.what() << '\n';
        return false;
    }
    return true;
}

//métodos para retorno do conteúdo de variáveis protegidas
string SensorEletrico::getId()
{
    return this->id;
}

string SensorEletrico::getNomeSensor()
{
    return this->nomeSensor;
}

string SensorEletrico::getUnidade()
{
    return this->unidade;
}

int SensorEletrico::getNumMed()
{
    return this->numMed;
}

int SensorEletrico::getFreqAmostragem()
{
    return this->freqA;
}

int SensorEletrico::getFreqRede()
{
    return this->freqRede;
}

double SensorEletrico::getDado(const int amostra, double &dado)
{
    //Método utilizado para se obter o valor de um sensor em determinada amostra

    for (auto it = this->dadosRMS.begin(); it != (this->dadosRMS.end() - 1); it++)
    {
        if (it->amostra == amostra)
        {
            dado = it->valor;
            return dado;
        }
    }
    return 0;
}

double SensorEletrico::rms(const string &horario, double &dado, const int n)
{
    //Método para cálculo do valor RMS de dado sensor em determinado tempo
    //utilizando os dados obtidos em cada uma das amostras daquele horário.
    int segundosTotais = 0;
    int amostraInicial = 0;

    segundosTotais += stod(horario.substr(0, 2)) * 3600;
    segundosTotais += stod(horario.substr(3, 5)) * 60;
    segundosTotais += stod(horario.substr(6, 8));
    amostraInicial = ((segundosTotais - 65335) * this->getFreqAmostragem());

    for (auto it = this->dadosRMS.begin(); it != (this->dadosRMS.end()); it++)
    {

        if (it->amostra == amostraInicial)
        {

            dado = it->valor;

            for (int i = 0; i < n; i++)
            {
                auto it2 = it + i;

                dado = sqrt((dado) * (dado) + (it2->valor) * (it2->valor) / n - (it->valor) * (it->valor) / n);
            }
        }
    }

    return dado;
}