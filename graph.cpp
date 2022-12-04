/*
 * graph.cpp
 *
 *  Created on: 13-Jul-2022
 *      Author: Apurba Das
 */

#include "graph.h"
#include <fstream>
#include <bits/stdc++.h>


graph::graph() {
	// TODO Auto-generated constructor stub
	this->max_degree = INT_MIN;
	this->n=0;
	this->m=0;

}

graph::graph(const graph &g){
	n = g.n;
	m = g.m;
	max_degree = g.max_degree;
	adj = g.adj;
	vertex_degree = g.vertex_degree;
	vertex_set = g.vertex_set;
	adj_mat = g.adj_mat;
    degen = g.degen;
}


/* Assume that the graph is stored in the edge list format
 * with the vertices id 0, 1, ..., n-1 where n is the number of vertices.
 * We also assume that the graph has no self loop or multiple edges. In other
 * words, we assume that the input graph is simple, unweighted and undirected
 * */
void graph::read_edge_list(const char *filepath) {
	std::ifstream infile;
	char buf[1024];

	printf("%s\n", filepath);

	infile.open(filepath, std::ios::in);

	printf("[%d]: file opened\n", __LINE__);

	if(!infile.is_open()){
			fprintf(stderr, "can not find file %s\n", filepath);
			exit(1);
	}

	int u, v;
	

	while(infile.getline(buf, 1024)){
		char *p = buf;
		while(*p == ' ' && *p != '\0') p++;
		if(*p == '#' || *p == '\0') continue;
		std::stringstream ss1(buf);
		ss1 >> u >> v;
		//printf("[%d]: %d %d\n", __LINE__, u, v);
		vertex_set.insert(u);
		vertex_set.insert(v);

		
		adj[u].push_back(v);
		adj[v].push_back(u);
		this->max_degree = mmax(this->max_degree, mmax((int)adj[u].size(), (int)adj[v].size()));

		//printf("[%d]: max_degree: %d\n", __LINE__, max_degree);
		vertex_degree[u] = adj[u].size();
		vertex_degree[v] = adj[v].size();
		
		
		//printf("[%d]: inserting edge (%d, %d) with hash value: %lld\n", __LINE__, u, v, hash(u,v));
		adj_mat.insert(hash(u,v));
		adj_mat.insert(hash(v,u));

		//vertex_degree[u] = 1;
		//vertex_degree[v] = 2;


		//printf("degree computation done\n");

		m++;
	}


	n = adj.size();

	printf("n: %d\n", n);
	printf("m: %d\n", m);
	
}

bool graph::is_edge(int u, int v){

	return adj_mat.find(hash(u,v)) != adj_mat.end();
	
}

void graph::add_edge(int u, int v){


	vertex_set.insert(u);
	vertex_set.insert(v);
	adj[u].push_back(v);
	adj[v].push_back(u);


	vertex_degree[u] = adj[u].size();
	vertex_degree[v] = adj[v].size();
	
	//printf("[%d]: Edge addition completed\n", __LINE__);
	
		
	adj_mat.insert(hash(u,v));
	adj_mat.insert(hash(v,u));


	this->max_degree = mmax(this->max_degree, mmax((int)adj[u].size(), (int)adj[v].size()));

}

long long int graph::hash(int u, int v){

	long long int h = (long long int)u*100000000+(long long int)v;
	
	return h;

}

void graph::add_vertex(int u){
	if(vertex_set.find(u) == vertex_set.end()){
		vertex_set.insert(u);
	
		vertex_degree[u] = 0;
	}

}

int graph::degree_of_vertex(int u){
	
	return adj[u].size();
}

int graph::min_degree(){
	int min = INT_MAX;

	for(int i=0; i < adj.size(); i++){
		if(min > adj[i].size())
			min = adj[i].size();
	}

	return min;

}

vector<int> graph::vertex_list(){
	vector<int> lst;
	for(int u : vertex_set){
		lst.push_back(u);
	}
	return lst;
}


vector<int>& graph::ngh(int u){



	return adj[u];

}


graph::~graph() {
	// TODO Auto-generated destructor stub
}

