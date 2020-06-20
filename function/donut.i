
/* donut */
template<typename T>
T isofunction(T x, T y, T z) {
  T D = 0.6*0.6;
  T R = pow(sqrt(x*x+y*y) - D,2) + z*z;
  return R - 0.3*0.3;
}

