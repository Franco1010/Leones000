struct min_queue: deque<ii> { // O(N)
  void add(ii cur){ // add a element to the right {v, pos}
    while( !empty() && back().f >= cur.f ){
      pop_back();
    }
    push_back(cur);
  }

  void rem(int i){// remove all less than i, O(K)
    while( front().s < s ){
      pop_front();
    }
  }

  lli qmin(){ // min[l, r], O(K)
    return front().f;
  }
} mnqu;
