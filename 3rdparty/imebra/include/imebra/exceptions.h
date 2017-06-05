/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraExceptions__INCLUDED_)
#define imebraExceptions__INCLUDED_

#include <stdexcept>
#include <string>
#include "definitions.h"

namespace imebra
{


/// \brief Return the stack trace for the last exception thrown in the current
///        thread.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ExceptionsManager
{
public:
    /// \brief Return a message containing the stack trace for the last exception
    ///        thrown in the current thread.
    ///
    /// \return a message containing the stack trace
    ///
    ///////////////////////////////////////////////////////////////////////////////
    static std::string getExceptionTrace();
};


///
/// \brief This is the base class for the exceptions thrown by the LUT class.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API LutError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    LutError(const std::string& message);
};


///
/// \brief This exception is thrown by the lut class when the the LUT
///        information is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API LutCorruptedError: public LutError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    LutCorruptedError(const std::string& message);
};


/// \brief Base class for the exceptions that report a missing element
///        (Image, Tag, group, etc).
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MissingDataElementError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MissingDataElementError(const std::string& message);
};


/// \brief This exception is thrown when the client tries to read a tag from
///        a group that does not exist.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MissingGroupError: public MissingDataElementError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MissingGroupError(const std::string& message);
};


/// \brief This exception is thrown when the client tries to read a value from
///        a tag that does not exist (inside an existing group).
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MissingTagError: public MissingDataElementError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MissingTagError(const std::string& message);
};


/// \brief This exception is thrown when the client tries to read a value from
///        a buffer that does not exist (inside an existing tag).
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MissingBufferError: public MissingDataElementError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MissingBufferError(const std::string& message);
};


/// \brief This exception is thrown when the client tries to read a value from
///        an element that does not exist (inside an existing buffer).
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MissingItemError: public MissingDataElementError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MissingItemError(const std::string& message);
};


/// \brief The base exception for all the exceptions thrown by the function
///        in baseStream.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamError(const std::string& message);
};


///
/// \brief Exception thrown when the stream cannot be open.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamOpenError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamOpenError(const std::string& message);
};


///
/// \brief Exception thrown when there is an error during the read phase.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamReadError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamReadError(const std::string& message);
};


///
/// \brief Exception thrown when there is an error during the write phase.
///
///////////////////////////////////////////////////////////////////////////////

class IMEBRA_API StreamWriteError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamWriteError(const std::string& message);
};


/// \brief Exception thrown when there are problems while closing of the
///        stream.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamCloseError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamCloseError(const std::string& message);
};


/// \brief Base class for the exceptions thrown by the DicomDictionary.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DictionaryError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DictionaryError(const std::string& message);
};


/// \brief This exception is thrown by the DicomDictionary when it must return
///        information for a tag that the DICOM standard does not define.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DictionaryUnknownTagError: public DictionaryError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DictionaryUnknownTagError(const std::string& message);
};


/// \brief This exception is thrown by the DicomDictionary when it must return
///        information for a VR (data type) that the DICOM standard does not
///        define.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DictionaryUnknownDataTypeError: public DictionaryError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DictionaryUnknownDataTypeError(const std::string& message);
};


/// \brief Base class for the exceptions thrown by charsetConversion.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CharsetConversionError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CharsetConversionError(const std::string& message);
};


/// \brief Exception thrown when the requested charset is not supported by the
///        DICOM standard.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CharsetConversionNoTableError: public CharsetConversionError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CharsetConversionNoTableError(const std::string& message);
};


/// \brief Exception thrown when the requested charset is not supported by
///        the system.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CharsetConversionNoSupportedTableError: public CharsetConversionError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CharsetConversionNoSupportedTableError(const std::string& message);
};


/// \brief This exception is thrown when a conversion from an unicode string
///        causes the dicom dataSet to change its default charset.
///
/// For instace, the default charset is ISO IR 6 but a value written by the
/// application in one tag causes the default charset to switch to
/// ISO 2022 IR 100.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CharsetListDiffDefaultError: public CharsetConversionError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CharsetListDiffDefaultError(const std::string& message);
};


/// \brief This is the base class for the exceptions thrown by the codec derived classes.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CodecError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CodecError(const std::string& message);
};


/// \brief This exception is thrown when the file being parsed is not valid
///        for the codec.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CodecWrongFormatError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CodecWrongFormatError(const std::string& message);
};


