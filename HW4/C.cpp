// AC, INF要開夠大!!!!!!
#include<iostream>
#include<vector>
using namespace std;

#define INF 999999999999999999

// dp[l][r]=best紀錄 l 到 r 最小的cost=best，record[l][r]=k紀錄 l 到 r 要切在 k 以獲得最小cost
long long solve(vector<long long>& v, vector<vector<long long>>& record, vector<vector<long long> >& dp, long long l, long long r){
    if(dp[l][r]!=-1){return dp[l][r];}
    if(l==r){
        dp[l][r]=0;
        return dp[l][r];
    }
    // l r 在隔壁 -> cost=0 (沒辦法切更小了)
    if(l==r-1){
        dp[l][r]=0;
        return dp[l][r];
    }
    // l 到 r 只有一個點 -> 切在中間那個點 (l+1)，cost=(v[r]-v[l+1])-(v[l+1]-v[l])
    if(l==r-2){
        dp[l][r]=abs((v[r]-v[l+1])-(v[l+1]-v[l]));
        record[l][r]=l+1;
        // record.push_back(l+1);
        // printf("l=%d, r=%d, push=%d (l==r-2)\n", l, r, l+1);
        return dp[l][r];
    }
    // l 到 r 有超過一個點，遞迴找最佳解 = min solve(left) + solve(right) + cost
    long long best=INF, rec=0;
    for(int i=l+1;i<r;i++){
        long long left=solve(v, record, dp, l, i);
        long long right=solve(v, record, dp, i, r);
        long long cost=left+right+abs((v[r]-v[i])-(v[i]-v[l]));
        if(cost<best){
            best=cost;
            rec=i;
        }
    }
    dp[l][r]=best;
    record[l][r]=rec;
    // printf("l=%d, r=%d, push=%d (for loop)\n", l, r, rec);
    return dp[l][r];
}
void print_cut(vector<vector<long long>>& record, long long l, long long r){
    if(r-l==1 || l==r){return;}
    cout<<record[l][r]<<" ";
    if(record[l][r]-l>1) print_cut(record, l, record[l][r]);
    if(r-record[l][r]>1) print_cut(record, record[l][r], r);
    /*vector<pair<long long, long long>> st;
    long long l=0, r=n;
    st.push_back({l, r});
    while(!st.empty()){
        l=st.back().first, r=st.back().second;
        st.pop_back();
        cout<<record[l][r]<<" ";
        if(r-record[l][r]>1) st.push_back({record[l][r], r});
        if(record[l][r]-l>1) st.push_back({l, record[l][r]});
    }*/
}

int main(){
    // read input
    long long  n;
    cin>>n;
    vector<long long> v(n+1, 0);
    vector<vector<long long> > dp(n+1, vector<long long>(n+1,-1)), record(n+1, vector<long long>(n+1, -1));
    for(long long i=1;i<=n;i++){cin>>v[i];}

    // dp
    long long ans=solve(v, record, dp, 0, n);
    vector<bool> has_print(n+1, false);
    cout<<ans<<"\n";
    print_cut(record, 0, n);
    // long long i=0, j=n;
    /*while(i>0){
        cout<<record[i][j]<<" ";
        i--;
        j=record[i][j];
    }*/
    cout<<"\n";

    // debug : print dp
    /*for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<dp[i][j]<<' ';
        }
        cout<<endl;
    }*/
    // debug : print record
    /*for(auto r:record){
        for(int rec:r){
            cout<<rec<<' ';
        }
        cout<<endl;
    }*/
    return 0;
}

/*
5
3 5 10 13 29
*/
/*
9
4 2 1 3
*/

/*
7
2 49 69 88 134 135 307
*/
/*
173
6 2 1 4 3 5
*/
