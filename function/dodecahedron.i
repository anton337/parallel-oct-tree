
/* dodecahedron */
template<typename T>
T isofunction(T x, T y, T z) {
  T vx = 0;
  T vy = 0;
  T vz = 1;
  T D = x*vx+y*vy+z*vz - 0.5;
  T R = D;

  vx = 0;
  vy = 0;
  vz =-1;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  T angle = atan(0.5);
  for(int i=0;i<5;i++) {
    vx = cos(angle)*sin((2*M_PI*i)/5.0);
    vy = cos(angle)*cos((2*M_PI*i)/5.0);
    vz = sin(angle);
    D = x*vx+y*vy+z*vz - 0.5;
    R = max(R,D);
  }

  for(int i=0;i<5;i++) {
    vx = -cos(angle)*sin((2*M_PI*i)/5.0);
    vy = -cos(angle)*cos((2*M_PI*i)/5.0);
    vz = -sin(angle);
    D = x*vx+y*vy+z*vz - 0.5;
    R = max(R,D);
  }

  return R;
}

