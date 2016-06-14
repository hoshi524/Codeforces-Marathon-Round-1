#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

mt19937 gen (12345);
uniform_int_distribution <> one_bit ('0', '1');
uniform_int_distribution <> rand5000(0, 5000);

int const inf = 0xffff;
int const n = 5000;
int const k = 2000;
int const x =  100;
char buf[x][n+1];
int score[x];

void solve(int a) {
	int value[n];
	memset(value, 0, sizeof(value));

	for(int i = 0; i < a; ++i) {
		for(int j = i + 1; j < a; ++j) {
			if(score[i] == score[j]) continue;
			int ms = min(score[i], score[j]);
			for(int z = 0; z < ms; ++z) {
				if(buf[i][z] == buf[j][z] || abs(value[z]) == inf) continue;
				if(((score[i] < score[j]) + (buf[i][z] == '0')) & 1) ++value[z];
				else --value[z];
			}
		}
		value[score[i]] = buf[i][score[i]] == '0' ? -inf : inf;
	}
	for(int i = 0; i < n; ++i) {
		buf[a][i] = value[i] > 0  ? '0' : '1';
	}
	if(a + 1 < x) {
		for(int i = 0; i < n; ++i) {
			int j = rand5000(gen);
			if(abs(value[j]) == inf) continue;
			buf[a][j] = value[j] > 0 ? '1' : '0';
		}
	}
}

int main (void) {
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
