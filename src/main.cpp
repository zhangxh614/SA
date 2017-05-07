#include "sa.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
		string problemname,filename;
		double time;
		cout<<"Which problem? (TSP or Knapsack): ";
		cin>>problemname;
		cout<<"Please enter file name: ";
		cin>>filename;
		cout<<"Please enter the max running time (s): ";
		cin>>time;

		Analyze *problem;

		if(problemname == "TSP") problem=new TSP(filename);
		else if(problemname == "Knapsack") problem=new Knapsack(filename);
		else cout<<"Error!\n";

		SimulatedAnnealing sa(problem,time);
		sa.do_SA();
}
