#include "Dados.h"
#include "Vertice.h"
#include <set>

void Dados::ler(string s) {
    ifstream in(s);
    if (!in) {
        throw "Erro ao abrir o arquivo";

    }
    in >> altura >> largura;
    int n_obstaculo;
    in >> n_obstaculo;
    int aux;
    for (int i = 0; i < n_obstaculo; i++) {
        in >> aux;
        obstaculo.insert(aux);
    }


    //imprimir();

    for (int i = 0; i < largura * altura; i++) {
        Map_locais_variaveis.push_back(-1);
        if (obstaculo.find(i) == obstaculo.end()) {
            Pontos p;
            p.x = (int)i / largura;
            p.y = (int)i % largura;
            p.id = i;
            Map_locais_variaveis[i] = Locais.size();
            Locais.push_back(p);

        }
    }
    n_locais =  largura * altura - n_obstaculo;
    cout <<"ff "<< n_locais << endl;
    for (int i = 0; i < n_locais; i++) {
        vector<int> v;
        Vizinhos.push_back(v);
    }

    C = new float* [n_locais];
    for (int i = 0; i < n_locais; i++) {
        C[i] = new float[n_locais];
        map<int, int> aux;
        Map_vizinho.push_back(aux);
        for (int j = 0; j < n_locais; j++) {
            float a = Locais[i].x - Locais[j].x;
            float b = Locais[i].y - Locais[j].y;
            C[i][j] = sqrt(a * a + b * b);
            if (C[i][j] > max_dist) {
                C[i][j] = m_kappa;
            }
            else {
                //cout <<Locais[i].id << " " << Locais[j].id <<" "<<C[i][j] << endl;
                //cout << "               " << Locais[i].x << " " << Locais[i].y << "       "<<Locais[j].x << " " << Locais[j].y<<endl;
                //cout << endl;
                C[i][j] *= m_pcn;
                if (i != j) {
                    Map_vizinho[i][j] = Vizinhos[i].size();
                    Vizinhos[i].push_back(j);
                    
                }

            }
        }


    }
    
    
    



    Q = new float** [n_locais];

    for (int i = 0; i < n_locais ; i++) {
        Q[i] = new float* [n_locais];

        for (int j = 0; j < n_locais ; j++) {
            Q[i][j] = new float[n_locais];

            float dx;
            float dy;
            for (int k = 0; k < n_locais; k++) {
                dx = Locais[i].x - Locais[j].x;
                dy = Locais[i].y - Locais[j].y;
                float r = sqrt(dx * dx + dy * dy);
                dx = Locais[k].x - Locais[j].x;
                dy = Locais[k].y - Locais[j].y;
                float e = sqrt(dx * dx + dy * dy);
                dx = Locais[k].x - Locais[i].x;
                dy = Locais[k].y - Locais[i].y;
                float s = sqrt(dx * dx + dy * dy);;
               
                if (r > max_dist * m_pcn || e > max_dist * m_pcn) {
                    Q[i][j][k] = m_kappa;
                    
                }
                else {
                    float t = (r * r + e * e - s * s) / (2.0 * r * e);
                    if (t > 1.0) {
                        t = 1.0;
                    }
                    else if (t < -1.0) {
                        t = -1.0;
                    }
                    
                    Q[i][j][k] =  m_pcn * (3.14159 - acos(t));
                    if (Q[i][j][k] < 0.001)Q[i][j][k] = 0;
                    
                }
            }
        }
    }


   

    

    Custo = new float*** [n_locais];
    C_floyd = new int*** [n_locais];
    for (int i = 0; i < n_locais; i++) {
        Custo[i] = new float** [Vizinhos[i].size()];
        C_floyd[i] = new int** [Vizinhos[i].size()];
        for (int j = 0; j < Vizinhos[i].size(); j++) {
            Custo[i][j] = new float* [n_locais];
            C_floyd[i][j] = new int* [n_locais];
            for (int k = 0; k < n_locais; k++) {
                Custo[i][j][k] = new float[Vizinhos[k].size()];
                C_floyd[i][j][k] = new int[Vizinhos[k].size()];
                for (int w = 0; w < Vizinhos[k].size(); w++) {
                    C_floyd[i][j][k][w] = -1;
                    Custo[i][j][k][w]= m_kappa;
                }
          
            }
        }
    }

    for (int i = 0; i < n_locais; i++) {
        for (int li = 0; li < Vizinhos[i].size(); li++) {
            for (int j = 0; j < n_locais; j++) {
                for (int ji = 0; ji < Vizinhos[j].size(); ji++) {
                    
                    float dx = Locais[i].x - Locais[Vizinhos[j][ji]].x;
                    float dy = Locais[i].y - Locais[Vizinhos[j][ji]].y;
                    float dist = sqrt(dx * dx + dy * dy);
                    if (dist < max_dist){
                        if (i == Vizinhos[j][ji]) {
                            Custo[i][li][j][ji] = gamma * (Q[Vizinhos[i][li]][i][j]) + lambda * (C[i][j] );
                            C_floyd[i][li][j][ji] = j;
                        }
                        else {
                            Custo[i][li][j][ji] = gamma * (Q[Vizinhos[i][li]][i][Vizinhos[j][ji]] + Q[i][Vizinhos[j][ji]][j]) + lambda * (C[i][Vizinhos[j][ji]] + C[Vizinhos[j][ji]][j]);
                            C_floyd[i][li][j][ji] = Vizinhos[j][ji];
                        }
                    }
                   
                }
            }
        }

    }
    floyd2();

}



