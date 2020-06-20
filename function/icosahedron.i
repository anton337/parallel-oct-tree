
/* icosahedron */
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

  T phi = (1+sqrt(5))/2.0;

  vx = 0;
  vy = phi;
  vz = 1/phi;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx = 0;
  vy =-phi;
  vz = 1/phi;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx = 0;
  vy =-phi;
  vz =-1/phi;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx = 0;
  vy = phi;
  vz =-1/phi;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);



  vx = 1/phi;
  vy = 0;
  vz = phi;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx =-1/phi;
  vy = 0;
  vz = phi;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx =-1/phi;
  vy = 0;
  vz =-phi;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx = 1/phi;
  vy = 0;
  vz =-phi;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);



  vx = phi;
  vy = 1/phi;
  vz = 0;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx =-phi;
  vy = 1/phi;
  vz = 0;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx =-phi;
  vy =-1/phi;
  vz = 0;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  vx = phi;
  vy =-1/phi;
  vz = 0;
  D = x*vx+y*vy+z*vz - 0.5;
  R = max(R,D);

  return R;
}

