#include "Glns.h"

Glns::Glns( int op_construdor){
    this->op_construdor = op_construdor;
}

void Glns::rodar(Dados &d){

    Solucao best_s(d.n_locais);
    best_s.FrameworkInsertionHeuristics(d,0);
    Nobank b(0.25,0,1);
    this->insert(best_s,d,b);
    best_s.imprime(d);
    cout<<"custo = "<<best_s.Avalia(d)<<endl;


}

void Glns::Constroi_inicial(Solucao &s,Dados &d)  {

        if(op_construdor==0) s.FrameworkInsertionHeuristics(d,0);
        else if(op_construdor==1)s.FrameworkInsertionHeuristics(d,1);
        else if(op_construdor==2)s.FrameworkInsertionHeuristics(d,2);
        else if(op_construdor==3)s.FrameworkInsertionHeuristics(d,3);
        else if(op_construdor==1)this->Constroi_Random(s,d);

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
        
        cout<<endl<<endl;
        

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











