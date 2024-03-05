#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class DisjointSet {
public:
    vector<long long> parent;
    vector<long long> size;

    DisjointSet(long long n) {
        parent.resize(n + 1);
        size.resize(n + 1, 0);
        for (long long i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    long long findp(long long node) {
        return parent[node]==node? node : parent[node]=findp(parent[node]);
    }
    void joint(long long a, long long b) {
        long long pa=findp(a);
        long long pb=findp(b);
        if (pa!=pb) {
            parent[pa]=pb;
            size[pb]+=size[pa];
        }
    }
};

long long bfs(const vector<vector<long long>>& adjlist, const vector<long long>& is_black, long long u) {
    long long n = adjlist.size();
    vector<bool> visited(n+1, false);
    queue<pair<long long, long long>> q;
    q.push({u, 0}); // q.push({node, dist})
    while (!q.empty()) {
        long long cur=q.front().first;
        long long dist=q.front().second;
        q.pop();
        visited[cur]=true;
        if (is_black[cur]==1) {
            return dist;
        }
        for (long long nd : adjlist[cur]) {
            if (!visited[nd]) {
                q.push({nd, dist+1});
            }
        }
    }
    return -1; // no black vertex in the same component with u
}

int main() {
    long long n_vertex, n_query;
    cin >>n_vertex>>n_query;

    vector<long long> is_black(n_vertex+1);
    DisjointSet ds(n_vertex);
    vector<vector<long long>> adjlist(n_vertex+1);

    for (long long i=1;i<=n_vertex;i++) {
        cin>>is_black[i];
        if (is_black[i]==1) {
            ds.size[i]=1; //init
        }
    }
    // start query
    for (long long i=0;i<n_query;i++) {
        long long type, u, v;
        cin>>type;
        // add edge and joint two vertex into the same set
        if (type == 1) {
            cin >> u >> v;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
            ds.joint(u, v);
        }
        // number of black vertex in the same set as u
        else if (type == 2) {
            cin>>u;
            long long root=ds.findp(u);
            cout<<ds.size[root]<<"\n";
        }
        // shortest distance from u to black vertex, bfs
        else if (type == 3) {
            cin>>u;
            // long long root=ds.findp(u);
            long long result=bfs(adjlist, is_black, u);
            cout<<result<<"\n";
        }
    }

    return 0;
}
