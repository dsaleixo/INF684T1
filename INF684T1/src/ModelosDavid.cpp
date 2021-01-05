#include "ModelosDavid.h"


ModelosDavid::ModelosDavid(Dados& d) :Base(d) {
    ;
}
void ModelosDavid::rodar() {
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
    
    IloArray<IloNumVarArray> u(env, d->n_locais);
    for (int i = 0; i < d->n_locais; i++) {
         u.add(IloNumVarArray(env, d->Vizinhos[i].size(), 0.0, IloInfinity, ILOFLOAT));
    }
    IloModel mod(env);

    IloExpr obj(env);
    cout << "DAvid" << endl;
    for (int i = 0; i < d->n_locais; i++) {
        for (int li = 0; li < d->Vizinhos[i].size(); li++) {
            for (int j = 0; j < d->n_locais; j++) {
                for (int ji = 0; ji < d->Vizinhos[j].size(); ji++) {
                    obj += d->Custo[i][li][j][ji] * X[i][li][j][ji];
                }
            }
        }
    }
    
    cout << "DAvid" << endl;
    mod.add(IloMinimize(env, obj));

    obj.end();



    for (int j = 0; j < d->n_locais; j++) {
        IloExpr flow_in(env);
        for (int i = 0; i < d->n_locais; i++) {
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
        cout << "DAvid" << endl;
        flow_in.end();
    }


    for (int i = 0; i < d->n_locais; i++) {
        IloExpr flow_out(env);
        for (int j = 0; j < d->n_locais; j++) {
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
    cout << "DAvid2" << endl;
    for (int i = 1; i < d->n_locais; i++) {


        for (int j = 1; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }
            IloExpr ui(env);
            for (int li = 0; li < d->Vizinhos[i].size(); li++) {
                ui += u[i][li];
            }
            IloExpr uj(env);
            for (int ji = 0; ji < d->Vizinhos[j].size(); ji++) {
                uj+= u[j][ji];
                ;
            }


            for (int li = 0; li < d->Vizinhos[i].size(); li++) {
                for (int ji = 0; ji < d->Vizinhos[j].size(); ji++)
                    mod.add(ui - uj + d->n_locais * X[i][li][j][ji] <= d->n_locais - 1);
            }
        

        }
    }
    cout << "DAvidddddd" << endl;
    IloCplex cplex(mod);
    cplex.setParam(IloCplex::EpGap, 0.01);
    cplex.setParam(IloCplex::TiLim, 1000000000);
    if (!cplex.solve()) {
        throw(-1);
    }
    
    cout << "valor = " << cplex.getObjValue() << endl;
    /*
    vector<int> Caminho;
    for (int i = 0; i < d->n_locais; i++)Caminho.push_back(-1);

    for (int i = 0; i < d->n_locais; i++) {
        for (int j = 0; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }

            if (cplex.getValue(X[i][j])) {
                Caminho[i] = j;

                break;
            }
        }
    }
    cout << "0 ";
    int atual = Caminho[0];
    while (atual != 0) {
        cout << d->Locais[atual].id << " ";
        atual = Caminho[atual];
    }
    cout << 0 << endl;

    */
}