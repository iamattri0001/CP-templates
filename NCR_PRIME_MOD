#define ll long long

int mod = 1e9 + 7;
ll *fact;

ll binpow(ll a, ll b){
    ll ans = 1;
    while(b){
        if(b&1)
            ans = ans * a % mod;
        a = a*a % mod;
        b >>= 1;
    }

    return ans;
}

ll ncr(ll n, ll r){
        if(r == n)
            return 1;
        if(r > n)
            return 0;

        ll num = fact[n];
        ll den = fact[r] * fact[n-r] % mod;
        return num * binpow(den, mod-2) % mod;
}

//call this function to build the factorial array
void calcFacts(ll upto){
    fact = new ll[upto+1];
    fact[0] = 1;
    for(ll i=1; i<=upto; i++)
        fact[i] = fact[i-1] * i % mod;
}
