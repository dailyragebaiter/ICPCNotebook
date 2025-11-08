#include <bits/stdc++.h>
#include <thread>
using namespace std;

// ================= TEMPLATE MULTITHREAD =================
// Constants
const int MAX_THREADS = 4; // number of threads

// Worker function example: compute sum of a segment
void worker(const vector<int> &a, int l, int r, long long &res) {
    long long sum = 0;
    for (int i = l; i < r; i++)
        sum += a[i];
    res = sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input example
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    // ===== Multithread execution =====
    vector<thread> threads;
    vector<long long> results(MAX_THREADS, 0);

    int chunk = (n + MAX_THREADS - 1) / MAX_THREADS;
    for (int i = 0; i < MAX_THREADS; i++) {
        int l = i * chunk;
        int r = min(n, l + chunk);
        if (l < r)
            threads.emplace_back(worker, cref(a), l, r, ref(results[i]));
    }

    for (auto &t : threads) t.join(); // wait all threads

    // Merge results
    long long total = 0;
    for (auto x : results) total += x;

    cout << total << "\n";
    return 0;
}

/* ================= COMMAND CHEAT SHEET =================
#include <thread>        // include threading library
thread t(func,args...) // create thread running func with arguments
t.join()               // wait for thread t to finish
ref(x)                 // pass variable by reference to thread
cref(x)                // pass variable by const reference
t.detach()             // run thread independently
thread::hardware_concurrency() // get number of CPU threads
========================================================= */
