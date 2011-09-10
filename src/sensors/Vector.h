#ifndef VECTOR_H_
#define VECTOR_H_

namespace naxsoft {

typedef struct vector
{
  double x, y, z;
} vector;

class Vector {
public:
	Vector();
	virtual ~Vector();

	static void cross(const vector *a, const vector *b, vector *out);
	static float dot(const vector *a,const vector *b);
	static void normalize(vector *a);};

}

#endif /* VECTOR_H_ */
