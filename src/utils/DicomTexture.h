#ifndef DICOMTEXTURE_H
#define DICOMTEXTURE_H

#include <GL/glu.h>

#include <DicomStructs.h>


class DicomTexture
{
public:
    DicomTexture();
    ~DicomTexture();

    void bind(int level);
    bool load(const DicomSet &dicomSet, std::uint8_t lowerBound = 0, std::uint8_t upperBound = 255);
    //    bool load(const DicomSingle &DicomSingle);

private:
    void unload();

    std::uint32_t m_texId;
    bool          m_isLoaded;
};

#endif  // DICOMTEXTURE_H
