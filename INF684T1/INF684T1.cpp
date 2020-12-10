// INF684T1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Dados.h"
#include "Base.h"
#include "ModeloPadrao.h"
#include "ModeloPadraoLinear.h"
#include "ModelosDavid.h"
#include "ModeloGTSP_Kara.h"
#include "ModeloGTSP_F1.h"
#include "ModeloGTSP_F2.h"
#include "Vertice.h"
int main()
{

    Dados d;
    d.ler("mapas/mapa13.txt");
    d.imprimir();
    //cout << "ddddddddd" << endl;
    // 0 4 8
    Base*  model = new ModeloGTSP_F1(d);

    model->rodar();

    model = new ModeloPadrao(d);

    model->rodar();

    return 0;
    vector<Vertice> v;

    d.NN(v);

    cout << d.Avalia(v) << endl;;

   // cout << d.BuscaLocalSwap(v) << endl;;

   // d.Avalia(v);


    
   
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
