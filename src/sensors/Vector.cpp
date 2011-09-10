#include "Vector.h"
#include <math.h>

namespace naxsoft {

Vector::Vector() {
	// TODO Auto-generated constructor stub

}

Vector::~Vector() {
	// TODO Auto-generated destructor stub
}


void Vector::cross(const vector *a,const vector *b, vector *out)
{
  out->x = a->y*b->z - a->z*b->y;
  out->y = a->z*b->x - a->x*b->z;
  out->z = a->x*b->y - a->y*b->x;
}

float Vector::dot(const vector *a,const vector *b)
{
  return a->x*b->x+a->y*b->y+a->z*b->z;
}

void Vector::normalize(vector *a)
{
  float mag = sqrt(Vector::dot(a,a));
  a->x /= mag;
  a->y /= mag;
  a->z /= mag;
}

}
