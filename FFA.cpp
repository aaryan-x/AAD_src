#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define deb(a, b, c) cout << #a << " = " << (a) << ", " << #b << " = " << (b) << ", " << #c << " = " << (c) << endl;

typedef long long int ll;
typedef string str;

ll adj[5005][5005];

bool bfs(ll par[], ll s, ll t, ll v)
{
	bool vis[v + 2] = {0};
	queue<ll> q;
	q.push(s);
	vis[s] = 1;
	while (!q.empty())
	{
		ll u = q.front();
		q.pop();
		for (ll i = 0; i <= v; i++)
		{
			if (vis[i] == 0 && adj[u][i] > 0)
			{
				par[i] = u;
				q.push(i);
				vis[i] = 1;
			}
		}
	}
	return vis[t];
}

ll bottle_neck(ll par[], ll s, ll t)
{
	ll c = LLONG_MAX;
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
	return c;
}

ll ffa(ll s, ll t, ll v)
{
	ll par[v + 2];
	ll flow = 0;
	while (bfs(par, s, t, v))
	{
		flow += bottle_neck(par, s, t);
	}
	return flow;
}

int main()
{
	ll n, m, i, a, b, w, s, t;
	cout << "\nEnter the number of vertices: ";
	cin >> n;
	cout << "\nEnter the number of edges: ";
	cin >> m;
	cout << "\nFor the next " << m << " lines, enter the edge and edge weights:";
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> w;
		adj[a][b] = w;
	}
	cout << "\nEnter the source: ";
	cin >> s;
	cout << "\nEnter the sink: ";
	cin >> t;
	cout << "\n\nThe maximum value of flow from vertex " << s << " to vertex " << t << " = " << ffa(s, t, n) << "\n\n";
}