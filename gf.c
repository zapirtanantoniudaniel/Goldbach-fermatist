#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN (6)

typedef unsigned long u;

int pr(u p) {
	u k = 3;
	while (k <= p / k) {
                if ((p % k) == 0)
                        return 0;
                k += 2;
	}
        return 1;
}

u gbn(u n) {
        u p = 3;
        while (p <= n - p) {
                if (pr(p)) {
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
	time_t time0 = time(NULL);
        while (1) {
		if (pr(p + 2))
			p += 2;
		else
			p = gbn(n);
                if (p == 0)
                        exit(2);
                if ((n & 131071) == 0) {
                        fprintf(stdout, "%luk\n", n / 1024);
                        fflush(stdout);
			if (difftime(time(NULL), time0) >= 300.0)
				return 0;
                }
                n += 2;
        }
}

