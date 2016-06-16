#include <bits/stdc++.h>

using namespace std;

int const inf = 0xffff;
int const n = 5000;
int const k = 2000;
int const x =  100;

char buf[x][n+1];
int score[x];
int value[n];
mt19937 gen (12345);
uniform_int_distribution <> one_bit ('0', '1');

void solve(int a) {
	int p = a - 1;
	value[score[p]] = buf[p][score[p]] == '0' ? -inf : inf;
	for(int i = 0; i < p; ++i) {
		int ms = min(score[i], score[p]), diff = 0;
		for(int j = 0; j < ms; ++j) {
			if(buf[i][j] != buf[p][j]) ++diff;
		}
		int v = abs(score[i] - score[p]) * k / diff;
		for(int j = 0; j < ms; ++j) {
			if(buf[i][j] == buf[p][j] || abs(value[j]) == inf) continue;
			if(((score[i] < score[p]) + (buf[i][j] == '0')) & 1) value[j] += v;
			else value[j] -= v;
		}
	}

	for(int i = 0; i < n; ++i) {
		buf[a][i] = value[i] > 0  ? '0' : '1';
	}
	if(a + 1 < x) {
		uniform_int_distribution <> randp(0, score[p]);
		bool u[n];
		memset(u, false, sizeof(u));
		for(int i = 0; i < k; ) {
			int j = randp(gen);
			if(abs(value[j]) == inf || u[j]) continue;
			++i;
			u[j] = true;
			buf[a][j] = value[j] > 0 ? '1' : '0';
		}
	}
}

void solve2(int a) {
	int p = a - 1;
	int vi[n],c0[n],c1[n];
	memset(vi, 0, sizeof(vi));
	memset(c0, 0, sizeof(c0));
	memset(c1, 0, sizeof(c1));
	for(int i = 0; i < a; ++i){
		vi[score[i]] = buf[i][score[i]] == '0' ? -inf : inf;
	}
	for(int i = 0; i < n; ++i){
		if(vi[i] == 0){
			int s0 = 0, s1 = 0;
			for(int j = 0; j < a; ++j){
				if(score[j] < i)continue;
				if(buf[j][i] == '0'){
					s0 += score[j];
					++c0[i];
				}else{
					s1 += score[j];
					++c1[i];
				}
			}
			if(c0[i] + c1[i] > 0){
				vi[i] += s0 * c1[i] - s1 * c0[i];
				vi[i] /= c0[i] + c1[i];
			}
		}
		buf[a][i] = vi[i] > 0  ? '0' : '1';
	}
	if(a + 1 < x) {
		uniform_int_distribution <> randp(0, score[p]);
		bool u[n];
		memset(u, false, sizeof(u));
		for(int i = 0; i < k; ) {
			int j = randp(gen);
			if(abs(vi[j]) == inf || u[j]) continue;
			++i;
			u[j] = true;
			buf[a][j] = vi[j] > 0 ? '1' : '0';
			// buf[a][j] = c0[j] > c1[j] ? '1' : '0';
		}
	}
}

void solve3(int a) {
	int p = a - 1;
	value[score[p]] = buf[p][score[p]] == '0' ? -inf : inf;
	for(int i = 0; i < p; ++i) {
		int ms = min(score[i], score[p]), diff = 0;
		for(int j = 0; j < ms; ++j) {
			if(buf[i][j] != buf[p][j]) ++diff;
		}
		int v = abs(score[i] - score[p]) * k / diff;
		for(int j = 0; j < ms; ++j) {
			if(buf[i][j] == buf[p][j] || abs(value[j]) == inf) continue;
			if(((score[i] < score[p]) + (buf[i][j] == '0')) & 1) value[j] += v;
			else value[j] -= v;
		}
	}
	
	int vi[n];
	memset(vi, 0, sizeof(vi));
	for(int i = 0; i < a; ++i){
		vi[score[i]] = buf[i][score[i]] == '0' ? -inf : inf;
	}
	for(int i = 0; i < n; ++i){
		if(vi[i] == 0){
			int s0 = 0, c0 = 0, s1 = 0, c1 = 0;
			for(int j = 0; j < a; ++j){
				if(buf[j][i] == '0'){
					s0 += score[j];
					++c0;
				}else{
					s1 += score[j];
					++c1;
				}
			}
			vi[i] += s0 * c1 - s1 * c0;
			vi[i] /= a;
		}
	}

	for(int i = 0; i < n; ++i) {
		buf[a][i] = value[i] * 10 + vi[i] * 10 > 0  ? '0' : '1';
	}
	if(a + 1 < x) {
		uniform_int_distribution <> randp(0, score[p]);
		bool u[n];
		memset(u, false, sizeof(u));
		for(int i = 0; i < k; ) {
			int j = randp(gen);
			if(abs(value[j]) == inf || u[j]) continue;
			++i;
			u[j] = true;
			buf[a][j] = buf[a][j] == '0' ? '1' : '0';
		}
	}
}

void test() {
	char correct[n];
	int sum = 0, testcase = 100;
	for(int z = 0; z < testcase; ++z) {
		for(int i = 0; i < n; ++i) {
			correct[i] = one_bit(gen);
		}
		memset(value, 0, sizeof(value));
		int maxscore = 0;
		for (int i = 0; i < x; ++i) {
			if(i == 0) {
				for (int p = 0; p < n; ++p) {
					buf[i][p] = one_bit(gen);
				}
			} else {
				solve2(i);
			}
			buf[i][n] = '\0';
			score[i] = 0;
			for(int w = 0; score[i] < n && w < k; ++score[i]) {
				if(correct[score[i]] != buf[i][score[i]]) ++w;
			}
			--score[i];
			if(maxscore < score[i]) maxscore = score[i];
		}
		sum += maxscore;
		if(false){
			double cs = 0, cc = 0;
			double bs = 0, bc = 0;
			for(int i = 0; i < n; ++i){
				int ok = correct[i] == buf[x-1][i];
				// cout<<ok<<" "<<value[i]<<endl;
				if(ok){
					if(abs(value[i]) + 1 < inf){
						cs += abs(value[i]);
						++cc;
					}
				}else{
					bs += abs(value[i]);
					++bc;
				}
			}
			cout<<(cs/cc)<<endl;
			cout<<(bs/bc)<<endl;
		}
	}
	cout<<"avg : "<<((double) sum / testcase)<<endl;
}

void submit() {
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
		int z = scanf("%d", &score[i]);
		--score[i];
	}
}

int main(void) {
	// submit();
	test();
	return 0;
}
