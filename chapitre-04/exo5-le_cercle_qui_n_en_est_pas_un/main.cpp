#include <cstdio>
#include <cmath>

int main() {
    const double pi = 3.141592653589793;
    int n;
    if (std::scanf("%d", &n) != 1) return 0;

    int visibles = 0;
    int refuses = 0;

    for (int i = 0; i < n; ++i) {
        long long r;
        int segs;
        std::scanf("%lld %d", &r, &segs);

        if (segs < 3) {
            std::printf("%lld %d REFUSE\n", r, segs);
            ++refuses;
            continue;
        }

        double g = (double)r * (1.0 - std::cos(pi / (double)segs));

        if (g == 0.0) {
            std::printf("%lld %d ecart JAMAIS\n", r, segs);
            continue;
        }

        long long ecart = (long long)std::floor(g * 1000.0);
        long long zoom = (long long)std::ceil(100.0 / g);

        const char* verdict = (zoom <= 100) ? "VISIBLE" : "INVISIBLE";
        if (zoom <= 100) ++visibles;

        std::printf("%lld %d %lld %lld %s\n", r, segs, ecart, zoom, verdict);
    }

    std::printf("VISIBLES %d\n", visibles);
    std::printf("REFUSES %d\n", refuses);
    return 0;
}