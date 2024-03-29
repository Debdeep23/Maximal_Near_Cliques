
#include<bits/stdc++.h>
#include<time.h>
#include "bkplex.h"
#include <cassert>


//WITH DEGENERACY AND WITHOUT DEGENERACY ORDERING AS WELL


bkplex::bkplex() {
	// TODO Auto-generated constructor stub

}

bkplex::bkplex(graph &g, int _k , int _d): plex_g(g), k(_k) , d(_d){
	maximal_k_plex_count = 0;
	degree_in_p = new int[g.n]();
	no_of_disconnection = 0;
	near_clique_count = 0;
	maximal_size = 0;

}



//find out degeneracy order and put that order in vector<int>p as order

/*vector<int> bkplex::degeneracy() {
  vector<int>v = plex_g.vertex_list();
  map<int,unordered_set<int>>adj_list;

  for(auto x : v)
  {
  unordered_set<int>st;
  adj_list[x] = st;
  vector<int> y = plex_g.ngh(x);
  for(auto z : y)
  {
  adj_list[x].insert(z);
  }
  }
  set<int>s;
  int shift = 1e9;
  for(auto it = adj_list.begin() ; it != adj_list.end() ; it++)
  {
  int u = it->first;
  plex_g.degen[u] = adj_list[u].size();
  int r = plex_g.degen[u];
  s.insert(r * shift + u);

  }
  set<int>::iterator it;
  vector<int>order;

  while (!s.empty()) {
  it = s.begin();
  int element = *it;
  s.erase(*it);
  int v = (element % shift);
  order.push_back(v);
  for (int w : adj_list[v]) {
  if (plex_g.degen[w] > plex_g.degen[v]) {
  s.erase(plex_g.degen[w] * shift + w);
  plex_g.degen[w] = plex_g.degen[w] - 1;
  s.insert(plex_g.degen[w] * shift + w);
  }
  }
  }



  return order;

  }*/











bool bkplex::is_near_clique(vector<int> p, int u){

	//printf("Inside is_near_clique()\n");

	int total_disconnections = 0;
	int added_disconnections = 0;


	/* if(degree_in_p[u] < d)
	   return false;*/




	/*for(int i =0 ; i<p.size();i++)
	  {
	  int v = p[i];
	  if(!plex_g.is_edge(v , u))
	  added_disconnections++;
	  }*/

	added_disconnections = p.size() - degree_in_p[u];

	//printf("p is: \n");

	//for(int v: p)
	//	printf("%d ", v);

	//printf("\n");
	//printf("degree_in_p[%d]: %d\n", u, degree_in_p[u]);
	//printf("Adding %d\n", u);
	//printf("no_of_disconnection: %d\n", no_of_disconnection);
	//printf("added_disconnections: %d\n", added_disconnections);
	// cout<<u<<" "<<added_disconnections<<" "<<no_of_disconnection<<" "<<(int)p.size() + 1<<endl;

	if(added_disconnections + no_of_disconnection > k)
	{
		return false;
	}

	//how do u ensure that each and every vertex has a degree of atleast d in that structure


	return true;
}





/*should we send the reference or value?*/
void bkplex::bkrec(vector<int>& p, vector<int>& c, vector<int>& x){


	vector<int> new_c;
	vector<int> new_x;


	/*updating c*/	
	for(int v : c){
		if(is_near_clique(p, v)){
			//printf("adding %d to new_c\n", v);
			new_c.push_back(v);
		}
	}



	/*updating x*/
	for(int v : x){
		if(is_near_clique(p, v)){
			new_x.push_back(v);
		}
	}

	//maximal_size = max(maximal_size , (int)p.size());

	// cout<<"New C size is"<<" "<<new_c.size()<<endl;
	// cout<<"New X size is"<<" "<<new_x.size()<<endl;

	/*new maximal k-plex generated*/
	if(new_c.size() == 0 && new_x.size() == 0){ //is maximal near clique
		near_clique_count++;
		//printf("==========Near Clique Found============\n");
		//for(int u : p)
		//	printf("%d ", u);
		//printf("\n");
		//cout<<p.size()<<endl;
		if(near_clique_count%1000 == 0)
			printf("%ld near cliques have been generated\n", near_clique_count);


	}
	else {
		if(new_c.size() > 0){


			auto c_begin = new_c.begin();

			while(new_c.size() > 0){	//Line 13

				c_begin = new_c.begin();

				auto u = *c_begin;
				
				//printf("P-Degree of all vertices: before adding %d\n", u);
				//for(int v: plex_g.vertex_list())
				//	printf("degree_in_p[%d]: %d\n", v, degree_in_p[v]);

				p.push_back(u);
				new_c.erase(c_begin);
				//maximal_size = max(maximal_size , (int)p.size());
				
				for(int v : plex_g.ngh(u)){
					//printf("%d's neighbor: %d\n", u, v);
					degree_in_p[v]++;
					//printf("degree_in_p[%d]: %d\n", v, degree_in_p[v]);
				}

				for(auto v : p){
					if((u != v) && !plex_g.is_edge(u,v))
						no_of_disconnection++;
				}

				//printf("=====Calling bkrec========\n");
				
				//printf("p is: \n");
				//for(int v: p)
				//	printf("%d ", v);
				//printf("\n");

				//printf("new_c is: \n");
				//for(int v: new_c)
				//	printf("%d ", v);
				//printf("\n");

				//printf("new_x is: \n");
				//for(int v: new_x)
				//	printf("%d ", v);
				//printf("\n");

				//printf("P-Degree of all vertices: after adding %d\n", u);
				//for(int v: plex_g.vertex_list())
				//	printf("degree_in_p[%d]: %d\n", v, degree_in_p[v]);
					


				bkrec(p, new_c, new_x);
				//maximal_size = max(maximal_size , (int)p.size());

				for(auto v : p){
					if((u != v) && !plex_g.is_edge(u,v))
						no_of_disconnection--;
				}
				for(int v : plex_g.ngh(u)){
					degree_in_p[v]--;
				}
				//maximal_size = max(maximal_size , (int)p.size());
				p.pop_back();
				//maximal_size = max(maximal_size , (int)p.size());

				new_x.push_back(u);

			}
		}
	}
}

