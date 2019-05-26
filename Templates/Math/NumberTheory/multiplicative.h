#include <bits/stdc++.h>
using namespace std;

#define W 1000001
bool ip[W]; vector<ll> ps;
void gp() {
	ps.reserve(W * 1.3 / log(W));
	memset(ip, 1, sizeof(ip)); ip[1] = 0;
	for (int i = 2; i != W; ++i) {
		if (ip[i]) ps.push_back(i);
		for (int p : ps) {
			if (i * p >= W) break;
			ip[i * p] = 0;
			if (i % p == 0) break;
		}
	}
}

ll eulerphi(ll n) {
	ll res = 1;
	for (ll p : ps) {
		if (p * p > n) break;
		if (n % p) continue;
		n /= p; res *= (p - 1);
		while (n % p == 0) { n /= p; res *= p; }
	}
	if (n != 1) res *= n - 1;
	return res;
}

ll moebiusmu(ll n) {
	ll res = 1;
	for (ll p : ps) {
		if (p * p > n) break;
		if (n % p) continue;
		n /= p; res = -res;
		if (n % p == 0) return 0;
	}
	if (n != 1) res = -res;
	return res;
}

//	Euler Sieve

//	Power of minimum prime factor pk[i];
//	(1): 1;	(2): 1; (3): pk[i] + 1;

//	px[i]=p^pk[i];
//	(1): i;	(2): p;	(3): px[i] * p;

//	MoebiusMu mu[i];
//	(1): -1; (2): -mu[i]; (3): 0;

//	EulerPhi ph[i];
//	(1): i - 1;	(2): ph[i] * (p - 1);
//	(3): ph[i] * p;

//	DivisorCount dc[i];
//	(1): 2;		(2): dc[i] * 2;
//	(3): dc[i] / (pk[i] + 1) * (pk[i] + 2);

//	DivisorSum ds[i];
//	(1): i + 1;	(2): ds[i] * (p + 1);
//	(3): ds[i / px[i]] * (qpow(p, pk[i] + 2) - 1) / (p - 1)

//	Sum of coprime numbers; sigma[i] = i * ph[i] / 2;
#define W 1000001
bool ip[W]; vector<ll> ps;
void eulersieve() {
	ps.reserve(N * 1.2 / log(N));
	memset(ip, 1, sizeof(ip)); ip[1] = 0;
	//  f[1] =
	for (int i = 2; i != N; ++i) {
		if (ip[i]) {
			ps.push_back(i);
			//  f[i] = (1)
		}
		for (ll p : ps) {
			if (i * p >= N) break;
			ip[i * p] = 0;
			if (i % p) {
				// f[i * p] = (2)
			}
			else {
				//	f[i * p] = (3)
				break;
			}
		}
	}
}