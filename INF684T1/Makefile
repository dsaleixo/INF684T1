all:
	echo "compilando"
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/Pontos.cpp  -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include  -I . -o ./obj/Pontos.o	
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/Vertice.cpp  -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include -I . -o ./obj/Vertice.o
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/NoSolucao.cpp  -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include -I . -o ./obj/NoSolucao.o
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/Dados.cpp -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include  -I . -o ./obj/Dados.o
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/Base.cpp -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include  -I . -o ./obj/Base.o 	
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/ModeloPadrao.cpp  -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include -I . -o ./obj/ModeloPadrao.o 
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/ModeloPadraoLinear.cpp  -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include -I . -o ./obj/ModeloPadraoLinear.o 
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/ModelosDavid.cpp  -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include -I . -o ./obj/ModelosDavid.o 
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/ModeloGTSP_F1.cpp -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include  -I . -o ./obj/ModeloGTSP_F1.o 
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/ModeloGTSP_F2.cpp -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include  -I . -o ./obj/ModeloGTSP_F2.o 
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/ModeloGTSP_Kara.cpp -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include  -I . -o ./obj/ModeloGTSP_Kara.o 
	g++ -O0 -c -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD ./src/INF684T1.cpp -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include  -I . -o ./obj/INF684T1.o
 

	echo "compilado"
	g++ -O0 -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD -I/opt/ibm/ILOG/CPLEX_Studio1210/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio1210/concert/include  -L/opt/ibm/ILOG/CPLEX_Studio1210/cplex/lib/x86-64_linux/static_pic -L/opt/ibm/ILOG/CPLEX_Studio1210/concert/lib/x86-64_linux/static_pic -o teste1 ./obj/*.o  -lconcert -lilocplex -lcplex -lm -lpthread -ldl

  

