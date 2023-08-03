#define LL long long
 
long long binpow(long long a, long long b, LL MOD) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
 
LL modINV(LL x, LL mod) {
    return binpow(x,  mod-2, mod);
}
 
vector<int> prefixHash(string &s, LL prime, LL MOD){
    int n = s.length();
    vector<int> pre(n+1);
    LL p = 1;
 
    for(int i=1; i<=n; i++){
        pre[i] = (pre[i-1] + (s[i-1]-'a' + 1) * p) % MOD;
        p = p * prime % MOD;
    }
    return pre;
}


//0-based indexing
int getSubstrinHash(vector<int> &pre, LL prime, LL mod, int i, int j){
    return (pre[j+1] - pre[i] + mod) * modINV(binpow(prime, i, mod), mod) % mod;
}
