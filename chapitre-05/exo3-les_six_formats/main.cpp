#include <cstdio>
#include <cstring>
#include <string>

struct Format {
    const char *nom;
    long long bpp;
    bool couleur, transparence, flottant;
};

static const Format FORMATS[6] = {
    {"GRAY8", 1, false, false, false},
    {"GRAY_A16", 2, false, true, false},
    {"RGB24", 3, true, false, false},
    {"RGBA32", 4, true, true, false},
    {"RGB96F", 12, true, false, true},
    {"RGBA128F", 16, true, true, true},
};

static const Format *trouver(const char *nom) {
    for (int i = 0; i < 6; ++i) {
        if (std::strcmp(FORMATS[i].nom, nom) == 0) return &FORMATS[i];
    }
    return nullptr;
}

int main() {
    long long w, h;
    if (std::scanf("%lld %lld", &w, &h) != 2) return 0;
    int n;
    if (std::scanf("%d", &n) != 1) n = 0;

    long long total = 0;
    int sansPerte = 0, refuses = 0;
    char a[64], b[64];

    for (int i = 0; i < n; ++i) {
        std::scanf("%63s %63s", a, b);
        const Format *src = trouver(a);
        const Format *dst = trouver(b);

        if (src == nullptr || dst == nullptr) {
            std::printf("%s %s REFUSE\n", a, b);
            ++refuses;
            continue;
        }

        long long sb = w * h * src->bpp;
        long long tb = w * h * dst->bpp;

        std::string pertes;
        if (src->transparence && !dst->transparence) pertes += "TRANSPARENCE";
        if (src->couleur && !dst->couleur) {
            if (!pertes.empty()) pertes += "+";
            pertes += "COULEUR";
        }
        if (src->flottant && !dst->flottant) {
            if (!pertes.empty()) pertes += "+";
            pertes += "ETENDUE";
        }
        if (pertes.empty()) {
            pertes = "AUCUNE";
            ++sansPerte;
        }

        total += tb;
        std::printf("%s %s %lld %lld %s\n", a, b, sb, tb, pertes.c_str());
    }

    std::printf("TOTAL %lld\n", total);
    std::printf("SANS_PERTE %d\n", sansPerte);
    std::printf("REFUSES %d\n", refuses);
    return 0;
}