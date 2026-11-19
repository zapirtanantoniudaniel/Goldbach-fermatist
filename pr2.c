#include <stdio.h>
#include <stdlib.h>

typedef unsigned u;

u mulm(u a, u b, u m) {
	if (b == 0)
		return 0;
	if (b == 1)
		return a % m;
	if (b & 1)
		return (mulm(a, b - 1, m) + a) % m;
	u w = mulm(a, b >> 1, m);
	return (w + w) % m;
}

u fact(u q, u p) {
	u f = 1L;
	for (u k = 0; k < q; k++) {
		u l = k + 1;
		f = mulm(f, l, p);
	}
	return f;
}

int pr(u p) {
	u f = fact(p - 1, p);
	return f + 1 == p;
}

int main(void) {
	for (u p = 2; p < 0xffff; p++) {
		int w = pr(p);
		if (w == 1) {
			printf("%u\n", p);
			fflush(stdout);
		}
	}
}

