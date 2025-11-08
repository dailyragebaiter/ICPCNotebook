#include <bits/stdc++.h>
using namespace std;

signed main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	while (true) { // for (int t = 1; t <= ...; t++)
		system("gen.exe");
		system("bai1.exe");
		system("bai1_bf.exe");
		if (system("fc bai1.out bai12.out") == 1) {
			cout << "Difference is found";
			break;
		}
	}

	return 0;
}
