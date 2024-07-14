#include <bits/stdc++.h>
using namespace std;

class Montgomery {
    uint64_t n, r, s;

public:
    // Constructor initializes Montgomery multiplication
    Montgomery(uint64_t n) : n(n), r(n) {
        // Compute r for Montgomery reduction
        for (int i = 0; i < 5; i++) r *= 2 - n * r;
        s = ((UINT64_MAX) % n + 1) % n;
        s = (__uint128_t(s) * s) % n;
    }

    // Reduce method for Montgomery reduction
    uint64_t reduce(__uint128_t x) {
        uint64_t q = uint64_t(x) * (-r);
        __uint128_t m = __uint128_t(q) * n;
        uint64_t res = (x + m) >> 64;
        return (res < n ? res : res - n);
    }

    // Montgomery multiplication
    uint64_t multiply(uint64_t x, uint64_t y) {
        return reduce(__uint128_t(x) * y);
    }

    // Transform to Montgomery form
    uint64_t transform(uint64_t x) {
        return reduce(__uint128_t(x) * s);
    }
};

// Check if a is a composite number with given parameters
bool isComposite(uint64_t a, uint64_t d, uint64_t n, uint64_t s) {
    Montgomery m(n);
    uint64_t res = m.transform(1);
    uint64_t acc = m.transform(a);
    for (uint64_t i = d; i > 0; i >>= 1) {
        if (i & 1) res = m.multiply(res, acc);
        acc = m.multiply(acc, acc);
    }
    uint64_t pos = m.transform(n + 1);
    uint64_t neg = m.transform(n - 1);
    if (res == pos) return false;
    while (s--) {
        if (res == neg) return false;
        res = m.multiply(res, res);
    }
    return true;
}

// Check if n is a prime number
bool isPrime(uint64_t n) {
    if (n == 1) return false;
    vector<uint64_t> limit = {2046ULL, 1373652ULL, 25326000ULL, 3215031750ULL, 2152302898746ULL, 3474749660382ULL, 341550071728320ULL, 341550071728320ULL, 3825123056546413050ULL, 3825123056546413050ULL, 3825123056546413050ULL, UINT64_MAX};
    vector<uint64_t> bases = {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL};
    if (find(bases.begin(), bases.end(), n) != bases.end()) return true;
    for (int p : bases) if (n % p == 0) return false;
    uint64_t s = __builtin_ctzll(n - 1);
    uint64_t d = (n - 1) >> s;
    uint64_t p = lower_bound(limit.begin(), limit.end(), n) - limit.begin();
    for (int i = 0; i <= p; i++) if (isComposite(bases[i], d, n, s)) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        uint64_t n;
        cin >> n;
        cout << (isPrime(n) ? "Yes\n" : "No\n");
    }
    return 0;
}