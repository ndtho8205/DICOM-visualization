/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file baseStreamInput.h
    \brief Declaration of the the base stream class BaseStreamInput.
*/

#if !defined(imebraBaseStreamInput__INCLUDED_)
#define imebraBaseStreamInput__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
    class baseStreamInput;
}
}

#endif

namespace imebra
{

///
/// \brief This class represents a generic input stream.
///
/// Specialized classes derived from this one can read data from files stored
/// on the computer's disks (FileStreamInput) or from memory
/// (MemoryStreamInput).
///
/// The client application cannot read the data directly from a
/// BaseStreamInput but must use a StreamReader. Several StreamReader objects
/// can read data from the same BaseStreamInput object.
///
/// The StreamReader class is not thread-safe, but different StreamReader
/// objects in different threads can access the same BaseStreamInput object.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API BaseStreamInput
{
    BaseStreamInput(const BaseStreamInput&) = delete;
    BaseStreamInput& operator=(const BaseStreamInput&) = delete;

#ifndef SWIG
	friend class StreamReader;
    friend class FileStreamInput;
    friend class MemoryStreamInput;

private:
    /// \brief Construct a BaseStreamInput object from an implementation object.
    ///
    /// \param pStream the implementation of BaseStreamInput
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamInput(std::shared_ptr<implementation::baseStreamInput> pStream);
#endif

public:
    /// \brief Destructor.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~BaseStreamInput();

#ifndef SWIG
protected:
    std::shared_ptr<implementation::baseStreamInput> m_pStream;
#endif
};

}

#endif // !defined(imebraBaseStreamInput__INCLUDED_)
