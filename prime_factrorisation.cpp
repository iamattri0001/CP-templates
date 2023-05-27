int SIZE = 1e6+5;
vector<int> fact(SIZE);

void build(){
    fact[1] = 1;
    for(int i=2; i*i<SIZE; i++){
        if(fact[i])
            continue;
        fact[i] = i;
        for(int j = i*i; j<SIZE; j += i)
            fact[j] = i;
    }
}


vector<int> getFact(int num){
    vector<int> pf;
    cout<<num<<endl;
    while(num > 1){
        if(fact[num] == 0)
            fact[num] = num;
        int f = fact[num];
        while(num%f == 0)
            num /= f;
        pf.push_back(f);
    }
    return pf;
}
