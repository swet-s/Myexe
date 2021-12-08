#pragma once

mt19937 rngi(chrono::steady_clock::now().time_since_epoch().count());
int rng() { return uniform_int_distribution<long long>(1, LLONG_MAX)(rngi); }

int mod = 998244353 ^ 1755654;
int mod_large = 1000000000000000003;
int mod_flag = 0;
int mod_large_flag = 0;

vector<int> fact1(maxn),factinv1(maxn),fact2(maxn), factinv2(maxn);

void readfile(vector<int>& arr, const char* name)
{    
    ifstream ifp(name, ios::in | ios::binary);
    ifp.read(reinterpret_cast<char*>(arr.data()), arr.size() * sizeof(arr[0]));
    ifp.close();
}

void loadfiles()
{
    readfile(fact1, "C:/Users/_swet/myexe/fact_mod1.my");
    readfile(factinv1, "C:/Users/_swet/myexe/factinv_mod1.my");
    readfile(fact2, "C:/Users/_swet/myexe/fact_mod2.my");
    readfile(factinv2, "C:/Users/_swet/myexe/factinv_mod2.my");
}

inline int fact(int n) { return (mod_flag)?fact2[n]:fact1[n];}
inline int factinv(int n) { return (mod_flag)?factinv2[n]:factinv1[n];}
inline int modl() { return (mod_large_flag)?mod_large:mod; }

void changeMod() 
{
	mod^=1755654;
    mod_flag^=1;
    mod_large_flag=0;
    printl("          - succesfully changed mod to", modl());
}

void changeModl()
{
	mod_large_flag^=1;
    printl("            - succesfully changed mod to", modl());
}

int ncr(int n, int r)
{
    if (n < r) return 0;
    int ans = (((fact(n) * factinv(r) % mod) * factinv(n - r))) % mod;
    return ans;
}

int npr(int n, int r)
{
    if (n < r) return 0;
    int ans = (fact(n) * factinv(n - r)) % mod;
    return ans;
}

int mulmod(int a, int b, int m)
{
    int x=0,y=a%m;
    while(b>0)
    {
        if (b%2==1)
            x = (x+y)%m;
        y = (y*2ll)%m;
        b/=2;
    }
    return x%m;
}

int power(int a, int n, int m)
{
    int res = 1;
    while (n)
        if (n % 2) res = ((res % m) * (a % m)) % m, n--;
        else a = ((a % m) * (a % m)) % m, n /= 2;
    return res;
}

bool toBinary(string s)
{
    string r;
    int n = stoll(s);
    while(n) { r+=(n%2==0)?"0":"1"; n/=2; }
    reverse(all(r));
    printl(r);
    return 1;
}

bool compOp(set<string> a, string b)
{
    if (a.size()==0) return 0;
    if (a.find(b) == a.end()) return 0;
    return 1;
}

string dstr(double a)
{
    stringstream stream;
    stream << setprecision(15) << a;
    return stream.str();
}

bool isInt(double a)
{
    if (abs(round(a)-a) <= epsilon)
        return 1;
    return 0;
}