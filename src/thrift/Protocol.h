#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdint.h>   /* Standard types */


namespace naxsoft {
    class SerialTransport; // Forward declaration

    enum TType {
      T_STOP      ,
      T_VOID       = 1,
      T_BOOL       = 2,
      T_BYTE       = 3,
      T_I08        = 3,
      T_FLOAT     = 4,
      T_I16        = 6,
      T_I32        = 8,
      T_U64        = 9,
      T_I64        = 10,
      T_STRING     = 11,
      T_UTF7       = 11,
      T_STRUCT     = 12,
      T_MAP        = 13,
      T_SET        = 14,
      T_LIST       = 15,
      T_UTF8       = 16,
      T_UTF16      = 17
    };

    /**
     * Enumerated definition of the message types that the Thrift protocol
     * supports.
     */
    enum TMessageType {
      T_CALL       = 1,
      T_REPLY      = 2,
      T_EXCEPTION  = 3,
      T_ONEWAY     = 4
    };


    class Protocol {
      public:
        Protocol(SerialTransport const* const transport);

        /**
         * Writing functions.
         */
        int32_t writeMessageBegin(/*const char* name,*/
                                   const TMessageType messageType
                                   /*,const int32_t seqid*/) const;

        int32_t writeMessageEnd() const;


        int32_t writeStructBegin(const char* name) const;

        int32_t writeStructEnd() const;

        int32_t writeFieldBegin(const char* name,
                                 const TType fieldType,
                                 const int16_t fieldId) const;

        int32_t writeFieldEnd() const;

        int32_t writeFieldStop() const;

        int32_t writeMapBegin(const TType keyType,
                               const TType valType,
                               const uint32_t size) const;

        int32_t writeMapEnd() const;

        int32_t writeListBegin(const TType elemType, const uint32_t size) const;

        int32_t writeListEnd() const;

        int32_t writeSetBegin(const TType elemType, const uint32_t size) const;

        int32_t writeSetEnd() const;

        int32_t writeBool(const bool value) const;

        int32_t writeI8(const int8_t byte) const;

        int32_t writeI16(const int16_t i16) const;

        int32_t writeI32(const int32_t i32) const;

        int32_t writeI64(const int64_t i64) const;

        int32_t writeFloat(const float dub) const;

        int32_t writeString(const char* str) const;

        int32_t writeBinary(const char* str, const uint32_t size) const;

        /**
         * Reading functions
         */
        int32_t readMessageBegin(/*char* name,*/
                                  TMessageType& messageType
                                  /*,int32_t& seqid */) const;

        int32_t readMessageEnd() const;

        int32_t readStructBegin(char* name) const;

        int32_t readStructEnd() const;

        int32_t readFieldBegin(char* name,
                                TType& fieldType,
                                int16_t& fieldId) const;

        int32_t readFieldEnd() const;

        int32_t readMapBegin(TType& keyType, TType& valType, uint32_t& size) const;

        int32_t readMapEnd() const;

        int32_t readListBegin(TType& elemType, uint32_t& size) const;

        int32_t readListEnd() const;

        int32_t readSetBegin(TType& elemType, uint32_t& size) const;

        int32_t readSetEnd() const;

        int32_t readBool(bool& value) const;

        int32_t readI8(int8_t& byte) const;

        int32_t readI16(int16_t& i16) const;

        int32_t readI32(int32_t& i32) const;

        int32_t readI64(int64_t& i64) const;

        int32_t readFloat(float& dub) const;

        int32_t readString(char* str) const;

        int32_t readBinary(char* str) const;

        /**
         * Method to arbitrarily skip over data.
         */
        int32_t skip(TType type) const;
     private:
       SerialTransport const* const trans_;
       int32_t readStringBody(char* str, int32_t size) const;
    };
}

#endif /* PROTOCOL_H_ */
