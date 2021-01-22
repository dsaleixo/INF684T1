#include "GK.h"

GK::GK(int n){
    this->M=n;
    this->n_populacao = 2*this->M;
    this->melhor=10000000;
    this->ult_atualizacao=0;
}

bool GK::criterioParada(){
    return this->ult_atualizacao>35;
}


void GK::inicializa(Dados &d){
    
    for(int i =0;i<this->M;i++){
     
        Solucao s(this->M);
        int j[] = {10, 15,15,20,20};

        int jj = rand()%5;
        s.NN_alet(d,j[jj]);
        double c= s.Avalia(d);
        this->Populacao.push_back(make_pair(c,s));

        G=0;
    }

}
void GK::imprime(Dados &d){
   
    for(int i=0;i<this->Populacao.size();i++ ){
        cout<<"Individuo "<<i<<endl;
        Populacao[i].second.imprime(d);
        cout<<Populacao[i].first<<endl;
        cout<<endl<<endl;
    }
}


void GK::atrapalha(){
    int fim = this->Populacao[0].second.T.size()-1;
    for(int i=0;i<this->Populacao.size();i++ ){
        Vertice aux(fim,0);
        this->Populacao[i].second.remove(aux.v);
        int novo = rand()%(fim-1);
        Vertice aux2(novo,0);
        this->Populacao[i].second.add(aux2,aux);
    }

}


void GK::arruma(){
    int fim = this->Populacao[0].second.T.size()-1;
    for(int i=0;i<this->Populacao.size();i++ ){
        Vertice aux(fim,0);
        this->Populacao[i].second.remove(aux.v);
        int novo = 0;
        Vertice aux2(novo,0);
        this->Populacao[i].second.add(aux2,aux);
    }
}

     
void GK::remove_duplo(){
    for(int i=0;i<this->Populacao.size()-1;i++ ){
        vector<int> repet;
        double c1 = this->Populacao[i].first;
        for(int j=i+1;j<this->Populacao.size();j++ ){
            double c2=this->Populacao[j].first;
            if(abs(c2-c1)<0.0001){
                if(this->Populacao[i].second==this->Populacao[j].second){
                    repet.push_back(j);
                }
            }
        }
        for(int p =repet.size()-1 ;p>=0;p--){
            Populacao.erase(Populacao.begin()+repet[p]);
        }

    }

}

void GK::nova_geracao(Dados  &d){
    G++;
    this->r =  M*0.5+10;
    int tam = this->Populacao.size();
    
    if(tam<r)r=tam;
   
    vector<pair<double,int>> aux;
    for(int i=0;i<this->Populacao.size();i++){
        aux.push_back(make_pair(this->Populacao[i].first,i));
    }
    sort(aux.begin(),aux.end());

    for(int i =0; i < r*1;i++){
        this->Populacao.push_back(this->Populacao[aux[i].second]);
    }
  

    for(int i = 0;i<r*4;i++){
        int max=tam*0.33+1;
        int p1 = rand()%max;
        int p2 = rand()%max;
    
        cross(Populacao[aux[p1].second].second,Populacao[aux[p2].second].second,d);
    }
   
    for(int i = 0;i<r*1.5;i++){
        int max=tam*0.3;
        int p1 = rand()%max;
    
        mut(Populacao[aux[p1].second].second,d);
    }


    for(int i =tam-1;i>=0;i--){
        this->Populacao.erase(this->Populacao.begin()+i);
    }

    if(this->Populacao[0].first<melhor){
        melhor=this->Populacao[0].first;
        this->ult_atualizacao=0;
    }else{
        this->ult_atualizacao++;
    }
    


}

void GK::cross(Solucao &p1,Solucao &p2,Dados &d){
    Solucao filho(M);

    int a = rand()%M;
    int l = rand()%M;
    int n =p1.T.size()-1;
    Vertice dump(n,0);
    int atual = p1.T[n].prox;
    int atual2 =  p2.T[n].prox;

   

    for(int t = 0; t< a;t++){
         atual   =  p1.T[atual].prox;
         atual2 =  p2.T[atual2].prox; 
    }
    
    for(int i =0; i<l;i++){
        Vertice v(atual,p1.T[atual].a);
        filho.add(dump,v);
        dump = v;
        atual = p1.T[atual].prox;
        if(atual==n) atual = p1.T[atual].prox;
        atual2 =  p2.T[atual2].prox; 
        if(atual2==n) atual2 = p2.T[atual2].prox;
      
        
       

    }
   

    while (filho.aberto.size()>0){
      //  cout<<"atual "<<atual2<<" "<<dump.v<<" "<<filho.T.size()<<endl;
        if(!filho.T[atual2].usado){
            Vertice v(atual2,p2.T[atual2].a);
            filho.add(dump,v);
            dump = v;
        }
        atual2 =  p2.T[atual2].prox; 
        if(atual2==n) atual2 = p2.T[atual2].prox;
    }
    double c= filho.Avalia(d);

    this->Populacao.push_back(make_pair(c,filho));

}



