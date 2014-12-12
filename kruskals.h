#ifndef kruskals_H
#define kruskals_H
#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <queue>
#include <iostream>
#include <vector>
#include <map>

typedef struct nodePair{
    int v1,v2,weight;


    nodePair(int _v1=0, int _v2=0, int _w=0) : v1(_v1), v2(_v2), weight(_w) { ; }

	bool operator > (const nodePair &rhs) const{
		return (weight > rhs.weight);
	}

}nodePair;

class kruskals
{
public:

	//nodePair G[1000];
	std::vector<std::vector<int>> associations;
	std::vector<bool> values;
	std::priority_queue<nodePair, std::vector<nodePair>, std::greater<nodePair>> pqOfNodes;

	unsigned long long int totalWeight = 0;
	kruskals(){;}
	~kruskals(){;}

	void pushToQueue(int v1,int  v2,int w){
		pqOfNodes.push(nodePair(v1,v2,w));

	}


	bool checkConnection(int from, int searching, int findMe){
		bool marked = false;
		int numOfAssoc = associations[searching].size();
		for (int i = 0; i < numOfAssoc; ++i)
		{
			int newSearching = associations[searching][i];
			// grabs the other node
			//int newSearching = connection.v1 != searching ? connection.v1 : connection.v2;
			if(newSearching == findMe){
				marked = true;
				return marked;
			}
			// not there check the next one...
			if(from == newSearching){ continue; }

			marked = checkConnection(searching, newSearching, findMe);
			if(marked){
				return marked;
			}
		}

		return marked;
	}	

	void mark(nodePair nodes){
		values[nodes.v1] = true;
		values[nodes.v2] = true;
		totalWeight += nodes.weight;
		associations[nodes.v1].push_back(nodes.v2);
		associations[nodes.v2].push_back(nodes.v1);
	}

	bool markIt(nodePair nodes){
		bool marked = false;
		// if one of them is not yet, find it and mark the location

		if (!values[nodes.v1] || !values[nodes.v2])
		{	
			mark(nodes);
			marked = true;

		}else{
			// we have found both of them.
			// but we might still add it.
			// check if it's connected.
			if(!checkConnection(-1, nodes.v1, nodes.v2)){
				mark(nodes);
				marked = true;
			}
		}


		return marked;
	}

	void findKrusks(int numOfEdges){
		values.resize(numOfEdges);
		associations.resize(numOfEdges);
		while(pqOfNodes.size() != 0){
			nodePair nodes = pqOfNodes.top();

			if(markIt(nodes)){
				std::cout << "Added " << nodes.v1 << " | " 
					<< nodes.v2 << " | " << nodes.weight << '\n';
			}
			pqOfNodes.pop();

		}
	}
	
};

#endif
