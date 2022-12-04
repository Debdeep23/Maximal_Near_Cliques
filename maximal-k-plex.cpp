#include<stdio.h>
#include<bits/stdc++.h>
#include<iostream>
#include<chrono>
#include "graph.h"
#include "bkplex.h"
using namespace std;
using namespace std::chrono;


int main(int argc , char **argv) {

	graph g;
	g.read_edge_list(argv[1]);
    //input(g);
    //value of k we are reading ?
    //cout<<argv[1]<<endl;
	printf("Reading graph completed\n");
    //k = 2 , k = 3 try

	bkplex algo(g, 2 , 2);
	
	printf("constructor called\n");
    auto start = high_resolution_clock::now();
	algo.run();
    auto end = high_resolution_clock::now();


    double time_taken =
            chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;

    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9);
    cout << " sec" << endl;
	printf("number of max near cliques: %ld\n", algo.countplex());
}
