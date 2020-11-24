#include "Dados.h"


void Dados::ler(string s) {
    ifstream in(s );
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
        if (obstaculo.find(i)==obstaculo.end()) {
            Pontos p;
            p.x = (int)i / largura;
            p.y = (int)i % largura;
            p.id = i;
            Locais.push_back(p);
                
        }
    }
    n_locais = largura * altura - n_obstaculo;
    C = new float* [n_locais];
    for (int i = 0; i < n_locais; i++) {
        C[i] = new float[n_locais];
        for (int j = 0; j < n_locais; j++) {
            float a = Locais[i].x - Locais[j].x;
            float b = Locais[i].y - Locais[j].y;
            C[i][j] = sqrt(a * a + b * b);
            if (C[i][j] >  max_dist) {
                C[i][j] = m_kappa;
            }
            else {
                //cout <<Locais[i].id << " " << Locais[j].id <<" "<<C[i][j] << endl;
                //cout << "               " << Locais[i].x << " " << Locais[i].y << "       "<<Locais[j].x << " " << Locais[j].y<<endl;
                //cout << endl;
                C[i][j] *=m_pcn;
                
            }
        }
    }

    

    Q = new float** [n_locais];
    for (int i = 0; i < n_locais; i++) {
        Q[i] = new float*[n_locais];
        for (int j = 0; j < n_locais; j++) {
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

                if (r > max_dist*m_pcn || e > max_dist * m_pcn) {
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
                    Q[i][j][k] = m_pcn * (3.14159 - acos(t)) ;
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
                cout << "o";
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