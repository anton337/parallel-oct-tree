
/* rounded cube */
template<typename T>
T isofunction(T x, T y, T z) {
  T D1 = x-0.85;
  T D2 = -x-0.85;
  T D3 = y-0.85;
  T D4 = -y-0.85;
  T D5 = z-0.85;
  T D6 = -z-0.85;
  T M = max(max(D1,D2),max(max(D3,D4),max(D5,D6)));
  T r = sqrt(x*x + y*y + z*z) - 1.2;
  return max(M,r);
}

