// INF684T1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Dados.h"
#include "NoSolucao.h"


#include "Vertice.h"
int main(int argc, char* argv[])
{

    string mapa(argv[1]);
    string jogador(argv[2]);
    cout << mapa << endl;
    Dados d;
    d.ler("mapas/mapa"+mapa+".txt");
    d.imprimir();    

    vector<Vertice> v;
    d.NN(v);
    d.Avalia(v);

    cout<<"fffffffffffffffffffff"<<endl<<endl;

    Solucao s(d.n_locais);
    for(int i =0;i<d.n_locais;i++){
        s.FrameworkInsertionHeuristics(d);
        s.imprime(d);

    }
    cout<<"custo"<<" "<<s.Avalia(d)<<endl;;
    s.imprime(d);
    s.Solucao_Vector(v);
    d.CO(v);
    d.Avalia(v);

    return 0;
}
//(0,3) (3,6) (6,8) (8,9) (9,7) (7,4) (4,5) (5,2) (2,1) (1,0)
//

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
