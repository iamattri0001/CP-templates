class StringMatch {
    bool multi_hash;
    vector<int> pre1, pre2, mi1, mi2;
    static const long long BASE1 = 31, BASE2 = 37;
    static const long long MOD1 = 1e9 + 7, MOD2 = 1e9 + 21;
    int n;

    static long long binpow(long long x, long long y, long long m) {
        long long ans = 1;
        x %= m;
        while(y) {
            if(y & 1)
                ans = ans * x % m;
            y >>= 1;
            x = x * x % m;
        }
        return ans;
    }

public:
    StringMatch(string &s, bool multi = 0) : n(s.size()), multi_hash(multi) {
        pre1.resize(n + 1);
        mi1.resize(n);

        if(multi_hash) {
            pre2.resize(n + 1);
            mi2.resize(n);
        }

        long long p1 = 1, p2 = 1;
        for(int i = 1; i <= n; i++) {
            pre1[i] = (pre1[i - 1] + (s[i - 1] - 'a' + 1) * p1 % MOD1) % MOD1;
            mi1[i - 1] = binpow(p1, MOD1 - 2,MOD1);
            p1 = p1 * BASE1 % MOD1;

            if(multi_hash) {
                pre2[i] = (pre2[i - 1] + (s[i - 1] - 'a' + 1) * p2 % MOD2) % MOD2;
                mi2[i - 1] = binpow(p2, MOD2 - 2, MOD2);
                p2 = p2 * BASE2 % MOD2;
            }
        }
    }

    long long Hash1(string s) { // highest power on left
        long long p = 1, h = 0;
        for(char ch: s) {
            h = (h + (ch - 'a' + 1) * p % MOD1) % MOD1;
            p = p * BASE1 % MOD1;
        }
        return h;
    }

    long long Hash2(string s) { // highest power on left
        long long p = 1, h = 0;
        for(char ch: s) {
            h = (h + (ch - 'a' + 1) * p % MOD2) % MOD2;
            p = p * BASE2 % MOD2;
        }
        return h;
    }

    static long long Hash1_r(string s) { // highest power on right
        long long h = 0;
        for(char ch: s) {
            h = (h * BASE1 % MOD1 + (ch - 'a' + 1)) % MOD1;
        }
        return h;
    }

    static long long Hash2_r(string s) { // highest power on right
        long long h = 0;
        for(char ch: s) {
            h = (h * BASE2 % MOD2 + (ch - 'a' + 1)) % MOD2;
        }
        return h;;
    }

    long long get1(int i, int j) {
        return (pre1[j + 1] - pre1[i] + MOD1) % MOD1 * mi1[i] % MOD1;
    }


    long long get2(int i, int j) {
        assert(multi_hash);
        return (pre2[j + 1] - pre2[i] + MOD2) % MOD2 * mi2[i] % MOD2;
    }

    static vector<int> find_all_occ(string &text, string &pattern) {
        int n = text.size(), m = pattern.size();
        auto hp1 = Hash1_r(pattern);
        auto hp2 = Hash2_r(pattern);

        long long ht1 = 0, ht2 = 0;
        long long p1 = binpow(BASE1, m - 1, MOD1);
        long long p2 = binpow(BASE2, m - 1, MOD2);

        vector<int> match;

        for(int i = 0; i < n; i++) {
            if(i >= m) {
                ht1 = (ht1 - (text[i - m] - 'a' + 1) * p1 % MOD1 + MOD1) % MOD1;
                ht2 = (ht2 - (text[i - m] - 'a' + 1) * p2 % MOD2 + MOD2) % MOD2;
            }

            ht1 = (ht1 * BASE1 % MOD1 + (text[i] - 'a' + 1)) % MOD1;
            ht2 = (ht2 * BASE2 % MOD2 + (text[i] - 'a' + 1)) % MOD2;

            if(ht1 == hp1 && ht2 == hp2)
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


