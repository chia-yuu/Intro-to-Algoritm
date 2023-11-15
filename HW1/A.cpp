// AC
// Kadane’s algorithm
#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> v(n,0);
    bool all_negative=true;
    for(int i=0;i<n;i++){
        cin>>v[i];
        if(v[i]>=0){all_negative=false;}
    }

    long long int max_ending_here=0, ans=0, max_negative=v[0];
    int low, high;
    vector<vector<int>> idx;
    for(int i=0;i<n;i++){
        if(all_negative){
            max_negative=max(max_negative,(long long)v[i]);
            ans=max_negative;
            if(ans==v[i]){idx.push_back({i, i});}
            continue;
        }
        
        if(max_ending_here==0){low=i;}
        max_ending_here=max((long long)0, max_ending_here+v[i]);
        ans=max(max_ending_here, ans);
        if(ans==max_ending_here){
            high=i;
            idx.push_back({low, high});
        }
    }
    cout<<ans<<'\n'<<idx[idx.size()-1][0]+1<<' '<<idx[idx.size()-1][1]+1<<endl;
    return 0;
}

/*
5
-5 6 -3 4 -1
4
1000000000 1000000000 1000000000 1000000000
7
-3 -5 -100 -2 -23 -15 -9
8
25 -32 8 13 47 -44 45 -100
*/
