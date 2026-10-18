// ---- Version qui FIGE (gardee en commentaire) ----
// NkThread a([]() {
//     NkScopedLockMutex verrouA1(m1);
//     NkChrono::SleepMilliseconds(100);
//     NkScopedLockMutex verrouA2(m2);   // a prend m1 puis m2
// });
// NkThread b([]() {
//     NkScopedLockMutex verrouB1(m2);
//     NkChrono::SleepMilliseconds(100);
//     NkScopedLockMutex verrouB2(m1);   // b prend m2 puis m1 : ordre inverse
// });
// ---------------------------------------------------

#include "NKThreading/NkThread.h"
#include "NKThreading/NkMutex.h"
#include "NKTime/NkChrono.h"
#include <cstdio>

using namespace nkentseu;

static NkMutex m1;
static NkMutex m2;

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    NkThread a([]() {
        NkScopedLockMutex verrouA1(m1);
        std::printf("a : m1 pris, attend 100 ms\n");
        NkChrono::SleepMilliseconds(100);
        std::printf("a : demande m2\n");
        NkScopedLockMutex verrouA2(m2);
        std::printf("a : m1 et m2 pris\n");
    });

    NkThread b([]() {
        NkScopedLockMutex verrouB1(m1);
        std::printf("b : m1 pris, attend 100 ms\n");
        NkChrono::SleepMilliseconds(100);
        std::printf("b : demande m2\n");
        NkScopedLockMutex verrouB2(m2);
        std::printf("b : m1 et m2 pris\n");
    });

    a.Join();
    b.Join();
    std::printf("fini\n");
    return 0;
}