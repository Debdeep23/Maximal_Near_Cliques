#include <cassert>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <cstring>
#include <bits/stdc++.h>


using ui = unsigned int;
const ui FILELEN = 1024;

std::ofstream outdata;
std::unordered_map<ui, ui> map_vertex_to_idx;
static ui n = 0;

int to_int(std::string &x) {
	std::stringstream aux; aux << x;
	int res; aux >> res;
	return res;
}

int add_vertex(int &A){

	//printf("[%d]: %d\n", __LINE__, A);
	if(map_vertex_to_idx.find(A) == map_vertex_to_idx.end()){
		//printf("[%d]:Inside if\n", __LINE__);
		map_vertex_to_idx[A] = n;
		n = n+1;
	}
	//printf("[%d]: %d\n", __LINE__, map_vertex_to_idx[A]);
	return map_vertex_to_idx[A];
}


void readEdgeListFile(const char *filepath){
	std::ifstream infile;
	char buf[1024];
	infile.open(filepath, std::ios::in);
	if(!infile.is_open()){
		fprintf(stderr, "can not find file %s\n", filepath);
		exit(1);
	}

	std::set<std::pair<ui, ui>> seen_edges;

	int from, to;
	while(infile.getline(buf, 1024)){
		char *p = buf;
		while(*p == ' ' && *p != '\0') p++;
		if(*p == '#' || *p == '\0') continue;
		std::stringstream ss(buf);
		ss >> from >> to;
		if(from != to){
			int A = from;
			int B = to;

			//printf("%d %d\n", A , B);

			int u = add_vertex(A);
			int v = add_vertex(B);

			if(u > v){	/*swapping*/
				int tmp = u;
				u = v;
				v=tmp;
			}

			if(seen_edges.find(std::make_pair(u, v)) != seen_edges.end())
			{
				//printf("Edge is aleady considered\n");
				continue;
			}

			seen_edges.insert(std::make_pair(u, v));

			//printf("%d %d\n", u, v);

			if(u == v){
				printf("loop\n");
				continue;
			}


			outdata << u << " " << v << std::endl;
		}
	}
}


static int fileSuffixPos(char * filepath){
	int j = strlen(filepath) - 1;
	while(filepath[j] != '.')
		j--;
	return j+1;
}

void promot() {
	printf("convert-to-zero-base txtfile [zero-base-file]\n");
}

int main(int argc, char **argv) {

	char txtFilePath[FILELEN] = "\0";
	char zeroBaseFilePath[FILELEN] = "\0";

	if(argc < 2){
		promot();
		exit(1);
	}
	else if(argc == 2){
		strncpy(txtFilePath, argv[1], FILELEN);
	}
	else if(argc == 3){
		strncpy(txtFilePath, argv[1], FILELEN);
		strncpy(zeroBaseFilePath, argv[2], FILELEN);
	}
	else{
		printf("Redundant args!\n");
	}

	//Identify format
	//currently only txt format is supported
	int pos = fileSuffixPos(txtFilePath);

	outdata.open(zeroBaseFilePath);

	if(strcmp(txtFilePath+pos, "txt") == 0){
		readEdgeListFile(txtFilePath);
	}



}
