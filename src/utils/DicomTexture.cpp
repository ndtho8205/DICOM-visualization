#include "DicomTexture.h"

#include <vector>

#include <DicomLogicClass.h>


DicomTexture::DicomTexture()
{
    m_isLoaded = false;
}

DicomTexture::~DicomTexture()
{
    unload();
}

//
// ---------------------------------------------------------------------------
//

void DicomTexture::bind(int level)
{
    if (m_isLoaded) {
        switch (level) {
            case 2:
                glBindTexture(GL_TEXTURE_2D, m_texId);
                break;
            case 3:
                glBindTexture(GL_TEXTURE_3D, m_texId);
                break;
            default:
                break;
        }
    }
}

bool DicomTexture::load(const DicomSet &dicomSet, std::uint8_t lowerBound, std::uint8_t upperBound)
{
    if (!dicomSet.data.size())
        return false;

    DicomLogicClass &logicClass = DicomLogicClass::getInstance();
    logicClass.changeStatus("Loading texture 3D...");
    logicClass.startProgressing();
    logicClass.changeProgressingRange(0, int(dicomSet.depth));

    // -----------------------------------------------------------------------

    unload();

    std::vector<std::uint8_t> rgbaBuffer;

    for (DicomSingle *dicomSingle : dicomSet.data) {
        for (std::uint8_t l : dicomSingle->luminance8) {
            rgbaBuffer.push_back(l);
            rgbaBuffer.push_back(l);
            rgbaBuffer.push_back(l);
            if (lowerBound <= l && l <= upperBound) {
                rgbaBuffer.push_back(l);
            } else
                rgbaBuffer.push_back(0);
        }
        logicClass.increaseProgressingValue();
    }

    glGenTextures(1, &m_texId);

    glBindTexture(GL_TEXTURE_3D, m_texId);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    glTexImage3D(GL_TEXTURE_3D,
                 0,
                 GL_RGBA,
                 int(dicomSet.width),
                 int(dicomSet.height),
                 int(dicomSet.depth),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 &rgbaBuffer[0]);
    glBindTexture(GL_TEXTURE_3D, 0);

    m_isLoaded = m_texId != 0;

    // -----------------------------------------------------------------------

    logicClass.stopProgressing();
    logicClass.resetStatus();

    return m_isLoaded;
}

// bool DicomTexture::load(const DicomSingle &DicomSingle)
//{
//    if (&!dicomSingle.luminance.size())
//        return false;

//    unload();


//    vector<std::uint8_t> rgbaBuffer;

//    for (int l : dicomSingle.luminance8) {
//        rgbaBuffer.push_back(l);
//        rgbaBuffer.push_back(l);
//        rgbaBuffer.push_back(l);
//        if (luminance8 < 100)
//            rgbaBuffer.push_back(0);
//        else
//            rgbaBuffer.push_back(255);
//    }

//    glGenTextures(1, &m_texId);
//    glBindTexture(GL_TEXTURE_2D, m_texId);

//    glTexImage2D(GL_TEXTURE_2D,
//                 0,
//                 GL_RGBA,
//                 dicomSingle.width,
//                 dicomSingle.height,
//                 0,
//                 GL_RGBA,
//                 GL_UNSIGNED_BYTE,
//                 &rgbaBuffer[0]);

//    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

//    glBindTexture(GL_TEXTURE_2D, 0);

//    m_isLoaded = m_texId != 0;
//    return m_isLoaded;
//}

//
// ---------------------------------------------------------------------------
//

void DicomTexture::unload()
{
    if (m_isLoaded)
        glDeleteTextures(1, &m_texId);
}
