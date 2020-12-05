
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <cmath>
#include "Pontos.h"
#include <algorithm> 
#include <map>

using namespace std;
class Dados
{
    public:
        float*** Q;
        float**** Custo;
        float** C;
        float lambda = 0.1164;
        float gamma = 0.0173;
        float m_kappa=10000000;
        float  m_pcn = 100;
        float max_dist= 1.5 ;
        int altura;
        int largura;
        vector<Pontos> Locais;
        vector<int> Map_locais_variaveis;
        vector<vector<int>> Vizinhos;
        vector < map<int, int>> Map_vizinho;
        int n_locais;
        int**** C_floyd;


        set<int> obstaculo;
        void ler(string s);
        void imprimir();
        void floyd2();
        vector<int> Caminho_floyd(int i, int li, int j, int lj);


};

