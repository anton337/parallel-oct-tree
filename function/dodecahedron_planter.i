
/* dodecahedron planter */
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

  T d = sqrt(x*x+y*y+z*z);
  vx = 0;
  vy = 0;
  vz = -1;
  D = x*vx+y*vy+z*vz - 0.485;
  T r = max(D, d - 0.56);

  vx = 0;
  vy = 0;
  vz = 1;
  D = x*vx+y*vy+z*vz - 0.485;
  r = max(r,D);
  if(z>0) {
    r = min(r,sqrt(x*x+y*y)-0.29);
  }

  T dot = 0;
  T proj = 0;
  for(int i=0;i<5;i++) {
    vx = cos(angle)*sin((2*M_PI*i)/5.0);
    vy = cos(angle)*cos((2*M_PI*i)/5.0);
    vz = sin(angle);
    dot = x*vx+y*vy+z*vz;
    D = dot - 0.485;
    r = max(r,D);
    if(dot>0) {
      proj = d*d - dot*dot;
      if(proj>0) {
        r = min(r, sqrt(proj) - 0.29);
      }
    }
  }

  for(int i=0;i<5;i++) {
    vx = -cos(angle)*sin((2*M_PI*i)/5.0);
    vy = -cos(angle)*cos((2*M_PI*i)/5.0);
    vz = -sin(angle);
    D = x*vx+y*vy+z*vz - 0.485;
    r = max(r,D);
  }

  return max(R,-r);
}

