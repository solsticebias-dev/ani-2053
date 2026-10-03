#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;

    int points = 0;
    int segments = 0;
    int triangles = 0;
    int refuses = 0;

    for (int i = 0; i < n; ++i) {
        std::string type;
        int vertices;

        std::cin >> type >> vertices;

        if (type == "POINTS") {
            int count = vertices;
            int left = 0;

            std::cout << type << " " << vertices << " "
                      << count << " POINTS " << left << "\n";

            points += count;
        }
        else if (type == "LINES") {
            int count = vertices / 2;
            int left = vertices % 2;

            std::cout << type << " " << vertices << " "
                      << count << " SEGMENTS " << left << "\n";

            segments += count;
        }
        else if (type == "LINE_STRIP") {
            int count = 0;
            int left = vertices;

            if (vertices >= 2) {
                count = vertices - 1;
                left = 0;
            }

            std::cout << type << " " << vertices << " "
                      << count << " SEGMENTS " << left << "\n";

            segments += count;
        }
        else if (type == "TRIANGLES") {
            int count = vertices / 3;
            int left = vertices % 3;

            std::cout << type << " " << vertices << " "
                      << count << " TRIANGLES " << left << "\n";

            triangles += count;
        }
        else if (type == "TRIANGLE_STRIP" ||
                 type == "TRIANGLE_FAN") {
            int count = 0;
            int left = vertices;

            if (vertices >= 3) {
                count = vertices - 2;
                left = 0;
            }

            std::cout << type << " " << vertices << " "
                      << count << " TRIANGLES " << left << "\n";

            triangles += count;
        }
        else {
            std::cout << type << " " << vertices << " REFUSE\n";
            ++refuses;
        }
    }

    std::cout << "POINTS " << points << "\n";
    std::cout << "SEGMENTS " << segments << "\n";
    std::cout << "TRIANGLES " << triangles << "\n";
    std::cout << "REFUSES " << refuses << "\n";

    return 0;
}