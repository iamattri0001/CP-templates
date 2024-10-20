class Manacher {
    vector<int> len;
public:
    Manacher(const string& t) {
        string s = "@";
        for (char ch : t) {
            s += ch;
            s += "@";
        }
        int n = s.size();
        s = "+" + s + "-";
        len.resize(n + 2);
        int low = 1, high = 1;
        for (int i = 1; i <= n; i++) {
            len[i] = max(0, min(high - i, len[low + high - i]));
            while (s[i - len[i]] == s[i + len[i]])  len[i]++;
            if (i + len[i] > high)  low = i - len[i],   high = i + len[i];
        }
    }

    // centered at index i
    int getOddLen(int i) { return len[2 * (i + 1)] - 1; }

    // centered between i - 1 and i
    int getEvenLen(int i) { return len[2 * i + 1] - 1; }

    // starting idx of odd len palin, center at i
    int getOddIndex(int i) { return i - (getOddLen(i) - 1) / 2; }

    // starting idx of even len palin, center at i and i - 1
    int getEvenIndex(int i) { return i - getEvenLen(i) / 2; }

    // verify if s[i...j] is palin
    bool check(int i, int j) {
        if (j < i)  return false;
        if (i == j) return true;

        int sz = j - i + 1;
        int mid = i + sz / 2;

        if (sz & 1) return getOddLen(mid) >= sz;
        else        return getEvenLen(mid) >= sz;
    }
};
