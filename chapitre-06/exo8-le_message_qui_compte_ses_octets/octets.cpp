#include "NKNetwork/NKNetwork.h"
#include <cmath>
#include <cstdio>

using namespace nkentseu;

struct Etat {
    bool vivant;
    uint8 numero;
    float32 x, y, angle;
    int32 sante;
};

static uint32 ecrirePlein(const Etat &e, uint8 *buf, uint32 taille, uint32 &bits, bool &debord) {
    NkBitWriter w(buf, taille);
    w.WriteU8(e.vivant ? 1 : 0);
    w.WriteU8(e.numero);
    w.WriteF32(e.x);
    w.WriteF32(e.y);
    w.WriteF32(e.angle);
    w.WriteI32(e.sante);
    bits = w.BitsWritten();
    debord = w.IsOverflowed();
    return w.BytesWritten();
}

static uint32 ecrireQuantifie(const Etat &e, uint8 *buf, uint32 taille, uint32 &bits, bool &debord) {
    NkBitWriter w(buf, taille);
    w.WriteBool(e.vivant);
    w.WriteU8(e.numero);
    w.WriteF32Q(e.x, -500.f, 500.f, 0.01f);
    w.WriteF32Q(e.y, -500.f, 500.f, 0.01f);
    w.WriteF32Q(e.angle, 0.f, 360.f, 0.5f);
    w.WriteInt(e.sante, 0, 100);
    bits = w.BitsWritten();
    debord = w.IsOverflowed();
    return w.BytesWritten();
}

static Etat lirePlein(const uint8 *buf, uint32 taille) {
    NkBitReader r(buf, taille);
    Etat e;
    e.vivant = (r.ReadU8() != 0);
    e.numero = r.ReadU8();
    e.x = r.ReadF32();
    e.y = r.ReadF32();
    e.angle = r.ReadF32();
    e.sante = r.ReadI32();
    return e;
}

static Etat lireQuantifie(const uint8 *buf, uint32 taille) {
    NkBitReader r(buf, taille);
    Etat e;
    e.vivant = r.ReadBool();
    e.numero = r.ReadU8();
    e.x = r.ReadF32Q(-500.f, 500.f, 0.01f);
    e.y = r.ReadF32Q(-500.f, 500.f, 0.01f);
    e.angle = r.ReadF32Q(0.f, 360.f, 0.5f);
    e.sante = r.ReadInt(0, 100);
    return e;
}

static void afficher(const char *titre, const Etat &e) {
    std::printf("  %-10s vivant=%d numero=%u x=%.4f y=%.4f angle=%.4f sante=%d\n",
                titre, e.vivant ? 1 : 0, static_cast<unsigned>(e.numero),
                static_cast<double>(e.x), static_cast<double>(e.y),
                static_cast<double>(e.angle), static_cast<int>(e.sante));
}

int main() {
    Etat envoye;
    envoye.vivant = true;
    envoye.numero = 42;
    envoye.x = 123.456f;
    envoye.y = -321.987f;
    envoye.angle = 271.3f;
    envoye.sante = 73;

    uint8 bufPlein[64] = {};
    uint8 bufQuant[64] = {};
    uint32 bitsPlein = 0, bitsQuant = 0;
    bool debordPlein = false, debordQuant = false;

    uint32 octetsPlein = ecrirePlein(envoye, bufPlein, sizeof(bufPlein), bitsPlein, debordPlein);
    uint32 octetsQuant = ecrireQuantifie(envoye, bufQuant, sizeof(bufQuant), bitsQuant, debordQuant);

    std::printf("Paquet en types complets : %u octets (%u bits)  debordement=%d\n",
                static_cast<unsigned>(octetsPlein), static_cast<unsigned>(bitsPlein), debordPlein ? 1 : 0);
    std::printf("Paquet quantifie         : %u octets (%u bits)  debordement=%d\n",
                static_cast<unsigned>(octetsQuant), static_cast<unsigned>(bitsQuant), debordQuant ? 1 : 0);

    // Les paquets sont lus par un second morceau de code qui ne connait
    // que l'octet recu et sa taille, pas l'etat d'origine.
    Etat luPlein = lirePlein(bufPlein, octetsPlein);
    Etat luQuant = lireQuantifie(bufQuant, octetsQuant);

    std::printf("Valeurs :\n");
    afficher("envoye", envoye);
    afficher("lu plein", luPlein);
    afficher("lu quantif", luQuant);

    // Plus grand ecart sur 100000 etats tires dans les bornes de l'enonce.
    double ecartX = 0, ecartY = 0, ecartAngle = 0;
    int ecartSante = 0, ecartNumero = 0, ecartVivant = 0;
    unsigned graine = 12345u;
    for (int i = 0; i < 100000; ++i) {
        graine = graine * 1664525u + 1013904223u;
        double a = (graine >> 8) / 16777216.0;
        graine = graine * 1664525u + 1013904223u;
        double b = (graine >> 8) / 16777216.0;
        graine = graine * 1664525u + 1013904223u;
        double c = (graine >> 8) / 16777216.0;

        Etat e;
        e.vivant = (i % 2 == 0);
        e.numero = static_cast<uint8>(i % 256);
        e.x = static_cast<float32>(-500.0 + 1000.0 * a);
        e.y = static_cast<float32>(-500.0 + 1000.0 * b);
        e.angle = static_cast<float32>(360.0 * c);
        e.sante = i % 101;

        uint8 buf[64] = {};
        uint32 bits = 0;
        bool debord = false;
        uint32 octets = ecrireQuantifie(e, buf, sizeof(buf), bits, debord);
        Etat lu = lireQuantifie(buf, octets);

        double dx = std::fabs(static_cast<double>(lu.x) - static_cast<double>(e.x));
        double dy = std::fabs(static_cast<double>(lu.y) - static_cast<double>(e.y));
        double da = std::fabs(static_cast<double>(lu.angle) - static_cast<double>(e.angle));
        if (dx > ecartX) ecartX = dx;
        if (dy > ecartY) ecartY = dy;
        if (da > ecartAngle) ecartAngle = da;
        int ds = std::abs(static_cast<int>(lu.sante) - static_cast<int>(e.sante));
        if (ds > ecartSante) ecartSante = ds;
        int dn = std::abs(static_cast<int>(lu.numero) - static_cast<int>(e.numero));
        if (dn > ecartNumero) ecartNumero = dn;
        if (lu.vivant != e.vivant) ecartVivant = 1;
    }

    std::printf("Plus grands ecarts sur 100000 etats (paquet quantifie) :\n");
    std::printf("  x      : %.6f m\n", ecartX);
    std::printf("  y      : %.6f m\n", ecartY);
    std::printf("  angle  : %.6f degres\n", ecartAngle);
    std::printf("  sante  : %d\n", ecartSante);
    std::printf("  numero : %d\n", ecartNumero);
    std::printf("  vivant : %d\n", ecartVivant);
    return 0;
}