#include <string.h>

#include "Protocol.h"
#include "SerialTransport.h"

namespace naxsoft {

//#define NDEBUG

Protocol::Protocol(SerialTransport const* const transport) :
	trans_(transport) {
}

/**
 * Writing functions.
 */
uint32_t Protocol::writeMessageBegin(
		/*const char* name, */const TMessageType messageType /*, const int32_t seqid*/) const {
	uint32_t wsize = 0;
	//    wsize += writeString(name);
	wsize += writeI8((int8_t) messageType);
	//    wsize += writeI32(seqid);
	return wsize;
}

uint32_t Protocol::writeMessageEnd() const {
	this->trans_->flush();
	return 0;
}

uint32_t Protocol::writeStructBegin(const char* name) const {
	(void) name;
	return 0;
}

uint32_t Protocol::writeStructEnd() const {
	return 0;
}

uint32_t Protocol::writeFieldBegin(const char* name, const TType fieldType,
		const int16_t fieldId) const {
	(void) name;
	int32_t wsize = 0;
	wsize += writeI8((int8_t) fieldType);
	wsize += writeI16(fieldId);
	return wsize;
}

uint32_t Protocol::writeFieldEnd() const {
	return 0;
}

uint32_t Protocol::writeFieldStop() const {
	return writeI8((int8_t) T_STOP);
}

uint32_t Protocol::writeMapBegin(const TType keyType, const TType valType,
		const uint32_t size) const {
	uint32_t wsize = 0;
	wsize += writeI8((int8_t) keyType);
	wsize += writeI8((int8_t) valType);
	wsize += writeI32((int32_t) size);
	return wsize;
}

uint32_t Protocol::writeMapEnd() const {
	return 0;
}

uint32_t Protocol::writeListBegin(const TType elemType, const uint32_t size) const {
	uint32_t wsize = 0;
	wsize += writeI8((int8_t) elemType);
	wsize += writeI32((int32_t) size);
	return wsize;
}

uint32_t Protocol::writeListEnd() const {
	return 0;
}

uint32_t Protocol::writeSetBegin(const TType elemType, const uint32_t size) const {
	uint32_t wsize = 0;
	wsize += writeI8((int8_t) elemType);
	wsize += writeI32((int32_t) size);
	return wsize;
}

uint32_t Protocol::writeSetEnd() const {
	return 0;
}

uint32_t Protocol::writeBool(const bool value) const {
	uint8_t tmp = value ? 1 : 0;
	this->trans_->write(&tmp, 1);
	return 1;
}

uint32_t Protocol::writeI8(const int8_t byte) const {
	this->trans_->write((uint8_t*) &byte, 1);
	return 1;
}

uint32_t Protocol::writeI16(const int16_t i16) const {
	//  int16_t net = (int16_t)htons(i16);
	int16_t net = i16;
	this->trans_->write((uint8_t*) &net, 2);
	return 2;
}

uint32_t Protocol::writeI32(const int32_t i32) const {
	//  int32_t net = (int32_t)htonl(i32);
	int32_t net = i32;
	this->trans_->write((uint8_t*) &net, 4);
	return 4;
}

uint32_t Protocol::writeI64(const int64_t i64) const {
	//  int64_t net = (int64_t)htonll(i64);
	int64_t net = i64;
	this->trans_->write((uint8_t*) &net, 8);
	return 8;
}

uint32_t Protocol::writeFloat(const float dub) const {
	//  assert(sizeof(double) == sizeof(uint64_t));
	//  assert(std::numeric_limits<double>::is_iec559);
	//  uint64_t bits = bitwise_cast<uint64_t>(dub);
	//  bits = htonll(bits);
	//  this->trans_->write((uint8_t*)&bits, 8);
	//  return 8;
	int32_t net = dub;
	this->trans_->write((uint8_t*) &net, 4);
	return 4;
}

uint32_t Protocol::writeString(const char* str) const {
	uint32_t size = strlen(str);
	uint32_t result = writeI32((int32_t) size);
	if (size > 0) {
		this->trans_->write((uint8_t*) str, size);
	}
	return result + size;
}

uint32_t Protocol::writeBinary(const char* str, const uint32_t size) const {
	uint32_t result = writeI32((int32_t) size);
	if (size > 0) {
		this->trans_->write((uint8_t*) str, size);
	}
	return result + size;
}

/**
 * Reading functions
 */
uint32_t Protocol::readMessageBegin(/*char* name,*/
TMessageType& messageType
/*, int32_t& seqid*/) const {
	uint32_t result = 0;
	int8_t type;

	//  int32_t sz;
	//  result += readI32(sz);
	//  result += readStringBody(name, sz);
	result += readI8(type);
	messageType = (TMessageType) type;
	//  result += readI32(seqid);

	//  Serial.print("Protocol::readMessageBegin name = ");
	//  Serial.print(name);
	//  Serial.print(" messageType = ");
	//  Serial.print(messageType);
	//  Serial.print(" seqid = ");
	//  Serial.println(seqid);

	return result;
}

uint32_t Protocol::readMessageEnd() const {
	return 0;
}

uint32_t Protocol::readStructBegin(char* name) const {
	*name = '\0';
	return 0;
}

uint32_t Protocol::readStructEnd() const {
	return 0;
}

uint32_t Protocol::readFieldBegin(char* name, TType& fieldType, int16_t& fieldId) const {
	(void) name;
	uint32_t result = 0;
	int8_t type;
	result += readI8(type);
	fieldType = (TType) type;
	if (fieldType == T_STOP) {
		fieldId = 0;
		return result;
	}
	result += readI16(fieldId);
	return result;

}

uint32_t Protocol::readFieldEnd() const {
	return 0;
}

uint32_t Protocol::readMapBegin(TType& keyType, TType& valType, uint32_t& size) const {

	int8_t k, v;
	uint32_t result = 0;
	int32_t sizei;
	result += readI8(k);
	keyType = (TType) k;
	result += readI8(v);
	valType = (TType) v;
	result += readI32(sizei);
	//  if (sizei < 0) {
	//    throw TProtocolException(TProtocolException::NEGATIVE_SIZE);
	//  } else if (this->container_limit_ && sizei > this->container_limit_) {
	//    throw TProtocolException(TProtocolException::SIZE_LIMIT);
	//  }
	size = (uint32_t) sizei;
	return result;
}

uint32_t Protocol::readMapEnd() const {
	return 0;
}

uint32_t Protocol::readListBegin(TType& elemType, uint32_t& size) const {
	int8_t e;
	uint32_t result = 0;
	int32_t sizei;
	result += readI8(e);
	elemType = (TType) e;
	result += readI32(sizei);
	//  if (sizei < 0) {
	//    throw TProtocolException(TProtocolException::NEGATIVE_SIZE);
	//  } else if (this->container_limit_ && sizei > this->container_limit_) {
	//    throw TProtocolException(TProtocolException::SIZE_LIMIT);
	//  }
	size = (uint32_t) sizei;
	return result;
}

uint32_t Protocol::readListEnd() const {
	return 0;
}

uint32_t Protocol::readSetBegin(TType& elemType, uint32_t& size) const {

	//  Serial.println("start readSetBegin");

	int8_t e;
	uint32_t result = 0;
	int32_t sizei;
	result += readI8(e);
	elemType = (TType) e;
	result += readI32(sizei);
	//  if (sizei < 0) {
	//    throw TProtocolException(TProtocolException::NEGATIVE_SIZE);
	//  } else if (this->container_limit_ && sizei > this->container_limit_) {
	//    throw TProtocolException(TProtocolException::SIZE_LIMIT);
	//  }
	size = (uint32_t) sizei;

	//  Serial.print("end readSetBegin. size = ");
	//  Serial.println(size);
	return result;
}

uint32_t Protocol::readSetEnd() const {
	return 0;
}

uint32_t Protocol::readBool(bool& value) const {
	uint8_t b[1];
	int32_t result = 0;
	result = this->trans_->readAll(b, 1);
	value = *(int8_t*) b != 0;
	return result;
	//      return 1;
}

uint32_t Protocol::readI8(int8_t& val) const {
	uint8_t b[1];
	int32_t result = 0;

	result = this->trans_->readAll(b, 1);
	val = *(int8_t*) b;

	//  Serial.print("readI8 val = ");
	// Serial.println(val);

	//      return 1;
	return result;
}

uint32_t Protocol::readI16(int16_t& i16) const {
	uint8_t b[2];
	int32_t result = 0;

	result = this->trans_->readAll(b, 2);
	i16 = *(int16_t*) b;
	// return 2;
	return result;
}

uint32_t Protocol::readI32(int32_t& i32) const {
	uint8_t b[4];
	uint32_t result = 0;

	result = this->trans_->readAll(b, 4);
	i32 = *(int32_t*) b;
	return result;
	//return 4;
}

uint32_t Protocol::readI64(int64_t& i64) const {
	uint8_t b[8];
	uint32_t result = 0;

	result = this->trans_->readAll(b, 8);
	i64 = *(int32_t*) b;
	//     return 8;
	return result;
}

uint32_t Protocol::readFloat(float& dub) const {
	uint8_t b[4];
	uint32_t result = 0;

	result = this->trans_->readAll(b, 4);
	dub = *(float*) b;
	//     return 4;
	return result;
}

uint32_t Protocol::readString(char* str) const {
	uint32_t result;
	int32_t size;
	result = readI32(size);
	return result + readStringBody(str, size);
}

uint32_t Protocol::readBinary(char* str) const {
	return this->readString(str);
}

uint32_t Protocol::readStringBody(char* str, int32_t size) const {
	uint32_t result = 0;

	if (size > 0) {
		str = (char*) malloc(size);
		result += this->trans_->readAll((uint8_t*) str, size);
	}
	return result;
}

/**
 * Method to arbitrarily skip over data.
 */
uint32_t Protocol::skip(TType type) const {

	switch (type) {
	case T_BOOL: {
		bool boolv;
		return readBool(boolv);
	}
	case T_BYTE: {
		int8_t bytev;
		return readI8(bytev);
	}
	case T_I16: {
		int16_t i16;
		return readI16(i16);
	}
	case T_I32: {
		int32_t i32;
		return readI32(i32);
	}
	case T_I64: {
		int64_t i64;
		return readI64(i64);
	}
	case T_FLOAT: {
		float dub;
		return readFloat(dub);
	}
	case T_STRING: {
		char* str = NULL;
		uint32_t res;
		res = readBinary(str);
		if (str != NULL) {
			free(str);
		}
		return res;
	}
	case T_STRUCT: {
		uint32_t result = 0;
		char* name = NULL;
		int16_t fid;
		TType ftype;
		result += readStructBegin(name);
		if (name != NULL) {
			free(name);
		}
		while (true) {
			result += readFieldBegin(name, ftype, fid);
			if (ftype == T_STOP) {
				break;
			}
			result += skip(ftype);
			result += readFieldEnd();
		}
		result += readStructEnd();
		return result;
	}
	case T_MAP: {
		uint32_t result = 0;
		TType keyType;
		TType valType;
		uint32_t i, size;
		result += readMapBegin(keyType, valType, size);
		for (i = 0; i < size; i++) {
			result += skip(keyType);
			result += skip(valType);
		}
		result += readMapEnd();
		return result;
	}
	case T_SET: {
		uint32_t result = 0;
		TType elemType;
		uint32_t i, size;
		result += readSetBegin(elemType, size);
		for (i = 0; i < size; i++) {
			result += skip(elemType);
		}
		result += readSetEnd();
		return result;
	}
	case T_LIST: {
		uint32_t result = 0;
		TType elemType;
		uint32_t i, size;
		result += readListBegin(elemType, size);
		for (i = 0; i < size; i++) {
			result += skip(elemType);
		}
		result += readListEnd();
		return result;
	}
	case T_STOP:
	case T_VOID:
	case T_U64:
	case T_UTF8:
	case T_UTF16:
		break;
	}
	return 0;
}
} // namespace
