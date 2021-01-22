
#include "NoSolucao.h"
#include <stdio.h>
#include <random>
#include "LK.h"


class GK{
public:
    vector<pair<double,Solucao>> Populacao;
    int n_populacao;
    int M;
    int r;
    int G=0;
    double melhor;
    int ult_atualizacao;
    GK(int n);
    void inicializa(Dados &d);
    void imprime(Dados &d);
    void remove_duplo();
    void atrapalha();
    void arruma();
    void nova_geracao(Dados &d);
    void cross(Solucao &p1,Solucao &p2,Dados &d);
    void mut(Solucao &p1,Dados &d);
    void LS_CO(Dados &d);
    bool criterioParada();
    void opt2(vector<Vertice> &v, Dados &d);
    void cortar_ciclo(vector<Vertice> &best_s,vector<Vertice> &P, int i);

    void vira(vector<Vertice> &P, int i);

};