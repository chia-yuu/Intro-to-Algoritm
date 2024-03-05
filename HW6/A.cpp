// 100/150
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;

typedef pair<long long, long long> pll;
typedef struct Edge{
    long long src, dest, weight, color;
}Edge;

vector<long long> parent, sz;
long long findp(long long node) {
    return parent[node]==node? node : parent[node]=findp(parent[node]);
}
void joint(long long a, long long b) {
    long long pa=findp(a);
    long long pb=findp(b);
    if (pa!=pb) {
        parent[pa]=pb;
        sz[pb]+=sz[pa];
    }
}

long long find_MST(vector<Edge>& adjlist, long long mask){
    long long cost=0;
    for(auto e:adjlist){
        long long u=e.src, v=e.dest, w=e.weight, c=e.color;
        if((mask>>c)&1 && findp(u)!=findp(v)){
            // printf("%lld, %lld, %lld, %lld\n", u, v, w, c);
            joint(u, v);
            cost+=w;
        }
    }
    return cost;
}

bool cmp(Edge a, Edge b){
    return a.weight<b.weight;
}

int main(){
    long long n_vertex, n_edge, n_color, mncost=LLONG_MAX;
    cin>>n_vertex>>n_edge>>n_color;
    parent=vector<long long>(n_vertex); // init
    sz=vector<long long>(n_vertex, 0);  // init
    vector<long long> color_cost(n_color);
    vector<Edge> adjlist(n_edge);
    for(long long i=0;i<n_color;i++){cin>>color_cost[i];}
    for(long long i=0;i<n_edge;i++){
        long long u, v, w, c;
        cin>>u>>v>>w>>c;
        u--, v--, c--;
        // adjlist.push_back({u, v, w, c});
        adjlist[i]={u, v, w, c};
    }
    sort(adjlist.begin(), adjlist.end(), cmp);
    
    // solve, try all possible color combination
    for(long long mask=0;mask<(1<<n_color);mask++){
        for(long long i=0;i<n_vertex;i++){parent[i]=i; sz[i]=0;}   // init
        long long cost=0;
        // count MST cost + color cost
        for(long long i=0;i<n_color;i++){
            // have (mask>>i)-th color, 
            if((mask>>i)&1){
                cost+=color_cost[i];
            }
        }
        // MST with these colors
        cost+=find_MST(adjlist, mask);
        // check whether all nodes are include in the MST
        for(auto p:parent){
            // cout<<p<<' ';
            if(findp(p)!=findp(0)){cost=LLONG_MAX; break;}
        }
        mncost=min(mncost, cost);
    }

    // output
    cout<<mncost<<"\n";
    // debug : print graph
    /*for(int i=0;i<n_vertex;i++){
        cout<<i+1<<": ";
        for(int j=0;j<adjlist[i].size();j++){
            graphNode g=adjlist[i][j];
            cout<<g.destination+1<<' '<<g.weight<<' '<<g.color<<",  ";
        }
        cout<<endl;
    }*/
    return 0;
}
