#include <iostream>
#include "P-2/Stack_LL.h"
using namespace std;

int* nextGreater(const int a[], int s){
    Stack_LL refStack{};
    int* arr = new int[s];

    for(int i=s-1; i>=0; i--){

        while(!refStack.isEmpty() && refStack.peek() <= a[i]) {
            refStack.pop();
        }

        if(refStack.isEmpty()){
            arr[i] = -1;
        } else{
            arr[i] = refStack.peek();
        }

        refStack.push(a[i]);

    }

    return arr;
}

int main(){
    int m[10] = {2,9,0,12,4,1,6,8,9,2};
    int n[4] = {2,3,1,2};

    int *a = nextGreater(m,10);
    int *b = nextGreater(n,4);

    for(int x=0;x<10;x++){
        cout<<a[x]<<'\t';
    }

    cout<<'\n';

    for(int x=0;x<4;x++) cout<<b[x]<<'\t';

    delete[] a;
    delete[] b;

    return 0;
}