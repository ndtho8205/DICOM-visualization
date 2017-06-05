#ifndef DICOMSTRUCTS_H
#define DICOMSTRUCTS_H

#include <vector>
#include <cstdint>
#include <QDebug>


typedef struct DicomSingle
{
    std::vector<int>          luminance;
    std::vector<std::uint8_t> luminance8;
    std::uint32_t             width;
    std::uint32_t             height;
    std::uint32_t             instanceNumber;
    int                       smallestPixelValue;
    int                       largestPixelValue;
    float                     spacing;
    float                     pixelSpacing;
} DicomSingle;


typedef struct DicomSet
{
    std::vector<DicomSingle *> data;
    std::uint32_t              width;
    std::uint32_t              height;
    std::uint32_t              depth;
    std::uint64_t *            histogram;

    ~DicomSet()
    {
        delete[] histogram;

        for (unsigned long i = 0; i < data.size(); ++i)
            delete data[i];
        data.clear();
    }
} DicomSet;

#endif  // DICOMSTRUCTS_H
