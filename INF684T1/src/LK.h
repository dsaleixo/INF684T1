

#ifndef LK_H
#define LK_H
#include "Dados.h"
#include "Glns.h"


class LK{
 public:   
    int alpha;
    int init;
    double relax;
    vector<bool> R;
    LK( int alpha,int init, int n,int aceite);
    void rodar(Dados &d);
    void rodar2(vector<Vertice> &v,Dados &d);
    void rodar3(vector<Vertice> &v,Dados &d);
    void inicia(vector<Vertice> &v, Dados d);
    void cortar_ciclo(vector<Vertice> &best_s,vector<Vertice> &P, int i);
    double Gain(vector<Vertice> &v1,vector<Vertice> &v2, Dados &d);
    void vira(vector<Vertice> &P, int i);
    void ImprovePath(vector<Vertice> &P,int depth, Dados &d);
    void ImprovePath2(vector<Vertice> &P,int depth, Dados &d);
    bool GainIsAcceptable(vector<Vertice> &v1,vector<Vertice> &v2,Dados &d);

};

#endif