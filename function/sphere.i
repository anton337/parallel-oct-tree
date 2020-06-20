
/* sphere */
template<typename T>
T isofunction(T x, T y, T z) {
  T R = sqrt(x*x+y*y+z*z);
  return R - 0.8;
}

