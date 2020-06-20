
/* corner gear 18 */
template<typename T>
T isofunction(T x, T y, T z) {
  T angle = atan2(y,x);
  T r = sqrt(x*x+y*y);
  T R = (r>0.11)?r-.45+0.1*(0.33-z)*sin(angle*18)+z:-r+0.1;
  T D1 = z-0.33;
  T D2 = -z-0.40;
  T M = max(R,max(D1,D2));
  return M;
}

