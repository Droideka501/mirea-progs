#include <cmath>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>


long long gcd(long long a, long long b)
{
    if(b == 0){
        return a;
    }
    return gcd(b, a%b);
}

long long scm(long long a, long long b)
{
    return a*b/gcd(a, b);
}

long long binPowMod(long long a, long long n, long long mod)
{
    long long res = 1;
    long long b = a%mod;
    while(n > 0){
        if(n & 1)
            res = (res * b) % mod;
        b = (b * b) % mod;
        n >>= 1;
    }
    return res%mod;
}

long long binPow(long long a, long long n)
{
	long long res = 1;
	while(n > 0){
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

long long phi(long long n)
{
    long long res = n;
    for(long long i = 2; i <= sqrt(n); i++){
        if(!(n % i)){
            while(!(n % i)){
                n /= i;
            }
            res -= res / i;
        }
    }
    if(n > 1){
        res = res - res / n;
    }
    if(res % 8 == 0){
        res /= 2;
    }
    return res;
}

long long combinationMod(long long n, long long k, long long mod)
{
    long long res = 1;
    for(long long i = k+1; i <= n; i++){
        res = (res * i) % mod;
        res = (res * binPowMod(i-k, mod-2, mod)) % mod;
    }
    return res%mod;
}

long long maxOrd(long long n)
{
    long long res = 1;
    std::vector <long long> divs;
    int count = 0;
    for(long long i = 2; i <= sqrt(n); i++){
        if(n % i == 0){
            divs.push_back(i);
            n /= i;
            while (n % i == 0){
                divs[count] *= i;
                n /= i;
            }
            count += 1;
        }
    }
    divs.push_back(n);
    
    for(int i = 0; i < divs.size(); i++){
        long long temp = phi(divs[i]);
        if(divs[i] % 2 == 0 && divs[i] > 2*2*2){
            temp /= 2;
        }
        res = scm(res, temp);
    }

    return res;
}

long long ordInField(long long a, long long p)
{
    long long maxord = maxOrd(p);
    for(int i = 1; i <= p; i++){
        if(maxord % i == 0){
            if(binPowMod(a, i, p) == 1){
                return i;
            }
        }
    }
}

void idempotents(long long p)
{
    bool checker = true;
    for(long long i = sqrt(p); i < p-1/2+1; i++){
        if((i * i)%p == i){
            std::cout << i << " ";
            checker = false;
        }
    }
    if(checker) std::cout << -1;
}

void DFS(int start, std::vector<std::vector <int>>& edges, std::vector<bool>& mark)
{
    std::stack<int> s;
    s.push(start);
    while (!s.empty())
    {
        int v = s.top();
        s.pop();
        for (int i = 0; i < edges[v].size(); ++i)
        {
            if (mark[edges[v][i]] == 0)
            {
                s.push(edges[v][i]);
                mark[edges[v][i]] = 1;
            }
        }
    }
}

void BFS(int start, std::vector<std::vector <int>>& edges, std::vector<bool>& mark, std::vector<int>& d)
{
    std::queue<int> q;
    q.push(start);
    d[start] = 0;
    mark[start] = 1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int i = 0; i < edges[v].size(); ++i)
        {
            if (mark[edges[v][i]] == 0)
            {
                d[edges[v][i]] = d[v] + 1;
                mark[edges[v][i]] = 1;
                q.push(edges[v][i]);
            }
        }
    }
}