#include "Glns.h"

Glns::Glns(){
    ;
}

Glns::Glns( int m,int op_construdor,float p1,float p2,float p3,int num_trials,int num_warm, float epslon ){
    this->op_construdor = op_construdor;
    this->p1 = p1;
    this->num_iterations =60*m;
    this->p2=p2;
    this->p3=p3;
    this->num_trials=num_trials;
    this->num_warm =num_warm ;
    this->first_improve = m*15;
    this->last_improve=m*30;
    this->epslon = epslon;
    double labdas_i[]= {0,0.1,0.25,0.5,1.2,1.75,10};
    double labdas_f[]= {1,1.1, 1.41,2,10};
    double noise[] = {0,0.1,0.25,0.5,0.75};
    for (double i : labdas_i){
        for(double j : noise){
            Nobank aux(i,j,1);
            this->Bi.push_back(aux);

        }
    }
    for(double j : noise){
        Nobank aux(0,j,0);
        this->Bi.push_back(aux);

    }
    for(double i : labdas_f){
        for(int j=0;j<2;j++){
            Nobank aux(i,0,1);
            this->Bf.push_back(aux);
        }
    }
    Nobank aux(0,0,2);
    this->Bf.push_back(aux);
    cout<<"B1 "<<Bi.size()<<endl;
    cout<<"Bf "<<Bf.size()<<endl;
    
}

void Glns::rodar(Dados &d){
    Nobank b(0.1,0.1,1);
    
    Solucao best_s(d.n_locais);
    
    double melhor =100000;

    for(int nt=0;nt<this->num_trials;nt++){
        Solucao T(d.n_locais);
        if(this->op_construdor==0){
             T.FrameworkInsertionHeuristics(d,0,0.0);
          this->insert(T,d,b);
        }
       else if (this->op_construdor==1) T.NN(d);
       else this->Constroi_Random(T,d);
       
        double  T_custo = T.Avalia(d);
        int ult_m=0;
        if(T_custo< melhor){
            melhor = T_custo;
            best_s = T;
            cout<<"custo = "<<melhor<<endl;
        }

        for(int rw = 0;rw<this->num_warm;rw++){
            double ln_meio= 0.18232155679;
            float temp= (T_custo - T_custo*(1+this->p1))/ln_meio;
            float c = pow((T_custo - T_custo*(1+this->p2))/(ln_meio*temp),1.0/this->num_iterations);
            this->atualiza_weight(this->Bi);
            this->atualiza_weight(this->Bf);
            float dest =0.35;
            for(int i=0;i<this->num_iterations;i++){
                //cout<<i<<" "<<this->num_iterations<<endl;
                if (this->num_iterations/2==i){
                    this->reset_weight(this->Bi);
                    this->reset_weight(this->Bf);
                }
                int hf = this->seleciona_heurisca(this->Bf);
                int hi = this->seleciona_heurisca(this->Bi);
            // cout<<"ddd "<<hf<<' '<<hi<<endl;
                int l = rand() % int(d.n_locais*dest);
                Solucao T_new = T;
                this->remove(T_new ,d,this->Bf[hf],l);
                this->insert(T_new ,d,this->Bi[hi]);

                vector<Vertice> vv;
                T_new .Solucao_Vector(vv);
                d.CO(vv);
                T_new .Vector_Solucao(vv);


                double novo = T_new .Avalia(d);

            // cout<<novo<<endl;
                if(novo<melhor) {
                    melhor = novo;
                    best_s = T_new ;
                        cout<<i<<" custo = "<<melhor<<" "<<hi<<" "<<hf<<endl;
                        ult_m = i;
                }
                if (this->accept(T_custo,novo,temp)){
                    T_custo=novo;
                    T= T_new;
                }
                temp = temp*c;
                

                if(this->last_improve<i - ult_m){
                    break;
                }
                double score = max((T_custo-novo)/T_custo,0.0);
                Bi[hi].score +=score;
                Bf[hf].score +=score;
                Bi[hi].n +=1;
                Bf[hf].n +=1;
               
            // cout<<hi<<" "<<hf<<endl;
                int y;
                //cin>>y;
                
            }
        }
    }
    best_s.imprime(d);
    cout<<"custo = "<<best_s.Avalia(d)<<endl;

}

