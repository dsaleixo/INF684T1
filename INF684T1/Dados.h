
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <cmath>
#include "Pontos.h"
using namespace std;
class Dados
{
    public:
        float*** Q;
        float** C;
        float lambda = 0.1164;
        float gamma = 0.0173;
        float m_kappa=10000000;
        float  m_pcn = 100;
        float max_dist= 1.5 ;
        int altura;
        int largura;
        vector<Pontos> Locais;
        int n_locais;


        set<int> obstaculo;
        void ler(string s);
        void imprimir();



};

