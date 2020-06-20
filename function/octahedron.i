
/* octahedron */
template<typename T>
T isofunction(T x, T y, T z) {
  T vx = 1;
  T vy = 1;
  T vz = 1;
  T D = x*vx+y*vy+z*vz - 0.5;
  T R = D;

  vx =-1;
  vy = 1;
  vz = 1;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx = 1;
  vy =-1;
  vz = 1;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx =-1;
  vy =-1;
  vz = 1;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx = 1;
  vy = 1;
  vz =-1;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx =-1;
  vy = 1;
  vz =-1;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx = 1;
  vy =-1;
  vz =-1;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx =-1;
  vy =-1;
  vz =-1;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  return R;
}