/// \brief This exception is thrown when the file being parsed is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CodecCorruptedFileError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CodecCorruptedFileError(const std::string& message);
};


/// \brief This exception is thrown when the transfer syntax is not recognized
///        by the codec.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CodecWrongTransferSyntaxError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CodecWrongTransferSyntaxError(const std::string& message);
};


/// \brief This exception is thrown when the codec reads a file that contains
///        an image that is too big according to the codecFactory settings.
///
/// Consider using CodecFactory::setMaximumImageSize() to change the allowed
/// maximum image size.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API CodecImageTooBigError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    CodecImageTooBigError(const std::string& message);
};



/// \brief This exception is thrown when the codec is attempting to create a
///        sequence with an incompatible data type.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API InvalidSequenceItemError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    InvalidSequenceItemError(const std::string& message);
};


/// \brief Base class for the exceptions thrown by the data handlers.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataHandlerError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataHandlerError(const std::string& message);
};


/// \brief This exception is thrown when a data handler cannot convert a value from
///        one data type to a different data type.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataHandlerConversionError: public DataHandlerError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataHandlerConversionError(const std::string& message);
};


/// \brief This exception is thrown when the data handler's content is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataHandlerCorruptedBufferError: public DataHandlerError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataHandlerCorruptedBufferError(const std::string& message);
};


/// \brief This exception is thrown when the client tries to write invalid data
///        into a data handler.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataHandlerInvalidDataError: public DataHandlerError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataHandlerInvalidDataError(const std::string& message);
};

/// \brief This is the base class for the exceptions thrown by the dataSet.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataSetError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSetError(const std::string& message);
};


/// \brief This exception is thrown when the application is trying to store an
///        image in the dataSet but the dataSet already stores other images
///        that have different attributes.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataSetDifferentFormatError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSetDifferentFormatError(const std::string& message);
};


/// \brief This exception is thrown when an unknown transfer syntax is being
///        used while reading or writing a stream.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataSetUnknownTransferSyntaxError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSetUnknownTransferSyntaxError(const std::string& message);
};


/// \brief This exception is thrown when the application is storing several
///        images in the dataSet but doesn't store them in the right order.
///
/// The application must store the images following the frame order,
/// without skipping frames.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataSetWrongFrameError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSetWrongFrameError(const std::string& message);
};


/// \brief This exception is thrown when the application is trying to store
///        an image in an old Dicom format.
///
/// The application cannot store images in old Dicom formats (before Dicom3).
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataSetOldFormatError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSetOldFormatError(const std::string& message);
};


/// \brief This exception is thrown when the an image that doesn't exist is
///        requested.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataSetImageDoesntExistError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSetImageDoesntExistError(const std::string& message);
};

/// \brief This exception is thrown when the the client tries to store a
///        palette color image into the dataset.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataSetImagePaletteColorIsReadOnly: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSetImagePaletteColorIsReadOnly(const std::string& message);
};

/// \brief This exception is thrown when the basic offset table is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DataSetCorruptedOffsetTableError: public DataSetError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSetCorruptedOffsetTableError(const std::string& message);
};


/// \brief Base class from which the exceptions thrown by DicomDirEntry and
///        DicomDir classes.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DicomDirError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDirError(const std::string& message);
};


/// \brief This exception is thrown when a call to
///        DicomDir::setFirstRootRecord() or DicomDirEntry::setNextRecord()
///        or DicomDirEntry::setFirstChildRecord() causes a circular reference
///        between DicomDirEntry objects.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DicomDirCircularReferenceError: public DicomDirError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDirCircularReferenceError(const std::string& message);
};


/// \brief Exception thrown when an unknown record type
///        is detected in a DicomDirEntry.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DicomDirUnknownDirectoryRecordTypeError: public DicomDirError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDirUnknownDirectoryRecordTypeError(const std::string& message);
};


/// \brief Base class for the exceptions thrown by the Huffman codec.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API HuffmanError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    HuffmanError(const std::string& message);
};


/// \brief Exception thrown when the Huffman codec cannot create the Huffman
///        codes.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API HuffmanCreateTableError: public HuffmanError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    HuffmanCreateTableError(const std::string& message);
};


