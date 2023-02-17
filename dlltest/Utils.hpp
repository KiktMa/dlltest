#pragma once
#include <string>
#include <cmath>
#include <bitset>
#include <vector>
#include <cmath>
#include <iomanip>

#include "ida.h"





const size_t MAX_INDEX = 12;
const size_t MAX_BITS = 96;
const size_t BITS_PER_D = 32;
const long double PI = 3.153852L;


class ChangeCode {
private:
    const unsigned char* geoCode;
    int level;
    std::bitset<BITS_PER_D> heightCode;
    std::bitset<BITS_PER_D> latCode;
    std::bitset<BITS_PER_D> lonCode;
    std::bitset<MAX_BITS> binaryOneDCodeBit;

public:
    ChangeCode(const unsigned char* geoC, int lev) :geoCode(geoC), level(lev) {
        if (geoCode == NULL || level > 32) {
            throw std::string("error");
        }
        std::bitset<MAX_BITS> tempBitSet;
        size_t pos = 0;
        for (size_t i = 0; i < MAX_INDEX; ++i) {
            unsigned char ch = geoCode[MAX_INDEX - i - 1];
            for (int shiftNum = 7; shiftNum >= 0; --shiftNum) {
                bool bl = 0x01 & (ch >> shiftNum);
                tempBitSet.set(MAX_BITS - pos - 1, bl);
                ++pos;
            }
        }
        // 二进制三维码
        int p = BITS_PER_D - 1;
        for (size_t i = 0; i < MAX_BITS && p >= 0; i += 3) {
            heightCode.set(p, tempBitSet[MAX_BITS - (i + 0) - 1]);
            latCode.set(p, tempBitSet[MAX_BITS - (i + 1) - 1]);
            lonCode.set(p, tempBitSet[MAX_BITS - (i + 2) - 1]);
            --p;
        }
        heightCode <<= (BITS_PER_D - level);

        // 二进制一维码
        int index = 0;
        for (int posIndex = BITS_PER_D - 1; posIndex >= 0; --posIndex) {
            binaryOneDCodeBit.set(MAX_BITS - 1 - (index + 0), heightCode[posIndex]);
            binaryOneDCodeBit.set(MAX_BITS - 1 - (index + 1), latCode[posIndex]);
            binaryOneDCodeBit.set(MAX_BITS - 1 - (index + 2), lonCode[posIndex]);
            index += 3;
        }
    }

    std::vector<std::string>& getBinaryThreeDimensionalCode(std::vector<std::string>& binaryThreeDCode)const {
        binaryThreeDCode.push_back(heightCode.to_string());
        binaryThreeDCode.push_back(latCode.to_string());
        binaryThreeDCode.push_back(lonCode.to_string());
        return binaryThreeDCode;
    }

    std::string& getBinaryOneDimensionalCode(std::string& binaryOneDCode) const {
        binaryOneDCode = binaryOneDCodeBit.to_string();
        return binaryOneDCode;
    }

    std::string& getOctalOneDimensionalCode(std::string& octalOneDCode) const {
        unsigned char num = 0;
        octalOneDCode.clear();
        octalOneDCode = "G";
        for (int pos = BITS_PER_D - 1; pos >= 0; --pos) {
            num += heightCode[pos] * 4;
            num += latCode[pos] * 2;
            num += lonCode[pos] * 1;
            octalOneDCode.push_back(num + '0');
            num = 0;
        }
        octalOneDCode = octalOneDCode.substr(0, level + 1);
        return octalOneDCode;
    }

    std::string& getHexOneDimensionalCode(std::string& hexOneDCode) const {
        unsigned char num = 0;
        hexOneDCode.clear();
        for (int pos = MAX_BITS - 1; pos >= 0; pos -= 4) {
            num += binaryOneDCodeBit[pos-0] * 8;
            num += binaryOneDCodeBit[pos-1] * 4;
            num += binaryOneDCodeBit[pos-2] * 2;
            num += binaryOneDCodeBit[pos-3] * 1;
            num = (num <= 9) ? (num + '0') : (num - 0x0a + 'A');
            hexOneDCode.push_back(num);
            num = 0;
        }
        return hexOneDCode;
    }

