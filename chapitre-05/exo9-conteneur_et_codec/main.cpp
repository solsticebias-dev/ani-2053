#include <cstdio>
#include <cstdlib>
#include <cstring>
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

static const char *conteneur(const std::vector<int> &b) {
    size_t n = b.size();
    if (n >= 12 && b[4] == 0x66 && b[5] == 0x74 && b[6] == 0x79 && b[7] == 0x70) return "MP4";
    if (n >= 4 && b[0] == 0x1A && b[1] == 0x45 && b[2] == 0xDF && b[3] == 0xA3) return "WEBM";
    if (n >= 12 && b[0] == 0x52 && b[1] == 0x49 && b[2] == 0x46 && b[3] == 0x46 &&
        b[8] == 0x57 && b[9] == 0x41 && b[10] == 0x56 && b[11] == 0x45) return "WAV";
    if (n >= 4 && b[0] == 0x4F && b[1] == 0x67 && b[2] == 0x67 && b[3] == 0x53) return "OGG";
    if (n >= 4 && b[0] == 0x66 && b[1] == 0x4C && b[2] == 0x61 && b[3] == 0x43) return "FLAC";
    if (n >= 3 && b[0] == 0x49 && b[1] == 0x44 && b[2] == 0x33) return "MP3";
    if (n >= 2 && b[0] == 0xFF && b[1] >= 0xE0) return "MP3";
    return "INCONNU";
}

static std::string nomCodec(const std::string &code) {
    if (code == "mp4a") return "aac";
    if (code == "Opus" || code == "opus") return "opus";
    if (code == "avc1" || code == "avc3") return "h264";
    if (code == "hvc1" || code == "hev1") return "h265";
    if (code == "vp08") return "vp8";
    if (code == "vp09") return "vp9";
    if (code == "mp4v") return "mpeg4";
    if (code == ".mp3") return "mp3";
    if (code == "twos" || code == "sowt" || code == "lpcm") return "pcm";
    return code;
}

static bool lisible(const std::string &code) {
    return code == "mjpa" || code == "jpeg" || code == "MJPG" || code == "avc1" ||
           code == "avc3" || code == "hvc1" || code == "hev1" || code == "av01";
}

int main() {
    int n;
    if (std::scanf("%d", &n) != 1) return 0;

    int mp4 = 0, lisibles = 0, inconnus = 0;
    char nom[256];
    char hex[4096];

    for (int i = 0; i < n; ++i) {
        int p;
        std::scanf("%255s %4095s %d", nom, hex, &p);

        std::vector<std::string> types(p), codes(p);
        char type[64], code[64];
        for (int k = 0; k < p; ++k) {
            std::scanf("%63s %63s", type, code);
            types[k] = type;
            codes[k] = code;
        }

        std::vector<int> b = decode(hex);
        const char *cont = conteneur(b);
        std::printf("%s %s\n", nom, cont);

        if (std::strcmp(cont, "INCONNU") == 0) ++inconnus;

        if (std::strcmp(cont, "MP4") == 0) {
            ++mp4;
            const char *verdict = "SANS_IMAGE";
            bool premiereVideoVue = false;
            for (int k = 0; k < p; ++k) {
                bool video = (types[k] == "vide");
                std::printf("%s PISTE %d %s %s\n", nom, k + 1, video ? "VIDEO" : "AUDIO",
                            nomCodec(codes[k]).c_str());
                if (video && !premiereVideoVue) {
                    premiereVideoVue = true;
                    verdict = lisible(codes[k]) ? "LISIBLE" : "ECHEC";
                }
            }
            std::printf("%s LECTEUR %s\n", nom, verdict);
            if (std::strcmp(verdict, "LISIBLE") == 0) ++lisibles;
        }
    }

    std::printf("MP4 %d\n", mp4);
    std::printf("LISIBLES %d\n", lisibles);
    std::printf("INCONNUS %d\n", inconnus);
    return 0;
}