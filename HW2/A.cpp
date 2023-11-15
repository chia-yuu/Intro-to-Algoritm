// AC
#include<iostream>
#include<numeric>
using namespace std;

long long int GCD(int a, int b){
    int temp;
    while(b!=0){
        temp=a;
        a=b;
        b=temp%b;
    }
    return a;
}

long long int LCM(int a, int b){
    int gcd;
    gcd=GCD(a, b);
    return (long long)a*(long long)b/gcd;
}

int main(){
    int n_testcase;
    cin>>n_testcase;
    while(n_testcase--){
        int a, b, k;
        cin>>a>>b>>k;
        long long int l=1, r=999999999999999999, m, ans=0, count=0;
        long long int lcm=LCM(a, b);
        while(l<=r){
            m=(abs(l)+abs(r))/2;
            count=abs(m/a)+abs(m/b)-abs(2*(m/lcm));
            // printf("l= %lld, r= %lld, m= %lld, count= %lld\n", l, r, m, count);
            if(count==k || count<k+3 && count>=k){
                // printf("m= %lld, count= %lld, ", m, count);
                if(((m%a==0 && m%b!=0) || (m%a!=0 && m%b==0)) && count==k){ans=m;}
                else{
                    ans=m;
                    long long int aa=ans/a, bb=ans/b;       // aa=3 bb=2 count=3, aa=2 bb=1 count=3, ans=4 aa=1 bb=1 count=2, 
                    // cout<<ans;
                    ans=a*aa;
                    count++;////////////
                    // printf(", ans= %lld, count= %lld\n", ans, count);
                    while(count>0){
                        /*if((ans%a==0 && ans%b!=0) || (ans%a!=0 && ans%b==0)){
                            if(count>k){count--;}
                            else{break;}
                        }
                        ans--;*/
                        if((ans%a==0 && ans%b!=0) || (ans%a!=0 && ans%b==0)){
                            if(count==k){break;}
                        }
                        if(a*aa>b*bb && a*aa%b!=0){
                            ans=a*aa;
                            aa--, count--;
                        }
                        else if(b*bb>a*aa && b*bb%a!=0){
                            ans=b*bb;
                            bb--, count--;
                        }
                        else{
                            aa--, bb--;
                        }

                    }
                }
                break;
            }
            else if(count>k){
                r=m;
            }
            else{
                l=m;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}

/*
894018597
1000000000
*/

// k+ak/b-2k/b

/*
12
1 2 1
1 2 2
2 3 1
2 3 2 x
2 3 3
2 3 4
3 6 1
3 6 2
37 61 100
42 91 123
9999 10000 1
9999 10000 2 x
*/

/*
1
3
2
3
4
8
3
9
2368
3948
9999
10000
*/

/*
12
2 3 1
2 3 4
2 3 100
1 42 1000000000
5 10 3
9 12 9
9 12 10
9 12 11
5 7 19
759208302 883019287 883271940
999999999 1000000000 1000000000
500000000 1000000000 1000000000
                     
*/

/*
2
8
200
1024390243
25
60
63
81
63
360572190497677566
500000000000000000
999999999500000000
*/
