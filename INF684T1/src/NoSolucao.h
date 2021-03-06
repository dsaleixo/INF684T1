#pragma once
#include <vector>
#include "Vertice.h"
#include "Dados.h"
#include <random>

typedef int (*Operacao)(Dados &d);

using namespace std;

class NoSolucao
{
public:
	
	int a = -1;
    int prev = -1;
    int prox = -1;
    bool usado =false;
	
};


class Solucao{
    
   
public:
    vector<NoSolucao> T;
    set<int> aberto;
    int TAM;
    Solucao(int n);
    void add(Vertice anterior, Vertice atual);
    void remove(int v);
    void NN(Dados &d);
    void imprime(Dados &d);
    float Avalia(Dados &d);
    Vertice FrameworkInsertionHeuristics(Dados &d,int k,float max_noisy); 
    int Vi_Nearest(Dados &d);
    int Vi_Farthest(Dados &d);
    int Vi_Random(Dados &d);
    int Vi_Cheapest(Dados &d);
    void Solucao_Vector(vector<Vertice> &V);
    void Vector_Solucao(vector<Vertice> &V);
    void operator=(const Solucao &s);
    bool operator==(const Solucao &s);
    double Di(int i , Dados &d);
    int getKeismo(int k );
    void NN_alet(Dados &d,int p);
    Vertice NN_V(Vertice v,Dados &d);
    
    
    


};