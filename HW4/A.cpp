#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

// binary search to find the leftmost point in the interval [left, right]
// delete the point and return true if we can find the point
// l, r is the index use to binary search
bool find_point(vector<long long>& point, long long left, long long right, long long l, long long r){
    // printf("l=%d, r=%d,  ", l, r);
    if(l>r){return false;}
    long long mid=(l+r)/2;
    // find the point (mid is the point), remove it and return true
    if(point[mid]==left){   // mid == left
        point.erase(point.begin()+mid);
        return true;
    }
    if(point[mid]>=left && (mid==0 || point[mid-1]<left)){   // mid is leftmost point
        if(point[mid]>right){return false;}
        point.erase(point.begin()+mid);
        return true;
    }
    
    // not found, keep searching
    if(point[mid]<left){
        return find_point(point, left, right, mid+1, r);
    }
    if(point[mid]>left){
        return find_point(point, left, right, l, mid-1);
    }
    return true;
}

int main(){
    int n_testcase;
    cin>>n_testcase;
    while(n_testcase--){
        // read input
        long long n;
        cin>>n;
        vector<long long> point;
        vector<pair<long, long> > interval(n);
        for(long long i=0;i<n;i++){
            long long p;
            cin>>p;
            point.push_back(p);
        }
        for(long long i=0;i<n;i++){
            long long l, r;
            cin>>l>>r;
            interval[i].first=r;
            interval[i].second=l;
        }

        sort(point.begin(), point.end());
        sort(interval.begin(), interval.end());

        // cout<<"point: ";for(int p:point){cout<<p<<' ';}cout<<endl;
        // cout<<"interval:\n";for(pair<int, int> p:interval){cout<<p.first<<' '<<p.second<<endl;}

        // solve
        // 找最早結束的區間，那個區間對應的點是在範圍內最左邊的點
        bool possible=true;
        for(long long i=0;i<n;i++){
            long long right=interval[i].first, left=interval[i].second;
            possible=find_point(point, left, right, 0, point.size()-1);
            if(!possible){break;}
        }

        // output result
        if(possible){cout<<"Yes\n";}
        else{cout<<"No\n";}

    }
    return 0;
}

/*
7
3
4 3 5
3 5
5 6
2 3

3
2 6 6
3 5
5 6
2 3

4
10 11 8 5
1 8
4 5
8 11
10 12

3
3 4 99
1 4
3 100
87 87

3
1 2 3
3 4
2 4
1 4

3
10 2 8
10 10
1 10
7 9

1
100
101 102
*/
