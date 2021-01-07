#include "NoSolucao.h"

 Solucao::Solucao(int n){
    for (int i = 0; i < n; i++) {
        aberto.insert(i);
    }
    TAM = 0;
     for(int i =0;i<=n;i++){
         NoSolucao s;
         T.push_back(s);
     }
     T[n].prev = n;
     T[n].prox = n;
     T[n].usado = true;

     
     
 }

 void Solucao::add(Vertice anterior, Vertice atual){
    TAM++;
       
    T[atual.v].a = atual.a;
    T[atual.v].prev = anterior.v;
    T[atual.v].prox = T[anterior.v].prox;
    T[anterior.v].prox = atual.v;
    T[T[atual.v].prox].prev = atual.v;
    T[atual.v].usado = true;
    aberto.erase(atual.v);
        
 }
 void Solucao::remove(Vertice v){
     int anterior = T[v.v].prev;
     int prox = T[v.v].prox;

     T[anterior].prox = prox;
     T[prox].prev = anterior;
     T[v.v].usado = false;
     TAM--;
     aberto.insert(v.v);

 }

 void Solucao::NN(Dados &d){
     vector<Vertice> v;
    d.NN(v);
    Vertice dump;
    dump.v=T.size()-1;
    for(int i=0;i<v.size();i++){
        this->add(dump,v[i]);
        
        dump = v[i];

    }

 }

void Solucao::imprime(Dados &d){
    int n = T.size()-1;

    
    int atual = T[n].prox;
   
    cout<<"[ ";
    while (atual != n){
       cout << "(" <<d.Locais[ d.Vizinhos[atual][T[atual].a]].id << "," <<d.Locais[ atual ].id<< ") ";
       atual = T[atual].prox;
    }

    cout<<" ]"<<endl;


}

float Solucao::Avalia(Dados &d){

    if(TAM<=1)return 0;

     int n = T.size()-1;
    int aux = T[n].prev;
    int aux1 = T[n].prox;
    float soma = d.Custo[aux][T[aux].a][aux1][T[aux1].a];
    int anterior = n;
   
    int atual = T[anterior].prox;
    
    while (T[atual].prox != n){
      anterior = atual;
       atual = T[atual].prox;
    
       soma+=d.Custo[anterior][T[anterior].a][atual][T[atual].a];

    }
    return soma;
}



void Solucao::FrameworkInsertionHeuristics(Dados &d){
    int n = T.size()-1;
    if(TAM==0){
        Vertice c(-1,0);
        float menor = 10000000;
        for (int i = 0; i < d.Vizinhos[0].size(); i++) {
            if (d.C[0][d.Vizinhos[0][i]] < menor) {
                menor = d.C[0][d.Vizinhos[0][i]];
                c.v = d.Vizinhos[0][i];
            }
        }
        Vertice dump( T.size()-1,-1);
        this->add(dump,c);
        return ;
    }

    int Vi = this->Vi_Cheapest(d);


    float menor = 1000000;
    Vertice dumb(n,n);
    Vertice v(Vi,-1);

    int aux = T[n].prev;
    int aux1 = T[n].prox;
    for (int i = 0; i < d.Vizinhos[Vi].size(); i++) {
        float w = d.Custo[aux][T[aux].a][Vi][i] +
                d.Custo[Vi][i][aux1][T[aux1].a] -
                    d.Custo[aux][T[aux].a][aux1][T[aux1].a];
        if (w < menor) {
            menor = w;
            v.a=i;
            
        }
    }


    
    int anterior = n;
   
    int atual = T[anterior].prox;
    
    while (T[atual].prox != n){
      anterior = atual;
       atual = T[atual].prox;
    
        for (int i = 0; i < d.Vizinhos[Vi].size(); i++) {
            float w = d.Custo[anterior][T[anterior].a][Vi][i] +
                    d.Custo[Vi][i][atual][T[atual].a]-
                        d.Custo[anterior][T[anterior].a][atual][T[atual].a];
            if (w < menor) {
                menor = w;
                v.a=i;
                dumb.v=anterior;
                
            }
        }

   

    }
    this->add(dumb,v);

}


