#include "geometry.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

point3d_t corss(point3d_t v1, point3d_t v2) {
  point3d_t result;
  result.x = v1.y * v2.z - v1.z * v2.y;
  result.y = v1.z * v2.x - v1.x * v2.z;
  result.z = v1.x * v2.y - v1.y * v2.x;
  return result;
}

double dot(point3d_t v1, point3d_t v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

bool points_on_same_plane(const point3d_t A, const point3d_t B,
                          const point3d_t C, const point3d_t D) {

  point3d_t AB = {B.x - A.x, B.y - A.y, B.z - A.z};
  point3d_t AC = {C.x - A.x, C.y - A.y, C.z - A.z};
  point3d_t AD = {D.x - A.x, D.y - A.y, D.z - A.z};

  point3d_t cross_AB_AC = corss(AB, AC);
  double triple_product = dot(cross_AB_AC, AD);

  return triple_product == 0.0;
}

void equation_sphere_from_4points(const point3d_t A, const point3d_t B,
                                  const point3d_t C, const point3d_t D,
                                  sphere_t *sphere) {
  if (points_on_same_plane(A, B, C, D)) {
    fprintf(stderr, "Points are on the same plane\n");
    return;
  }

  double asqrt = pow(A.x, 2) + pow(A.y, 2) + pow(A.z, 2);
  double bsqrt = pow(B.x, 2) + pow(B.y, 2) + pow(B.z, 2);
  double csqrt = pow(C.x, 2) + pow(C.y, 2) + pow(C.z, 2);
  double dsqrt = pow(D.x, 2) + pow(D.y, 2) + pow(D.z, 2);

  double mm11[4][4] = {
      {A.x, A.y, A.z, 1},
      {B.x, B.y, B.z, 1},
      {C.x, C.y, C.z, 1},
      {D.x, D.y, D.z, 1},
  };
  double mm12[4][4] = {
      {asqrt, A.y, A.z, 1},
      {bsqrt, B.y, B.z, 1},
      {csqrt, C.y, C.z, 1},
      {dsqrt, D.y, D.z, 1},
  };
  double mm13[4][4] = {
      {asqrt, A.x, A.z, 1},
      {bsqrt, B.x, B.z, 1},
      {csqrt, C.x, C.z, 1},
      {dsqrt, D.x, D.z, 1},
  };
  double mm14[4][4] = {
      {asqrt, A.x, A.y, 1},
      {bsqrt, B.x, B.y, 1},
      {csqrt, C.x, C.y, 1},
      {dsqrt, D.x, D.y, 1},
  };
  double mm15[4][4] = {
      {asqrt, A.x, A.y, A.z},
      {bsqrt, B.x, B.y, B.z},
      {csqrt, C.x, C.y, C.z},
      {dsqrt, D.x, D.y, D.z},
  };

  double m11, m12, m13, m14, m15;
  

  double x0 = 0.5 * m12 / m11;
  double y0 = -0.5 * m13 / m11;
  double z0 = 0.5 * m14 / m11;
  double r = sqrt(x0 * x0 + y0 * y0 + z0 * z0 - m15 / m11);
}