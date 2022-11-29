#include <iostream>
#include "sensorvazao.h"

using namespace std;

SensorVazao::SensorVazao(const string &path, const vector<string> &h) : nomeSensor("desconhecido"), id("desconhecido"), unidade("desconhecida"), horarioInicial("desconhecido"), numMed(0), freqA(0)
{
    this->headers.assign(h.begin(), h.end()); //faz uma copia de h para headers
    this->abrirArquivo(path);
}

SensorVazao::~SensorVazao()
{
    this->file.close();
}

bool SensorVazao::abrirArquivo(const string &path)
{
    try
    {
        this->file.open(path);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
    return false;
}

bool SensorVazao::lerDados()
{
    try
    {
        if (this->file.is_open()) // caso o arquivo esteja aberto, prosseguimos
        {

            string d;
            getline(this->file, d); // toda vez que usar getline leremos uma linha e saltaremos para a proxima no fim
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
                    // atribui para "dadosHeader[n]" um recorte do conteúdo da string de "d" de "idx+1" até o fim da string
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
            this->unidade = dadosHeader[2];
            this->freqA = (int)stod(dadosHeader[3]);
            this->horarioInicial = dadosHeader[4];
            this->numMed = stod(dadosHeader[5]); //stod converte string em double

            Medicao m; // declaração variável auxiliar para armazenar dados
            getline(this->file, d);

            int segundosTotais = 0;

            //cálculo dos segundos totais referentes ao horário inicial
            segundosTotais += stod(this->horarioInicial.substr(0, 2)) * 3600;
            segundosTotais += stod(this->horarioInicial.substr(3, 5)) * 60;
            segundosTotais += stod(this->horarioInicial.substr(6, 8));

            string hora, minuto, segundo;

            for (int i = 0; i < this->numMed; i++)
            {
                getline(this->file, d, ','); // utilizamos getline agora com o parâmetro de parada uma virgula, não quebra de linha
                idx = d.find(",");

                //cálculo de horas, minutos e segundos a cada repetição do laço
                if ((segundosTotais / 3600) < 10)
                {
                    hora = "0" + to_string((segundosTotais / 3600));
                }
                else
                {
                    hora = to_string((segundosTotais / 3600));
                }

                if (((segundosTotais % 3600) / 60) < 10)
                {
                    minuto = "0" + to_string(((segundosTotais % 3600) / 60));
                }
                else
                {
                    minuto = to_string(((segundosTotais % 3600) / 60));
                }

                if ((segundosTotais % 60) < 10)
                {
                    segundo = "0" + to_string((segundosTotais % 60));
                }
                else
                {
                    segundo = to_string((segundosTotais % 60));
                }

                m.horario = hora + ":" + minuto + ":" + segundo; // atribuição do horário referente à repetição do laço
                m.valor = stod(d.substr(idx + 1, d.length() - idx));
                this->dados.push_back(m); //permite alocação dinamica de dados no tempo de execucao
                segundosTotais++;
            }
        }
        else
        {
            return false;
        }
    }
    catch (const std::exception &e)
    {
        // mensagem no terminal caso as instruções anteriores não consigam ser executadas
        std::cout << "Arquivo corrompido. Erro: " << e.what() << '\n';
        return false;
    }
    return true;
}

string SensorVazao::getId()
{
    return this->id;
}

string SensorVazao::getNomeSensor()
{
    return this->nomeSensor;
}

string SensorVazao::getUnidade()
{
    return this->unidade;
}

int SensorVazao::getNumMed()
{
    return this->numMed;
}

int SensorVazao::getFreqAmostragem()
{
    return this->freqA;
}

string SensorVazao::getHorarioInicial()
{
    return this->horarioInicial;
}

bool SensorVazao::getDado(const string &horario, double &dado)
{
    for (auto it = this->dados.begin(); it != this->dados.end(); it++) //laço para varrer o vetor "dados"
    {
        // caso o horário referente à repetição em questão seja igual ao horário fornecido, atribuímos ao "dado" o valor da repetição em questão
        if (it->horario == horario)
        {
            dado = it->valor;
            return true;
        }
    }
    return false;
}

double SensorVazao::getVazao(const string &horario)
{
    for (auto it = this->dados.begin(); it != this->dados.end(); it++) //laço para varrer o vetor "dados"
    {
        // caso o horário referente à repetição em questão seja igual ao horário fornecido, retornamos o valor da vazão da repetição em questão
        if (it->horario == horario)
        {
            return it->valor;
        }
    }
    return 0;
}

double SensorVazao::somaVazao(const string &horario)
{
    double soma = 0;
    for (auto it = this->dados.begin(); it != this->dados.end(); it++) //laço para varrer o vetor "dados"
    {
        soma = soma + it->valor;
        // caso o horário referente à repetição em questão seja igual ao horário fornecido, retornamos o valor da soma das vazões
        if (it->horario == horario)
        {
            return soma;
        }
    }
    return 0;
}