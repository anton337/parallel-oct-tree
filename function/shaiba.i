
/* shaiba */
template<typename T>
T isofunction(T x, T y, T z) {
  T vx = 0;
  T vy = 0;
  T vz = 1;
  T D = x*vx+y*vy+z*vz - 0.4;
  T R0 = D;
  vx = 0;
  vy = 0;
  vz = -1;
  D = x*vx+y*vy+z*vz - 0.4;
  R0 = max(R0,D);

  T R = R0;
  for(int i=0;i<6;i++) {
    vx = cos((2*M_PI*i)/6);
    vy = sin((2*M_PI*i)/6);
    vz = 0;
    D = x*vx+y*vy+z*vz - 0.7;
    R = max(R,D);
  }

  T angle = atan2(y,x);
  T r = sqrt(x*x+y*y) + 0.025*sin(angle+z*40);

  return (r>0.6)?R:max(R0,0.5-r);
}

