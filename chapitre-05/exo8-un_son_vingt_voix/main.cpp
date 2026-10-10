#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    long long D, C;
    if (std::scanf("%lld %lld", &D, &C) != 2) return 0;
    int n;
    if (std::scanf("%d", &n) != 1) n = 0;

    std::vector<long long> t(n);
    for (int i = 0; i < n; ++i) std::scanf("%lld", &t[i]);

    long long voixMax = 0, retardMax = 0, coupes = 0;
    long long finChargement = 0;
    int debut = 0;

    for (int i = 0; i < n; ++i) {
        while (debut <= i && t[debut] + D <= t[i]) ++debut;
        long long voix = i - debut + 1;

        long long start = (i == 0) ? t[i] : std::max(t[i], finChargement);
        finChargement = start + C;
        long long retard = finChargement - t[i];

        bool coupe = (i + 1 < n) && (t[i + 1] < t[i] + D);

        std::printf("%lld %lld %lld %s\n", t[i], voix, retard, coupe ? "COUPE" : "ENTIER");

        voixMax = std::max(voixMax, voix);
        retardMax = std::max(retardMax, retard);
        if (coupe) ++coupes;
    }

    std::printf("VOIX_MAX %lld\n", voixMax);
    std::printf("RETARD_MAX %lld\n", retardMax);
    std::printf("COUPES %lld\n", coupes);
    return 0;
}