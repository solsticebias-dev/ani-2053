#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

struct Groupe {
    std::string nom;
    long long n, w, h;
};

int main() {
    long long P, L;
    if (std::scanf("%lld %lld", &P, &L) != 2) return 0;
    int g;
    if (std::scanf("%d", &g) != 1) g = 0;

    if (g <= 0) {
        std::printf("AUCUN\n");
        return 0;
    }

    std::vector<Groupe> groupes;
    char nom[128];
    for (int i = 0; i < g; ++i) {
        Groupe gr;
        std::scanf("%127s %lld %lld %lld", nom, &gr.n, &gr.w, &gr.h);
        gr.nom = nom;
        groupes.push_back(gr);
    }

    long long besoin = 0;
    for (size_t i = 0; i < groupes.size(); ++i) {
        besoin += groupes[i].n * (groupes[i].w + P) * (groupes[i].h + P);
    }

    long long W = (L > 0) ? L : 512;
    while (W * W < 2 * besoin && W < 4096) W *= 2;
    long long H = W;

    for (int essai = 1; essai <= 8; ++essai) {
        long long x = P, y = P, e = 0;
        bool ok = true;
        std::vector<long long> fx(groupes.size()), fy(groupes.size());
        std::vector<long long> lx(groupes.size()), ly(groupes.size());

        for (size_t gi = 0; gi < groupes.size() && ok; ++gi) {
            for (long long k = 0; k < groupes[gi].n; ++k) {
                long long rw = groupes[gi].w + P;
                long long rh = groupes[gi].h + P;

                if (x + rw > W - P) {
                    x = P;
                    y = y + e + P;
                    e = 0;
                    if (x + rw > W - P) { ok = false; break; }
                }
                if (y + rh > H - P) { ok = false; break; }

                if (k == 0) { fx[gi] = x; fy[gi] = y; }
                lx[gi] = x;
                ly[gi] = y;

                x += rw;
                e = std::max(e, rh);
            }
        }

        if (ok) {
            long long occupe = 0;
            for (size_t i = 0; i < groupes.size(); ++i) {
                occupe += groupes[i].n * groupes[i].w * groupes[i].h;
            }
            long long perdu = (W * H - occupe) * 100 / (W * H);

            std::printf("ESSAIS %d\n", essai);
            std::printf("TEXTURE %lld %lld\n", W, H);
            for (size_t i = 0; i < groupes.size(); ++i) {
                std::printf("%s %lld %lld %lld %lld\n", groupes[i].nom.c_str(), fx[i], fy[i], lx[i], ly[i]);
            }
            std::printf("OCCUPE %lld\n", occupe);
            std::printf("PERDU %lld\n", perdu);
            return 0;
        }

        if (W == H) W *= 2;
        else H = W;
    }

    std::printf("ESSAIS 8\n");
    std::printf("ECHEC\n");
    return 0;
}