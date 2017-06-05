/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcImage__INCLUDED_)
#define imebraObjcImage__INCLUDED_

#if defined(__APPLE__)
#include "TargetConditionals.h"

#import <Foundation/Foundation.h>
#include "../definitions.h"

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/NSImage.h>
#endif
#include <imebra/imebra.h>

namespace imebra
{

#if TARGET_OS_IPHONE
/**
 * Generates a NSImage on OS-X or an UIImage on iOS from a 24bpp RGB data returned by
 * imebra::DrawBitmap::getBitmap().
 *
 * @param image      the image to pass as parameter to imebra::DrawBitmap::getBitmap()
 * @param drawBitmap the imebra::DrawBitmap object to use to generate the 24bpp RGB
 *                   representation of the DICOM image
 * @return           a UIImage initialized with the 24bpp RGB data returned by imebra::DrawBitmap
 */
IMEBRA_API UIImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap);

#else

/**
 * Generates a NSImage on OS-X or an UIImage on iOS from a 24bpp RGB data returned by
 * imebra::DrawBitmap::getBitmap().
 *
 * @param image      the image to pass as parameter to imebra::DrawBitmap::getBitmap()
 * @param drawBitmap the imebra::DrawBitmap object to use to generate the 24bpp RGB
 *                   representation of the DICOM image
 * @return           a NSImage initialized with the 24bpp RGB data returned by imebra::DrawBitmap
 */
IMEBRA_API NSImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap);
#endif

} // namespace imebra

#endif //__APPLE__

#endif // imebraObjcImage__INCLUDED_


