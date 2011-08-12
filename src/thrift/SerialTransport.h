#ifndef SERIALTRANSPORT_H_
#define SERIALTRANSPORT_H_

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <termios.h>  /* POSIX terminal control definitions */

#include "fd_stream.h"

namespace naxsoft {

class SerialTransport {
public:

	/**
	 * Constructs a new XBee AT Transport. Note that this does NOT actually connect.
	 */
	SerialTransport(const char serialport[], speed_t baudrate);

	/**
	 * Destroyes the object, closing the transport if necessary.
	 */
	~SerialTransport();

	/**
	 * Calls select on the socket to see if there is more data available.
	 * Tests whether there is more data to read or if the remote side is
	 * still open. By default this is true whenever the transport is open,
	 * but implementations should add logic to test for this condition where
	 * possible (i.e. on a socket).
	 * This is used by a server to check if it should listen for another
	 * request.
	 */
	bool peek() const;

	/**
	 * Creates and opens the UNIX socket.
	 *
	 * @throws TTransportException If the socket could not connect
	 */
	void open();
	/**
	 * Whether this transport is open.
	 */
	bool isOpen() const;

	/**
	 * Shuts down communications on the socket.
	 */
	void close();

	/**
	 * Flushes any pending data to be written. Typically used with buffered
	 * transport mechanisms.
	 *
	 * @throws TTransportException if an error occurs
	 */
	void flush() const;

	/**
	 * Attempt to read up to the specified number of bytes into the string.
	 *
	 * @param buf  Reference to the location to write the data
	 * @param len  How many bytes to read
	 * @return How many bytes were actually read
	 * @throws TTransportException If an error occurs
	 */
	uint32_t read(uint8_t* buf, uint32_t len) const;

	/**
	 * Called when read is completed.
	 * This can be over-ridden to perform a transport-specific action
	 * e.g. logging the request to a file
	 *
	 * @return number of bytes read if available, 0 otherwise.
	 */
	virtual uint32_t readEnd() const {
		// default behaviour is to do nothing
		return 0;
	}

	/**
	 * Reads the given amount of data in its entirety no matter what.
	 *
	 * @param s     Reference to location for read data
	 * @param len   How many bytes to read
	 * @return How many bytes read, which must be equal to size, non-positive if insufficient data was read
	 */
	uint32_t readAll(uint8_t* buf, uint32_t len) const;

	/**
	 * Writes the string in its entirety to the buffer.
	 *
	 * Note: You must call flush() to ensure the data is actually written,
	 * and available to be read back in the future.  Destroying a TTransport
	 * object does not automatically flush pending data--if you destroy a
	 * TTransport object with written but unflushed data, that data may be
	 * discarded.
	 *
	 * @param buf  The data to write out
	 * @throws TTransportException if an error occurs
	 */
	void write(const uint8_t* buf, uint32_t len) const;

	/**
	 * Called when write is completed.
	 * This can be over-ridden to perform a transport-specific action
	 * at the end of a request.
	 *
	 * @return number of bytes written if available, 0 otherwise
	 */
	uint32_t writeEnd() {
		// default behaviour is to do nothing
		return 0;
	}

private:
	int baudrate; // default
	const char* serialport;
	int fd;
	char buf[256];
	boost::fdistream* inStream;
	boost::fdostream* outStream;

	int serialport_init(const char* serialport, int baud);
};

} // namespace


#endif /* SERIALTRANSPORT_H_ */
