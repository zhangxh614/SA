设计思想:
    	1.由类SimulatedAnnealing定义算法的基本骨架,将不变的内容比如SA算法的核心实现,随机数的产生等放在该
	类中,变的部分如针对不同问题的数据读取,储存不同以及判断是否更优的方法不同等,抽象为新的接口来分别实
	现.
	2.由于TSP问题和0/1背包问题在SA算法中一些部分具体实现的不同,故抽象出新的接口Analyze,将数据的处理委
	托给新的类Data,并且通过继承的方式来实现针对不同问题的多态.实现变与不变的分离和单一责任原则.


测试环境:Fedora25
源码储存在src文件里


测试用例生成(test文件里包含有生成好的测试用例):
make TSPtest
make KnapsaceTest.out

输入样例:


//TSP:

TSP
TSPtest.txt
2

//Knapsack

Knapsack
KnapsackTest.txt
2


输出样例:


TPS:./sa.out


Please enter file name: TSPtest.txt
Please enter the max running time (s): 2
Time taken: 2.00s
The shortest cost obtained so far is 538.054
1 42 47 18 29 28 45 36 49 21 39 46 40 17 38 25 11 35 44 20 31 26 22 16 33 48 5 9 34 14 8 6 12 15 10 23 13 32 2 41 24 3 50 37 7 19 27 30 43 4 
SimulatedAnnealing ends


Knapsack:./sa.out

Time taken: 2.00s
The most valuable Knapsack so far is 592
0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 1 1 0 
SimulatedAnnealing ends