void Dados::floyd2() {
    for (int k = 0; k < n_locais; k++) {
        for (int ki = 0; ki < Vizinhos[k].size(); ki++) {
            for (int i = 0; i < n_locais; i++) {
                for (int li = 0; li < Vizinhos[i].size(); li++) {
                    for (int j = 0; j < n_locais; j++) {
                        for (int ji = 0; ji < Vizinhos[j].size(); ji++) {
                    
                            if (Custo[i][li][j][ji] > Custo[i][li][k][ki] + Custo[k][ki][j][ji] && Vizinhos[k][ki]!=i && k!=i) {
                                Custo[i][li][j][ji] = Custo[i][li][k][ki] + Custo[k][ki][j][ji];
                                C_floyd[i][li][j][ji] = C_floyd[i][li][k][ki];
                                
                            }
                           
                     
                        }
                    }
                }
            }
        }
            
    }
    for (int i = 0; i < n_locais; i++) {
        for (int li = 0; li < Vizinhos[i].size(); li++) {
            for (int j = 0; j < n_locais; j++) {
                for (int ji = 0; ji < Vizinhos[j].size(); ji++) {
                    if (i == j) {
                        continue;
                    }
                    else if (i == 0 and Vizinhos[j][ji] == 0) {
                        Custo[i][li][j][ji] = lambda * C[Vizinhos[j][ji]][j];
                    }
                    else if (i == 0 and Vizinhos[j][ji] != 0) {
                        Custo[i][li][j][ji] = 100000.0;
                    }
                  
                }
            }
        }
    }
}


void Dados::imprimir() {
    for (int i = 0; i < altura+2; i++) cout << "-";
    cout << endl;
    for (int i = 0; i < altura; i++) {
        cout << "|";
        for (int j = 0; j < largura; j++) {
            if (obstaculo.find(i*largura+j) == obstaculo.end()) {
                cout <<'O'<< "";
            }
            else {
                cout << "X";
            }
        }
        cout << "|"<<endl;
    }
    for (int i = 0; i < altura + 2; i++) cout << "-";
    cout << endl;
}

vector<int> Dados::Caminho_floyd(int i, int li, int j, int lj) {
    vector<int> v;
    ;
    i = Map_locais_variaveis[i];
    j = Map_locais_variaveis[j];
    li = Map_locais_variaveis[li];
    lj = Map_locais_variaveis[lj];
    v.push_back(li);
    int l0 = Map_vizinho[i][li];
    int l1 = Map_vizinho[j][lj];
   
    cout << "custo " << Custo[i][l0][j][l1] << endl;;

    while (i != j) {
        v.push_back (i );;
        int aux = i;
        i = C_floyd[i][l0][j][l1];
        l0 = Map_vizinho[i][aux];
    }
    v.push_back(j);
     return v;
}


