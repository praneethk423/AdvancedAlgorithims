#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <curl/curl.h>

constexpr uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

inline uint32_t rotr(uint32_t x, uint32_t n) {
    return (x >> n) | (x << (32 - n));
}

inline uint32_t shr(uint32_t x, uint32_t n) {
    return x >> n;
}

std::vector<uint8_t> sha256(const std::string &message) {
    uint32_t h[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    std::vector<uint8_t> paddedMessage(message.begin(), message.end());
    paddedMessage.push_back(0x80);
    while ((paddedMessage.size() * 8 + 64) % 512 != 0) {
        paddedMessage.push_back(0);
    }
    uint64_t originalLength = message.size() * 8;
    for (int i = 7; i >= 0; --i) {
        paddedMessage.push_back((originalLength >> (i * 8)) & 0xFF);
    }

    for (size_t chunkStart = 0; chunkStart < paddedMessage.size(); chunkStart += 64) {
        std::vector<uint32_t> w(64, 0);
        for (size_t i = 0; i < 16; ++i) {
            w[i] = (paddedMessage[chunkStart + 4 * i] << 24) |
                   (paddedMessage[chunkStart + 4 * i + 1] << 16) |
                   (paddedMessage[chunkStart + 4 * i + 2] << 8) |
                   (paddedMessage[chunkStart + 4 * i + 3]);
        }
        for (size_t i = 16; i < 64; ++i) {
            uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ shr(w[i - 15], 3);
            uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ shr(w[i - 2], 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], h_temp = h[7];

        for (size_t i = 0; i < 64; ++i) {
            uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h_temp + S1 + ch + K[i] + w[i];
            uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            h_temp = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += h_temp;
    }

    std::vector<uint8_t> digest;
    for (uint32_t elem : h) {
        digest.push_back((elem >> 24) & 0xFF);
        digest.push_back((elem >> 16) & 0xFF);
        digest.push_back((elem >> 8) & 0xFF);
        digest.push_back(elem & 0xFF);
    }

    return digest;
}

std::string bytesToHexString(const std::vector<uint8_t> &bytes) {
    std::ostringstream oss;
    for (uint8_t byte : bytes) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}

size_t writeCallback(char *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

std::string downloadBook(const std::string &url) {
    std::string content;
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return content;
}

int main() {
    std::string markUrl = "https://quod.lib.umich.edu/cgi/r/rsv/rsv-idx?type=DIV1&byte=4697892";
    std::string markText = downloadBook(markUrl);
    
    std::vector<uint8_t> hash = sha256(markText);
    
    std::cout << "SHA-256 hash of the book of Mark:\n" << bytesToHexString(hash) << std::endl;

    return 0;
}
