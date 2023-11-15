// `vector<TreeNode> &tree` call by reference, if call by value will TLE
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct TreeNode{
    int left;
    int right;
    vector<int> val;
}TreeNode;

int lchild(int x){
    return x*2;
}
int rchild(int x){
    return x*2+1;
}
void build_segmentTree(vector<int>& v, vector<TreeNode>& tree, int l, int r, int x){
    tree[x].left=l, tree[x].right=r;
    if(l==r){
        tree[x].val={v[l]};
        return;
    }
    int mid=(l+r)/2;
    build_segmentTree(v, tree, l, mid, lchild(x));
    build_segmentTree(v, tree, mid+1, r, rchild(x));
    vector<int> temp;
    if(r+1-l>12){
        merge(tree[lchild(x)].val.begin(), tree[lchild(x)].val.begin()+5, tree[rchild(x)].val.begin(), tree[rchild(x)].val.begin()+5, back_inserter(temp));
        while(temp.size()>5){temp.pop_back();}
    }
    else{
        merge(tree[lchild(x)].val.begin(), tree[lchild(x)].val.end(), tree[rchild(x)].val.begin(), tree[rchild(x)].val.end(), back_inserter(temp));
        while(temp.size()>5){temp.pop_back();}
    }
    tree[x].val=temp;
}
void update(vector<TreeNode>& tree, int cur, int idx, int k){
    if(tree[cur].left==idx && tree[cur].right==idx){
        tree[cur].val={k};
        return;
    }
    int mid=(tree[cur].left+tree[cur].right)/2;
    if(idx<=mid){
        update(tree, lchild(cur), idx, k);
    }
    else{
        update(tree, rchild(cur), idx, k);
    }
    vector<int> temp;
    int l=tree[cur].left, r=tree[cur].right;
    if(r+1-l>12){
        merge(tree[lchild(cur)].val.begin(), tree[lchild(cur)].val.begin()+5, tree[rchild(cur)].val.begin(), tree[rchild(cur)].val.begin()+5, back_inserter(temp));
        while(temp.size()>5){temp.pop_back();}
    }
    else{
        merge(tree[lchild(cur)].val.begin(), tree[lchild(cur)].val.end(), tree[rchild(cur)].val.begin(), tree[rchild(cur)].val.end(), back_inserter(temp));
        while(temp.size()>5){temp.pop_back();}
    }
    tree[cur].val=temp;
}
vector<int> query(vector<TreeNode>& tree, int l, int r, int cur){
    if(tree[cur].left>=l && tree[cur].right<=r){
        return tree[cur].val;
    }
    int mid=(tree[cur].left+tree[cur].right)/2;
    // printf("left: %d, right: %d, l= %d, r= %d, mid: %d\n", tree[cur].left, tree[cur].right, l, r, mid);
    if(r<=mid){
        // cout<<"r<=mid\n";
        /*vector<int> ret=query(tree, l, r, lchild(cur));
        cout<<"in update r<=mid, return vector= ";
        for(int n:ret){cout<<n<<' ';}cout<<endl;
        return ret;*/
        return query(tree, l, r, lchild(cur));
    }
    else if(l>mid){
        // cout<<"l>mid\n";
        /*vector<int> ret=query(tree, l, r, rchild(cur));
        cout<<"in update l>mid, return vector= ";
        for(int n:ret){cout<<n<<' ';}cout<<endl;
        return ret;*/
        return query(tree, l, r, rchild(cur));
    }
    else{
        // cout<<"else\n";
        vector<int> lans, rans, ret;
        lans=query(tree, l, mid, lchild(cur));
        rans=query(tree, mid+1, r, rchild(cur));
        merge(lans.begin(), lans.end(), rans.begin(), rans.end(), back_inserter(ret));
        // debug
        /*cout<<"in update else, return vector= ";
        for(int n:ret){cout<<n<<' ';}cout<<endl;
        cout<<"lans= ";
        for(int n:lans){cout<<n<<' ';}cout<<endl;
        cout<<"rans= ";
        for(int n:rans){cout<<n<<' ';}cout<<endl;*/
        return ret;
    }
}

int main(){
    int n, q;
    cin>>n>>q;
    vector<int> v(n,0);
    vector<TreeNode> tree(4*n);
    for(int i=0;i<n;i++){cin>>v[i];}
    build_segmentTree(v, tree, 0, n-1, 1);  // 一開始x=1，如果從0開始沒辦法找到left child
        // debug : print segment tree
        /*cout<<"segment tree :\n";
        for(int i=0;i<tree.size();i++){
            printf("l: %d, r: %d, val: ", tree[i].left, tree[i].right);
            for(int n:tree[i].val){cout<<n<<' ';}cout<<endl;
        }*/
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int idx, val;
            cin>>idx>>val;
            idx--;
            update(tree, 1, idx, val);
        }
        else{
            int l, r, k;
            cin>>l>>r>>k;
            l--, r--, k--;
            vector<int> ans=query(tree, l, r, 1);
            // cout<<"ans: ";for(int i:ans){cout<<i<<' ';}cout<<endl;
            cout<<ans[k]<<'\n';
        }
    }
    return 0;
}

/*
5 4
3 2 1 5 4
2 2 4 1
2 2 4 3 
1 3 3
2 2 4 1
*/
/*
1 5 2
*/

/*
6 7
3 6 10 3 5 8
2 1 6 5
2 2 5 3
1 3 1
2 3 6 4
1 6 4
2 4 6 2
2 2 2 1
*/
/*
8 6 8 4 6
*/
