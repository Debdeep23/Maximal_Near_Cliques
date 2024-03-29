

#include "graph.h"

#ifndef BKPLEX_H_
#define BKPLEX_H_


class bkplex {

	graph plex_g;
	int k;
    int d;
	unsigned long maximal_k_plex_count;
	void bkrec(vector<int>& , vector<int>& , vector<int>& );
	bool is_k_plex(vector<int> , int);
    bool is_near_clique(vector<int> , int );
    vector<int> degeneracy();
	int *degree_in_p;
    int no_of_disconnection;
    long int near_clique_count;
    int maximal_size;

public:
	bkplex();
	bkplex(graph &, int , int);
	void run();
	long countplex();
	virtual ~bkplex();
};

#endif /* BKPLEX_H_ */
