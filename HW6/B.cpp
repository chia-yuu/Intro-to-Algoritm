// johnson's algo, AC
// use adjlist instead of adj mtx
// compute sum during dijkstra (line 47, use visit to record the visited node), don't use another for loop to compute
// *** e.w=e.w+e.u-e.v, sum+=cur.dist+height[cur]-height[src]
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define INF 99999999999999999

bool bellmanFord(vector<vector<long long>>& edge, vector<long long>& height){
    long long n_vertex=height.size();
    height[0]=0;
    // relax
    for(long long i=0;i<n_vertex-1;i++){
        for(long long j=0;j<edge.size();j++){
            long long w=edge[j][0], u=edge[j][1], v=edge[j][2];
            if(height[u]!=INF && height[u]+w<height[v]){
                height[v]=height[u]+w;
            }
        }
    }

    // debug : print height
    /*for(auto h:height){
        cout<<h<<' ';
    }cout<<endl;*/

    // check negative cycle
    for(long long i=0;i<edge.size();i++){
        long long w=edge[i][0], u=edge[i][1], v=edge[i][2];
        if(height[u]!=INF && height[u]+w<height[v]){
            return true;    // have negative cycle
        }
    }
    return false;   // no negative cycle
}
long long dijkstra(vector<vector<pair<long long, long long>>>& adjlist, long long src, vector<long long>& height){
    long long sum=0;
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;   // {dist, node}
    vector<long long> dist(adjlist.size(), INF);
    vector<bool> visit(adjlist.size(), false);
    dist[src]=0;
    pq.push({0, src});
    while(!pq.empty()){
        long long cur=pq.top().second;      // cur node
        if(visit[cur]){pq.pop(); continue;}
        visit[cur]=true;
        sum+=pq.top().first+height[cur]-height[src];    // uv+v-u
        // printf("%lld to %lld = %lld,    ", src, cur, pq.top().first+height[cur]-height[src]);
        pq.pop();

        // printf("\ncur= %lld:\n", cur);
        for(long long i=0;i<adjlist[cur].size();i++){
            long long w=adjlist[cur][i].second;  // weight
            long long nd=adjlist[cur][i].first;  // neighbor node
            // if(!visit[nd]){    // haven't visit
                if(dist[cur]!=INF && dist[cur]+w<dist[nd]){
                    dist[nd]=dist[cur]+w;
                    pq.push({dist[nd], nd});
                    // printf("%lld from %lld with weight %lld,    ", nd, cur, dist[i]);
                }
            // }
        }
    }
    // printf("from %lld: ", src);
    /*for(long long i=0;i<dist.size();i++){
        if(dist[i]!=INF){sum+=dist[i]+height[i]-height[src]; /*cout<<i<<','<<dist[i]+height[i]-height[src]<<' ';}
    }//cout<<endl;*/
    return sum;
}

int main(){
    // read input and construct graph
    long long n_vertex, n_edge;
    long long sum=0;
    cin>>n_vertex>>n_edge;
    vector<vector<pair<long long, long long>>> adjlist(n_vertex+5);     // adjlist[a]={b, weight}
    vector<vector<pair<long long, long long>>> reweight_adjlist(n_vertex+5);     // adjlist[a]={b, weight}
    vector<vector<long long>> edge;    // edge[i]={weight, src, dest};
    vector<long long> height(n_vertex+5, INF);
    bool has_negCycle=false;
    for(long long i=0;i<n_edge;i++){
        long long a, b, w;
        cin>>a>>b>>w;
        adjlist[a].push_back({b, w});
        // adjlist[a][b]=min(w, adjlist[a][b]);
        edge.push_back({w, a, b});
    }
    
    // add a new vertex s
    if(n_edge!=0){
        for(long long i=0;i<n_vertex;i++){
            adjlist[0].push_back({i, 0});
            edge.push_back({0, 0, i+1});
        }

        // debug : print graph
        /*printf("original graph:\n");
        for(int i=0;i<adjlist.size();i++){
            cout<<i<<": ";
            for(int j=0;j<adjlist[i].size();j++){
                cout<<adjlist[i][j].first<<','<<adjlist[i][j].second<<"   ";
            }
            cout<<endl;
        }*/

        // bellman ford to find shortest distance from s to other node and check if there is negative cycle
        if(bellmanFord(edge, height)){
            has_negCycle=true;
        }
        else{
            // no negative cycle, reweight
            for(long long i=0;i<edge.size();i++){
                long long w=edge[i][0], u=edge[i][1], v=edge[i][2];
                edge[i][0]=w+height[u]-height[v];
                // adjlist[u][v]=w+height[u]-height[v];
                reweight_adjlist[u].push_back({v, w+height[u]-height[v]});
            }

            // debug : print reweighing graph
            /*printf("reweighing graph:\n");
            for(int i=0;i<reweight_adjlist.size();i++){
                cout<<i<<": ";
                for(int j=0;j<reweight_adjlist[i].size();j++){
                    cout<<reweight_adjlist[i][j].first<<','<<reweight_adjlist[i][j].second<<"   ";
                }
                cout<<endl;
            }*/

            // dijkstra to find all source shortest path
            for(long long i=1;i<=n_vertex;i++){
                sum+=dijkstra(reweight_adjlist, i, height);
                // cout<<endl;
            }
        }
    }

    // output
    if(has_negCycle){
        cout<<"Negative-weight cycle found\n";
    }
    else{
        cout<<sum<<endl;
    }

    /*for(auto v:dist){
        for(auto d:v){
            if(d==INF){cout<<-1<<' ';}
            else{cout<<d<<' ';}
        }cout<<endl;
    }*/
    return 0;
}
