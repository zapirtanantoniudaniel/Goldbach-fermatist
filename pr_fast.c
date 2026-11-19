#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned u;

int pr(u p) {
	if (p == 2)
		return 1;
	u k = 2;
	while (k <= p / k) {
                if ((p % k) == 0)
                        return 0;
                k++;
	}
        return 1;
}

int main(void) {
        u p = 2;
        while (p < 0xffffff) {
		if (pr(p)) {
			printf("%u\n", p);
			fflush(stdout);
		}
		p++;
        }
}