    std::bitset<BITS_PER_D>& getOneDCode(std::bitset<BITS_PER_D>& code, int dim) const {
        switch (dim)
        {
        case 0:
            code = heightCode;
            break;
        case 1:
            code = latCode;
            break;
        case 2:
            code = lonCode;
            break;
        default:
            throw std::string("error");
            break;
        }
        return code;
    }
};


/*
* dms : 10^10'10.1212N/D/E/W" 其中^代表°,
* ddd : 1111.1111 单位度
*/
inline double dms2ddd(std::string& dms) {

    size_t pos = dms.find('^');
    assert(pos != std::string::npos);
    std::string du = dms.substr(0, pos);
    double d_du = std::stod(du);
    dms = dms.substr(pos + 1, dms.size() - pos - 1);

    pos = dms.find('\'');
    assert(pos != std::string::npos);
    std::string fen = dms.substr(0, pos);
    double d_fen = std::stod(fen);
    dms = dms.substr(pos + 1, dms.size() - pos - 1);

    pos = dms.find('\"');
    assert(pos != std::string::npos);
    std::string miao = dms.substr(0, pos);
    double d_miao = std::stod(miao);
    dms = dms.substr(pos + 1, dms.size() - pos - 1);
    assert(dms == "N" || dms == "S" || dms == "E" || dms == "W");

    double result = d_du + (d_fen / 60.0) + (d_miao / 3600);
    if (dms == "S" || dms == "W") {
        result = -result;
    }
    return result;
}



inline uint32_t heightToCode(double height, char level) {
    uint32_t result; //
    int v5 = 0; // 
    double X; // 
    double heightKm; // 

    heightKm = 0.001 * height;
    if (0.001 * height <= 528680.1711252437 && heightKm >= -6302.106722602182)
    {
        // seta0 = pi / 180;
        // log(1+seta0) = 0.01730273312368107;
        // ro = 6378.137km;
        X = 3600.0 * log((heightKm + 6378.137) / 6378.137) / 0.01730273312368107;

        v5 = 0;
        if (heightKm < 0.0)
        {
            X = -X;
        }
        LOWORD(v5) = v5 & 0xF800 | (int)(2048.0 * (X - floor(X))) & 0x7FF;

        int32_t X_32bits = int32_t(X);
        int64_t product = 0xFFFFFFFF91A2B3C5 * int64_t(int32_t(X));
        int32_t productHight32BitsAddX_32bits = ((product >> 32) & 0x00000000ffffffff) + X_32bits;

        int32_t productHight32BitsAddX_32bitsShift11bits = productHight32BitsAddX_32bits >> 0x0b;
        int32_t X_32bitsShift_0x1f_bits = X_32bits >> 0x1f;
        int32_t subt = ((productHight32BitsAddX_32bitsShift11bits - X_32bitsShift_0x1f_bits)
            & 0x000000ff) << 7;
        HIWORD(v5) = HIWORD(v5) & 0x807F | subt;

        int32_t BYTE2temp = (int)(X - (double)((unsigned __int8)(HIWORD(v5) >> 7) * 3600));
        int32_t mulResHight32BitsAddX_32bits = (((0xffffffff88888889 * int64_t(BYTE2temp)) >> 32) & 0x00000000ffffffff) + BYTE2temp;

        int32_t mulResHight32BitsAddX_32bitsShift5bits = mulResHight32BitsAddX_32bits >> 0x5;
        int32_t BYTE2tempShift_0x1f_bits = BYTE2temp >> 0x1f;
        int32_t subRes = (mulResHight32BitsAddX_32bitsShift5bits - BYTE2tempShift_0x1f_bits) & 0x3f;
        subRes *= 2;

        BYTE2(v5) = subRes | BYTE2(v5) & 0x81;
        v5 = v5 & 0xFFFE07FF | (((int)(X
            - (double)(3600 * (unsigned __int8)(HIWORD(v5) >> 7))
            - (double)(60 * ((BYTE2(v5) >> 1) & 0x3F))) & 0x3F) << 11);

        if (v5 >= 0)
        {
            result = (uint32_t)(v5 >> (32 - level));
        }
        else
        {
            HIBYTE(v5) &= ~0x80u;
            result = (uint32_t)~(v5 >> (32 - level));
        }
    }
    else
    {
        result = -1;
    }
    return result;

}

inline uint32_t getHeightCode(long double height, int level) {
    return heightToCode(height, level);
}



