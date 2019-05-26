#include <bits/stdc++.h>
using namespace std;


int main(void) {
    double MSS = 16;
    double ssthresh = 128;
    double cwnd = MSS;
    for (int rtt = 0; rtt != 20; ++rtt) {
        double ncwnd = cwnd;
        for (double t = 0; abs(t - cwnd) > 1e-6; t += MSS) {
            if (ncwnd < ssthresh)
                ncwnd += MSS;
            else
                ncwnd += MSS * (1. * MSS / cwnd);
        }

        cout << ncwnd - cwnd << endl;
        cwnd = ncwnd;
    }
    return 0;
}