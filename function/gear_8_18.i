
/* gear 8 / 18 */
template<typename T>
T isofunction(T x, T y, T z) {
  T angle = atan2(y,x);
  T r = sqrt(x*x+y*y);
  T R = (r>0.2)?r+0.1*sin(angle*18)-.8:-r+0.1;
  T D1 = z-0.15;
  T D2 = -z-0.15;
  T M = max(R,max(D1,D2));
  T _R = (r>0.2)?r+0.1*sin(angle*8)-.3:-r+0.1;
  T _D1 = z-0.40;
  T _D2 = -z-0.05;
  T _M = max(_R,max(_D1,_D2));
  return -max(-M,-_M);
}

