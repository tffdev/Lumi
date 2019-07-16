#ifndef MATH_H
#define MATH_H

template <typename T>
class Vector2 {
public:
  Vector2(T x = 0, T y =  0) :x(x), y(y) {}
  T x;
  T y;
};

template <typename T>
class Vector3 {
public:
  Vector3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
  T x;
  T y;
  T z;
};

#endif // MATH_H