void Glns::reset_weight(vector<Nobank> &B){
    for(int i =0;i<B.size();i++){
        B[i].score = 0;
        B[i].weight = 1;
        B[i].n=0;
    }
}


void Glns::atualiza_weight( vector<Nobank> &B){

    for(int i =0; i < B.size();i++){
        if(B[i].n>0){
            B[i].weight = this->epslon*B[i].weight + (1-this->epslon)*(B[i].score/B[i].n);
        }
        
    }

}

bool Glns::accept(double T, double T_new,float Temp){

    float g = min(exp((T-T_new)/Temp),1.0);
    float alet = (1.0*(rand()%1000))/1000;
    
    return alet <g;
    
}

int Glns::seleciona_heurisca( vector<Nobank> &B){
    

    double soma=0;
    for(int i=0;i<B.size();i++){
        soma+=B[i].weight;
    }


    uniform_real_distribution<double> unif(0,soma);
    random_device re;
    
    double g = unif(re);
    double aux=0;
    for(int i=0;i<B.size();i++){
        aux+=B[i].weight;
        if(aux>=g){
            return i;
        }
    }
    return B.size()-1;
}


void Glns::Constroi_inicial(Solucao &s,Dados &d)  {
        Nobank b(-1,-1,-1);
        s.FrameworkInsertionHeuristics(d,0,0.0);
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
    
    Vertice dump;
    dump.v=s.T.size()-1;

    while(s.aberto.size()>0){
        int g = s.Vi_Random(d);
        Vertice v(g,0);
        s.add(dump,v);
        
        dump = v;

    }
  
    

}


   Nobank::Nobank(double lambda, double noise,int op){
       int tam =100;
       this->lambda=lambda;
       this->noise=noise;
       this->op=op;
       this->weight=1;
        this->n=0;
        this->score=0;

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
       
        Vertice v = s.FrameworkInsertionHeuristics(d,D[k].second,b.noise);
      
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
       s.FrameworkInsertionHeuristics(d,v,b.noise);
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
    if(b.op==0||b.op==1)RemovalHeuristicFramework(s,d,b,l);
    if(b.op==2)SegmentRemoval(s,d,l);

}

void Glns::RemovalHeuristicFramework(Solucao &s, Dados &d, Nobank &b,int l){

    while(l>0){
        
        vector<pair<double,int>> R;
        int k = b.select_k(s.TAM);
        
        if(b.op==0)UnifiedWorstRemoval(s,d,R);
        if(b.op==1)DistanceRemoval(s,d,R);
        l--;
       // cout<<"remove "<<R[k].second<<" "<<R[k].first<<endl;
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





void Glns::DistanceRemoval(Solucao &s, Dados &d,vector<pair<double,int>> &R){
    int g = rand() % s.TAM;
    int v = s.getKeismo(g);
    int n = s.T.size()-1;
    
    
    int atual = s.T[n].prox;
    
    while (atual != n){
       double menor=1000000;
        for (int j = 0; j < d.Vizinhos[atual].size(); j++) {
            double aux1 = min(d.Custo[atual][j][v][s.T[v].a],d.Custo[v][s.T[v].a][atual][j]);
                 if (menor > aux1) {
                    menor = aux1;
                
                }


        }
      
        R.push_back(make_pair(menor,atual));
       atual = s.T[atual].prox;
    
    

    }
   
     sort(R.begin(),R.end());
     return;
    for(int i =0;i<R.size();i++){
        cout<<R[i].second<<" "<<R[i].first<<endl;
    }

    



}





void Glns::SegmentRemoval(Solucao &s, Dados &d,int l){
    int g = rand() % s.TAM;
    int v = s.getKeismo(g);
    int n = s.T.size()-1;
    
    
    int atual = s.T[n].prox;
    
    for(int i=0;i<l;i++){
     
        
        int anterior = s.T[atual].prev;
      if(anterior == n) anterior = s.T[anterior].prev;
        s.remove(anterior);
       atual = s.T[atual].prox;
        if(atual == n)atual = s.T[atual].prox;
    

    }
}