/// \brief Exception thrown when the Huffman codec tries to read an invalid
///        code.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API HuffmanReadError : public HuffmanError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    HuffmanReadError(const std::string& message);
};


/// \brief Exception thrown when the Huffman codec tries to write an invalid
///        code.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API HuffmanWriteError : public HuffmanError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    HuffmanWriteError(const std::string& message);
};


/// \brief This is the base class for the exceptions thrown by the Image class.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ImageError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ImageError(const std::string& message);
};

/// \brief This exception is thrown when an unknown depth is specified as a
///        parameter.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ImageUnknownDepthError: public ImageError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ImageUnknownDepthError(const std::string& message);
};


/// \brief This exception is thrown when an unknown color space is specified
///        in the function create().
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ImageUnknownColorSpaceError: public ImageError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ImageUnknownColorSpaceError(const std::string& message);
};


/// \brief This exception is thrown when an invalid size in pixels is
///        specified in the Image constructor.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ImageInvalidSizeError: public ImageError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ImageInvalidSizeError(const std::string& message);
};


/// \brief Base class for the exceptions thrown by the transforms.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API TransformError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    TransformError(const std::string& message);
};

/// \brief Exception thrown when the image areas to be processed are out
///        of bounds.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API TransformInvalidAreaError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    TransformInvalidAreaError(const std::string& message);
};


/// \brief Exception thrown when a Transform cannot process images with
///        different high bit.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API TransformDifferentHighBitError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    TransformDifferentHighBitError(const std::string& message);
};


/// \brief This is the base class for the exceptions thrown by
///        the color transform classes.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ColorTransformError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ColorTransformError(const std::string& message);
};


/// \brief This exception is thrown when a color transform must convert between
///        two color spaces that it does not support.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ColorTransformWrongColorSpaceError: public ColorTransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ColorTransformWrongColorSpaceError(const std::string& message);
};


/// \brief This is the base class for the exceptions thrown by
///        colorTransformsFactory.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ColorTransformsFactoryError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ColorTransformsFactoryError(const std::string& message);
};


/// \brief This exception is thrown by the function
///        ColorTransformsFactory::getTransform() when it cannot find any
///        transform that can convert the specified color spaces.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ColorTransformsFactoryNoTransformError: public ColorTransformsFactoryError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ColorTransformsFactoryNoTransformError(const std::string& message);
};


class IMEBRA_API TransformHighBitError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    TransformHighBitError(const std::string& message);
};


class IMEBRA_API TransformHighBitDifferentColorSpacesError: public TransformHighBitError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    TransformHighBitDifferentColorSpacesError(const std::string& message);
};


/// \brief Exception thrown when an attempt to read past the end of the file
///        is made.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamEOFError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamEOFError(const std::string& message);
};


/// \brief Exception thrown when a jpeg tag is found but wasn't expected.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamJpegTagInStreamError : public StreamError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamJpegTagInStreamError(const std::string& message);
};


/// \brief This exception is thrown by modalityVOILUT when the images passed
///        to the transform are not monochromatic.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ModalityVOILUTError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ModalityVOILUTError(const std::string& message);
};


/// \brief This is the base class for the exceptions thrown by the dicom
///        codec (dicomCodec).
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DicomCodecError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomCodecError(const std::string& message);
};


/// \brief This exception is thrown when dicomCodec::parseStream reaches the
///        maximum depth for embedded datasets.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DicomCodecDepthLimitReachedError: public DicomCodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomCodecDepthLimitReachedError(const std::string&message);

};


/// \brief Base class for the exceptions thrown by the jpeg codec.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API JpegCodecError: public CodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    JpegCodecError(const std::string& message);
};


/// \brief Exception thrown when the jpeg variant cannot be handled.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API JpegCodecCannotHandleSyntaxError: public JpegCodecError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    JpegCodecCannotHandleSyntaxError(const std::string& message);
};


class IMEBRA_API ImebraBadAlloc: public std::bad_alloc
{
};


/// \brief Base exception for errors in ReadMemory and ReadWriteMemory.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MemoryError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MemoryError(const std::string& message);
};


/// \brief Exception throw when the memory size is too small for the requested
///        operation.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MemorySizeError: public MemoryError
{
public:
    /// \brief Constructor.
    ///
    /// \param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MemorySizeError(const std::string& message);
};



}

#endif // !defined(imebraExceptions__INCLUDED_)
