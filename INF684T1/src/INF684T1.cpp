// INF684T1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Dados.h"
#include "NoSolucao.h"
#include "Glns.h"
#include "LK.h"
#include "GK.h"
#include <random>

#include "Vertice.h"
int main(int argc, char* argv[])
{
   
   
    string mapa(argv[1]);
    string jogador(argv[2]);
    cout << mapa << endl;
    Dados d;
    d.ler("mapas/mapa"+mapa+".txt");
    d.imprimir();    
    cout<<"mapa = "<<mapa<<"   jogador = "<<jogador<<endl;
    long double Tfinal;
	long double TInicial;
	TInicial = (clock() / (double)CLOCKS_PER_SEC);
    srand(time(NULL));
    /*
    GK gk(d.n_locais);

    gk.inicializa(d);
    
    for(int i =0 ;i<1000;i++){
        cout<<i<<"  custo "<<gk.Populacao[0].second.Avalia(d)<<" "<<gk.Populacao.size()<<" " << (clock() / (double)CLOCKS_PER_SEC) - TInicial<<endl;
        gk.LS_CO(d);
        gk.arruma();
        gk.remove_duplo();
        gk.nova_geracao(d);
        if(gk.criterioParada()){
            break;
        }
        
        
    }
    cout<<"custo "<<gk.Populacao[0].second.Avalia(d)<<" "<<gk.Populacao.size()<<endl;
    
   
      
    LK lk(1,1,d.n_locais,0);

    lk.rodar(d);
 */
 Glns g(d.n_locais,1,0.05,0.0005,0.005,3,2,0.5);
     g.rodar(d);
     



    Tfinal = (clock() / (double)CLOCKS_PER_SEC) - TInicial;
    cout<<"TEmpo "<<Tfinal<<endl;


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
