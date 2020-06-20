#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "cube.h"

using namespace std;

/*
 *      v6------e2------v7
 *     / |              /|
 *   e11 |    f3      e10|
 *   /   e5     f5    /  e6
 *  /    |           /   | 
 *  v2------e1-------v3  |
 *  | f0 |           | f1|
 *  |   v4------e3---|---v5
 *  e4  /   f4      e7   /
 *  |  e8     f2     |  e9
 *  | /              | /    y z
 *  |/               |/     |/
 *  v0------e0-------v1     O--x
 */

static int faces[6][4] = {{0,2,6,4},{1,3,7,5},{0,4,5,1},{2,6,7,3},{0,1,3,2},{4,5,7,6}};

static int edges[12][2] = {{0,1},{2,3},{6,7},{4,5},{0,2},{4,6},{5,7},{1,3},{0,4},{1,5},{3,7},{2,6}};

static vector<vector<vector<int> > > cycleTable;

static void stringtok(vector<string> &v, string const &in,
               const char * const delim = " \t\n",
               bool includeDelim = false)
{
  const string::size_type len = in.length();
  string::size_type i;
  string::size_type j = 0;
  int k;

  while ( j < len )
  {
    // find the start of the token
    i = in.find_first_not_of(delim, j);
    
    if (i == string::npos) { // nothing left but delim
      if (includeDelim) {
        string s = in.substr(j);
        for (k = 0; k < s.length(); k++)
          v.push_back(s.substr(k,1));
      }
      return;
    } else
      if (includeDelim)
        if (i-j!=0) {
          string s = in.substr(j, i-j);
          for (k = 0; k < s.length(); k++)
            v.push_back(s.substr(k,1));
        }

    // find the end of the token
    j = in.find_first_of(delim, i);

    // push token
    if (j == string::npos) { // nothing left but a token
      v.push_back(in.substr(i));
      return;
    } else
      v.push_back(in.substr(i, j-i));
  }
}

static void initCycleTable(){

  string line;
  ifstream myfile ("cycleTable.txt");
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      vector<string> temp;
      stringtok(temp,line,"{}",false);
      vector<vector<int> > in1;
      for(int i=0;i<temp.size();i++){
        if(temp[i][0] != ','){
          vector<string> input;
          stringtok(input,temp[i],", ",false);
          vector<int> in2;
          for(int j=0;j<input.size();j++)
            in2.push_back(atoi(input[j].c_str()));
          in1.push_back(in2);
        }
      }
      cycleTable.push_back(in1);
    }
    myfile.close();
  }
  else cout << "Unable to open file" << endl; 


}

template<typename T>
vector<Triangle<T> *> marchingCubes(T (*func)(T x, T y, T z), cube<T>* node) {

  vector<Triangle<T> *> triangles;

  vector<Vertex<T> > const * vPtr = node->toVertex(func);
  vector<Vertex<T> > const & vertex = *vPtr;

  bool collision[8];
  for(int i=0;i<8;i++) {
    collision[i] = vertex[i].value > 0;
  }

  int index = 0;

  for(int i=1,j=0;i<256;i*=2,j++)
    if(collision[j])
      index += i;

  Vertex<T> const * a, * b;
  double wta, wtb, W;
  for(int i=0;i<cycleTable[index].size();i++){
    for(int j=1;j<cycleTable[index][i].size()-1;j++){
      Triangle<T>* face = new Triangle<T>();
     
      // 1
      a = &vertex[edges[cycleTable[index][i][j+1]][0]];
      b = &vertex[edges[cycleTable[index][i][j+1]][1]];
      wta = fabs(b->value);
      wtb = fabs(a->value);
      W = wta+wtb;
      wta /= W;
      wtb /= W;
      face->v.push_back(new Vertex<T>(
        wta*a->p[0] + wtb*b->p[0],
        wta*a->p[1] + wtb*b->p[1],
        wta*a->p[2] + wtb*b->p[2]
      ));

      // 2
      a = &vertex[edges[cycleTable[index][i][j]][0]];
      b = &vertex[edges[cycleTable[index][i][j]][1]];
      wta = fabs(b->value);
      wtb = fabs(a->value);
      W = wta+wtb;
      wta /= W;
      wtb /= W;
      face->v.push_back(new Vertex<T>(
        wta*a->p[0] + wtb*b->p[0],
        wta*a->p[1] + wtb*b->p[1],
        wta*a->p[2] + wtb*b->p[2]
      ));

      // 3
      a = &vertex[edges[cycleTable[index][i][0]][0]];
      b = &vertex[edges[cycleTable[index][i][0]][1]];
      wta = fabs(b->value);
      wtb = fabs(a->value);
      W = wta+wtb;
      wta /= W;
      wtb /= W;
      face->v.push_back(new Vertex<T>(
        wta*a->p[0] + wtb*b->p[0],
        wta*a->p[1] + wtb*b->p[1],
        wta*a->p[2] + wtb*b->p[2]
      ));

      face->setnormal();
      triangles.push_back(face);

    }
  }

  delete vPtr;

  return triangles;

}

#endif

