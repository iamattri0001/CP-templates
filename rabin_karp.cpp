class RabinKarp {
    bool multi_hash;
    vector<long long> pre1, pre2, pow1, pow2;
    static const long long BASE1 = 31, BASE2 = 37;
    static const long long MOD1 = 1e9 + 7, MOD2 = 1e9 + 21;
    int n;

    static long long binpow(long long a, long long b, long long m) {
        a %= m;
        long long res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a % m;
            a = a * a % m;
            b >>= 1;
        }
        return res;
    }

public:
    RabinKarp(string& s, bool multi = 0) : n(s.size()), multi_hash(multi) {
        pre1.resize(n + 1);
        pow1.resize(n + 1, 1);

        if (multi_hash) {
            pre2.resize(n + 1);
            pow2.resize(n + 1, 1);
        }

        for (int i = 1; i <= n; i++) {
            pre1[i] = (pre1[i - 1] * BASE1 + (s[i - 1] - 'a' + 1)) % MOD1;
            pow1[i] = pow1[i - 1] * BASE1 % MOD1;
            if (multi_hash) {
                pre2[i] = (pre2[i - 1] * BASE2 + (s[i - 1] - 'a' + 1)) % MOD2;
                pow2[i] = pow2[i - 1] * BASE2 % MOD2;
            }
        }
    }

    static long long Hash1(string s) { // highest power on left
        long long h = 0;
        for (char ch : s) {
            h = (h * BASE1 % MOD1 + (ch - 'a' + 1)) % MOD1;
        }
        return h;
    }

    static long long Hash2(string s) { // highest power on left
        long long h = 0;
        for (char ch : s) {
            h = (h * BASE2 % MOD2 + (ch - 'a' + 1)) % MOD2;
        }
        return h;
    }

    long long get1(int i, int j) { // 0 based index
        return (pre1[j + 1] - pre1[i] * pow1[j - i + 1] % MOD1 + MOD1) % MOD1;
    }

    long long get2(int i, int j) { // 0 based index
        assert(multi_hash);
        return (pre2[j + 1] - pre2[i] * pow2[j - i + 1] % MOD2 + MOD2) % MOD2;
    }

    static vector<int> find_all_occ(string& text, string& pattern) {
        int n = text.size(), m = pattern.size();
        auto hp1 = Hash1(pattern);
        auto hp2 = Hash2(pattern);

        long long ht1 = 0, ht2 = 0;
        long long p1 = binpow(BASE1, m - 1, MOD1);
        long long p2 = binpow(BASE2, m - 1, MOD2);

        vector<int> match;

        for (int i = 0; i < n; i++) {
            if (i >= m) {
                ht1 = (ht1 - (text[i - m] - 'a' + 1) * p1 % MOD1 + MOD1) % MOD1;
                ht2 = (ht2 - (text[i - m] - 'a' + 1) * p2 % MOD2 + MOD2) % MOD2;
            }

            ht1 = (ht1 * BASE1 % MOD1 + (text[i] - 'a' + 1)) % MOD1;
            ht2 = (ht2 * BASE2 % MOD2 + (text[i] - 'a' + 1)) % MOD2;

            if (ht1 == hp1 && ht2 == hp2)
                match.push_back(i - m + 2);
        }

        return match;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LL long long
const int PRIME = 31;
const long long MOD = 1e9 + 7;

LL Hash(string &s){
    LL h = 0;
    for(int i=0; i<s.length(); i++){
        h = (h*31 + (s[i] - 'a' + 1)) % MOD;
    }
    return h;
}

bool match(string &s, string &t, int i){
    for(int k=0; k < t.length(); k++)
        if(s[i+k] != t[k])
            return 0;

    return 1;
}


vector<int> rabin_karp(string &s, string &t){
    vector<int> pos;
    int n = s.length(), m = t.length();
    if(n < m)
        return pos;

    LL ht = Hash(t);
    LL hs = 0, p = 1;
    for(int i=0; i<m; i++){
        if(i != 0)
            p = p * PRIME % MOD;
        hs = (hs*31 + (s[i] - 'a' + 1))%MOD;
    }

    if(hs == ht)
        pos.push_back(0);

    for(int i=m; i<n; i++){
        auto to_del = (s[i - m] - 'a' + 1) * p % MOD;
        auto to_add = (s[i] -'a' + 1);
        hs = ((hs - to_del + MOD) * PRIME + to_add) % MOD;
        if(hs == ht){
            pos.push_back(i-m+1);
        }
    } 

    return pos;
}


