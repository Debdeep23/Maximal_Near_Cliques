#include<stdio.h>

#include<iostream>
#include "graph.h"
#include "bkplex.h"
using namespace std;


/*void input(graph &g){
    int nn , mm;
    cin >> nn >> mm;
    g.n = nn;
    g.m = mm;
    set<int>gg = g.vertex_set;
    unordered_map<int, vector<int>> adj1 = g.adj;
    unordered_map<int,int> deg = g.vertex_degree;
    unordered_set<long long int> adj_mat1 = g.adj_mat;
    int mx_degree = 0;
    for(int i =0 ; i<mm ; i++) {
        int u , v;
        cin >> u >> v;
        gg.insert(u);
        gg.insert(v);
        adj1[u].push_back(v);
        adj1[v].push_back(u);
        mx_degree = max(mx_degree , (int)adj1[u].size());
        mx_degree = max(mx_degree , (int)adj1[v].size());
        deg[u] = adj1[u].size();
        deg[v] = adj1[v].size();
        adj_mat1.insert(g.hash(u,v));
        adj_mat1.insert(g.hash(v,u));



    }

    g.max_degree = mx_degree;


}*/

int main(int argc , char **argv) {

	graph g;
	g.read_edge_list(argv[1]);
    //input(g);
    //value of k we are reading ?
    //cout<<argv[1]<<endl;
	printf("Reading graph completed\n");

	bkplex algo(g, 2 , 2);
	
	printf("constructor called\n");

	algo.run();
	printf("number of max near cliques: %ld\n", algo.countplex());
}
