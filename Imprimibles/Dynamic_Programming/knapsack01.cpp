void knapsack01(){
  Forn(i, n){ // cant elementos
    // Rof(j, size(dp) - 1, v[i].snd, -1){ // Se tiene un unico elemento
    For(j, v[i].snd, size(dp) - 1, 1){ // Infinita cantidad de un mismo elemento
      dp[j] = min(dp[j], dp[j - v[i].snd] + v[i].fst); // min, max
    }
  }
}