void Dados::NN(vector<Vertice>& P) {
    const int n = this->n_locais;
    vector<bool> visitado(n, false );
    set<int> aberto;
    for (int i = 1; i < n; i++) {
        aberto.insert(i);
    }

    int v = 0;
    int a = 0;
    float menor = 10000000;
    for (int i = 0; i < Vizinhos[0].size(); i++) {
        if (C[0][Vizinhos[0][i]] < menor) {
            menor = C[0][Vizinhos[0][i]];
            v = Vizinhos[0][i];
        }
    }
    Vertice c;
    c.v = v;
    c.a = a;
    visitado[0] = true;
    visitado[c.v] = true;
    aberto.erase(c.v);
    P.push_back(c);
    int ult = 0;
    while (!aberto.empty())
    {
        bool achou=false;
        menor = 1000000;
        Vertice c1;

    
        for (int i = 0; i < Vizinhos[P[ult].v].size(); i++) {
            int vis = Vizinhos[P[ult].v][i];
        
            if (menor > Custo[P[ult].v][P[ult].a][vis][Map_vizinho[vis][P[ult].v]] && !visitado[vis]) {
                menor = Custo[P[ult].v][P[ult].a][vis][Map_vizinho[vis][P[ult].v]];
                c1.v = vis;
                c1.a = Map_vizinho[vis][P[ult].v];
                achou = true;
       
            }
        }
        if (achou) {
               
            P.push_back(c1);
            ult++;
            
            aberto.erase(c1.v);
            visitado[c1.v] = true;
            continue;
        }
        for (int i : aberto) {
            for (int j = 0; j < Vizinhos[i].size(); j++) {
                if (menor > Custo[P[ult].v][P[ult].a][i][j]) {
                    menor = Custo[P[ult].v][P[ult].a][i][j];
                    c1.v = i;
                    c1.a = j;
                }
            }
        }

        P.push_back(c1);
        ult++;
        aberto.erase(c1.v);
        visitado[c1.v] = true;



    }
    menor = 10000000;
    for (int i = 0; i<Vizinhos[0].size(); i++) {
        
        if (menor > Custo[P[ult].v][P[ult].a][0][i]) {
            menor = Custo[P[ult].v][P[ult].a][0][i];
            c.a=i;
            c.v=0;
        }
    }
    P.push_back(c);


    return;
}






void Dados::NN2(vector<Vertice>& P) {
    const int n = this->n_locais;
    vector<bool> visitado(n, false);
    set<int> aberto;
    for (int i = 1; i < n; i++) {
        aberto.insert(i);
    }

    int v = 0;
    int a = 0;
    float menor = 10000000;
   
    for (int i = 0; i < Vizinhos[0].size(); i++) {
        if (C[0][Vizinhos[0][i]] < menor) {
            menor = C[0][Vizinhos[0][i]];
            v = Vizinhos[0][i];

        }
    }
    Vertice c;
    c.v = v;
    c.a = a;
    visitado[0] = true;
    visitado[c.v] = true;
    aberto.erase(c.v);
    P.push_back(c);
    int ult = 0;
    while (!aberto.empty())
    {
        bool achou = false;
        menor = 1000000;
        float empate=1000000;
        Vertice c1;


        for (int i = 0; i < Vizinhos[P[ult].v].size(); i++) {
            int vis = Vizinhos[P[ult].v][i];
            if (!visitado[vis]) {
                float atual = Custo[P[ult].v][P[ult].a][vis][Map_vizinho[vis][P[ult].v]];
                float empate1 = Custo[vis][Map_vizinho[vis][P[ult].v]][P[0].v][P[0].a];
                if (menor > atual) {
                    menor = atual;
                    empate = empate1;
                    c1.v = vis;
                    c1.a = Map_vizinho[vis][P[ult].v];
                    achou = true;

                }
                else if (menor > atual && empate > empate1) {
                    menor = atual;
                    empate = empate1;
                    c1.v = vis;
                    c1.a = Map_vizinho[vis][P[ult].v];
                    achou = true;
                }
            }
        }
        if (achou) {

            P.push_back(c1);
            ult++;

            aberto.erase(c1.v);
            visitado[c1.v] = true;
            continue;
        }
        for (int i : aberto) {
            for (int j = 0; j < Vizinhos[i].size(); j++) {
                if (menor > Custo[P[ult].v][P[ult].a][i][j]) {
                    menor = Custo[P[ult].v][P[ult].a][i][j];
                    empate = Custo[i][j][P[0].v][P[0].a];
                    c1.v = i;
                    c1.a = j;
                }
                else if (menor == Custo[P[ult].v][P[ult].a][i][j] && empate > Custo[i][j][P[0].v][P[0].a]) {
                    menor = Custo[P[ult].v][P[ult].a][i][j];
                    empate = Custo[i][j][P[0].v][P[0].a];
                    c1.v = i;
                    c1.a = j;
                }
            }
        }

        P.push_back(c1);
        ult++;
        aberto.erase(c1.v);
        visitado[c1.v] = true;



    }
    menor = 10000000;
    for (int i = 0; i < Vizinhos[0].size(); i++) {

        if (menor > Custo[P[ult].v][P[ult].a][0][i]) {
            menor = Custo[P[ult].v][P[ult].a][0][i];
            c.a = i;
            c.v = 0;
        }
    }
    P.push_back(c);


    return;
}







