/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcStrings__INCLUDED_)
#define imebraObjcStrings__INCLUDED_

#import <Foundation/Foundation.h>
#include <string>
#include "../definitions.h"

namespace imebra
{

/**
 * @brief Convert an NSString to a std::string accepted by imebra.
 *
 * @param str an NSString
 * @return a UTF-8 encoded std::string
 */
IMEBRA_API std::string NSStringToString ( NSString* str );


/**
 * @brief Convert a UTF-8 encoded std::string to an NSString.
 *
 * @param str a UTF-8 encoded std::string
 * @return a NSString
 */
IMEBRA_API NSString* stringToNSString ( const std::string& str );

} // namespace imebra

#endif // imebraObjcStrings__INCLUDED_
