#ifndef __GRAPH_
#define __GRAPH_
#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#include<stack>
/*
#define UNDISCOVER 0
#define DISCOVERED 1
#define VISITED 2
*/
#define TREE_EDGE 0
#define CROSS_EDGE 1

enum VStatus{UNDISCOVERED, DISCOVERED, VISITED};

using namespace std;

typedef struct Vetex{
	int dTime;
	int fTime;
	VStatus status;
};
typedef struct Edge{
	int data;
	int status;
};
///////////////////////////////////
template<class T>
class Graph{
private:
	T find;
	Edge E[10][10];
	Vetex V[10];
	int num;

public:
	Graph();
	Graph(int n);
	Graph(ifstream file);

	int size();
	void printEdge();
	void printNeighbor(int i);
	void setEdge(int i,int j,int data);
	void resetVetex();
	void setVetex(int, int, int, int);
	bool edgeExist(int i, int j);
	virtual void insertEdge(int i,int j,int count);
	template<class F> friend ifstream & operator>> (ifstream &f, Graph<F> &G);

	int firstNeighbor(int);
	int nextNeighbor(int, int);

	void BFSearch(Vetex);
	void DFSearch(Vetex);
	
};


///////////////////////////////////
template<class T>
class indirGraph : public Graph<T>{
public:
	virtual void insertEdge(int i,int j,int count);
};

////////////////////////////////////////construction function////////////////////////////////
template<class T>
Graph<T>::Graph(){
	int n = 10;
	num = 10;
	int i, j;
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			setEdge(i, j, 0);
	resetVetex();
}
template<class T>
Graph<T>::Graph(int n){
	num = n;
	int i,j;
	for(i = 0; i < n; ++i)
		for(j = 0 ;j < n; ++j)
			E[i][j] = 0;
	for(i = 0; i < n; ++i)V[i] = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
int Graph<T>::size(){
	return num;
}
//////////////////////////////////////
template<class T>
void Graph<T>::setEdge(int i,int j,int data){
	E[i][j].data = data;
}
template<class T>
void Graph<T>::resetVetex(){
	for(int i = 0;i < size(); ++i){
		V[i].dTime = 0;
		V[i].fTime = 0;
		V[i].status = UNDISCOVERED;
	}
}
////////////////////////////////////////
template<class T>
void Graph<T>::printEdge(){
	int i,j;
	for(i = 0; i < size(); ++i){
		for(j=0; j < size(); ++j)
			cout << E[i][j] <<' ';
		cout << endl;

	}
}
/////////////////////////////////////////////
template<class T> 
void Graph<T>::insertEdge(int i,int j,int data){
	setEdge(i, j, data);
}
///////////////////////////////////////////////////
template<class T> 
void indirGraph<T>::insertEdge(int i,int j,int data){
	setEdge(i, j, data);
	setEdge(j, i, data);
}
/////////////////////////////////////////////


template<class F>
ifstream & operator>> (ifstream &f,Graph<F> &G){
	int vnum,n,a,b,d;
	f>>vnum>>n;
	G.num = vnum;
	for(int i = 0;i < n; ++i){
		f>>a>>b>>d;
		G.insertEdge(a,b,d);
	}
	return f;
}
ostream & operator << (ostream& o, const Edge& e){
	o<<e.data;
	return o;
}
//////////////////////////////////////////////
template<class T>
void Graph<T>::DFSearch(Vetex v){
	int clock = 0;
	v.dTime = clock;
	v.state = DISCOVERED;
}
//////////////////////////////对边的操作///
template<class T>
bool Graph<T>::edgeExist(int i, int j){
	return E[i][j].data != 0;
}
//////////////////////////////对顶点的基本操作//
template<class T>
int Graph<T>::nextNeighbor(int i,int j){
	while(j < size() && !edgeExist(i, ++j));
	return j;
}
template<class T>
int Graph<T>::firstNeighbor(int i){
	return nextNeighbor(i, -1);
}
template<class T>
void Graph<T>::printNeighbor(int i){
	for(int j = firstNeighbor(i); j < size(); j = nextNeighbor(i,j))
		cout<<j<<' ';
	cout<<endl;
}

#endif
