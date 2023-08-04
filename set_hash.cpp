const vector<long long> PRIMES = {(long long)1e9+7, (long long)1e9+9, (long long)1e9+21, (long long)1e9+33, (long long)1e9+87};

const long long K = 8234245; //random number (big)
const long long H = 67; //random number (small)
const long long MOD = PRIMES[1]; //change it to some other big prime



long long binpow(long long a, long long b, long long MOD) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}


long long set_hash(vector<int> &v, long long H, long long K, long long MOD){
    long long h = 0;
    for(auto &i: v)
        h = (h + binpow(i + K, H, MOD)) % MOD;

    return h;
}
