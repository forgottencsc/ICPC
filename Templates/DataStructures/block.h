//  blocks
int bi[N], bl[M], br[M], bs, bc;
void block_init() {
    bs = sqrt(n); bc = 1; bl[1] = 1;
    for (int i = 1; i <= n; ++i) {
        if (i - bl[bc] == bs) {
            br[bc++] = i - 1;
            bl[bc] = i;
        }
        bi[i] = bc;
    }
    br[bc] = n;
}