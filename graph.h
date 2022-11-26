

#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define mmin(x, y) ((x)<(y)?(x):(y))
#define mmax(x, y) ((x)>(y)?(x):(y))

#ifndef GRAPH_H_
#define GRAPH_H_

class graph {
public:
	graph();
	graph(const graph &);
	virtual ~graph();
	int n;	//number of vertices
	int m; //number of edges
	int max_degree;
	//vector<vector<int>> adj;
	unordered_map<int, vector<int>> adj;
	unordered_map<int, int> vertex_degree;
	unordered_set<long long int> adj_mat;
	set<int> vertex_set;
	vector<int> vertex_list();
	void read_edge_list(const char *);
	int degree_of_vertex(int);
	void add_vertex(int);
	void add_edge(int, int);
	int min_degree();
    bool is_edge(int, int);
	long long int hash(int , int);
	vector<int>& ngh(int);
};

#endif /* GRAPH_H_ */
