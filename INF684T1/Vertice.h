#pragma once




class Vertice
{
public:
	int v = -1;
	int a = -1;

	class Vertice(int v, int a) {
		this->v = v;
		this->a = a;
	}

	bool operator<(Vertice v) {
		if (this->v == v.v) {
			return this->a < v.a;
		}
		return this->v < v.v;
	}
	Vertice() {
		;
	}
	bool operator==(Vertice v) {
		return v.a == this->a && this->v == v.v;
	}
	
};

