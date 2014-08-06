#include <iostream>
#include <unistd.h>
#include <malloc.h>

using namespace std;

int * call1(){
	int *i = (int*)realloc(i,sizeof(int)*2);
	i[0] = 6;
	i[1] = 7;
	return i;
}

int * call(int **i){
	*i = (int*)malloc(sizeof(int)*2);
	*i[0] = 8;
}

int main(){
	int *i = (int *)malloc(sizeof(int));
	*i=1;
	cout << *i;
	free(i);

	int *temp = call1();
	cout << temp[0] << temp[1];
	free(temp);

	int * v;
	call(&v);

	cout << *v;
	free(v);
}