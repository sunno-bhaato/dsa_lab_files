#include <iostream>
#include <deque>
using namespace std;

int* slide_max(int *arr, int s, int k){
    deque<int> dq;
    int* ans = new int[s-k+1];

    for(int i=0;i<s;i++){
        while(!dq.empty() && dq.front() <= (i-k)) dq.pop_front();
        while(!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();
        dq.push_back(i);
        if(i>=k-1) ans[i-k+1] = arr[dq.front()];
    }

    return ans;
}

int main(){
    int a[] = {1,3,42,4,9, 34, 30,2 ,9, 10};
    int k = 2;
    int* b = slide_max(a,sizeof(a)/sizeof(int),k);
    for(int i=0;i<(sizeof(a)/sizeof(int) - k + 1);i++) cout<<b[i]<<'\t';
    delete b;
    return 0;

}