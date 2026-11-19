#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN (6)
#define SIZE (43390 + 1)
#define SSIZE (1UL << 20)

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
u sieve[SSIZE];

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
	if (ix != SIZE)
		exit(4);
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

void setsieve(u page) {
	for (u i = 0; i < SSIZE; i++)
		sieve[i] = 1;
	u p;
	u minq = page * SSIZE;
	u maxq = (page + 1) * SSIZE;
	for (p = 2; p <= (maxq - 1) / p; p++)
	if (pr(p)) {
		u r;
		if (p * p >= minq)
			r = p * p;
		else r = (minq - 1) / p + 1;
		for (u s = r; s < maxq; s += p)
			sieve[s] = 0;
	}
}

u gbn(u page) {
        u n = page * SSIZE;
	while (n < (page + 1) * SSIZE) {
		u p = 3;
		while (p <= n - p) {
			if (small_pr(p)) {
				u q = n - p;
				if (q < page * SSIZE) {
					if (pr(q))
						return 1;
					}
				else if (sieve[q - page * SSIZE])
					return 1;
			}
			p += 2;
		}
	}
        return 0;
}

int main(void) {
        u page = 1;
	u p = 7;
	inittab();
        while (page < 0x1000) {
		setsieve(page);
		if (!gbn(page))
			exit(2);
		fprintf(stdout, "%luM\n", page + 1);
		fflush(stdout);
                page++;
        }
}