float Dados::Avalia(vector<Vertice>& P) {

    

    double soma = Custo[P[P.size() - 1].v][P[P.size()-1].a][P[0].v][P[0].a];
    
    cout << endl;
    cout << "(" << Vizinhos[P[0].v][P[0].a] << "," << P[0].v << ") ";
    for (int i = 1; i < P.size();i++) {
        soma += Custo[P[i-1].v][P[i-1].a][P[i].v][P[i].a];
        cout << "(" <<Locais[ Vizinhos[P[i].v][P[i].a]].id << "," <<Locais[ P[i].v ].id<< ") ";
      
      
        // (0, 1) (1, 2) (2, 5) (5, 7) (7, 10) (10, 9) (9, 6) (6, 3) (0, 4) (3, 0)
         //0 1 2 5 4 7 10 9 6 3 0
    }
    cout << endl << "Custo = " << soma << endl;;;

    
    return soma;


}

bool operator<(const Vertice& c1, const Vertice& c2) {
    if (c1.v == c2.v) {
        return c1.a < c2.a;
    }
    return c1.v < c2.v;
}

struct compare
{
    bool operator()(pair<float, pair<Vertice, Vertice>> const & p1,  pair<float, pair<Vertice, Vertice>> const & p2)   {
        
            return p1.first > p2.first;    // ***EDIT***
    }
};


float Dados::CO(vector<Vertice>& P) {


    float menor = 10000000;

    for (int op = 0; op < Vizinhos[P[0].v].size() ; op++) {

        map<Vertice, Vertice> Caminho;
        priority_queue<pair<float, pair<Vertice, Vertice>>, vector<pair<float, pair<Vertice, Vertice>>>, compare> pq;
        set<Vertice> fechado;

        Vertice obj;
        obj.v = 0;
        obj.a = op;
    

        for (int i = 0; i < Vizinhos[P[1].v].size(); i++) {
            // cout << itr->second[i].v << " "<< itr->second[i].a << endl;
            float c = Custo[P[0].v][P[0].a][P[1].v][i];
            Vertice aux;
            aux.v = 1;
            aux.a = i;
            pq.push(make_pair(c, make_pair(aux, obj)));
            Caminho.insert(make_pair(aux, obj));
        }
        
        

        float custo_total = -1;
        while (!pq.empty()) {

            

            auto v = pq.top();
            pq.pop();
            Vertice no = v.second.first;
            Vertice pai = v.second.second;
            float cc = v.first;
            // cout << " sainda  = " << Vizinhos[no.v][no.a] << " " << no.v<<"   " << cc<< endl;
            if (obj == no) {
                custo_total = cc;
                Caminho.insert(make_pair(no, pai));
                break;
            }

            if (fechado.find(no) != fechado.end()) {
                continue;
            }
            Caminho.insert(make_pair(no, pai));
            fechado.insert(no);

            int prox = (no.v + 1) % n_locais;

            for (int i = 0; i < Vizinhos[P[prox].v].size(); i++) {

                //cout << " gg " << Vizinhos[P[no.v].v][no.a] << " " << P[no.v].v << "       " << Vizinhos[P[prox].v][i] << " " << P[prox].v;

                float c = Custo[P[no.v].v][no.a][P[prox].v][i] + cc;
                // cout<<" "
               //  cout<< " c= " << c << endl;
                Vertice aux2(prox, i);

                pq.push(make_pair(c, make_pair(aux2, no)));

            }


        }

    //    cout << " sera ? " << custo_total << endl;
        if (menor > custo_total) {
            Vertice aux3 = obj;
            menor = custo_total;
            for (int i = n_locais - 1; i >=0; i--) {
             //   cout << aux3.a << " " << P[aux3.v].v << endl;
                aux3 = Caminho[aux3];
                P[i].a = aux3.a;


            }
        }
    }
    return menor;
}


