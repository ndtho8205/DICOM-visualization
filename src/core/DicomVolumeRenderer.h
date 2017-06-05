#ifndef DICOMVOLUMERENDERER_H
#define DICOMVOLUMERENDERER_H

#include <DicomVolume.h>
#include <DicomTexture.h>


class DicomVolumeRenderer
{
public:
    DicomVolumeRenderer();

    void setDicomData(const QString &dicomDir);
    std::uint64_t *getHistogramData();
    bool           isLoaded();

    void changeTextureAlphaRange(int lower, int upper);

    void drawCube();
    void renderTextureFixed();
    void renderTextureDynamic(const Point3d &orig, const Point3d &dest);
    void renderPolyDynamic(const Point3d &orig, const Point3d &dest);


private:
    void setTextureCoordinates(const Point3d &vertex);
    void setTexture(std::vector<Point3d> &vertices);
    DicomSet *   m_dicomSet = nullptr;
    DicomVolume  m_dicomVolume;
    DicomTexture m_dicomTexture;

    bool m_isLoaded;
};

#endif  // DICOMVOLUMERENDERER_H
