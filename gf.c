#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN (6)
#define SIZE (43389 + 1)

typedef unsigned long u;

int small_pr(u p) {
	u k = 2;
	while (k <= p / k) {
                if ((p % k) == 0)
                        return 0;
                k++;
	}
        return 1;
}

u tabpr[SIZE];

void inittab(void) {
	u ix = 0;
	u p = 2;
	tabpr[ix++] = p;
	while (p < 524288) {
		p++;
		if (small_pr(p))
			tabpr[ix++] = p;
	}
	tabpr[ix++] = 0;
}

int pr(u p) {
	u ix = 1;
	u k;
	while (tabpr[ix]) {
		k = tabpr[ix];
		if (k > p / k)
			return 1;
		if ((p % k) == 0)
			return 0;
		ix++;
	}
	return 1;
}

u gbn(u n) {
        u p = 3;
        while (p <= n - p) {
                if (small_pr(p)) {
                        if (pr(n - p))
                                return p;
                }
		p += 2;
        }
        return 0;
}

int main(void) {
        u n = MIN;
	u p = 7;
	inittab();
        while (n > 0) {
		if (small_pr(p + 2))
			p += 2;
		else
			p = gbn(n);
                if (p == 0)
                        exit(2);
                if ((n & 131071) == 0) {
                        fprintf(stdout, "%luk\n", n >> 10);
                        fflush(stdout);
                }
                n += 2;
        }
}

