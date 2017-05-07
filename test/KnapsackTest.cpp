#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

int main() {
		int n,m;
		string filename;
		cout<<"Please enter amount: ";
		cin>>n;
		cout<<"Please enter Maxweight: ";
		cin>>m;
		cout<<"Please enter filename: ";
		cin>>filename;

		ofstream out(filename);
		if(! out.is_open()) {
				cout<<"Error!"; exit(1);
		}
		out<<n<<endl<<m<<endl;
		for(int i=0;i<n;i++)
				out<<int(rand()%(m-2))+1<<" ";
		out<<endl;
		for(int i=0;i<n;i++)
				out<<int(rand()%100)<<" ";
		out<<endl;
		out.close();
		return 0;
}
