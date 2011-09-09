/* The following code declares classes to read from and write to
 * file descriptore or file handles.
 *
 * See
 *      http://www.josuttis.com/cppcode
 * for details and the latest version.
 *
 * - open:
 *      - integrating BUFSIZ on some systems?
 *      - optimized reading of multiple characters
 *      - stream for reading AND writing
 *      - i18n
 *
 * (C) Copyright Nicolai M. Josuttis 2001.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 *
 * Version: Jul 28, 2002
 * History:
 *  Jul 28, 2002: bugfix memcpy() => memmove()
 *                fdinbuf::underflow(): cast for return statements
 *  Aug 05, 2001: first public version
 */
#ifndef BOOST_FDSTREAM_HPP
#define BOOST_FDSTREAM_HPP

#include <istream>
#include <ostream>
#include <streambuf>
// for EOF:
#include <cstdio>
// for memmove():
#include <cstring>
#include <ext/stdio_filebuf.h>


// low-level read and write functions
#ifdef _MSC_VER
# include <io.h>
#else
# include <unistd.h>
//extern "C" {
//    int write (int fd, const char* buf, int num);
//    int read (int fd, char* buf, int num);
//}
#endif


// BEGIN namespace BOOST
namespace boost {


/************************************************************
 * fdostream
 * - a stream that writes on a file descriptor
 ************************************************************/


// For reference see Josuttis, "The C++ Standard Library", 13.13.3.
//   Note the casts to unsigned char, and the explicit constructors.
//   Josuttis erroneously omits them.

class FdOutBuf : public std::streambuf
{
  public:
    explicit FdOutBuf(int d)
      : fd(d)
      { this->setp(this->buf, this->buf+(size-1)); }

    ~FdOutBuf() { this->sync(); }
  protected:
    virtual int overflow(int ic)
    {
      if (ic != EOF) {
        // Double check that there is room for a character, otherwise
        // assume a previous I/O output failed, in which case just
        // returning a failure now is appropriate.
        if (pptr() >= &buf[size])
            return EOF;
        *this->pptr() = char(ic);
        this->pbump(1);
      }
      if (sync() < 0)
        return EOF;
      return ic;
    }

    virtual int sync()
    {
      char const*  p = this->pbase();
      int  n = this->pptr() - p;
      while (n) {
         int  done = ::write(fd, p, n);
         if (done < 0)
           return -1;
         n -= done;
         p += done;
      }
      this->pbump(-(p - this->pbase()));
      return 0;
    }

  private:
    enum { size = 1 << 13 } ; // 8192
    int fd;
    char buf[size];
};


class FdOStream : public std::ostream
{
  public:
    explicit FdOStream(int fd) : std::ostream(&buf), buf(fd) {}
  private:
    FdOutBuf buf;

//  public:
//    explicit FdOStream(int fd) : std::ostream(&buf), buf(fd, std::ios::in) {}
//  private:
//    __gnu_cxx::stdio_filebuf<char> buf;



};


class FdInBuf : public std::streambuf
{
  public:
    explicit FdInBuf(int d)
      : fd(d) { this->setg(this->buf+size, this->buf+size, this->buf+size); }

    virtual int underflow()
    {
      if (this->gptr() < this->egptr()) {
        return (unsigned char) *this->gptr();
      }
      bool  pb = (this->gptr() - this->eback()) != 0;
      if (pb) this->buf[0] = this->gptr()[-1];
      int  got = ::read(this->fd, this->buf+1, this->size-1);
      if (got <= 0) {
        return EOF;
      }
      this->setg(buf+(1-pb), buf+1, buf+1+got);
      return (unsigned char) *this->gptr();
    }

  private:
    enum { size = 1 << 13 } ; // 8192
    int fd;
    char buf[size];
};

class FdIStream : public std::istream
{
  public:
    explicit FdIStream(int fd) : std::istream(&buf), buf(fd) {}
  private:
    FdInBuf buf;
};



} // END namespace boost

#endif /*BOOST_FDSTREAM_HPP*/
