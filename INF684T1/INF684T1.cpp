// INF684T1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Dados.h"
#include <ilcplex/ilocplex.h>
int main()
{
    std::cout << "Hello World!\n";
    Dados d;
    d.ler("mapas/mapa3.txt");
    d.imprimir();

    IloEnv env;
    IloArray<IloBoolVarArray> X(env);
    for (int i = 0; i < d.n_locais; i++) {
        X.add(IloBoolVarArray(env, d.n_locais));
    }

    IloNumVarArray u(env, d.n_locais, 0.0, IloInfinity, ILOFLOAT);

    IloModel mod(env);

    IloExpr total_dist(env);


    for (int i = 0; i < d.n_locais; i++) {
        for (int j = 0; j < d.n_locais; j++) {
            if (j == i) {
                continue;
            }
            total_dist += d.C[i][j] * X[i][j];
        }
    }


    IloExpr total_turn(env);
    for (int i = 0; i < d.n_locais; i++) {
        for (int j = 1; j < d.n_locais; j++) {
            if (j == i ) {
                continue;
            }

            for (int k = 0; k < d.n_locais; k++) {
                if (k == j) {
                    continue;
                }

                total_turn += d.Q[i][j][k] * X[i][j] * X[j][k];
            }
        }
    }


    mod.add(IloMinimize(env, d.lambda*total_dist + d.gamma*total_turn));

    total_dist.end();
    total_turn.end();


    for (int j = 0; j < d.n_locais; j++) {
        IloExpr flow_in(env);
        for (int i = 0; i < d.n_locais; i++) {
            if (i == j) {
                continue;
            }

            flow_in +=  X[i][j];
        }

        mod.add(flow_in == 1);

        flow_in.end();
    }


    for (int i = 0; i < d.n_locais; i++) {
        IloExpr flow_out(env);
        for (int j = 0; j < d.n_locais; j++) {
            if (j == i) {
                continue;
            }

            flow_out += X[i][j];
        }

        mod.add(flow_out == 1);

        flow_out.end();
    }
    for (int i = 1; i < d.n_locais; i++) {
     

        for (int j = 1; j < d.n_locais; j++) {
            if ( j == i) {
                continue;
            }

            mod.add(u[i] - u[j] + d.n_locais * X[i][j] <= d.n_locais - 1);
        }
    }

    IloCplex cplex(mod);
    cplex.setParam(IloCplex::EpGap, 0.01);
    cplex.setParam(IloCplex::TiLim, 1000000000);
    if (!cplex.solve() ) {
        throw(-1);
    }
    cout << "valor = " << cplex.getObjValue() << endl;

    vector<int> Caminho;
    for (int i = 0; i < d.n_locais; i++)Caminho.push_back(-1);

    for (int i = 0; i < d.n_locais; i++) {
        for (int j = 0; j < d.n_locais; j++) {
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
            cout << d.Locais[atual].id<<" ";
            atual = Caminho[atual ];
    }
        cout << 0 << endl;
    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
