#include "Glns.h"

Glns::Glns( int op_construdor){
    this->op_construdor = op_construdor;
}

void Glns::rodar(Dados &d){

    Solucao best_s(d.n_locais);
    best_s.NN(d);
    Nobank b(0.25,0,1);
    Nobank bs(1,0,0);
    best_s.imprime(d);
   double melhor =best_s.Avalia(d);
    cout<<"custo = "<<melhor<<endl;
    
    
    for(int i=0;i<10000;i++){
        int l = rand() % 10;
        Solucao aux = best_s;
        this->remove(aux,d,bs,l);
        this->insert(aux,d,b);

        vector<Vertice> vv;
        aux.Solucao_Vector(vv);
        d.CO(vv);
        aux.Vector_Solucao(vv);


        double novo = aux.Avalia(d);

       // cout<<novo<<endl;
       if(novo<melhor) {
           melhor = novo;
           best_s = aux;
            cout<<i<<" custo = "<<melhor<<endl;
       }
      
    }
    best_s.imprime(d);
    cout<<"custo = "<<best_s.Avalia(d)<<endl;

}

void Glns::Constroi_inicial(Solucao &s,Dados &d)  {
        Nobank b(-1,-1,-1);
        s.FrameworkInsertionHeuristics(d,0);
        if(op_construdor==0) {
            b.op=0;
        }
        else if(op_construdor==1){
            b.op=1;
            b.lambda=0;

        }
        else if(op_construdor==2){
            b.op=1;
            b.lambda=10;

        }
        else if(op_construdor==3){
            b.op=1;
            b.lambda=1;

        }
        else if(op_construdor==4)this->Constroi_Random(s,d);
         this->insert(s,d,b);

}

void Glns::Constroi_Random(Solucao &s,Dados &d){
    cout<<"em construcao"<<endl;
  
    

}


   Nobank::Nobank(double lambda, double noise,int op){
       int tam =100;
       this->lambda=lambda;
       this->noise=noise;
       this->op=op;

   }

int Nobank::select_k( int l){

    if(lambda == 0) return 0;
    if(lambda >=10) return l-1;
    if(lambda == 1){

        return rand() % l;
    }

    double soma = (1.0 - pow(lambda,l))/(1.0-lambda);


    uniform_real_distribution<double> unif(0,soma);
    random_device re;
    
    double g = unif(re);
    
    double base = 1.0;
    double power =lambda;

    for (int i=0;i<l;i++){
        
        if(base>= g)return i;
      
        power*=lambda;
        base+=power;

    }
    return l-1;


}



void Glns::UnifiedInsertionHeuristic(Solucao &s, Dados &d, Nobank &b){
    int l = s.aberto.size();
    vector<pair<double,int>> D;
    for(int i : s.aberto){
        double Di = s.Di(i,d);
        D.push_back(make_pair(Di,i));
    }
    sort(D.begin(),D.end());
 
  
    while(l>0){
        int k = b.select_k(l);
       
        Vertice v = s.FrameworkInsertionHeuristics(d,D[k].second);
      
        D.erase(D.begin()+k);
       
      
        l--;
        for(int i=0;i<D.size();i++ ){
            double new_Di =10000000;
            for (int j = 0; j < d.Vizinhos[D[i].second].size(); j++) {
                int aux1 = min(d.Custo[v.v][v.a][D[i].second][j],d.Custo[D[i].second][j][v.v][v.a]);
                if (new_Di > aux1) {
                    new_Di = aux1;
              
                }
            }
            D[i].first = min(D[i].first,new_Di);
        }
        
        sort(D.begin(),D.end());
        
        
        

    }

}





void Glns::Cheapest(Solucao &s, Dados &d, Nobank &b){
   int l = s.aberto.size();
   for(int i = 0 ;i<l;i++){
       int v = s.Vi_Cheapest(d);
       s.FrameworkInsertionHeuristics(d,v);
   }

}


void Glns::insert(Solucao &s, Dados &d, Nobank &b){
    if(b.op==0) {
   
        Cheapest(s,d,b);
    
    }
    
    else if(b.op==1){

     UnifiedInsertionHeuristic(s,d,b);
   

    }
}




void Glns::remove(Solucao &s, Dados &d, Nobank &b,int l){
    if(b.op==0)RemovalHeuristicFramework(s,d,b,l);
    if(b.op==1)cout<<endl;

}

void Glns::RemovalHeuristicFramework(Solucao &s, Dados &d, Nobank &b,int l){

    while(l>0){
        
        vector<pair<double,int>> R;
        int k = b.select_k(s.TAM);
        if(b.op==0)UnifiedWorstRemoval(s,d,R);
        l--;
        
        s.remove(R[k].second);
        
    }
}

void Glns::UnifiedWorstRemoval(Solucao &s, Dados &d,vector<pair<double,int>> &R){

    

     int n = s.T.size()-1;
    
    
    int atual = s.T[n].prox;
    
    while (atual != n){
        int anterior = s.T[atual].prev;
        if(anterior==n)anterior =s.T[anterior].prev;
        int prox = s.T[atual].prox;
        if(prox==n)prox =s.T[prox].prox;
        double w = d.Custo[anterior][s.T[anterior].a][atual][s.T[atual].a]+
                    d.Custo[atual][s.T[atual].a][prox][s.T[prox].a]-
                    d.Custo[anterior][s.T[anterior].a][prox][s.T[prox].a];
     
        R.push_back(make_pair(w,atual));
       atual = s.T[atual].prox;
    
    

    }
    sort(R.begin(),R.end());
}









