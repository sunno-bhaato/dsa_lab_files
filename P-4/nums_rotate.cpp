#include <iostream>
#include "P-3/queue_LL.h"
using namespace std;

void rotate(int *nums, int S, int k){
    int steps = k%S;
    if(!steps) return;
    else{

        queue_LL<int> refQ;
        for(int i=0;i<S;i++) refQ.enqueue(nums[i]);

        int x = 0;

        while(!refQ.isEmpty()){
            nums[(steps+x)%S] = refQ.peek();
            refQ.dequeue();
            x++;
        }

    }
}

int main(){
    int a[] = {1,2,3,4,5,8,2,10,9};
    for(int i:a) cout<<i<<'\t';
    rotate(a,sizeof(a)/sizeof(int),7);
    cout<<'\n';
    for(int i:a) cout<<i<<'\t';
    return 0;
}