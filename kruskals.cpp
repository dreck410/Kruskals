#include "kruskals.h"

using namespace std;


int main(int argc, char* argv[])
{
	int v1,v2,w;
	int numOfedges = 0;


	if(argc == 2)
	{
		ifstream read(argv[1]);
		kruskals myK;

		while(read>>v1>>v2>>w){
			myK.pushToQueue(v1, v2, w);

			numOfedges++;

		}
		myK.findKrusks(numOfedges);
		std::cout << "Total Cost of tree is " << myK.totalWeight << "\n";
	}
	else
	{
		cout<<"Please give a file name."<<'\n';
	}
}

