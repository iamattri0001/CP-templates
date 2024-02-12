//KMP_find_all(text, pattern) -> return startng indices of all patterns matches in text (0 based)

void build_lps(string &s, vector<int> &lps) {
    int len = 0, n = s.size();
    for(int i = 1; i < n;) {
        if(s[i] == s[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len != 0) {
                len = lps[len - 1];
            } else {
                lps[len] = 0;
                i++;
            }
        }
    }
}

vector<int> KMP_find_all(string &text, string &pattern) {
    int n = text.size(), m = pattern.size();
    
    vector<int> lps(m);
    build_lps(pattern, lps);

    vector<int> pos;

    for(int i = 0, j = 0; i < n;) {
        if(text[i] == pattern[j]) {
            i++, j++;
        } else {
            if(j == 0)
                i++;
            else
                j = lps[j - 1];
        }

        if(j == m) {
            pos.push_back(i - j);
            j = lps[j - 1];
        }
    }

    return pos;
}
