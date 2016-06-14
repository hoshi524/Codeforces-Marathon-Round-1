#include <bits/stdc++.h>

using namespace std;

int const inf = 0xffff;
int const n = 5000;
int const k = 2000;
int const x =  100;

char buf[x][n+1];
int score[x];
double value[n];
mt19937 gen (12345);
uniform_int_distribution <> one_bit ('0', '1');
uniform_int_distribution <> rand5000(0, n);

void solve(int a) {
	int p = a - 1;
	value[score[p]] = buf[p][score[p]] == '0' ? -inf : inf;
	for(int i = 0; i < p; ++i) {
		int ms = min(score[i], score[p]), diff = 0;
		for(int j = 0; j < ms; ++j) {
			if(buf[i][j] != buf[p][j]) ++diff;
		}
		double v = (double) abs(score[i] - score[p]) / diff;
		for(int j = 0; j < ms; ++j) {
			if(buf[i][j] == buf[p][j] || abs(value[j]) + 1 >= inf) continue;
			if(((score[i] < score[p]) + (buf[i][j] == '0')) & 1) value[j] += v;
			else value[j] -= v;
		}
	}

	for(int i = 0; i < n; ++i) {
		buf[a][i] = value[i] > 0  ? '0' : '1';
	}
	if(a + 1 < x) {
		for(int i = 0; i < n; ++i) {
			int j = rand5000(gen);
			if(abs(value[j]) + 1 >= inf) continue;
			buf[a][j] = value[j] > 0 ? '1' : '0';
		}
	}
}

int main (void) {
	memset(value, 0, sizeof(value));
	for (int i = 0; i < x; ++i) {
		if(i == 0) {
			for (int p = 0; p < n; ++p) {
				buf[i][p] = one_bit(gen);
			}
		} else {
			solve(i);
		}
		buf[i][n] = '\0';
		printf("%s\n", buf[i]);
		fflush(stdout);
		scanf("%d", &score[i]);
		--score[i];
	}
	return 0;
}
