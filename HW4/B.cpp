// 2d dp, bfs
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define negINF -99999999

int main(){
    // read input
    long long m, n;
    cin>>m>>n;
    vector<vector<long long>> mtx(m, vector<long long>(n)), best(m, vector<long long>(n, negINF));
    for(long long i=0;i<m;i++){
        for(long long j=0;j<n;j++){ 
            cin>>mtx[i][j];
        }
    }

    // bfs
    queue<pair<long long, long long>> q;
    q.push({0,0});
    best[0][0]=0;
    while(!q.empty()){
        long long x=q.front().first, y=q.front().second;
        // printf("at %d, %d: ", x, y);
        q.pop();
        if(y+1<n){  // right, *1
            long long val=best[x][y]+mtx[x][y+1];
            if(val>best[x][y+1]){
                best[x][y+1]=val;
                q.push({x, y+1});
                // printf("right push %d, %d   ", x, y+1);
            }
        }
        if(x+1<m){  // down, *2
            long long val=best[x][y]+2*mtx[x+1][y];
            if(val>best[x+1][y]){
                best[x+1][y]=val;
                q.push({x+1, y});
                // printf("down push %d, %d    ", x+1, y);
            }
        }
        if(x+1<m && y+1<n){ //down right, *4
            long long val=best[x][y]+4*mtx[x+1][y+1];
            if(val>best[x+1][y+1]){
                best[x+1][y+1]=val;
                q.push({x+1, y+1});
                // printf("down right push %d, %d  ", x+1, y+1);
            }
        }
        // cout<<endl;
    }
    /*cout<<"best:\n";
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<best[i][j]<<' ';
        }
        cout<<endl;
    }*/
    cout<<best[m-1][n-1]<<"\n";
    return 0;
}

/*
3 4
3 1 4 1
5 9 2 6
5 3 5 8
*/
// 70

/*
3 3
-1 -1 -1
-1 -1 -1
-1 -1 -1
*/
// -6

/*
5 3
-1 2 9
-10 4 -7
3 1 5
-2 0 -6
3 5 2
*/
// 30

/*
1 1
3
*/
// 0
