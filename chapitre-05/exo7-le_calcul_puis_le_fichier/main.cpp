#include <cstdio>

int main() {
    long long S;
    if (std::scanf("%lld", &S) != 1) return 0;
    int n;
    if (std::scanf("%d", &n) != 1) n = 0;

    long long totalMemoire = 0;
    long long flux = 0, refuses = 0;
    char nom[128];

    for (int i = 0; i < n; ++i) {
        long long freq, canaux, bits, duree, fichier;
        std::scanf("%127s %lld %lld %lld %lld %lld", nom, &freq, &canaux, &bits, &duree, &fichier);

        if (bits != 8 && bits != 16 && bits != 24 && bits != 32) {
            std::printf("%s REFUSE\n", nom);
            ++refuses;
            continue;
        }

        long long brut = freq * canaux * (bits / 8) * duree / 1000;
        long long pourcent = fichier * 100 / brut;

        if (brut > S) {
            std::printf("%s %lld %lld FLUX\n", nom, brut, pourcent);
            ++flux;
        } else {
            std::printf("%s %lld %lld MEMOIRE\n", nom, brut, pourcent);
            totalMemoire += brut;
        }
    }

    std::printf("MEMOIRE %lld\n", totalMemoire);
    std::printf("FLUX %lld\n", flux);
    std::printf("REFUSES %lld\n", refuses);
    return 0;
}