
#include<bits/stdc++.h>
#include "bkplex.h"
#include <cassert>




bkplex::bkplex() {
	// TODO Auto-generated constructor stub

}

bkplex::bkplex(graph &g, int _k , int _d): plex_g(g), k(_k) , d(_d){
	maximal_k_plex_count = 0;
	degree_in_p = new int[g.n]();
    no_of_disconnection = 0;
    near_clique_count = 0;
	
}



//find out degeneracy order and put that order in vector<int>p as order








//condition for (k , d)




bool bkplex::is_near_clique(vector<int> p, int u){



    int total_disconnections = 0;
    int added_disconnections = 0;


    if(degree_in_p[u] < d)
        return false;




    for(int i =0 ; i<p.size();i++)
    {
        int v = p[i];
        if(!plex_g.is_edge(v , u))
            added_disconnections++;
    }


    if(added_disconnections + no_of_disconnection > k)
    {
        return false;
    }

    //how do u ensure that each and every vertex has a degree of atleast d in that structure


    return true;
}





/*should we send the reference or value?*/
void bkplex::bkrec(vector<int> p, vector<int> c, vector<int> x){


	vector<int> new_c;
	vector<int> new_x;
	
	
	/*updating c*/	
	for(int v : c){
		if(is_near_clique(p, v)){
			new_c.push_back(v);
		}
	}

	/*updating x*/
	for(int v : x){
		if(is_near_clique(p, v)){
			new_x.push_back(v);
		}
	}


	
	/*new maximal k-plex generated*/
	if(new_c.size() == 0 && new_x.size() == 0){ //is maximal near clique
		near_clique_count++;
      //  cout<<p.size()<<endl;

		return;
	}
	else {
		if(new_c.size() > 0){
		

			auto c_begin = new_c.begin();

			while(new_c.size() > 0){	//Line 13
			
				c_begin = new_c.begin();
				
				int u = *c_begin;

				p.push_back(u);
				
			/*	for(int v : plex_g.ngh(u)){
					degree_in_p[v]++;
				}*/

            for(int v : p)
            {
                
            }
                for(auto v : p){
                    if(!plex_g.is_edge(u,v))
                        no_of_disconnection++;
                }



				new_c.erase(c_begin);
				bkrec(p, new_c, new_x);

                for(auto v : p){
                    if(!plex_g.is_edge(u,v))
                        no_of_disconnection--;
                }
				for(int v : plex_g.ngh(u)){
					degree_in_p[v]--;
				}
				
				p.pop_back();
				
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


    //vector<int>c will give the one with generacy ordering
	
	printf("[%d]:Initialization completed\n", __LINE__);

	bkrec(p, c, x);
}

long bkplex::countplex(){
	//return maximal_k_plex_count;
    cout<<no_of_disconnection<<endl;
    return near_clique_count;
}

bkplex::~bkplex() {
	// TODO Auto-generated destructor stub
	
	delete[] degree_in_p;
}

