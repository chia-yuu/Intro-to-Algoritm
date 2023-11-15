// long long?
#include<iostream>
#include<queue>
using namespace std;

int main(){
    priority_queue<long long> mx;     // max heap record 0 - k-1 element
    priority_queue<long long, vector<long long>, greater<long long> > mn;     // min heap record k - n element
    long long q, k, type, num;
    cin>>q>>k;
    while(q--){
        cin>>type;
        if(type==1){
            cin>>num;
            // printf("mx.size()=%d, mn.size()=%d\n", mx.size(), mn.size());
            if(mx.size()<k-1){
                mx.push(num);
            }
            else{
                if(!mx.empty() && num<mx.top()){
                    long long temp=mx.top();
                    mx.pop();
                    mx.push(num);
                    mn.push(temp);
                }
                else{
                    mn.push(num);
                }
            }
        }
        else if(type==2){
            if(mn.empty()){
                cout<<-1<<'\n';
            }
            else{
                cout<<mn.top()<<'\n';
                mn.pop();
            }
        }
    }
    return 0;
}

/*
15 2
2       -1
1 5     // 5,
2       -1
1 7     // 5, 7
2       7   // 5,
1 3     // 3, 5
1 1     // 1, 3 5
2       3   // 1, 5
1 9     //1, 5 9
1 12    // 1, 5 9 12
2       5   // 1, 9 12
2       9   // 1, 12
2       12  // 1,
2       -1
2       -1
*/
/*
-1
-1
7
3
5
9
12
-1
-1
*/

/*
7 1
1 1000000000
1 1000000000
2
2
2
1 1000000000
2
*/
/*
1000000000
1000000000
-1
1000000000
*/