void GK::mut(Solucao &p1,Dados &d){
    Solucao filho = p1;
    int min = M*0.05;
    int max = M*0.3;
    int a= rand()%M;
    int l = rand()%(max-min)+min;

    vector<Vertice> aux;
    int atual = a;
    int n =filho.T.size()-1;
    for (int i = 0; i<l ;i++){
        Vertice v (atual,filho.T[atual].a);
        aux.push_back(v);
        atual = filho.T[atual].prox;
        if(atual==n) atual = filho.T[atual].prox;
        int ant = filho.T[atual].prev;
        if(ant==n) ant = filho.T[ant].prev;

        filho.remove(ant);
                
    }
    Vertice dump(n,0);
    int pos = rand()%(M-l);
    for(int i = 0;i<pos;i++){
        dump.v = filho.T[dump.v].prox;
    }

    for(int i=0;i<aux.size();i++){
        filho.add(dump,aux[i]);
        dump=aux[i];
    }


    double c = filho.Avalia(d);
    Populacao.push_back(make_pair(c,filho));

}

void GK::LS_CO(Dados &d){
    LK lk(0,0,M,0);
    for(int i =0;i<this->Populacao.size();i++){
        vector<Vertice> v;
        Populacao[i].second.Solucao_Vector(v);
            
           if(G%15==0) lk.rodar2(v,d);
            d.CO(v);
        
        Populacao[i].second.Vector_Solucao(v);
        double c = Populacao[i].second.Avalia(d);
        Populacao[i].first = c;
    }


}

void GK::opt2(vector<Vertice> &v, Dados &d){
    int m_i=-1;
    int m_j=-1;
    double melhor =10;
    while(melhor>0){
        int m_a1;
        int m_a2;
        melhor = 0;

       
        for (int i = 0; i<v.size()-1;i++ ){
            for(int j= i+1;j<v.size();j++){
                Vertice v1 = v[i];
                Vertice v2 = v[i+1];
                Vertice v3 = v[j];
                Vertice v4 = v[(j+1)%v.size()];

                double custo_atual = d.Custo[v1.v][v1.a][v2.v][v2.a];
                custo_atual += d.Custo[v3.v][v3.a][v4.v][v4.a];


                int a1;
                int a2;
                double ma1=1000000;
                double ma2=1000000;


                for(int k=0;k<d.Vizinhos[v1.v].size();k++){
                        double aux =d.Custo[v3.v][v3.a][v1.v][k];
                        if(aux<ma1){
                            ma1=aux;
                            a1=k;
                        }
                }

                for(int k=0;k<d.Vizinhos[v2.v].size();k++){
                        double aux =d.Custo[v4.v][v4.a][v2.v][k];
                        if(aux<ma2){
                            ma2=aux;
                            a2=k;
                        }
                }

                double custo_futuro = d.Custo[v3.v][v3.a][v1.v][a1];
                custo_futuro += d.Custo[v4.v][v4.a][v2.v][a2];
                cout<<custo_atual<<" "<<custo_futuro<<" "<<custo_atual-custo_futuro<<endl;
                int aaaa;
                cin>>aaaa;
                if(melhor<custo_atual-custo_futuro){
                    m_a1=a1;
                    m_a2=a2;
                    melhor = custo_atual-custo_futuro;
                    m_i=i;
                    m_j=j;
                }

            }
        }
        cout<<"m= "<<melhor<<" "<<d.Avalia(v)<<endl;
        if (melhor>0){
            cout<<"cccccccccccccccccccccccccccccccccccccc"<<endl;
            cout<<m_i<<endl;
            d.imprimir(v);
            v[m_j].a =m_a2;
            v[m_i].a=m_a1;
            vector<Vertice> P;
           
            this->cortar_ciclo(v,P,m_i+1);
            d.imprimir(P);
            
            v=P;
            this->vira(v,m_j);
            d.imprimir(v);
            cout<<"j = "<<m_j<<endl;
            cout<<"dddddddddddddddddddddddddddddddddd"<<endl;
        }
    }
    cin>>melhor;
}

void GK::cortar_ciclo(vector<Vertice> &best_s,vector<Vertice> &P, int i){
    for(int j=0;j<best_s.size();j++){
        P.push_back(best_s[(i+j)%best_s.size()]);
    }
}
void GK::vira(vector<Vertice> &P, int i){
    int n = (P.size() - i)/2;
    int m = P.size() -1;
    for(int j=0; j<n;j++ ){
        Vertice aux = P[j+i];
        P[j+i]=P[m-j];
        P[m-j]= aux;
    }  
}