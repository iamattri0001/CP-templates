#include <bits/stdc++.h>
using namespace std;


//general macros
#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define vb vector<bool>
#define VEC vector
#define pii pair<int, int> 
#define pll pair<ll, ll>
#define loop(i,a,b) for(int i=a; i<b; i++)
#define pb push_back
#define FF first
#define SS second
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()

//input and output
#define input(v,n)  loop(i,0,n)  cin>>v[i];
#define output(v,n) loop(i,0,n) cout<<v[i]<<" ";
#define nl cout<<"\n"
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define prt(a) cout<<a<<endl


void solve(){
    ll n;
    cin>>n;
    oset<int> os;
    for(int i=0; i<n; i++){
        int x;
        cin>>x;
        os.insert(x);
    }

    for(auto i: os)
        cout<<i<<" ";
    cout<<endl;

    cout<< os.order_of_key(5);
}

int32_t main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif  
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    t = 1;
    while(t--)
        solve();
    return 0;
}
