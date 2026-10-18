#include "NKThreading/NkThread.h"
#include "NKThreading/NkThreadPool.h"
#include "NKTime/NkChrono.h"
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace nkentseu;

static const int NB_TACHES = 200;
static const int NB_MESURES = 3;
static const long long TACHE_COURTE = 1000;
static const long long TACHE_LONGUE = 100000;

static long long tache(long long n, long long graine) {
    long long s = graine;
    for (long long k = 0; k < n; ++k) {
        s += (k * 7 + s) % 13;
    }
    return s;
}

static double versionReserve(long long n, long long &controle) {
    std::vector<long long> res(NB_TACHES, 0);

    NkChrono chrono;
    {
        NkThreadPool reserve;
        for (int i = 0; i < NB_TACHES; ++i) {
            reserve.Enqueue([&res, i, n]() {
                res[i] = tache(n, i);
            });
        }
        reserve.Join();
    }
    double ms = chrono.Elapsed().ToMilliseconds();

    controle = 0;
    for (int i = 0; i < NB_TACHES; ++i) controle += res[i];
    return ms;
}

static double versionFils(long long n, long long &controle) {
    std::vector<long long> res(NB_TACHES, 0);
    std::vector<NkThread> fils;
    fils.reserve(NB_TACHES);

    NkChrono chrono;
    for (int i = 0; i < NB_TACHES; ++i) {
        fils.emplace_back([&res, i, n]() {
            res[i] = tache(n, i);
        });
    }
    for (size_t i = 0; i < fils.size(); ++i) fils[i].Join();
    double ms = chrono.Elapsed().ToMilliseconds();

    controle = 0;
    for (int i = 0; i < NB_TACHES; ++i) controle += res[i];
    return ms;
}

static void mesurer(const char *nom, long long n, bool reserve) {
    double temps[NB_MESURES];
    long long controle = 0;
    for (int m = 0; m < NB_MESURES; ++m) {
        temps[m] = reserve ? versionReserve(n, controle) : versionFils(n, controle);
    }

    double tries[NB_MESURES];
    std::copy(temps, temps + NB_MESURES, tries);
    std::sort(tries, tries + NB_MESURES);

    std::printf("%-8s n=%-7lld %.2f %.2f %.2f ms  mediane %.2f ms  controle %lld\n",
                nom, n, temps[0], temps[1], temps[2], tries[1], controle);
}

int main() {
    {
        NkThreadPool reserve;
        std::printf("Workers : %u\n", static_cast<unsigned>(reserve.GetNumWorkers()));
    }

    mesurer("Reserve", TACHE_COURTE, true);
    mesurer("Fils", TACHE_COURTE, false);
    mesurer("Reserve", TACHE_LONGUE, true);
    mesurer("Fils", TACHE_LONGUE, false);
    return 0;
}