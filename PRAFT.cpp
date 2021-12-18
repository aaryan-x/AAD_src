#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ff first
#define L LLONG_MAX
#define ss second
#define deb(a, b, c) cout << #a << " = " << (a) << ", " << #b << " = " << (b) << ", " << #c << " = " << (c) << endl;

typedef long long int ll;
typedef pair<ll, ll> node;
typedef string str;

ll adj[5005][5005];
ll pri[5005][5005];
vector<vector<ll>> path;
vector<ll> flow;
ll maxflow = 0;

bool ucs(ll par[], ll s, ll t, ll v)
{
	bool vis[v + 2] = {0};
	priority_queue<node, vector<node>, greater<node>> q;
	ll val[v + 2];
	for (ll i = 0; i <= v; i++)
	{
		val[i] = L;
	}
	val[s] = 0;
	q.push(mp(0, s));
	while (!q.empty())
	{
		node u = q.top();
		q.pop();
		// deb(u.ff,u.ss,q.size());
		if (!vis[u.ss])
		{
			for (ll i = 0; i <= v; i++)
			{
				if (vis[i] == 0 && adj[u.ss][i] > 0 && (u.ff + pri[u.ss][i] < val[i]))
				{
					par[i] = u.ss;
					val[i] = u.ff + pri[u.ss][i];
					q.push(mp(val[i], i));
				}
			}
			vis[u.ss] = 1;
		}
	}
	return (val[t] != L);
}

void addpath(ll par[], ll s, ll t)
{
	ll v = t;
	vector<ll> pa;
	while (v != s)
	{
		pa.pb(v);
		v = par[v];
	}
	pa.pb(s);
	path.pb(pa);
}

void bottle_neck(ll par[], ll s, ll t)
{
	ll c = L;
	ll v = t;

	while (v != s)
	{
		ll u = par[v];
		c = min(c, adj[u][v]);
		v = u;
	}
	v = t;
	while (v != s)
	{
		ll u = par[v];
		adj[u][v] -= c;
		adj[v][u] += c;
		v = u;
	}
	flow.pb(c);
	maxflow += c;
}

void praft(ll s, ll t, ll v)
{
	ll par[v + 2];
	while (ucs(par, s, t, v))
	{
		bottle_neck(par, s, t);
		addpath(par, s, t);
	}
}

int main()
{
	ll n, m, i, a, b, w, s, t, p, j;
	cout << "\nEnter the number of vertices: ";
	cin >> n;
	cout << "\nEnter the number of edges: ";
	cin >> m;
	cout << "\nFor the next " << m << " lines, enter the edge and edge weights and priorities:";
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> w >> p;
		adj[a][b] = w;
		pri[a][b] = p;
	}
	cout << "\nEnter the source: ";
	cin >> s;
	cout << "\nEnter the sink: ";
	cin >> t;
	praft(s, t, n);

	cout << "\n\nThe total maximum flow value is = " << maxflow << ".\n";
    
	// If the maxflow > 0
	for (i = 0; i < path.size(); i++)
	{
		cout << "PATH-" << i + 1 << " have flow value = " << flow[i] << ", and the path is: ";
		ll aa = path[i].size();
		for (j = aa - 1; j >= 0; j--)
		{
			if (j)
				cout << path[i][j] << "->";
			else
				cout << path[i][j] << "\n";
		}
	}
}