#include "NKThreading/NkThread.h"
#include "NKThreading/NkMutex.h"
#include "NKCore/NkAtomic.h"
#include "NKTime/NkChrono.h"
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace nkentseu;

static const int NB_FILS = 8;
static const int NB_INCREMENTS = 1000000;
static const int NB_MESURES = 3;

struct Resultat {
    long long total;
    double ms;
};

static Resultat versionNue() {
    int compteur = 0;
    std::vector<NkThread> fils;
    fils.reserve(NB_FILS);

    NkChrono chrono;
    for (int i = 0; i < NB_FILS; ++i) {
        fils.emplace_back([&compteur]() {
            for (int k = 0; k < NB_INCREMENTS; ++k) {
                compteur += 1;
            }
        });
    }
    for (size_t i = 0; i < fils.size(); ++i) fils[i].Join();

    Resultat r;
    r.ms = chrono.Elapsed().ToMilliseconds();
    r.total = compteur;
    return r;
}

static Resultat versionVerrou() {
    int compteur = 0;
    NkMutex verrou;
    std::vector<NkThread> fils;
    fils.reserve(NB_FILS);

    NkChrono chrono;
    for (int i = 0; i < NB_FILS; ++i) {
        fils.emplace_back([&compteur, &verrou]() {
            for (int k = 0; k < NB_INCREMENTS; ++k) {
                NkScopedLockMutex garde(verrou);
                compteur += 1;
            }
        });
    }
    for (size_t i = 0; i < fils.size(); ++i) fils[i].Join();

    Resultat r;
    r.ms = chrono.Elapsed().ToMilliseconds();
    r.total = compteur;
    return r;
}

static Resultat versionAtomique() {
    NkAtomicInt compteur(0);
    std::vector<NkThread> fils;
    fils.reserve(NB_FILS);

    NkChrono chrono;
    for (int i = 0; i < NB_FILS; ++i) {
        fils.emplace_back([&compteur]() {
            for (int k = 0; k < NB_INCREMENTS; ++k) {
                compteur.FetchAdd(1);
            }
        });
    }
    for (size_t i = 0; i < fils.size(); ++i) fils[i].Join();

    Resultat r;
    r.ms = chrono.Elapsed().ToMilliseconds();
    r.total = compteur.Load();
    return r;
}

static Resultat versionLocale() {
    std::vector<long long> parFil(NB_FILS, 0);
    std::vector<NkThread> fils;
    fils.reserve(NB_FILS);

    NkChrono chrono;
    for (int i = 0; i < NB_FILS; ++i) {
        fils.emplace_back([&parFil, i]() {
            long long local = 0;
            for (int k = 0; k < NB_INCREMENTS; ++k) {
                local += 1;
            }
            parFil[i] = local;
        });
    }
    for (size_t i = 0; i < fils.size(); ++i) fils[i].Join();

    long long somme = 0;
    for (size_t i = 0; i < parFil.size(); ++i) somme += parFil[i];

    Resultat r;
    r.ms = chrono.Elapsed().ToMilliseconds();
    r.total = somme;
    return r;
}

static void mesurer(const char *nom, Resultat (*version)()) {
    double temps[NB_MESURES];
    long long total = 0;
    for (int m = 0; m < NB_MESURES; ++m) {
        Resultat r = version();
        temps[m] = r.ms;
        total = r.total;
    }

    double tries[NB_MESURES];
    std::copy(temps, temps + NB_MESURES, tries);
    std::sort(tries, tries + NB_MESURES);

    std::printf("%-16s total %lld (attendu %d)  mediane %.2f ms  [%.2f %.2f %.2f]\n",
                nom, total, NB_FILS * NB_INCREMENTS, tries[1], temps[0], temps[1], temps[2]);
}

int main() {
    mesurer("Sans protection", versionNue);
    mesurer("Verrou", versionVerrou);
    mesurer("Atomique", versionAtomique);
    mesurer("Local", versionLocale);
    return 0;
}