// Hàm tính Phi Euler
ll euler_phi (ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; ++ i) {
        if (n % i == 0) {
            res = res / i * (i - 1); // Áp dụng công thức (1 - 1/p_i)
            while (n % i == 0) {
                n /= i; // Chia n cho tất cả các lũy thừa của i
            }
        }
    }
    // Nếu sau vòng lặp, n vẫn còn > 1, nghĩa là n là một số nguyên tố lớn
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}

void solve () {
    ll n;
    cin >> n;
    cout << euler_phi (n) << "\n";
    return;
}
