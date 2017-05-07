#include "sa.h"

SimulatedAnnealing::SimulatedAnnealing(Analyze *problem,double time):temperature(3000),delta(0.999),timeMAX(time) {
		tStart=clock();
		pro=problem;
		pro->tstart=tStart;
}

double SimulatedAnnealing::RandomNumber() {
		return (double) (rand()/ (double) RAND_MAX);
}

bool SimulatedAnnealing::time_check() {
		return ((double)(clock() - tStart)/CLOCKS_PER_SEC)<=timeMAX;
}

double SimulatedAnnealing::Probability() {
		return 1/(1+ pow(M_E, (dE/temperature)));
}

void SimulatedAnnealing::do_SA() {
		while(time_check()) {
				for(int i=0;i<kMAX;i++) {
						pro->getNewdata();
						dE=pro->get_dE();
						if(dE < 0) {
								pro->Update();
						}
						else {
								if(Probability()>RandomNumber())
										pro->Update();
						}
						pro->get_better();
				}
				temperature*=delta;
		}
		pro->get_answer();
		std::cout<<"SimulatedAnnealing ends\n";
}

TSPdata::~TSPdata() {
		delete [] x;
		delete [] y;
		for(int i=0;i<n;i++)
				delete [] adjacency_matrix[i];
		delete [] adjacency_matrix;
		delete [] curr_path;
		delete [] new_path;
		delete [] min_path;
}

void TSPdata::readFile(std::string filename) {
		std::ifstream in(filename);  
		if (! in.is_open())  { 
				std::cout << "Error opening file"; exit (1); 
		}  
		in>>distance_type;
		if(strcmp(distance_type, "non") == 0) in>>distance_type;
		in>>n;

		x=new double[n];
		y=new double[n];
		adjacency_matrix=new double*[n];
		for(int i=0;i<n;i++)
				adjacency_matrix[i]=new double[n];

		for(int i=0;i<n;i++)
				in>>x[i]>>y[i];
		for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
						in>>adjacency_matrix[i][j];
		init();
}

void TSPdata::init() {
		curr_path=new int[n+1];
		curr_path[0]=curr_path[n]=0;
		new_path=new int[n+1];
		new_path[0]=new_path[n]=0;
		min_path=new int[n+1];
		min_path[0]=min_path[n]=0;
		
		for(int i=1;i<n;i++)
				curr_path[i]=new_path[i]=min_path[i]=i;
}

TSP::TSP(std::string filename) {
		m_data=new TSPdata;
		m_data->readFile(filename);
}

TSP::~TSP() {
		delete m_data;
}

double TSP::get_cost(int *path) {
		double cost=0;
		for(int i=0;i<m_data->n;i++)
				cost+=m_data->adjacency_matrix[path[i]][path[i+1]];
		return cost;
}

double TSP::get_dE() {
		double ch=0;
		ch=get_cost(m_data->new_path)-get_cost(m_data->curr_path);
		return ch;
}

void TSP::Update() {
		for(int i=1;i<m_data->n;i++)
				m_data->curr_path[i]=m_data->new_path[i];
}

void TSP::getNewdata() {
		int r1,r2;

		for(int i=1;i<m_data->n;i++)    
				m_data->new_path[i]=m_data->curr_path[i];  
		r1=generateRandomNumber();
		r2=generateRandomNumber();

		int i,j,k,limit,temp;

		if(r1 > r2) {
			temp=r1;
			r1=r2;
			r2=temp;
		}
		limit=floor((r2-r1+1)/2);
		i=r1, j=r2;

		for(k=0;k<limit+1;k++)
			swap(i++, j--, m_data->new_path);
}

int TSP::generateRandomNumber() {
		return (rand()%(m_data->n-1))+1;
}

void TSP::swap(int r1, int r2, int *new_path) {
		int temp=new_path[r1];
		new_path[r1]=new_path[r2];
		new_path[r2]=temp;
}

void TSP::get_better() {
		if(get_cost(m_data->new_path) < get_cost(m_data->min_path) ) {
				for(int i=1;i<m_data->n;i++)    
						m_data->min_path[i]=m_data->new_path[i];
				//get_answer();
		}
}

void TSP::get_answer() {
		printf("Time taken: %.2fs\n", (double)(clock() - tstart)/CLOCKS_PER_SEC);
		std::cout<<"The shortest cost obtained so far is "<<get_cost(m_data->min_path)<<std::endl;
		for(int i=0;i<m_data->n;i++)
				std::cout<<m_data->min_path[i]+1<<" ";
		std::cout<<std::endl;
}

Knapsack::Knapsack(std::string filename) {
		m_data=new Knapsackdata;
		m_data->readFile(filename);
}

Knapsack::~Knapsack() {
		delete m_data;
}

void Knapsackdata::readFile(std::string filename) {
		std::ifstream in(filename);  
		if (! in.is_open())  { 
				std::cout << "Error opening file"; exit (1); 
		}	
		in>>n>>m;

		v=new int[n];
		w=new int[n];

		for(int i=0;i<n;i++)
				in>>w[i];//in>>v[i]>>w[i];
		for(int i=0;i<n;i++)
				in>>v[i];

		init();
}

Knapsackdata::~Knapsackdata() {
		delete [] v;
		delete [] w;
		delete [] curr_state;
		delete [] new_state;
		delete [] max_state;
}

void Knapsackdata::init() {
		curr_state=new int[n];
		new_state=new int[n];
		max_state=new int[n];

		for(int i=0;i<n;i++)
				curr_state[i]=new_state[i]=max_state[i]=0;
}

int Knapsack::get_value(int *state) {
		int value=0;
		for(int i=0;i<m_data->n;i++)
				value+=m_data->v[i]*state[i];
		return value;
}

bool Knapsack::is_ok() {
		int weight=0;
		for(int i=0;i<m_data->n;i++)
				weight+=m_data->w[i]*m_data->new_state[i];
		return weight<=m_data->m;
}

double Knapsack::get_dE() {
		double ch=get_value(m_data->new_state)-get_value(m_data->curr_state);
		ch=-ch;
		return ch;
}

void Knapsack::Update() {
		for(int i=0;i<m_data->n;i++)
				m_data->curr_state[i]=m_data->new_state[i];
}

void Knapsack::getNewdata() {
		int r1,r2;

		for(int i=1;i<m_data->n;i++)
				m_data->new_state[i]=m_data->curr_state[i];
		r1=generateRandomNumber();
		r2=generateRandomNumber();

		m_data->new_state[r1]=1;
		m_data->new_state[r2]=1;

		if(!is_ok()) m_data->new_state[r2]=0;
		if(!is_ok()) m_data->new_state[r1]=0;
}

int Knapsack::generateRandomNumber() {
		return (rand()%(m_data->n-1))+1;
}

void Knapsack::get_better() {
		if(get_value(m_data->new_state) > get_value(m_data->max_state)) {
				for(int i=0;i<m_data->n;i++)
						m_data->max_state[i]=m_data->new_state[i];
				//get_answer();
		}
}

void Knapsack::get_answer() {
		printf("Time taken: %.2fs\n", (double)(clock() - tstart)/CLOCKS_PER_SEC);
		std::cout<<"The most valuable Knapsack so far is "<<get_value(m_data->max_state)<<std::endl;
		for(int i=0;i<m_data->n;i++)
				std::cout<<m_data->max_state[i]<<" ";
		std::cout<<std::endl;
}
