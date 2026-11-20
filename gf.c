#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN (6)
#define SIZE (1077871 + 1)
#define EXPSIZE (30)
#define SSIZE (1UL << EXPSIZE)

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
bool sieve[SSIZE];

void inittab(void) {
	u ix = 0;
	u p = 2;
	tabpr[ix++] = p;
	while (p < (1ULL << 24)) {
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
		sieve[i] = true;
	if (page == 0) {
		sieve[0] = false;
		sieve[1] = false;
	}
	u p;
	u minq = page * SSIZE;
	u maxq = (page + 1) * SSIZE;
	for (p = 2; p <= (u) (sqrt((double) maxq)); p++)
	if (pr(p)) {
		u r;
		if (p * p >= minq)
			r = p * p;
		else r = (minq - 1) / p + 1;
		for (u s = r * p; s < maxq; s += p)
			sieve[s - page * SSIZE] = false;
	}
}

u gbn(u page) {
	setsieve(page);
        u n = page * SSIZE;
	while (n < (page + 1) * SSIZE) {
		u p = 3;
		while (p <= 65536) {
			if (small_pr(p)) {
				u q = n - p;
				if (q < page * SSIZE) {
					if (pr(q))
						goto label;
					}
				else if (sieve[q - page * SSIZE])
					goto label;
			}
			p += 2;
		}
		return 0;
		label:
		n += 2;
	}
        return 1;
}

int main(void) {
        u page = 512;
	inittab();
        while (page < (1UL << (48 - EXPSIZE))) {
		if (!gbn(page))
			exit(2);
		printf("%.17lf\n", log(log((double) ((page + 1) * SSIZE)) / log(2.0)) / log(2.0));
		fflush(stdout);
		if ((page & 7) == 0) {
			FILE *rec = fopen("record.txt", "w");
			fprintf(rec, "%luG\n", ((page + 1) * SSIZE) >> 30);
			fclose(rec);
		}
                page++;
        }
}

