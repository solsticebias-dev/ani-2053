#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <string>
#include <vector>

static std::vector<int> decode(const char *hex) {
    std::vector<int> bytes;
    if (hex[0] == '-' && hex[1] == '\0') return bytes;
    for (size_t i = 0; hex[i] != '\0' && hex[i + 1] != '\0'; i += 2) {
        char pair[3] = {hex[i], hex[i + 1], '\0'};
        bytes.push_back(static_cast<int>(std::strtol(pair, nullptr, 16)));
    }
    return bytes;
}

static bool starts(const std::vector<int> &b, std::initializer_list<int> sig) {
    if (b.size() < sig.size()) return false;
    size_t i = 0;
    for (int v : sig) {
        if (b[i] != v) return false;
        ++i;
    }
    return true;
}

static const char *detect(long long taille, const std::vector<int> &b) {
    if (taille < 4) return nullptr;
    if (taille >= 8 && starts(b, {0x89, 0x50, 0x4E, 0x47})) return "PNG";
    if (starts(b, {0xFF, 0xD8, 0xFF})) return "JPEG";
    if (starts(b, {0x42, 0x4D})) return "BMP";
    if (starts(b, {0x71, 0x6F, 0x69, 0x66})) return "QOI";
    if (starts(b, {0x47, 0x49, 0x46, 0x38})) return "GIF";
    if (b.size() >= 4 && b[0] == 0 && b[1] == 0 && (b[2] == 1 || b[2] == 2) && b[3] == 0) return "ICO";
    if (taille >= 10 && starts(b, {0x23, 0x3F})) return "HDR";
    if (starts(b, {0x76, 0x2F, 0x31, 0x01})) return "EXR";
    if (b.size() >= 2 && b[0] == 0x50 && b[1] >= 0x31 && b[1] <= 0x36) {
        if (b[1] == 0x31 || b[1] == 0x34) return "PBM";
        if (b[1] == 0x32 || b[1] == 0x35) return "PGM";
        return "PPM";
    }
    if (taille >= 18 && b.size() >= 3 &&
        (b[2] == 0x00 || b[2] == 0x01 || b[2] == 0x02 || b[2] == 0x03 ||
         b[2] == 0x09 || b[2] == 0x0A || b[2] == 0x0B)) return "TGA";

    size_t i = 0;
    if (starts(b, {0xEF, 0xBB, 0xBF})) i = 3;
    while (i < b.size() && (b[i] == 0x20 || b[i] == 0x09 || b[i] == 0x0A || b[i] == 0x0D)) ++i;
    if (b.size() >= i + 5 && b[i] == 0x3C && b[i + 1] == 0x3F && b[i + 2] == 0x78 &&
        b[i + 3] == 0x6D && b[i + 4] == 0x6C) return "SVG";
    if (b.size() >= i + 4 && b[i] == 0x3C && b[i + 1] == 0x73 && b[i + 2] == 0x76 &&
        b[i + 3] == 0x67) return "SVG";
    return nullptr;
}

static bool extensionJuste(const char *format, const std::string &ext) {
    if (ext.empty()) return false;
    if (!std::strcmp(format, "PNG")) return ext == "png";
    if (!std::strcmp(format, "JPEG")) return ext == "jpg" || ext == "jpeg";
    if (!std::strcmp(format, "BMP")) return ext == "bmp";
    if (!std::strcmp(format, "QOI")) return ext == "qoi";
    if (!std::strcmp(format, "GIF")) return ext == "gif";
    if (!std::strcmp(format, "ICO")) return ext == "ico" || ext == "cur";
    if (!std::strcmp(format, "HDR")) return ext == "hdr";
    if (!std::strcmp(format, "EXR")) return ext == "exr";
    if (!std::strcmp(format, "PBM")) return ext == "pbm";
    if (!std::strcmp(format, "PGM")) return ext == "pgm";
    if (!std::strcmp(format, "PPM")) return ext == "ppm";
    if (!std::strcmp(format, "TGA")) return ext == "tga";
    if (!std::strcmp(format, "SVG")) return ext == "svg";
    return false;
}

int main() {
    int n;
    if (std::scanf("%d", &n) != 1) return 0;

    int lus = 0, mensonges = 0, refuses = 0;
    char nom[256];
    char hex[4096];

    for (int i = 0; i < n; ++i) {
        long long taille;
        std::scanf("%255s %lld %4095s", nom, &taille, hex);
        std::vector<int> b = decode(hex);
        const char *fmt = detect(taille, b);

        if (fmt == nullptr) {
            std::printf("%s REFUSE\n", nom);
            ++refuses;
            continue;
        }

        std::string name(nom);
        std::string ext;
        size_t dot = name.rfind('.');
        if (dot != std::string::npos) {
            ext = name.substr(dot + 1);
            for (size_t k = 0; k < ext.size(); ++k) {
                if (ext[k] >= 'A' && ext[k] <= 'Z') ext[k] = static_cast<char>(ext[k] - 'A' + 'a');
            }
        }

        ++lus;
        if (extensionJuste(fmt, ext)) {
            std::printf("%s %s OK\n", nom, fmt);
        } else {
            std::printf("%s %s MENT\n", nom, fmt);
            ++mensonges;
        }
    }

    std::printf("LUS %d\n", lus);
    std::printf("MENSONGES %d\n", mensonges);
    std::printf("REFUSES %d\n", refuses);
    return 0;
}