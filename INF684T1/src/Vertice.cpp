#include "Vertice.h"


bool Vertice::operator<(Vertice v) {
	if (this->v == v.v) {
		return this->a < v.a;
	}
	return this->v < v.v;
}

Vertice::Vertice() {
	;
}

Vertice::Vertice(int v, int a) {
	this->v = v;
	this->a = a;
}

bool Vertice::operator==(Vertice v) {
	return v.a == this->a && this->v == v.v;
}






