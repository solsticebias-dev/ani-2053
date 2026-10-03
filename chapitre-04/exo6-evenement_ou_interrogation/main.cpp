#include <iostream>
#include <string>

int main() {
    int v, n;
    std::cin >> v >> n;

    int xe = 0;
    int xi = 0;

    bool spacePressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

    int sautsEvenements = 0;
    int sautsInterrogation = 0;
    int manques = 0;

    for (int frame = 1; frame <= n; ++frame) {
        int k;
        std::cin >> k;

        int spacePressesThisFrame = 0;

        for (int i = 0; i < k; ++i) {
            std::string event;
            std::cin >> event;

            if (event == "+SPACE") {
                spacePressed = true;
                ++sautsEvenements;
                ++spacePressesThisFrame;
            }
            else if (event == "-SPACE") {
                spacePressed = false;
            }
            else if (event == "+RIGHT") {
                rightPressed = true;
                xe += v;
            }
            else if (event == "-RIGHT") {
                rightPressed = false;
            }
            else if (event == "+LEFT") {
                leftPressed = true;
                xe -= v;
            }
            else if (event == "-LEFT") {
                leftPressed = false;
            }
        }

        if (spacePressed) {
            ++sautsInterrogation;
        }

        if (rightPressed) {
            xi += v;
        }

        if (leftPressed) {
            xi -= v;
        }

        if (!spacePressed) {
            manques += spacePressesThisFrame;
        }

        std::cout << frame << " "
                  << xe << " "
                  << xi << "\n";
    }

    std::cout << "SAUTS EVENEMENTS " << sautsEvenements << "\n";
    std::cout << "SAUTS INTERROGATION " << sautsInterrogation << "\n";
    std::cout << "MANQUES " << manques << "\n";

    return 0;
}