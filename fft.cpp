#include<bits/stdc++.h>
#define endl '\n'

using namespace std;
typedef long long ll;

void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

const double Pi = acos(-1);

struct complex_number
{
    double a, b; /// a + b * i

    complex_number(double _a = 0, double _b = 0)
    {
        a = _a;
        b = _b;
    }

    complex_number operator + (const complex_number &C) const
    {
        return complex_number(a + C.a, b + C.b);
    }

    complex_number operator - (const complex_number &C) const
    {
        return complex_number(a - C.a, b - C.b);
    }

    complex_number operator * (const complex_number &C) const
    {
        return complex_number(a * C.a - b * C.b, a * C.b + C.a * b);
    }

    complex_number operator / (const ll &d) const
    {
        return complex_number(a / (double)(d), b / (double)(d));
    }
};

void dft(vector < complex_number > &a, bool invert)
{
    int sz = a.size();
    if (sz == 1)
        return;

    vector < complex_number > a0, a1;
    for (int i = 0; i < sz; i ++)
    {
        if (i % 2 == 0)
            a0.push_back(a[i]);
        else
            a1.push_back(a[i]);
    }

    dft(a0, invert);
    dft(a1, invert);

    double ang = 2.0 * Pi / (double)(sz);
    if (invert)
        ang = - ang;
    complex_number wn(cos(ang), sin(ang));
    complex_number w(1, 0);
    for (int i = 0; 2 * i < sz; i ++)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + sz / 2] = a0[i] - w * a1[i];
        w = w * wn;
    }



}

vector < ll > multiply(vector < ll > a, vector < ll > b)
{
    int n = 1;
    while(n < a.size() + b.size())
        n = n * 2;

    while(a.size() < n)
        a.push_back(0);
    while(b.size() < n)
        b.push_back(0);

    vector < complex_number > fa(n), fb(n);
    for (int i = 0; i < n; i ++)
    {
        fa[i] = complex_number(a[i], 0);
        fb[i] = complex_number(b[i], 0);
    }

    dft(fa, 0);
    dft(fb, 0);

    vector < complex_number > res(n);
    for (int i = 0; i < n; i ++)
        res[i] = fa[i] * fb[i];

    //for (int i = 0; i < n; i ++)
      //  cout << round(a[i].a) << " ";
    //cout << endl;
    dft(res, 1);
    for (int i = 0; i < n; i ++)
        res[i] = res[i] / n;

    vector < ll > ans(n);
    for (int i = 0; i < n; i ++)
        ans[i] = round(res[i].a);

    return ans;
}

void solve()
{
     vector < ll > a, b;
     int n;
     cin >> n;
     for (int i = 0; i <= n; i ++)
     {
         int x;
         cin >> x;
         a.push_back(x);
     }
     for (int i = 0; i <= n; i++)
     {
         int x;
         cin >> x;
         b.push_back(x);
     }

    vector < ll > r = multiply(a, b);
    while(r.size() > 2 * n + 1)
        r.pop_back();
    for (int i = 0; i < r.size(); i ++)
        cout << r[i] << " ";
    cout << endl;
}

int main()
{
    speed();
    int t;
    cin >> t;
    while(t --)
        solve();

    return 0;
}
