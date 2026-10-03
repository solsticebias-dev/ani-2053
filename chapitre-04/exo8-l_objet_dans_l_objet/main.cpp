#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct Objet {
    std::string nom;
    int parent;

    double tx;
    double ty;
    double angle;
    double scale;

    double worldX;
    double worldY;
    double worldAngle;
    double worldScale;

    int profondeur;
};

int main() {
    int n;
    std::cin >> n;

    std::vector<Objet> objets(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> objets[i].nom
                 >> objets[i].parent
                 >> objets[i].tx
                 >> objets[i].ty
                 >> objets[i].angle
                 >> objets[i].scale;

        int p = objets[i].parent;

        if (p == -1) {
            objets[i].worldX = objets[i].tx;
            objets[i].worldY = objets[i].ty;
            objets[i].worldAngle = objets[i].angle;
            objets[i].worldScale = objets[i].scale;
            objets[i].profondeur = 0;
        }
        else {
            const Objet& parent = objets[p];

            double angleRad = parent.worldAngle * 3.141592653589793 / 180.0;

            double x = objets[i].tx * parent.worldScale;
            double y = objets[i].ty * parent.worldScale;

            double rotatedX = x * std::cos(angleRad)
                            - y * std::sin(angleRad);

            double rotatedY = x * std::sin(angleRad)
                            + y * std::cos(angleRad);

            objets[i].worldX = parent.worldX + rotatedX;
            objets[i].worldY = parent.worldY + rotatedY;

            objets[i].worldAngle =
                parent.worldAngle + objets[i].angle;

            while (objets[i].worldAngle >= 360.0) {
                objets[i].worldAngle -= 360.0;
            }

            while (objets[i].worldAngle < 0.0) {
                objets[i].worldAngle += 360.0;
            }

            objets[i].worldScale =
                parent.worldScale * objets[i].scale;

            objets[i].profondeur =
                parent.profondeur + 1;
        }
    }

    for (const Objet& objet : objets) {
        std::cout << objet.nom << " "
                  << objet.worldX << " "
                  << objet.worldY << " "
                  << objet.worldAngle << " "
                  << objet.worldScale << "\n";
    }

    int profondeurMax = 0;

    for (const Objet& objet : objets) {
        if (objet.profondeur > profondeurMax) {
            profondeurMax = objet.profondeur;
        }
    }

    std::cout << "PROFONDEUR " << profondeurMax << "\n";

    return 0;
}