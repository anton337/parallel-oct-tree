#ifndef OCT_TREE_H
#define OCT_TREE_H

#include <map>
#include <stdio.h>
#include <deque>
#include "marching_cubes.h"
#include "producer_consumer_queue.h"
#include <boost/thread.hpp>
#include "vbo.h"

using namespace boost;
using namespace std;

template<typename T>
class oct_tree {
private:
  int max_generation;
  cube<T>* root;
  vector<ProducerConsumerQueue<cube<T> > * > queues;
  vector<boost::thread* > threads;
  vector<Triangle<T>* > triangles;
  boost::mutex draw_mutex;
  VBOFactory<T> * vbo_factory = NULL;
  bool vbo_draw = false;
public:
  oct_tree( T p_xmin
          , T p_ymin
          , T p_zmin
          , T p_xmax
          , T p_ymax
          , T p_zmax
          , int p_max_generation = 15
          , T resolution = 1e-3
          )
    : root(new cube<T>( p_xmin
                      , p_ymin
                      , p_zmin
                      , p_xmax
                      , p_ymax
                      , p_zmax
                      , 0 // initial generation
                      , resolution
                      )
          )
    , max_generation(p_max_generation)
  {
    initCycleTable();
  }
  void run( vector<ProducerConsumerQueue<cube<T> > * > & Q
          , int id
          , int max_generation
          , T (*func)(T, T, T)
          ) 
  {
    while(true) {
      cube<T>* node = Q[id%Q.size()]->get();
      if(node->get_generation() == max_generation) {
        vector<Triangle<T> *> const & vec = marchingCubes(func, node);
        {
          boost::unique_lock<boost::mutex> lock(draw_mutex);
          for(Triangle<T> * tri : vec) {
            triangles.push_back(tri);
          }
        }
      }
      if(node->division_condition(func) && node->get_generation() < max_generation) {
        node->subdivide();
        for(cube<T> * d : node->getDiv()) {
          Q[rand()%Q.size()]->put(d);
        }
      }
    }
  }
  void subdivide(T (*func)(T, T, T)) {
    int nthreads = boost::thread::hardware_concurrency();
    for(int i=0;i<nthreads;i++) {
      queues.push_back(new ProducerConsumerQueue<cube<T> >());
    }
    for(int i=0;i<nthreads;i++) {
      threads.push_back(new thread(bind(&oct_tree::run
                                       , this
                                       , queues
                                       , i
                                       , max_generation
                                       , func
                                       )
                                  )
                       );
    }
    queues[0]->put(root);
  }
  void write(string name) {
    std::cout << "writing to file:" << name << std::endl;
    const int SCALAR = 1000000;
    vector<Triangle<T>*> _face;
    vector<Vertex<T>*> _vertex;
    map<int,map<int,map<int,Vertex<T>*> > > vertMap;
    for(int i=0;i<triangles.size();i++) {
      for(int j=0;j<triangles[i]->v.size();j++) {
        int X = triangles[i]->v[j]->p[0] * SCALAR;
        int Y = triangles[i]->v[j]->p[1] * SCALAR;
        int Z = triangles[i]->v[j]->p[2] * SCALAR;
        vertMap[X][Y][Z] = triangles[i]->v[j];
      }
    }
    for(int i=0;i<triangles.size();i++) {
      Triangle<T>* f = new Triangle<T>();
      for(int j=0;j<triangles[i]->v.size();j++) {
        int X = triangles[i]->v[j]->p[0] * SCALAR;
        int Y = triangles[i]->v[j]->p[1] * SCALAR;
        int Z = triangles[i]->v[j]->p[2] * SCALAR;
        f->v.push_back(vertMap[X][Y][Z]);
      }
      _face.push_back(f);
    }
    typename map<int,map<int,map<int,Vertex<T>*> > >::iterator it = vertMap.begin();
    while(it != vertMap.end()) {
      typename map<int,map<int,Vertex<T>*> >::iterator it0 = it->second.begin();
      while(it0 != it->second.end()) {
        typename map<int,Vertex<T>*>::iterator it1 = it0->second.begin();
        while(it1 != it0->second.end()) {
          _vertex.push_back(it1->second);
          it1++;
        }
        it0++;
      }
      it++;
    }
    ofstream out(name.c_str());
    for(int i=0;i<_vertex.size();i++) {
      _vertex[i]->index = i+1;
      out << "v " << _vertex[i]->p[0] << " " << _vertex[i]->p[1] << " " << _vertex[i]->p[2] << endl;
    }
    for(int i=0;i<_face.size();i++) {
      out << "f ";
      for(int j=0;j<_face[i]->v.size();j++) {
        out << _face[i]->v[j]->index << " ";
      }
      out << endl;
    }
    out.close();
    std::cout << "finished writing:" << name << std::endl;
  }
  void draw() {
    if(vbo_draw == false) {
      {
        boost::unique_lock<boost::mutex> lock(draw_mutex);
        for(Triangle<T> * tri : triangles) {
          glBegin(GL_POLYGON);
          glNormal3f(tri->n->p[0],tri->n->p[1],tri->n->p[2]);
          glVertex3f(tri->v[0]->p[0],tri->v[0]->p[1],tri->v[0]->p[2]);
          glNormal3f(tri->n->p[0],tri->n->p[1],tri->n->p[2]);
          glVertex3f(tri->v[1]->p[0],tri->v[1]->p[1],tri->v[1]->p[2]);
          glNormal3f(tri->n->p[0],tri->n->p[1],tri->n->p[2]);
          glVertex3f(tri->v[2]->p[0],tri->v[2]->p[1],tri->v[2]->p[2]);
          glEnd();
        }
      }
      sleep(1);
    } else {
      if(vbo_factory == NULL) {
        vbo_factory = new VBOFactory<T>();
      }
      vbo_factory->build(triangles);
    }
  }
  void enable_vbo_draw() {
    vbo_draw = true;
  }
};

#endif

