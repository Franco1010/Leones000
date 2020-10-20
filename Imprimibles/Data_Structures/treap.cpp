
struct treap{
  struct node{
    int x, y;
    node* left;
    node* right;
    int tot;
    lli sum;
    lli lazy;

    node(int x1){
      x = x1;
      y = rand() + (rand() << 15);
      left = right = NULL;
      tot = 1;
      sum = x;
      lazy = 0;
    }
  };
  
  int tot(node* t){
    return t ? t->tot: 0;
  }

  lli sum(node* t){
    return t ? t->sum: 0;
  }

  node* refresh(node* t){
    if( !t || !t->lazy ){
      return t;
    }
    swap(t->left, t->right);
    if( t->left ){
      t->left->lazy += t->lazy
    }
    if( t->right ){
      t-right->lazy += t->lazy;
    }
    t->lazy = 0;
    return t;
  }

  void print(node* t){
    if( t ){
     refresh(t);
     inorder(t->left);
     cout << t->x << '\n';
     inorder(t->right);
    }
  }

  node* calc(node* t){
    refresh(t->left);
    refresh(t->right);
    t->tot = tot(t->left) + tot(t->right) + 1;
    t->sum = sum(t->left) + sum(t->right) + t->x;
    return t;
  }

  pair<node*, node*> split(node* t, int z){ // >= z to right
    if( !t ){
      return {t, t};
    }
    refresh(t);
    if( t->x >= z ){
      auto p = split(t->left, z);
      t->left = t->s;
      return {p.f, calc(t)};
    }else{
      auto p = split(t->right, z);
      t->right = p.f;
      return {calc(t), p.s};
    }
  }
    
    pair<pt,pt> split(pt t, int v) { // >= v goes to the right
        if (!t) return {t,t};
        prop(t);
        if (t->val >= v) {
            auto p = split(t->c[0], v); t->c[0] = p.s;
            return {p.f, calc(t)};
        } else {
            auto p = split(t->c[1], v); t->c[1] = p.f;
            return {calc(t), p.s};
        }
    }
    
    pair<pt,pt> splitsz(pt t, int sz) { // leftmost sz nodes go to left
        if (!t) return {t,t};
        prop(t);
        if (getsz(t->c[0]) >= sz) {
            auto p = splitsz(t->c[0], sz); t->c[0] = p.s;
            return {p.f, calc(t)};
        } else {
            auto p = splitsz(t->c[1], sz-getsz(t->c[0])-1); t->c[1] = p.f;
            return {calc(t), p.s};
        }
    }
        
    pt merge(pt l, pt r) {
        if (!l || !r) return l ? l : r;
        prop(l), prop(r);
        pt t;
        if (l->pri > r->pri) l->c[1] = merge(l->c[1],r), t = l;
        else r->c[0] = merge(l,r->c[0]), t = r;
        return calc(t);
    }
    
    pt ins(pt x, int v) { // insert v
        auto a = split(x,v), b = split(a.s,v+1);
        return merge(a.f,merge(new tnode(v),b.s));
    }
    
    pt del(pt x, int v) { // delete v
        auto a = split(x,v), b = split(a.s,v+1);
        return merge(a.f,b.s);
    }
}