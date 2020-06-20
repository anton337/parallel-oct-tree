
/* rounded tetrahedron */
template<typename T>
T isofunction(T x, T y, T z) {
  T vx = 0;
  T vy = 0;
  T vz = 1;
  T D = x*vx+y*vy+z*vz - 0.3;
  T R = D;

  vx = sqrt(8.0/9.0);
  vy = 0;
  vz = -1.0/3.0;
  D = x*vx+y*vy+z*vz - 0.3;
  R = max(R,D);

  vx = -sqrt(2.0/9.0);
  vy = sqrt(2.0/3.0);
  vz = -1.0/3.0;
  D = x*vx+y*vy+z*vz - 0.3;
  R = max(R,D);

  vx = -sqrt(2.0/9.0);
  vy = -sqrt(2.0/3.0);
  vz = -1.0/3.0;
  D = x*vx+y*vy+z*vz - 0.3;
  R = max(R,D);

  T r = sqrt(x*x + y*y + z*z) - 0.5;

  return max(R,r);
}

