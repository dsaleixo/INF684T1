#include "ModeloPadrao.h"


ModeloPadrao::ModeloPadrao(Dados &d) :Base(d) {
    ;
}
void ModeloPadrao::rodar() {
    IloEnv env;
    IloArray<IloBoolVarArray> X(env);
    for (int i = 0; i < d->n_locais; i++) {
        X.add(IloBoolVarArray(env, d->n_locais));
    }

    IloNumVarArray u(env, d->n_locais, 0.0, IloInfinity, ILOFLOAT);

    IloModel mod(env);

    IloExpr total_dist(env);


    for (int i = 0; i < d->n_locais; i++) {
        for (int j = 0; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }
            total_dist += d->C[i][j] * X[i][j];
        }
    }


    IloExpr total_turn(env);
    for (int i = 0; i < d->n_locais; i++) {
        for (int j = 1; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }

            for (int k = 0; k < d->n_locais; k++) {
                if (k == j) {
                    continue;
                }

                total_turn += d->Q[i][j][k] * X[i][j] * X[j][k];
            }
        }
    }


    mod.add(IloMinimize(env, d->lambda * total_dist + d->gamma * total_turn));

    total_dist.end();
    total_turn.end();


    for (int j = 0; j < d->n_locais; j++) {
        IloExpr flow_in(env);
        for (int i = 0; i < d->n_locais; i++) {
            if (i == j) {
                continue;
            }

            flow_in += X[i][j];
        }

        mod.add(flow_in == 1);

        flow_in.end();
    }


    for (int i = 0; i < d->n_locais; i++) {
        IloExpr flow_out(env);
        for (int j = 0; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }

            flow_out += X[i][j];
        }

        mod.add(flow_out == 1);

        flow_out.end();
    }
    for (int i = 1; i < d->n_locais; i++) {


        for (int j = 1; j < d->n_locais; j++) {
            if (j == i) {
                continue;
            }

            mod.add(u[i] - u[j] + d->n_locais * X[i][j] <= d->n_locais - 1);
        }
    }

    IloCplex cplex(mod);
    cplex.setParam(IloCplex::EpGap, 0.01);
    cplex.setParam(IloCplex::TiLim, 1000000000);
    if (!cplex.solve()) {
        throw(-1);
    }
    cout << "valor = " << cplex.getObjValue() << endl;

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
}