#include <cstdio>
#include <algorithm>

static long long arrondi(long long a, long long b) {
    return (2 * a + b) / (2 * b);
}

struct Rep {
    const char *nom;
    long long vx, vy, vw, vh, mw, mh;
};

int main() {
    long long RW, RH, AW, AH, W, H;
    if (std::scanf("%lld %lld %lld %lld %lld %lld", &RW, &RH, &AW, &AH, &W, &H) != 6) return 0;

    bool hasRef = (RW > 0 && RH > 0);
    Rep r[6];

    r[0] = {"FOLLOW_WINDOW", 0, 0, W, H, W, H};

    if (!hasRef) {
        r[1] = {"STRETCH", 0, 0, W, H, W, H};
        r[2] = {"FIT_LETTERBOX", 0, 0, W, H, W, H};
        r[3] = {"INTEGER_SCALE", 0, 0, W, H, W, H};
        r[4] = {"FIT_CROP", 0, 0, W, H, W, H};
    } else {
        r[1] = {"STRETCH", 0, 0, W, H, RW, RH};

        long long vw, vh;
        if (W * RH <= H * RW) {
            vw = W;
            vh = arrondi(RH * W, RW);
        } else {
            vh = H;
            vw = arrondi(RW * H, RH);
        }
        r[2] = {"FIT_LETTERBOX", (W - vw) / 2, (H - vh) / 2, vw, vh, RW, RH};

        if (W >= RW && H >= RH) {
            long long k = std::min(W / RW, H / RH);
            long long iw = RW * k, ih = RH * k;
            r[3] = {"INTEGER_SCALE", (W - iw) / 2, (H - ih) / 2, iw, ih, RW, RH};
        } else {
            r[3] = r[2];
            r[3].nom = "INTEGER_SCALE";
        }

        long long mw, mh;
        if (W * RH > H * RW) {
            mw = RW;
            mh = arrondi(RW * H, W);
        } else {
            mw = arrondi(RH * W, H);
            mh = RH;
        }
        r[4] = {"FIT_CROP", 0, 0, W, H, mw, mh};
    }

    r[5] = {"MANUAL", 0, 0, AW, AH, AW, AH};

    int bandes = 0;
    for (int i = 0; i < 6; ++i) {
        std::printf("%s %lld %lld %lld %lld %lld %lld\n", r[i].nom,
                    r[i].vx, r[i].vy, r[i].vw, r[i].vh, r[i].mw, r[i].mh);
        if (r[i].vw < W || r[i].vh < H) ++bandes;
    }

    bool deformation = hasRef && (W * RH != H * RW);
    std::printf("BANDES %d\n", bandes);
    std::printf("DEFORMATION %s\n", deformation ? "OUI" : "NON");
    return 0;
}