// AC, use adj mtx not adj list
#include<iostream>
#include<vector>
#include<climits>
#include<queue>
using namespace std;

#define dest first
#define flow second
#define INF 999999999999999999
typedef pair<long long, long long> pll;

// to find whether there is path from s to t, if no then return false, else construct the path
bool bfs(vector<vector<long long>>& adjlist, long long s, long long t, vector<long long>& parent){
    vector<bool> visit(adjlist.size(), false);
    queue<long long> q;
    q.push(s);
    visit[s]=true, parent[s]=-1;
    while(!q.empty()){
        long long cur=q.front();
        q.pop();
        for(long long nd=0;nd<adjlist[cur].size();nd++){
            if(!visit[nd] && adjlist[cur][nd]>0){
                if(nd==t){
                    parent[nd]=cur;
                    return true;    // has graph from s to t
                }
                q.push(nd);
                parent[nd]=cur;
                visit[nd]=true;
            }
        }
    }
    return false;   // no path from s to t
}
long long max_flow(vector<vector<long long>>& adjlist, long long s, long long t){
    vector<long long> parent(adjlist.size());   // filled by bfs to record the path
    long long mx_f=0;
    while(bfs(adjlist, s, t, parent)){
        // find min flow in the path
        long long add_flow=INF;
        for(long long v=t;v!=s;v=parent[v]){
            long long u=parent[v];
            long long wt=adjlist[u][v];
            add_flow=min(add_flow, wt);
        }
        // add the min flow to all edge along the path
        for(long long v=t;v!=s;v=parent[v]){
            long long u=parent[v];
            adjlist[u][v]-=add_flow;
            adjlist[v][u]+=add_flow;
        }
        // count max flow
        mx_f+=add_flow;
    }
    return mx_f;
}

int main(){
    // read input and construct graph
    long long n_vertex, n_edge, tot_weight=0;
    cin>>n_vertex>>n_edge;
    vector<vector<long long>> adjlist(n_vertex+n_edge+2, vector<long long>(n_vertex+n_edge+2, 0));     // {dest, weight}
    // vertex weight, s connect to every vertex
    for(long long i=1;i<=n_vertex;i++){
        long long w;
        cin>>w;
        adjlist[0][i]=w;
        adjlist[i][0]=w;
    }
    // edge, vertex connect to edge, edge connect to t
    for(long long i=1;i<=n_edge;i++){
        long long u, v, w;
        cin>>u>>v>>w;
        adjlist[u][n_vertex+i]=INF;                 // vertex u connect to edge with INF capacity
        adjlist[v][n_vertex+i]=INF;                 // vertex v connect to edge with INF capacity
        adjlist[n_vertex+i][n_vertex+n_edge+1]=w;   // edge connect to t with capacity = edge weight
        tot_weight+=w;                              // count total edge weight
    }

    // find max flow
    long long min_cut=max_flow(adjlist, 0, n_vertex+n_edge+1);
    // output, answer = total edge weight - min cut (max flow)
    cout<<tot_weight-min_cut<<"\n";
    return 0;
}
