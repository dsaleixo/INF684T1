
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
    int n;
    double score;
    vector<long double> dist_prob;
    Nobank(double lambda, double noise,int op);
    int select_k( int l);

};



class Glns{
    public:
    int op_construdor;
    float p1;
    float p2;
    float p3;
    int num_iterations;
    int num_trials;
    int num_warm ;
    int first_improve;
    int last_improve;
    float epslon;
    vector<Nobank> Bi;
    vector<Nobank> Bf;
    
    Glns(int m, int op_construdor,float p1,float p2,float p3,int num_trials,int num_warm,float epslon );
    
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
    void DistanceRemoval(Solucao &s, Dados &d,vector<pair<double,int>> &R);
    void SegmentRemoval(Solucao &s, Dados &d,int l);
    bool accept(double T, double T_new,float Temp);
    int seleciona_heurisca( vector<Nobank> &Bi);
    void atualiza_weight( vector<Nobank> &Bi);
    void reset_weight(vector<Nobank> &Bi);



    
};
