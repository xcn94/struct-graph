#include<stdlib.h>
#include"graph.h"

int main(){
	ifstream f("graph.txt");
	indirGraph<int> G;
	f>>G;
	G.printEdge();
	G.printNeighbor(2);
	system("pause");
	return 0;
}