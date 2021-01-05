#pragma once
#include <vector>
#include "Dados.h"
#include <ilcplex/ilocplex.h>
using namespace std;

class Base
{
	public:
		Base(Dados &dados);
		vector<int> solucao;
		float custo;
		Dados *d;
		virtual void rodar();


};

