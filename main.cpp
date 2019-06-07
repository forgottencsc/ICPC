#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const unsigned long long lim = (1ll << 32) - 1;

char cmd[N];
unsigned long long a[N], b[N];
unsigned long long sum, c[N], cur;

int main (void) {
	unsigned long long n;
	scanf("%llu", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", cmd);
		if (cmd[0] == 'a') a[i] = 1;
		else if (cmd[0] == 'f') a[i] = 2;
		else a[i] = 3;
		if (a[i] == 2) scanf("%llu", &b[i]);
		b[i] = min(lim + 1, b[i]);
	}
	stack<unsigned long long> v;
	v.push(1);
	unsigned long long sum = 0;
	for (int i = 1; i <= n; i++) {
		v.top() = min(v.top(), lim + 1);
		if (a[i] == 1) {
			if (v.top() == lim + 1) {
				puts("OVERFLOW!!!");
				return 0;
			}
			sum += v.top();
			if (sum > lim) {
				puts("OVERFLOW!!!");
				return 0;
			}
		} else if (a[i] == 2) {
			if (v.top() == lim + 1 || b[i] == lim + 1 || v.top() * b[i] > lim) v.push(lim + 1);
			else {
				unsigned long long vv = v.top();
				v.push(vv * b[i]);
			}
		} else {
			v.pop();
		}
	}
	printf("%llu\n", sum);
}