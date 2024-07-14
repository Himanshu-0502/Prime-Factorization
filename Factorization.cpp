#include <bits/stdc++.h>
using namespace std;

// Montgomery class for fast modular arithmetic
class Montgomery {
    uint64_t n, r, s;

public:
    // Constructor to initialize Montgomery multiplication
    Montgomery(uint64_t n) : n(n), r(n) {
        for (int i = 0; i < 5; i++) r *= 2 - n * r; // Calculate r for Montgomery reduction
        s = (UINT64_MAX % n + 1) % n;
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

// Compute GCD using Stein's algorithm
uint64_t stein(uint64_t x, uint64_t y) {
    if (x == y) return x;
    uint64_t a = y - x;
    uint64_t b = x - y;
    int n = __builtin_ctzll(b);
    uint64_t s = (x < y) ? a : b;
    uint64_t t = (x < y) ? x : y;
    return stein(s >> n, t);
}

// Fast GCD calculation
uint64_t fastGCD(uint64_t x, uint64_t y) {
    if (x == 0) return y;
    if (y == 0) return x;
    int n = __builtin_ctzll(x);
    int m = __builtin_ctzll(y);
    return (stein(x >> n, y >> m) << min(n, m));
}

// Function to generate a random number between a and b
uint64_t Number(uint64_t a, uint64_t b) {
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return a + rng() % (b - a + 1);
}

// Factorize a number using Pollard's Rho algorithm
uint64_t factor(uint64_t n) {
    vector<uint64_t> bases = {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL};
    for (int p : bases) if (n % p == 0) return p;
    Montgomery m(n);
    uint64_t N = 256;
    uint64_t one = m.transform(1);
    uint64_t ane = m.transform(n);
    uint64_t cnt = Number(1, n);
    retry:
    uint64_t x = m.transform(cnt);
    uint64_t c = m.transform(cnt);
    for (uint64_t i = 1;; i <<= 1) {
        uint64_t y = x + ane;
        for (uint64_t j = 1; j <= i; j++) {
            uint64_t q = one;
            for (uint64_t k = 1; k <= N; k++) {
                x = m.multiply(x, x) + c;
                q = m.multiply(q, y - x);
            }
            uint64_t g = fastGCD(n, q);
            if (g == 1) continue;
            if (g != n) return g;
            cnt++;
            goto retry;
        }
    }
}

// Recursively factorize a number
void factorize(uint64_t n, vector<uint64_t> &factors) {
    if (n == 1) return;
    if (isPrime(n)) { factors.push_back(n); return; }
    uint64_t f = factor(n);
    factorize(f, factors);
    factorize(n / f, factors);
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
        vector<uint64_t> factors;
        factorize(n, factors);
        sort(factors.begin(), factors.end());
        cout << factors.size() << " \n"[factors.empty()];
        for (int i = 0; i < factors.size(); i++) {
            cout << factors[i] << " \n"[i == factors.size() - 1];
        }
    }
    return 0;
}