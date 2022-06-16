void build_segtree(int *arr,int *tree,int start,int end,int tree_node){
  if(start==end){
    tree[tree_node]=arr[start];
    return;
  }
  int mid=(start+end)/2;
  build_segtree(arr,tree,start,mid,2*tree_node);
  build_segtree(arr,tree,mid+1,end,2*tree_node+1);
  tree[tree_node]=tree[2*tree_node]+tree[2*tree_node+1];
}
void update_lazypropagation(int *tree,int *lazy,int low,int high,int left,int right,int tree_node,int inc){
  if(low > high){
    return;
  }
  if(lazy[tree_node]!=0){
    tree[tree_node]+=(high-low+1)*lazy[tree_node];
    if(low!=high){
      lazy[2*tree_node]+=lazy[tree_node];
      lazy[2*tree_node+1]+=lazy[tree_node];
    }
    lazy[tree_node]=0;
  }

  if(low > high || right < low){
    return;
  }
  if(left <= low && high <= right){
      tree[tree_node] += (high-low+1)*inc;
      if(low!=high){
        lazy[2*tree_node]+=inc;
        lazy[2*tree_node+1]+=inc;
      }
      return;
  }
  int mid=(low+high)/2;
  update_lazypropagation(tree,lazy,low,mid,left,right,2*tree_node,inc);
  update_lazypropagation(tree,lazy,mid+1,high,left,right,2*tree_node+1,inc);
  tree[tree_node]=tree[2*tree_node]+tree[2*tree_node+1];
}
int rangequery_lazypropagation(int *tree,int *lazy,int start,int end,int left,int right,int tree_node){
  if(start > end){
    return 0;
  }
  if(lazy[tree_node]!=0){
    tree[tree_node] += (end-start+1)*lazy[tree_node];
    if(start!=end){
      lazy[2*tree_node]+=lazy[tree_node];
      lazy[2*tree_node+1]+=lazy[tree_node];
    }
    lazy[tree_node]=0;
  }
   if(start > right || end < left){
    return 0;
  }
  if(start>=left && end<=right){
    return tree[tree_node];
  }
  int mid=(start+end)/2;
  int p2=rangequery_lazypropagation(tree,lazy,start,mid,left,right,2*tree_node);
  int p1=rangequery_lazypropagation(tree,lazy,mid+1,end,left,right,2*tree_node+1);
  return p1+p2;
}
