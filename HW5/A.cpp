#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

long long timer=0;
void dfs(vector<vector<long long>>& adjlist, vector<pair<long long, long long>>& finishTime, vector<bool>& visit, long long node){
    timer++;
    visit[node]=true;
    for(long long nd:adjlist[node]){
        if(!visit[nd]){
            dfs(adjlist, finishTime, visit, nd);
        }
    }
    timer++;
    finishTime.push_back({timer, node});
}
long long findsum(vector<vector<long long>>& adjlist, vector<long long>& weight, vector<long long>& sum, long long node){
    if(sum[node]!=INT_MIN){return sum[node];}
    sum[node]=weight[node];
    for(long long nd:adjlist[node]){
        long long temp=weight[node];
        temp=max(temp, temp+findsum(adjlist, weight, sum, nd));
        sum[node]=max(sum[node], temp);
    }
    return sum[node];
}

int main(){
    long long n_vertex, n_edge;
    cin>>n_vertex>>n_edge;
    // construct graph
    vector<long long> weight(n_vertex);
    vector<vector<long long>> adjlist(n_vertex);
    vector<pair<long long, long long>> finishTime;    // {finish time, node}
    for(long long i=0;i<n_vertex;i++){
        cin>>weight[i];
    }
    for(long long i=0;i<n_edge;i++){
        long long a, b;
        cin>>a>>b;
        a--, b--;
        adjlist[a].push_back(b);
    }

    // dfs to find finish time
    vector<bool> visit(n_vertex, false);
    for(long long i=0;i<n_vertex;i++){
        if(!visit[i]) dfs(adjlist, finishTime, visit, i);
    }

    // sort finish time to get topological sort
    sort(finishTime.begin(), finishTime.end());

    // dp to find the max sum
    vector<long long> sum(n_vertex, INT_MIN);   // dp
    long long mxsum=INT_MIN;
    for(auto p:finishTime){
        long long node=p.second;
        mxsum=max(mxsum, findsum(adjlist, weight, sum, node));
    }
    // for(long long s:sum){cout<<s<<' ';}cout<<endl;

    // output
    cout<<mxsum<<"\n";

    return 0;
}
