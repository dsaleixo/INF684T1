#pragma once
#include <vector>
#include "Vertice.h"
#include "Dados.h"

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
    Vertice FrameworkInsertionHeuristics(Dados &d,int k); 
    int Vi_Nearest(Dados &d);
    int Vi_Farthest(Dados &d);
    int Vi_Random(Dados &d);
    int Vi_Cheapest(Dados &d);
    void Solucao_Vector(vector<Vertice> &V);
    void Vector_Solucao(vector<Vertice> &V);
    void operator=(const Solucao &s);
    double Di(int i , Dados &d);
    
    


};