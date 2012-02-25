#include <iostream>
#include <cstdlib>
#include <ctime>
void printTable(int *);
int sortByFirst(int *, int, int);
void divideTable(int * , int, int);
int test();
int testTable(int *, int);

int main(int argc, char * argv[]){
srand(time(NULL));
	int table[20] = {5,6,7,20,15,23,45,8,100,10, 12,13,78,51,34,81,3,4,9,11};
/*	printTable(table);
	divideTable(table,20,13);
	printTable(table);
*/
	if(argc <=1) return -1;
	for (int i = 0; i < atoi(argv[1]); i++) {
		if(test()==0){
			std::cout<<"Test failed!"<<std::endl;
			return -1;
		}
	}
	std::cout<<"Test succeded"<<std::endl;
	return 0;
}

void printTable(int * table){
	for (int i = 0; i < 20; i++) std::cout<<table[i]<<",";
	std::cout<<std::endl;
}

int sortByFirst(int * table, int beg, int end){
	int w = table[beg];
	while(1){
		while(table[beg]<w) ++beg;
		while(table[end]>w) --end;
		if(beg<end){
			int tmp = table[beg];
			table[beg] = table[end];
			table[end] = tmp;
			++beg;
			--end;
		}
		else return end;
	}
}
void divideTable(int tab[], int tableSize, int k){
	int beg = 0;
	int end = tableSize - 1;
	while(beg<end){
		int m = sortByFirst(tab, beg, end);
		if(k<m) end=m;
		else beg=m+1;
	}
}

int test(){
	int table[20];
	for (int i = 0; i < 20; i++) {
		table[i] = rand() % 100;
	}
	int k = rand() % 20;
	divideTable(table, 20, k);
	return testTable(table, k);
}

int testTable(int * table, int k){
	for (int i = 0; i <= k; i++) {
		for (int j = k+1; j < 20; j++) {
			if (table[i]>table[j]) return 0;	
		}
	}
	return 1;
}
