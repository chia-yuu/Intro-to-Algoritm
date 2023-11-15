// AC
// INF should be big enough
// prefix sum
#include<iostream>
#include<vector>
using namespace std;

#define INF 99999999

long long int sum=0;

void merge_arr(vector<long long> &v, int l, int m, int r){
    vector<int> leftarr(v.begin()+l, v.begin()+m+1);
    vector<int> rightarr(v.begin()+m+1, v.begin()+r+1);
    leftarr.push_back(INF);
    rightarr.push_back(INF);
    int lidx=0, ridx=0;
    long long int l_num=0, l_sum=0;

    for(int i=l;i<=r;i++){
        if(leftarr[lidx]<=rightarr[ridx]){
            l_num++, l_sum+=leftarr[lidx];
            v[i]=leftarr[lidx];
            lidx++;
        }
        else{
            sum+=rightarr[ridx]*l_num-l_sum;
            v[i]=rightarr[ridx];
            ridx++;
        }
    }
}
void merge_sort(vector<long long> &v, int l, int r){
    if(l<r){
        int m=l+(r-l)/2;
        merge_sort(v, l, m);
        merge_sort(v, m+1, r);
        merge_arr(v, l, m, r);
    }
}

int main(){
    int n;
    cin>>n;
    vector<long long> v(n,0);
    for(int i=0;i<n;i++){cin>>v[i];}
    sum=0;  // init
    merge_sort(v, 0, n-1);
    cout<<sum<<'\n';
    return 0;
}
