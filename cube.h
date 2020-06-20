#ifndef CUBE_H
#define CUBE_H

#include <vector>

using namespace std;

template<typename T>
struct Vertex {
  T p[3]; // x y z
  T value;
  size_t index;
  Vertex(T x, T y, T z, T v = 1) {
    p[0] = x;
    p[1] = y;
    p[2] = z;
    value = v;
    index = -1;
  }
};

template<typename T>
struct Triangle {
  vector<Vertex<T>*> v;
  Vertex<T>* n;
  void setnormal(){
    Vertex<T> v1(v[1]->p[0]-v[0]->p[0],v[1]->p[1]-v[0]->p[1],v[1]->p[2]-v[0]->p[2]);
    Vertex<T> v2(v[2]->p[0]-v[0]->p[0],v[2]->p[1]-v[0]->p[1],v[2]->p[2]-v[0]->p[2]);
    Vertex<T>* norm = new Vertex<T>( v1.p[1]*v2.p[2]-v2.p[1]*v1.p[2],
                                     v1.p[2]*v2.p[0]-v2.p[2]*v1.p[0],
                                     v1.p[0]*v2.p[1]-v2.p[0]*v1.p[1]);
    double r = sqrt(norm->p[0]*norm->p[0]+norm->p[1]*norm->p[1]+norm->p[2]*norm->p[2]);
    if(r > .000000000000000001){
      norm->p[0] /= r;
      norm->p[1] /= r;
      norm->p[2] /= r;
    }
    n = norm;
  }
};

template<typename T>
class cube {
private:
  int generation;
  T resolution;
  T xmin, ymin, zmin;
  T xmax, ymax, zmax;
  vector<cube<T>*> div;
public:
  cube(T p_xmin, T p_ymin, T p_zmin, T p_xmax, T p_ymax, T p_zmax, int p_generation = 0, T p_resolution = 1e-2):
    xmin(p_xmin),
    ymin(p_ymin),
    zmin(p_zmin),
    xmax(p_xmax),
    ymax(p_ymax),
    zmax(p_zmax),
    generation(p_generation),
    resolution(p_resolution)
  {

  }
  vector<Vertex<T> > const * toVertex(T (*func)(T, T, T)) const {
    vector<Vertex<T> > * vertex = new vector<Vertex<T> >();
    vertex->push_back(Vertex<T>(xmin,ymin,zmin,(*func)(xmin,ymin,zmin)));
    vertex->push_back(Vertex<T>(xmax,ymin,zmin,(*func)(xmax,ymin,zmin)));
    vertex->push_back(Vertex<T>(xmin,ymax,zmin,(*func)(xmin,ymax,zmin)));
    vertex->push_back(Vertex<T>(xmax,ymax,zmin,(*func)(xmax,ymax,zmin)));
    vertex->push_back(Vertex<T>(xmin,ymin,zmax,(*func)(xmin,ymin,zmax)));
    vertex->push_back(Vertex<T>(xmax,ymin,zmax,(*func)(xmax,ymin,zmax)));
    vertex->push_back(Vertex<T>(xmin,ymax,zmax,(*func)(xmin,ymax,zmax)));
    vertex->push_back(Vertex<T>(xmax,ymax,zmax,(*func)(xmax,ymax,zmax)));
    return vertex;
  }
  bool division_condition(T (*func)(T, T, T)) const {
    if(fabs(xmax-xmin) < resolution || fabs(ymax-ymin) < resolution || fabs(zmax-zmin) < resolution) {
      return false;
    }
    if(generation < 2) return true;
    bool result = (*func)(xmax, ymax, zmax) > 0.0;
    for(T y=ymin;y<ymax;y+=resolution) {
      for(T z=zmin;z<zmax;z+=resolution) {
        if(result != ((*func)(xmin, y, z) > 0.0)) return true;
      }
    }
    for(T y=ymin;y<ymax;y+=resolution) {
      for(T z=zmin;z<zmax;z+=resolution) {
        if(result != ((*func)(xmax, y, z) > 0.0)) return true;
      }
    }
    for(T x=xmin;x<xmax;x+=resolution) {
      for(T z=zmin;z<zmax;z+=resolution) {
        if(result != ((*func)(x, ymin, z) > 0.0)) return true;
      }
    }
    for(T x=xmin;x<xmax;x+=resolution) {
      for(T z=zmin;z<zmax;z+=resolution) {
        if(result != ((*func)(x, ymax, z) > 0.0)) return true;
      }
    }
    for(T x=xmin;x<xmax;x+=resolution) {
      for(T y=ymin;y<ymax;y+=resolution) {
        if(result != ((*func)(x, y, zmin) > 0.0)) return true;
      }
    }
    for(T x=xmin;x<xmax;x+=resolution) {
      for(T y=ymin;y<ymax;y+=resolution) {
        if(result != ((*func)(x, y, zmax) > 0.0)) return true;
      }
    }
    return false;
  }
  void subdivide() {
    T xmid = 0.5*(xmin+xmax);
    T ymid = 0.5*(ymin+ymax);
    T zmid = 0.5*(zmin+zmax);
    div.push_back(new cube<T>(xmin,ymin,zmin,xmid,ymid,zmid,generation+1,resolution));
    div.push_back(new cube<T>(xmid,ymin,zmin,xmax,ymid,zmid,generation+1,resolution));
    div.push_back(new cube<T>(xmin,ymid,zmin,xmid,ymax,zmid,generation+1,resolution));
    div.push_back(new cube<T>(xmid,ymid,zmin,xmax,ymax,zmid,generation+1,resolution));
    div.push_back(new cube<T>(xmin,ymin,zmid,xmid,ymid,zmax,generation+1,resolution));
    div.push_back(new cube<T>(xmid,ymin,zmid,xmax,ymid,zmax,generation+1,resolution));
    div.push_back(new cube<T>(xmin,ymid,zmid,xmid,ymax,zmax,generation+1,resolution));
    div.push_back(new cube<T>(xmid,ymid,zmid,xmax,ymax,zmax,generation+1,resolution));
  }
  vector<cube<T>*> const & getDiv() const {
    return div;
  }
  int get_generation() const {
    return generation;
  }
};

#endif

