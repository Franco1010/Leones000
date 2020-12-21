struct Bipartite_Matching {
  vvc<int> graph;
  vi dist, match, used;
  vector<bool> vv;

  Bipartite_Matching(int n, int m) {
    graph.resize(n);
    match.assign(m, -1);
    used.assign(n, -1);
  }

  void add(int u, int v) { graph[u].push_back(v);}

  void bfs() {
    dist.assign(graph.size(), -1);
    queue< int > que;
    for(int i = 0; i < graph.size(); i++) {
      if(used[i] == -1) {
        que.emplace(i);
        dist[i] = 0;
      }
    }

    while(!que.empty()) {
      int a = que.front();
      que.pop();
      for(auto &b : graph[a]) {
        int c = match[b];
        if(c >= 0 && dist[c] == -1) {
          dist[c] = dist[a] + 1;
          que.emplace(c);
        }
      }
    }
  }

  bool dfs(int a) {
    vv[a] = true;
    for(auto &b : graph[a]) {
      int c = match[b];
      if(c < 0 || (!vv[c] && dist[c] == dist[a] + 1 && dfs(c))) {
        match[b] = a;
        used[a] = b;
        return (true);
      }
    }
    return (false);
  }

  int bipartite_matching() {
    int ret = 0;
    while(true) {
      bfs();
      vv.assign(graph.size(), false);
      int flow = 0;
      for(int i = 0; i < graph.size(); i++) {
        if(used[i] == -1 && dfs(i)) ++flow;
      }
      if(flow == 0) return (ret);
      ret += flow;
    }
  }
};
