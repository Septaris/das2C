/** @file core.h A roll-up header for the core Das2 C-Library */

/**
 * \mainpage
 *
 * <p>Das2 Streams are a self-describing, streamable format that allows for the 
 * transmission of large and complex data sets between different systems and 
 * programming environments.  A precise description of the Das Stream
 * specification 2.2 is found elsewhere in the Das2 Interface Reference at
 * <a href="http://www-pw.physics.uiowa.edu/das2">http://www-pw.physics.uiowa.edu/das2</a>.
 * </p>
 * <p>This library of C functions provides utilities for more easily producing 
 * Das2 Streams that are correctly formatted and will be compatible with future
 * versions of the Das2 Stream specification.
 * </p>
 *
 * <h2>Writing Streams</h2>
 * <p>A Das2 Stream is created by first opening the stream and getting a handle
 * to it, then calling functions of this library that create and send out the 
 * various entities that live in Das2 Streams.  There are functions for creating
 * a packetDescriptor and then specifying what data will be in each packet,
 * functions for populating the fields of the packet and sending out the packet
 * onto the stream.  Also there are functions for indicating progress and
 * sending out messages on the stream for human consumption.  The top level
 * stream writing functions are defined in output.h.
 * </p>
 *
 * <p>Here is an illustration of a typical use of the library:
 * <ul>
 * <li>Declare an output ::DasIO structure using new_DasIO_file() or 
 * new_DasIO_cfile().
 * </li>
 * <li>Call new_StreamDesc() to create a ::StreamDesc structure.
 * </li>
 * <li>Set global properties of the stream with the various ::Descriptor
 *     functions such as Desc_setPropString() and similar calls
 * </li>
 * <li>Write out the stream descriptor using DasIO_writeStreamDesc()
 * </li>
 * <li>Call new_PktDesc() to create a type of packet that will be found on the
 * stream.  Attach it to the stream using StreamDesc_addPktDesc()
 * </li>
 * <li>Create the data planes for the packet using new_PlaneDesc() and 
 *     new_PlaneDesc_yscan().  Attach them to the packet using PktDesc_addPlane().
 * </li>
 * <li>Set extra properties such as labels for the data planes using
 *     Desc_setPropString() and similar functions.
 * </li>
 * <li>Call DasIO_writePktDesc() to send the packet descriptor out onto the
 *     stream.
 * </li>
 * <li>While reading through the records of input data do the following:
 *   <ul>
 *     <li>Call PlaneDesc_setValue() current values for each plane such as the
 *         current time and amplitudes.
 *     </li>
 *     <li>Call DasIO_writePktData() to encode and output the current plane 
 *         values
 *     </li>
 *   </ul>
 * <li>close the stream using DasIO_close()
 * </li>
 * </ul>
 * </p>
 *
 * <h2>Reading Streams</h2>
 * <p>A Das2 Stream is consumed by defining a set of callback functions that
 *  are invoked as the stream is read.  Once the functions are set, program
 *  control is handed over to the library, and the callbacks are invoked until
 *  the entire stream is read.  The top level stream reading functions are 
 *  defined in input.h.
 * </p>
 *
 * <p>Here is an illustration of a typical use of the library to read a stream:
 * <ol>
 * <li>Declare an input ::DasIO structure using new_DasIO_file() or 
 *     new_DasIO_cfile().
 * </li>
 * <li>Declare a callback function of type ::StreamDescHandler to be triggered
 *     when a new das2 stream header is read in.
 * </li>
 * <li>Declare a callback function of type ::PktDescHandler for handling
 *     packet headers.
 * </li>
 * <li>Declare a callback function of type ::PktDataHandler for handling the 
 *     incoming data packets.
 * </li>
 * </li>
 * <li>Optionally declare functions for handling comments and exceptions.
 *     Often these are simply forwarded onto the output stream.
 * </li>
 * <li>Fill out a ::StreamHandler structure to tie together your callbacks.  
 *     If your callback functions need to maintain non-global state information
 *     use the StreamHandler::userData pointer to address a structure of your
 *     own design.
 * </li>
 * <li>Call DasIO_readAll() to have the library read in the stream.
 * </li>
 * <li>Exit after the DasIO_readAll() is completed.
 * </li>
 * </ol>
 *
 * <h2>Example Program</h2>
 * 
 * The program:
 * 
 *     - @b das2_bin_avg.c 
 * 
 * is a small filter for averaging Das2 Stream data into fixed size bins.
 * Since it has to handle both input and output and does some minimal 
 * data processing, this short program provides a good example of using
 * this library to read and write Das2 streams.
 * 
 * <h2>Compiling and Linking</h2>
 *
 * There are about a half-dozen or so library headers, but you don't need to
 * worry about find the right ones if you don't want to.  A roll-up header
 * is included with the library that will grab all definitions.  So including
 * the header:
 * @code
 *    #include <das2/das2.h>
 * @endcode
 * in your application source files will define all the needed data structures.
 *
 * Linking is handled by command line options similar to:
 * @code
 *   -L /YOUR/LIB/INSTALL/PATH -l das2            // GCC
 *   /LIBPATH C:\YOUR\LIB\INSTALL\PATH das2.lib   // link.exe
 * @endcode
 * The exact details depend on your C tool-chain and installation locations.
 */

#ifndef _das2_core_h_
#define _das2_core_h_

/* Include all the Das1 functions as well */
#include <das2/das1.h>

/* Add Das2 stream parsing */
#include <das2/util.h>
#include <das2/encoding.h>
#include <das2/buffer.h>
#include <das2/units.h>
#include <das2/data.h>
#include <das2/descriptor.h>
#include <das2/plane.h>
#include <das2/packet.h>
#include <das2/oob.h>
#include <das2/stream.h>
#include <das2/processor.h>
#include <das2/das2io.h>
#include <das2/dsdf.h>
#include <das2/dft.h>
#include <das2/log.h>

/* Add a utility for handling UTF-8 as an internal string format, though
   almost all string manipulation algorithms get by without this even when
	the strings contain utf-8 characters */
#include <das2/utf8.h>

#endif /* _das2_core_h_ */
