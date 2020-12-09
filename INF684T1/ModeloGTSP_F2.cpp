#include "ModeloGTSP_F2.h"


ModeloGTSP_F2::ModeloGTSP_F2(Dados& d) :Base(d) {
    ;
}
void ModeloGTSP_F2::rodar() {
    IloEnv env;
    IloBoolVar**** X;
    X = new IloBoolVar * **[d->n_locais];
    for (int i = 0; i < d->n_locais; i++) {
        X[i] = new IloBoolVar * *[d->Vizinhos[i].size()];
        for (int li = 0; li < d->Vizinhos[i].size(); li++) {
            X[i][li] = new IloBoolVar * [d->n_locais];
            for (int j = 0; j < d->n_locais; j++) {
                X[i][li][j] = new IloBoolVar[d->Vizinhos[j].size()];
                for (int ji = 0; ji < d->Vizinhos[j].size(); ji++) {
                    X[i][li][j][ji] = IloBoolVar(env);
                }
            }
        }
    }


    IloModel mod(env);

    IloExpr obj(env);

    for (int i = 0; i < d->n_locais; i++) {
        for (int li = 0; li < d->Vizinhos[i].size(); li++) {
            for (int j = 0; j < d->n_locais; j++) {
                for (int ji = 0; ji < d->Vizinhos[j].size(); ji++) {
                    if (i == j) {
                        continue;
                    }


                    obj += d->Custo[i][li][j][ji] * X[i][li][j][ji];

                }
            }
        }
    }



    IloBoolVar** w;
    w = new IloBoolVar * [d->n_locais];
    for (int i = 0; i < d->n_locais; i++) {
        w[i] = new IloBoolVar[d->n_locais];
        for (int j = 0; j < d->n_locais; j++) {
            w[i][j] = IloBoolVar(env);

        }
    }

    IloFloatVar** y;
    y = new IloFloatVar * [d->n_locais];
    for (int i = 0; i < d->n_locais; i++) {
        y[i] = new IloFloatVar[d->n_locais];
        for (int j = 0; j < d->n_locais; j++) {
            y[i][j] = IloFloatVar(env);

        }
    }

    mod.add(IloMinimize(env, obj));

    obj.end();



    for (int i = 0; i < d->n_locais; i++) {
        IloExpr flow_in(env);
        for (int j = 0; j < d->n_locais; j++) {
            if (i == j) {
                continue;
            }
            for (int li = 0; li < d->Vizinhos[i].size(); li++) {
                for (int ji = 0; ji < d->Vizinhos[j].size(); ji++) {
                    flow_in += X[i][li][j][ji];
                }
            }

        }

        mod.add(flow_in == 1);

        flow_in.end();
    }


    for (int j = 0; j < d->n_locais; j++) {
        IloExpr flow_out(env);
        for (int i = 0; i < d->n_locais; i++) {
            if (j == i) {
                continue;
            }
            for (int li = 0; li < d->Vizinhos[i].size(); li++) {
                for (int ji = 0; ji < d->Vizinhos[j].size(); ji++) {
                    flow_out += X[i][li][j][ji];
                }
            }

        }

        mod.add(flow_out == 1);

        flow_out.end();
    }

    for (int i = 0; i < d->n_locais; i++) {
        for (int li = 0; li < d->Vizinhos[i].size(); li++) {
            IloExpr entrada_saida(env);
            for (int j = 0; j < d->n_locais; j++) {
                if (j == i)continue;
                for (int lj = 0; lj < d->Vizinhos[j].size(); lj++) {
                    entrada_saida += X[j][lj][i][li] - X[i][li][j][lj];
                }
            }
            mod.add(entrada_saida == 0);
            entrada_saida.end();
        }

    }


    for (int i = 0; i < d->n_locais; i++) {
        for (int j = 0; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }

            IloExpr pq(env);

            for (int li = 0; li < d->Vizinhos[i].size(); li++) {
                for (int lj = 0; lj < d->Vizinhos[j].size(); lj++) {
                    pq += X[i][li][j][lj];
                }
            }

            mod.add(w[i][j] == pq);
            pq.end();

        }
    }


    for (int i = 1; i < d->n_locais; i++) {
        for (int j = 0; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }
            mod.add(y[i][j] <= d->n_locais*w[i][j]);
        }
    }


    for (int i = 1; i < d->n_locais; i++) {
        mod.add(y[0][i] == w[0][i]);
    }

    for (int i = 1; i < d->n_locais; i++) {
        IloExpr ypq(env);
        for (int j = 0; j < d->n_locais; j++) {
            if (i == j)continue;
            ypq += y[i][j];
        }
        IloExpr yrp(env);
        for (int j = 0; j < d->n_locais; j++) {
            if (i == j)continue;
            yrp += y[j][i];
        }
        mod.add(ypq - yrp == 1);
        ypq.end();
        yrp.end();
    }

    IloCplex cplex(mod);
    cplex.setParam(IloCplex::EpGap, 0.01);
    cplex.setParam(IloCplex::TiLim, 1000000000);
    cplex.setOut(env.getNullStream());
    if (!cplex.solve()) {
        throw(-1);
    }

    cout << "valor = " << cplex.getObjValue() << endl;

    vector<int> Caminho;
    vector<int> antes;
    for (int i = 0; i < d->n_locais; i++) {
        Caminho.push_back(-1);
        antes.push_back(-1);
    }


    for (int i = 0; i < d->n_locais; i++) {
        for (int j = 0; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }
            for (int li = 0; li < d->Vizinhos[i].size(); li++) {
                for (int lj = 0; lj < d->Vizinhos[j].size(); lj++) {
                    if (cplex.getValue(X[i][li][j][lj])) {
                        Caminho[i] = j;
                        antes[i] = lj;
                      


                    }
                }
            }



        }
    }
    int atual = Caminho[0];
    int a = antes[0];
    int a1;
    int a2;
    double soma = d->C[0][atual] * d->lambda;
    while (atual != 0) {
        a1 = a;
        a2 = atual;
        cout << "(" << d->Vizinhos[atual][a] << "," << atual << ") ";
        a = antes[atual];
        atual = Caminho[atual];
        soma += d->Custo[a2][a1][atual][a];
        // (0, 1) (1, 2) (2, 5) (5, 7) (7, 10) (10, 9) (9, 6) (6, 3) (0, 4) (3, 0)
         //0 1 2 5 4 7 10 9 6 3 0
    }
    cout << "(" << d->Vizinhos[atual][a] << "," << atual << ") " << endl;;

    cout << "soma = " << soma << endl;




    cout << endl;


}
