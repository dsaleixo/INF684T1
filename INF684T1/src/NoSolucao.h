#pragma once
#include <vector>
#include "Vertice.h"
#include "Dados.h"

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
    vector<NoSolucao> T;
    set<int> aberto;
    int TAM;
    Vertice dump;
public:
    Solucao(int n);
    void add(Vertice anterior, Vertice atual);
    void remove(Vertice v);
    void NN(Dados &d);
    void imprime(Dados &d);
    float Avalia(Dados &d);
    void FrameworkInsertionHeuristics(Dados &d); 
    int Vi_Nearest(Dados &d);
    int Vi_Farthest(Dados &d);
    int Vi_Random(Dados &d);
    int Vi_Cheapest(Dados &d);
    void Solucao_Vector(vector<Vertice> &V);
    void Vector_Solucao(vector<Vertice> &V);
    
    


};