#pragma once




class Vertice
{
public:
	int v = -1;
	int a = -1;

	Vertice(int v, int a);

	bool operator<(Vertice v);

	Vertice();

	bool operator==(Vertice v);
	
};

