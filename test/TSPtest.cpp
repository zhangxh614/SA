#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdio>
#include <cmath>

using namespace std;

double d(double x1,double y1,double x2,double y2) {
		return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int main() {
		int n;
		double *x,*y;
		string filename;
		cout<<"Please enter amount: ";
		cin>>n;
		cout<<"Please enter filename: ";
		cin>>filename;
		x=new double[n];
		y=new double[n];
		ofstream out(filename);
		if(! out.is_open()) {
				cout<<"Error!"; exit(1);
		}
		out<<"euclidean"<<endl;
		out<<n<<endl;
		for(int i=0;i<n;i++){
				x[i]=double(rand()%100);
			    y[i]=double(rand()%100);
				out<<x[i]<<" "<<y[i]<<endl;
		}
		for(int i=0;i<n;i++) {
				for(int j=0;j<n;j++)
						out<<d(x[i],y[i],x[j],y[j])<<"  ";
				out<<endl;
		}
		out.close();
		
		return 0;
}
