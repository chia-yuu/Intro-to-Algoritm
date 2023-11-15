// AC
#include<iostream>
#include<vector>
#include<set>
#include<queue>
using namespace std;

int main(){
    // read input
    long long n, m, k, ans=0;
    cin>>n>>m>>k;
    vector<long long> a(n), b(m);
    priority_queue<long long> pq;
    for(long long i=0;i<n;i++){cin>>a[i];}
    // read array b and calculate a^2+ab+b^2 = (a+b)^2-ab
    for(long long i=0;i<m;i++){
        cin>>b[i];
        for(int j=0;j<n;j++){
            long long temp=abs((a[j]+b[i])*(a[j]+b[i]))-abs(a[j]*b[i]);
            // using pq
            if(pq.size()<k){
                pq.push(temp);
                ans^=temp;
            }
            else if(temp<pq.top()){
                ans^=pq.top();
                ans^=temp;
                pq.pop();
                pq.push(temp);
            }
            else{break;}
        }
    }
    cout<<ans<<'\n';
    // debug
    // for(auto num:s){cout<<num<<' ';}
    return 0;
}

/*
2 3 6
1 2
3 4 5
*/
// 47

/*
10 10 15
3 4 5 6 7 9 10 19 19 29880
1 8 12 20 30 49 64 87 94 100000
*/
// 56
/*
13v 21v 31v 43v 57v 91v 111v 381 381 892844281
97v 112v 129v 148v 169v 217v 244 577 577 893053504
189v 208v 229 252 277 333 364 733 733 893173104
469 496 525 556 589 661 700 1141 1141 893412400
999 1036 1075 1116 1159 1251 1300 1831 1831 893711700
2557 2613 2671 2731 2793 2923 2991 3693 3693 894280921
4297 4368 4441 4516 4593 4753 4836 5673 5673 894730816
*/


/*
2 2 3
1000000000 1000000000
1000000000 1000000000
*/
// 3000000000000000000

/*
10 8 59
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
*/
// 3000000000000000000

/*
11 6 51
1 1 1 1 1 1 1 1 1 1 2
2 1 1 1 1 11
*/
// 7
