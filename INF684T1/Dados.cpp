#include "Dados.h"


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

}


void Dados::imprimir() {
    for (int i = 0; i < altura+2; i++) cout << "-";
    cout << endl;
    for (int i = 0; i < altura; i++) {
        cout << "|";
        for (int j = 0; j < largura; j++) {
            if (obstaculo.find(i*largura+j) == obstaculo.end()) {
                cout << i*largura+j<< "  ";
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