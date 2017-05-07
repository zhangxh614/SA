#ifndef SA_H
#define SA_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <cstring>

class Analyze;
class SimulatedAnnealing {
		private:
				enum { kMAX=100 };//每个温度下的循环次数
				double temperature;//初始温度,目前设为3000
				double delta;//退火系数
				double timeMAX;//运行时长,运行时指定
				double dE;//能量变化
				Analyze *pro;
		protected:
				clock_t tStart;//记录开始时间
		public:
				SimulatedAnnealing(Analyze*,double);
				double RandomNumber();//产生0-1间随机数
				bool time_check();//判断是否超时
				double Probability();//接受更差数据的概率
				void do_SA();//模拟退火算法核心
};

class Data {
		public:
				virtual ~Data() { };
				virtual void readFile(std::string) = 0;//读取文件
				virtual void init() = 0;//初始化
};

class TSPdata:public Data {
		public:
				~TSPdata();
				char distance_type[30];
				int n;
				double *x,*y;
				double **adjacency_matrix;
				int *curr_path,*new_path,*min_path;
				void readFile(std::string);
				void init();
};

class Knapsackdata:public Data {
		public:
				~Knapsackdata();
				int n,m;
				int *v,*w;
				int *curr_state,*new_state,*max_state;
				void readFile(std::string);
				void init();
};

				
class Analyze {
		public:
				clock_t tstart;
				//virtual bool is_better() = 0;//判断当前状态是否最优
				virtual ~Analyze() { };
				virtual double get_dE() = 0;
				virtual void Update() = 0;//更新数据
				virtual void getNewdata() = 0;//产生扰动,获得新数据
				virtual void get_better() = 0;//判断结果是否更优
				virtual void get_answer() = 0;//打印现有最优解
				virtual int generateRandomNumber() = 0;
};

class TSP:public Analyze {
		private:
				TSPdata *m_data;
		public:
				TSP(std::string);
				~TSP();
				double get_dE();
				void Update();
				void getNewdata();
				void get_better();
				void get_answer();
				int generateRandomNumber();
				double get_cost(int *);
				void swap(int,int,int*);
};

class Knapsack:public Analyze {
		private:
				Knapsackdata *m_data;
		public:
				Knapsack(std::string);
				~Knapsack();
				double get_dE();
				void Update();
				void getNewdata();
				void get_better();
				void get_answer();
				int generateRandomNumber();
				int get_value(int*);
				bool is_ok();
};

#endif
