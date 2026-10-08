#include <cstdio>
#include <algorithm>

int main() {
    int n;
    if (std::scanf("%d", &n) != 1) return 0;

    int refuses = 0;
    char nom[64];

    for (int i = 0; i < n; ++i) {
        long long w, h, px, py, ox, oy, sx, sy, angle;
        std::scanf("%63s %lld %lld %lld %lld %lld %lld %lld %lld %lld",
                   nom, &w, &h, &px, &py, &ox, &oy, &sx, &sy, &angle);

        if (angle % 90 != 0) {
            std::printf("%s ANGLE REFUSE\n", nom);
            ++refuses;
            continue;
        }

        long long a = ((angle % 360) + 360) % 360;
        long long c = 0, s = 0;
        if (a == 0)        { c = 1;  s = 0; }
        else if (a == 90)  { c = 0;  s = 1; }
        else if (a == 180) { c = -1; s = 0; }
        else               { c = 0;  s = -1; }

        long long lx[4] = {0, w, w, 0};
        long long ly[4] = {0, 0, h, h};
        long long wx[4], wy[4];

        for (int k = 0; k < 4; ++k) {
            long long ax = (lx[k] - ox) * sx;
            long long ay = (ly[k] - oy) * sy;
            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;
            wx[k] = px + rx;
            wy[k] = py + ry;
        }

        long long minx = wx[0], maxx = wx[0], miny = wy[0], maxy = wy[0];
        for (int k = 1; k < 4; ++k) {
            minx = std::min(minx, wx[k]);
            maxx = std::max(maxx, wx[k]);
            miny = std::min(miny, wy[k]);
            maxy = std::max(maxy, wy[k]);
        }

        std::printf("%s COINS %lld %lld %lld %lld %lld %lld %lld %lld\n", nom,
                    wx[0], wy[0], wx[1], wy[1], wx[2], wy[2], wx[3], wy[3]);
        std::printf("%s BOITE %lld %lld %lld %lld\n", nom, minx, miny, maxx, maxy);
    }

    std::printf("REFUSES %d\n", refuses);
    return 0;
}