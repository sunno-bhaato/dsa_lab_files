#include <iostream>
#include "P-2/Stack_LL.h"
using namespace std;

int* nextGreaterIndex(const int a[], int s){
    Stack_LL indices{};
    int *arr = new int[s];

    for(int i=s-1; i>=0; i--){

        while(!indices.isEmpty() && a[indices.peek()] <= a[i]) {
            indices.pop();
        }

        if(indices.isEmpty()){
            arr[i] = 0;
        } else{
            arr[i] = (indices.peek() - i);
        }

        indices.push(i);

    }

    return arr;
}

int main(){
    int m[10] = {2,9,0,12,4,1,6,8,9,2};
    int n[4] = {2,1,4,2};
    int eg1[] = {73,74,75,71,69,72,76,73};
    int eg2[] = {30,40,60,60};
    int eg3[] = {30,60,90};

    int *a = nextGreaterIndex(m,10);
    int *b = nextGreaterIndex(n,4);
    int *c = nextGreaterIndex(eg1, 8);
    int *d = nextGreaterIndex(eg2, 4);
    int *e = nextGreaterIndex(eg3, 3);

    for(int x=0;x<10;x++) cout<<a[x]<<'\t';

    cout<<'\n';

    for(int x=0;x<4;x++) cout<<b[x]<<'\t';

    cout<<'\n';

    for(int x=0;x<8;x++) cout<<c[x]<<'\t';

    cout<<'\n';

    for(int x=0;x<4;x++) cout<<d[x]<<'\t';

    cout<<'\n';

    for(int x=0;x<3;x++) cout<<e[x]<<'\t';

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] d;
    delete[] e;

    return 0;
}