float Dados::Wco_Busca(vector<Vertice>& P) {


    

    

        map<Vertice, Vertice> Caminho;
        priority_queue<pair<float, pair<Vertice, Vertice>>, vector<pair<float, pair<Vertice, Vertice>>>, compare> pq;
        set<Vertice> fechado;

         


        for (int i = 0; i < Vizinhos[P[0].v].size(); i++) {
            // cout << itr->second[i].v << " "<< itr->second[i].a << endl;
        
            Vertice aux;
            aux.v = 0;
            aux.a = i;
            pq.push(make_pair(0.0, make_pair(aux, aux)));
            Caminho.insert(make_pair(aux, aux));
        }

        Vertice obj;
      

        float custo_total = -1;
        while (!pq.empty()) {



            auto v = pq.top();
            pq.pop();
            Vertice no = v.second.first;
            Vertice pai = v.second.second;
            float cc = v.first;
            // cout << " sainda  = " << Vizinhos[no.v][no.a] << " " << no.v<<"   " << cc<< endl;
            if (n_locais-1 == no.v) {
                custo_total = cc;
                Caminho.insert(make_pair(no, pai));
                obj = no;
                break;
            }

            if (fechado.find(no) != fechado.end()) {
                continue;
            }
            Caminho.insert(make_pair(no, pai));
            fechado.insert(no);

            int prox = (no.v + 1) % n_locais;

            for (int i = 0; i < Vizinhos[P[prox].v].size(); i++) {

                //cout << " gg " << Vizinhos[P[no.v].v][no.a] << " " << P[no.v].v << "       " << Vizinhos[P[prox].v][i] << " " << P[prox].v;

                float c = Custo[P[no.v].v][no.a][P[prox].v][i] + cc;
                // cout<<" "
               //  cout<< " c= " << c << endl;
                Vertice aux2(prox, i);

                pq.push(make_pair(c, make_pair(aux2, no)));

            }


        }

        cout << " sera ? " << custo_total << endl;
        
            Vertice aux3 = obj;
            for (int i = n_locais -1; i >= 0; i--) {
                cout << Vizinhos[P[aux3.v].v][aux3.a] << " " << P[aux3.v].v << endl;
                
                P[i].a = aux3.a;

                aux3 = Caminho[aux3];
            }
        
        return custo_total;

}

float Dados::BuscaLocalSwap(vector<Vertice>& P) {

    bool achou = true;
    float melhor;
    while (achou) {
         melhor = 10000;
        int melhor_i = -1;
        int melhor_j = -1;
        int melhor_li = -1;
        int melhor_lj = -1;

        achou = false;

        for (int i = 0; i < n_locais; i++) {
            for (int j = i + 1; j < n_locais; j++) {

                Vertice oi = P[i];
                Vertice oj = P[j];

                Vertice aux = P[i];
                P[i] = P[j];
                P[j] = P[i];


                for (int li = 0; li < Vizinhos[P[i].v].size(); li++) {
                    for (int lj = 0; lj < Vizinhos[P[j].v].size(); lj++) {
                        P[i].a = li;
                        P[j].a = lj;
                        float ava = Avalia(P);
                        //cout << "a =  " << ava << endl;
                        if (melhor > ava) {
                            melhor = ava;
                            melhor_i = i;
                            melhor_j = j;
                            melhor_li = li;
                            melhor_lj = lj;
                            achou = true;

                        }

                    }

                }
                P[i] = oi;
                P[j] = oj;




            }
        }

        if (achou) {
            Vertice aux2 = P[melhor_i];
            P[melhor_i] = P[melhor_j];
            P[melhor_j] = aux2;
            melhor = CO(P);
        }
        cout << "melhor atual "<<melhor << endl;
    }
    return melhor;

}


