#include "LK.h"


LK::LK( int alpha, int init,int n,int aceite){
    this->alpha = alpha;
    this->init = init;
    if(aceite == 0)this->relax=1.0;
    if(aceite == 1)this->relax=1.01;
    if(aceite == 2)this->relax=1.05;
    if(aceite == 3)this->relax=1.1;
    if(aceite == 4)this->relax=1.2;
    for(int i =0 ;i<n;i++)R.push_back(false);

}

void LK::inicia(vector<Vertice> &v, Dados d){
    Glns g;
    Nobank b(1,0.1,1);
    Solucao T(d.n_locais);
        if(this->init==0){
             T.FrameworkInsertionHeuristics(d,0,0.0);
            g.insert(T,d,b);
        }
       else if (this->init==1) T.NN(d);
       else g.Constroi_Random(T,d);

       T.Solucao_Vector(v);
}


void LK::cortar_ciclo(vector<Vertice> &best_s,vector<Vertice> &P, int i){
    for(int j=0;j<best_s.size();j++){
        P.push_back(best_s[(i+j)%best_s.size()]);
    }
}

double LK::Gain(vector<Vertice> &v1,vector<Vertice> &v2,Dados &d){
    
    d.Wco_Busca(v2);
    double aux1 = d.Avalia_w(v1);
    double aux2 = d.Avalia_w(v2);
    return  aux1 - aux2;
}

void LK::vira(vector<Vertice> &P, int i){
    int n = (P.size() - i)/2;
    int m = P.size() -1;
    for(int j=0; j<n;j++ ){
        Vertice aux = P[j+i];
        P[j+i]=P[m-j];
        P[m-j]= aux;
    }

    
}

bool LK::GainIsAcceptable(vector<Vertice> &v1,vector<Vertice> &v2,Dados &d){
    double a1 = d.Avalia_w(v1);
    double a2 = d.Avalia_w(v2);
    return  a1 < a2*this->relax;
}

void LK::ImprovePath(vector<Vertice> &P,int depth,Dados &d){

    if(depth>=this->alpha){
        double gain = -1;
        vector<Vertice> T=P;
        
        for(int i = 1; i<P.size()-1;i++){
            if(this->R[P[i].v])continue;
            vector<Vertice> Aux = P;
            this->vira(Aux,i);
            double aux = this->Gain(P,Aux,d);
            
            if(aux>gain){
                T=Aux;
                gain = aux;
            }

        }


        if(this->GainIsAcceptable(T,P,d)){
            d.CO(T);
            double T_c = d.Avalia(T);
            double P_c = d.Avalia(P);
            if(T_c < P_c){
                P=T;
                
            }
        }
    
    }
    else{
        for(int i = 1; i<P.size()-1;i++){
            if(this->R[P[i].v])continue;
            vector<Vertice> Aux = P;
            this->vira(Aux,i);
            d.Wco_Busca(Aux);
            
            if(this->GainIsAcceptable(Aux,P,d)){
                
                d.CO(Aux);
                double aux_c = d.Avalia(Aux);
                double P_c = d.Avalia(P);
                if(aux_c>=P_c){
                    this->R[P[i].v] = true;
                    this->ImprovePath(Aux,depth +1,d);
                    this->R[P[i].v] = false;
                }

                if(aux_c<P_c){
                    //this->ImprovePath(Aux,depth +1,d);
                    P=Aux;
                    return;
                }
            }

        }

    }



}


void LK::rodar(Dados &d){
    cout<<this->alpha<<" "<<this->relax<<endl;
    vector<Vertice> best_s;
    this->inicia(best_s,d);

    double melhor=  d.Avalia(best_s);
    int i=0;
    int m = d.n_locais;
     cout<<"melhorou "<<melhor<<endl;
    d.imprimir(best_s);
    while(i<m){
        vector<Vertice> P;
        cortar_ciclo(best_s,P,i);

        this->ImprovePath(P,1,d);
        double novo = d.Avalia(P);
      //  cout<<novo<<endl;
        if(novo-melhor<-0.0005){
            melhor = novo;
            best_s = P;
            cout<<"melhorou "<<novo<<endl;
            i=0;
        }else{
            i++;
        }
      



    }
    d.imprimir(best_s);


}

void LK::rodar2(vector<Vertice> &best_s,Dados &d){



    double melhor=  d.Avalia(best_s);
    int i=0;
    int m = d.n_locais;
 
   
    while(i<m){
        vector<Vertice> P;
        cortar_ciclo(best_s,P,i);

        this->ImprovePath2(P,1,d);
        double novo = d.Avalia(P);
      //  cout<<novo<<endl;
        if(novo-melhor<-0.0005){
            melhor = novo;
            best_s = P;
            return;
            i=0;
        }else{
            i++;
        }
      



    }
    


}


void LK::rodar3(vector<Vertice> &best_s,Dados &d){



    double melhor=  d.Avalia(best_s);
    int i=0;
    int m = d.n_locais;
 
   
    while(i<m){
        vector<Vertice> P;
        cortar_ciclo(best_s,P,i);

        this->ImprovePath(P,1,d);
        double novo = d.Avalia(P);
      //  cout<<novo<<endl;
        if(novo-melhor<-0.0005){
            melhor = novo;
            best_s = P;
           
            i=0;
        }else{
            i++;
        }
      



    }
    


}


void LK::ImprovePath2(vector<Vertice> &P,int depth,Dados &d){

       

        double c_p = d.Avalia(P);
        vector<Vertice> T=P;
        double mel =0;
        for(int i = 1; i<P.size()-1;i++){
            if(this->R[P[i].v])continue;
            vector<Vertice> Aux = P;
            this->vira(Aux,i);
            double aux = c_p - d.Avalia(Aux);
            
            if(aux>mel){
                T=Aux;

                mel=aux;
                break;
              
            }

        }
        if(mel>0)P=T;

      
        
        
    
    }