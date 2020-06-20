#ifndef VBO_H
#define VBO_H

class CVec {
public:
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

template<typename T>
class VBOFactory {

private:
  CVec* Vertices = NULL;
  CVec* Normals  = NULL;

  size_t nTriangles = -1;
  GLuint nVBOVertices;
  GLuint nVBONormals;

public:
  void build(vector<Triangle<T>*> const & triangles, bool init = false) {
    if(init == true || Vertices == NULL) {

      nTriangles   = triangles.size();
      Vertices = new CVec[3*nTriangles];
      Normals  = new CVec[3*nTriangles];
      size_t i = 0;
      for(Triangle<T> * tri : triangles) {
        for(int j=0;j<3;j++) {
          Vertices[i+j].x = tri->v[j]->p[0];
          Vertices[i+j].y = tri->v[j]->p[1];
          Vertices[i+j].z = tri->v[j]->p[2];
          Normals [i+j].x = tri->n->p[0];
          Normals [i+j].y = tri->n->p[1];
          Normals [i+j].z = tri->n->p[2];
        }
        i += 3;
      }

      glGenBuffersARB( 1, &nVBOVertices );
      glBindBufferARB( GL_ARRAY_BUFFER_ARB, nVBOVertices );
      glBufferDataARB( GL_ARRAY_BUFFER_ARB, 9*nTriangles*sizeof(float), Vertices, GL_STATIC_DRAW_ARB );

      glGenBuffersARB( 1, &nVBONormals );
      glBindBufferARB( GL_ARRAY_BUFFER_ARB, nVBONormals );
      glBufferDataARB( GL_ARRAY_BUFFER_ARB, 9*nTriangles*sizeof(float), Normals, GL_STATIC_DRAW_ARB );

    }

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, nVBOVertices );
    glVertexPointer( 3, GL_FLOAT, 0, (char *)NULL );
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, nVBONormals );
    glNormalPointer( GL_FLOAT, 0, (char *)NULL );
    glDrawArrays( GL_TRIANGLES, 0, nTriangles * 3 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );

  }

};

#endif

