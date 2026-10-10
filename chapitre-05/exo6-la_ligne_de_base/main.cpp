#include <algorithm>
#include <cstdio>
#include <map>
#include <string>

struct Glyphe {
    bool present;
    long long avance, x0, y0, x1, y1;
};

int main() {
    Glyphe table[256];
    for (int i = 0; i < 256; ++i) table[i].present = false;

    int g;
    if (std::scanf("%d", &g) != 1) return 0;
    char c[16];
    for (int i = 0; i < g; ++i) {
        Glyphe gl;
        std::scanf("%15s %lld %lld %lld %lld %lld", c, &gl.avance, &gl.x0, &gl.y0, &gl.x1, &gl.y1);
        gl.present = true;
        table[static_cast<unsigned char>(c[0])] = gl;
    }

    int k;
    std::scanf("%d", &k);
    std::map<std::string, long long> crenage;
    char paire[16];
    for (int i = 0; i < k; ++i) {
        long long v;
        std::scanf("%15s %lld", paire, &v);
        crenage[paire] = v;
    }

    char texte[1024];
    long long ox, oy;
    std::scanf("%1023s %lld %lld", texte, &ox, &oy);

    long long x = ox;
    bool dessine = false;
    long long minx = 0, miny = 0, maxx = 0, maxy = 0;
    int absents = 0;
    size_t len = std::string(texte).size();

    for (size_t i = 0; i < len; ++i) {
        unsigned char ch = static_cast<unsigned char>(texte[i]);
        if (!table[ch].present) {
            std::printf("%c ABSENT\n", texte[i]);
            ++absents;
            continue;
        }

        const Glyphe &gl = table[ch];
        std::printf("%c %lld\n", texte[i], x);

        if (gl.x1 > gl.x0 && gl.y1 > gl.y0) {
            long long rx0 = x + gl.x0, ry0 = oy + gl.y0;
            long long rx1 = x + gl.x1, ry1 = oy + gl.y1;
            if (!dessine) {
                minx = rx0; miny = ry0; maxx = rx1; maxy = ry1;
                dessine = true;
            } else {
                minx = std::min(minx, rx0);
                miny = std::min(miny, ry0);
                maxx = std::max(maxx, rx1);
                maxy = std::max(maxy, ry1);
            }
        }

        x += gl.avance;
        if (i + 1 < len) {
            std::string p;
            p += texte[i];
            p += texte[i + 1];
            std::map<std::string, long long>::const_iterator it = crenage.find(p);
            if (it != crenage.end()) x += it->second;
        }
    }

    std::printf("CURSEUR %lld\n", x);
    if (!dessine) {
        std::printf("BOITE AUCUNE\n");
        std::printf("MONTE 0\n");
        std::printf("DESCEND 0\n");
        std::printf("ECRAN RIEN\n");
    } else {
        long long monte = (miny < oy) ? (oy - miny) : 0;
        long long descend = (maxy > oy) ? (maxy - oy) : 0;
        const char *ecran = "VISIBLE";
        if (maxy <= 0) ecran = "HORS";
        else if (miny < 0) ecran = "COUPE";
        std::printf("BOITE %lld %lld %lld %lld\n", minx, miny, maxx, maxy);
        std::printf("MONTE %lld\n", monte);
        std::printf("DESCEND %lld\n", descend);
        std::printf("ECRAN %s\n", ecran);
    }
    std::printf("ABSENTS %d\n", absents);
    return 0;
}