int Solucao::Vi_Farthest(Dados &d){

    float menor = 10000000;
    int Vi=-1;

    int n = T.size()-1;
   

    for (int i : aberto) {
        for (int j = 0; j < d.Vizinhos[i].size(); j++) {
            int atual = T[n].prox;
            while (atual != n){
                int aux1 = min(d.Custo[atual][T[atual].a][i][j],d.Custo[i][j][atual][T[atual].a]);
                 if (menor > aux1) {
                menor = aux1;
                Vi = i;
                
                }
                atual = T[atual].prox;

            }
        }
           
    }
    return Vi;
}





void Solucao::Solucao_Vector(vector<Vertice> &V){
    V.clear();
    int n = T.size()-1;
    int atual = T[n].prox;
   
    while (atual != n){
       //cout << "(" <<d.Locais[ d.Vizinhos[atual][T[atual].a]].id << "," <<d.Locais[ atual ].id<< ") ";
       Vertice c(atual,T[atual].a);
       V.push_back(c);
       atual = T[atual].prox;
    }




}



void Solucao::Vector_Solucao(vector<Vertice> &v){
     Vertice dump;
    dump.v=T.size()-1;
    for(int i=0;i<v.size();i++){
        this->add(dump,v[i]);
        
        dump = v[i];

    }

}




int Solucao::Vi_Nearest(Dados &d){

    float maior = -1;
    int Vi=-1;

    int n = T.size()-1;
   

    for (int i : aberto) {
        float menor = 100000;
        for (int j = 0; j < d.Vizinhos[i].size(); j++) {
            int atual = T[n].prox;
            while (atual != n){
                int aux1 = min(d.Custo[atual][T[atual].a][i][j],d.Custo[i][j][atual][T[atual].a]);
                 if (menor > aux1) {
                menor = aux1;
                
                }
                atual = T[atual].prox;

            }
        }
        if(maior<menor){
            Vi=i;
            maior = menor;
        }
           
    }
    return Vi;
}


int Solucao::Vi_Random(Dados &d){
    int n = aberto.size();
    int g = rand() % n;
    int cont = 0;
    for (int i : aberto) {
        if(g==cont)return i;
        cont++;
    }
}


int Solucao::Vi_Cheapest(Dados &d){
    float menor = 1000000;
    int Vi_m = -1;
     int n = T.size()-1;
    for(int Vi : aberto){
        Vertice v(Vi,-1);
        cout<<"teste "<<Vi<<endl;
        int aux = T[n].prev;
        int aux1 = T[n].prox;
        for (int i = 0; i < d.Vizinhos[Vi].size(); i++) {
            float w = d.Custo[aux][T[aux].a][Vi][i] +
                    d.Custo[Vi][i][aux1][T[aux1].a] -
                        d.Custo[aux][T[aux].a][aux1][T[aux1].a];
            if (w < menor) {
                menor = w;
                Vi_m =Vi;
                
            }
        }


        
        int anterior = n;
    
        int atual = T[anterior].prox;
        
        while (T[atual].prox != n){
            anterior = atual;
            atual = T[atual].prox;
        
            for (int i = 0; i < d.Vizinhos[Vi].size(); i++) {
                float w = d.Custo[anterior][T[anterior].a][Vi][i] +
                        d.Custo[Vi][i][atual][T[atual].a]-
                            d.Custo[anterior][T[anterior].a][atual][T[atual].a];
                if (w < menor) {
                    menor = w;
                    Vi_m=Vi;
                   
                    
                }
            }

    

        }
    }
    cout<<"fdf "<<Vi_m<<endl;
    cin>>Vi_m;
    return Vi_m;
}

