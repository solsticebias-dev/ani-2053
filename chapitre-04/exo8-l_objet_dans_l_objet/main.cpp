#include <cstdio>
#include <string>
#include <map>

struct Obj {
    long long x, y, angle, scale, level;
};

int main() {
    int n;
    if (std::scanf("%d", &n) != 1) return 0;

    std::map<std::string, Obj> objs;
    long long profondeur = 0;
    char nom[64], parent[64];

    for (int i = 0; i < n; ++i) {
        long long tx, ty, angle, echelle;
        std::scanf("%63s %63s %lld %lld %lld %lld", nom, parent, &tx, &ty, &angle, &echelle);

        Obj o;
        if (std::string(parent) == "-") {
            o.x = tx;
            o.y = ty;
            o.angle = ((angle % 360) + 360) % 360;
            o.scale = echelle;
            o.level = 1;
        } else {
            const Obj &p = objs[parent];
            long long ax = tx * p.scale;
            long long ay = ty * p.scale;
            long long c = 0, s = 0;
            if (p.angle == 0)        { c = 1;  s = 0; }
            else if (p.angle == 90)  { c = 0;  s = 1; }
            else if (p.angle == 180) { c = -1; s = 0; }
            else                     { c = 0;  s = -1; }
            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;
            o.x = p.x + rx;
            o.y = p.y + ry;
            o.angle = (((p.angle + angle) % 360) + 360) % 360;
            o.scale = p.scale * echelle;
            o.level = p.level + 1;
        }

        objs[nom] = o;
        if (o.level > profondeur) profondeur = o.level;

        std::printf("%s %lld %lld %lld %lld\n", nom, o.x, o.y, o.angle, o.scale);
    }

    std::printf("PROFONDEUR %lld\n", profondeur);
    return 0;
}