
// rabin_karp(string&, string&): vector<int> -> all starting indices of pattern matches (0-based indexing)


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
            if(match(s, t, i-m+1)) //usualy not required
                pos.push_back(i-m+1);
        }
    } 

    return pos;
}


