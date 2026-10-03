#include <iostream>

int main() {
    int C, R, W, H, F;
    long long D, P;

    std::cin >> C >> R >> W >> H >> F >> D >> P;

    int frame = 0;
    long long temps = 0;
    int avances = 0;
    int plafonnes = 0;

    int N;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        long long dt;
        std::cin >> dt;

        if (dt > P) {
            dt = P;
            ++plafonnes;
        }

        temps += dt;

        while (temps >= D) {
            temps -= D;
            ++frame;

            if (frame >= F) {
                frame = 0;
            }

            ++avances;
        }

        int x = (frame % C) * W;
        int y = (frame / C) * H;

        std::cout << "case "
                  << x << " "
                  << y << " "
                  << W << " "
                  << H << "\n";
    }

    std::cout << "AVANCES " << avances << "\n";
    std::cout << "PLAFONNES " << plafonnes << "\n";

    return 0;
}