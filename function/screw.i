
/* screw */
template<typename T>
T isofunction(T x, T y, T z) {
  T vx = 0;
  T vy = 0;
  T vz = 1;
  T D = x*vx+y*vy+z*vz - 0.9 + 0.7*(x*x+y*y);
  T R0 = D;
  vx = 0;
  vy = 0;
  vz = -1;
  D = x*vx+y*vy+z*vz - 0.9;
  R0 = max(R0,D);

  vx = 0;
  vy = 0;
  vz = 1;
  D = x*vx+y*vy+z*vz + 0.6;
  T R1 = D;
  vx = 0;
  vy = 0;
  vz = -1;
  D = x*vx+y*vy+z*vz - 0.95;
  R1 = max(R1,D);
  T R = R1;
  for(int i=0;i<6;i++) {
    vx = cos((2*M_PI*i)/6);
    vy = sin((2*M_PI*i)/6);
    vz = 0;
    D = x*vx+y*vy+z*vz - 0.7;
    R = max(R,D);
  }

  T angle = atan2(y,x);
  T r = sqrt(x*x+y*y) + 0.025*sin(angle+z*40);

  return min(R,max(R0,r - 0.48));
}

