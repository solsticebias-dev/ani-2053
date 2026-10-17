#include "NKThreading/NkThread.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace nkentseu;

static const int NB_INCREMENTS = 1000000;
static int compteur = 0;

int main(int argc, char **argv) {
    int nbFils = (argc > 1) ? std::atoi(argv[1]) : 8;
    if (nbFils < 1) nbFils = 1;

    std::vector<NkThread> fils;
    fils.reserve(nbFils);

    for (int i = 0; i < nbFils; ++i) {
        fils.emplace_back([]() {
            for (int k = 0; k < NB_INCREMENTS; ++k) {
                compteur += 1;
            }
        });
    }

    for (int i = 0; i < nbFils; ++i) {
        fils[i].Join();
    }

    std::printf("Total obtenu : %d  (attendu : %d)\n", compteur, nbFils * NB_INCREMENTS);
    return 0;
}