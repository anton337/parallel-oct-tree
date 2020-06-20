#include <math.h>
#include <stdio.h>
#include "common.h"
#include "cube.h"
#include "oct_tree.h"

#include ISOFUNCTION

oct_tree<double> tree(-1,-1,-1,1,1,1,  10,  5e-4);

void initialize() {
  tree.subdivide(isofunction);
}

void draw() {
  tree.draw();
}

void save() {
  tree.write("out.obj");
}

void vbo() {
  tree.enable_vbo_draw();
}