/*
 *
 *
 * t calls a recursive procedure BKRec with three
 disjoint sets as parameters, i.e., 𝑃, 𝐶 and 𝑋 . 𝑃 represents the set
 of vertices that should be contained in the 𝑘-plex in the current
 stage. 𝐶 includes the remaining candidate vertices for enumerating.
 𝑋 contains excluded vertices. They are excluded from the 𝑘-plex to
 avoid non-maximal solutions.
 */

void bkplex::run(){

	vector<int> p;
	vector<int> c = plex_g.vertex_list(); // basically the list of all vertices

	vector<int> x;
	vector<int>cc ;
	cc.clear();
	//for(auto x : )
	
	time_t my_time = time(NULL);

	vector<int>v = plex_g.vertex_list();
	map<int,unordered_set<int>>adj_list;

	for(auto x : v)
	{
		unordered_set<int>st;
		adj_list[x] = st;
		vector<int> y = plex_g.ngh(x);
		for(auto z : y)
		{
			adj_list[x].insert(z);
		}
	}
	set<long long>s;
	//long shift = (long)1e9;
	long long shift = 1e9;
	for(auto it = adj_list.begin() ; it != adj_list.end() ; it++)
	{
		int u = it->first;
		plex_g.degen[u] = adj_list[u].size();
		int r = plex_g.degen[u];
		long long c = r;
		c*= shift;
		c += u;
		s.insert(c);

	}
	// set<int>::iterator it;


	while (!s.empty()) {
		auto it = s.begin();
		auto element = *it;
		s.erase(*it);
		int v = (int)(((element % shift) + shift)%shift);
		cc.push_back((int)v);
		for (int w : adj_list[v]) {
			if (plex_g.degen[w] > plex_g.degen[v]) {
				long long c = plex_g.degen[w];
				c *= shift;
				c += w;
				s.erase(c);
				plex_g.degen[w] = plex_g.degen[w] - 1;
				c = plex_g.degen[w];
				c *= shift;
				c += w;
				s.insert(c);
			}
		}
	}





	//vector<int>c will give the one with degeneracy ordering

	printf("[%d]:Initialization completed\n", __LINE__);

	vector<int> degen_cand;
	vector<int> degen_x;

	//printf("Degeneracy ordering with value\n");
	//for(int i=0; i < plex_g.n; i++)
	//	printf("Degeneracy of %d is %d\n", i, plex_g.degen[i]);

/*	for(int i=0; i < plex_g.n; i++){

		p.push_back(cc[i]);
		for(int j = i+1; j < plex_g.n; j++){
			degen_cand.push_back(cc[j]);
		}

		for(int k = 0; k < i; k++){
		
			degen_x.push_back(cc[k]);
		
		}

		bkrec(p, degen_cand, degen_x);

		printf("[%s]:call on vertex %d completed\n", ctime(&my_time), cc[i]);
		printf("number of near cliques computed: %ld\n", near_clique_count);


	}*/

	//bkrec(p, cc, x); //call for rec with degeneracy ordering
	bkrec(p , c , x); //call if you want without degeneracy ordering and comment upper one

}

long bkplex::countplex(){
	//return maximal_k_plex_count;
	// cout<<no_of_disconnection<<endl;
	//cout<<maximal_size<<endl;
	return near_clique_count;
}

bkplex::~bkplex() {
	// TODO Auto-generated destructor stub

	delete[] degree_in_p;
}

