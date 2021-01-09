
#pragma once

#include "NoSolucao.h"
#include <stdio.h>
#include <random>

class Nobank{
public:
    double lambda;
    double noise;
    int op;
    double weight;
    vector<long double> dist_prob;
    Nobank(double lambda, double noise,int op);
    int select_k( int l);

};



class Glns{
    public:
    int op_construdor;
    Glns( int op_construdor);
    
    void rodar(Dados &d);
    void Constroi_inicial(Solucao &s, Dados &d);
    void Constroi_InsertRandom(Solucao &s,Dados &d);
    void Constroi_Random(Solucao &s,Dados &d);
    void UnifiedInsertionHeuristic(Solucao &s, Dados &d, Nobank &b);
    void Cheapest(Solucao &s, Dados &d, Nobank &b);
    void insert(Solucao &s, Dados &d, Nobank &b);
    void remove(Solucao &s, Dados &d, Nobank &b,int l);
    void RemovalHeuristicFramework(Solucao &s, Dados &d, Nobank &b,int l);
    void UnifiedWorstRemoval(Solucao &s, Dados &d,vector<pair<double,int>> &R);



    
};
