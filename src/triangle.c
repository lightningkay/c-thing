#include "triangle.h"

CT_EXPORT CT_Triangle2f *ct_triangle2f_init(CT_Triangle2f *t, CT_Vec2f *a,
                                            CT_Vec2f *b, CT_Vec2f *c) {
  t->a = *a;
  t->b = *b;
  t->c = *c;
  return t;
}

CT_EXPORT CT_Triangle2f *ct_triangle2f_initpv(CT_Triangle2f *t,
                                              CT_Vec2f *points) {
  t->a = *points++;
  t->b = *points++;
  t->c = *points;
  return t;
}

CT_EXPORT CT_Triangle2f *ct_triangle2f_initpf(CT_Triangle2f *t, float *coords) {
  t->buf[0] = *coords++;
  t->buf[1] = *coords++;
  t->buf[2] = *coords++;
  t->buf[3] = *coords++;
  t->buf[4] = *coords++;
  t->buf[5] = *coords;
  return t;
}

float ct_triangle2f_normsign(CT_Triangle2f *t) {
  return (t->b.x - t->a.x) * (t->c.y - t->a.y) -
         (t->c.x - t->a.x) * (t->b.y - t->a.y);
}

CT_EXPORT float ct_triangle2f_area(CT_Triangle2f *t) {
  return 0.5f * ct_triangle2f_normsign(t);
}

CT_EXPORT float ct_triangle2f_circumference(CT_Triangle2f *t) {
  return ct_dist2fv(&t->a, &t->b) + ct_dist2fv(&t->b, &t->c) +
         ct_dist2fv(&t->c, &t->a);
}

CT_EXPORT size_t ct_triangle2f_is_clockwise(CT_Triangle2f *t) {
  return ct_triangle2f_normsign(t) < 0.f;
}

CT_EXPORT CT_Triangle3f *ct_triangle3f_init(CT_Triangle3f *t, CT_Vec3f *a,
                                            CT_Vec3f *b, CT_Vec3f *c) {
  t->a = *a;
  t->b = *b;
  t->c = *c;
  return t;
}

CT_EXPORT CT_Triangle3f *ct_triangle3f_initpv(CT_Triangle3f *t,
                                              CT_Vec3f *points) {
  t->a = *points++;
  t->b = *points++;
  t->c = *points;
  return t;
}

CT_EXPORT CT_Triangle3f *ct_triangle3f_initpf(CT_Triangle3f *t, float *coords) {
  t->a.x = *coords++;
  t->a.y = *coords++;
  t->a.z = *coords++;
  t->b.x = *coords++;
  t->b.y = *coords++;
  t->b.z = *coords++;
  t->c.x = *coords++;
  t->c.y = *coords++;
  t->c.z = *coords;
  return t;
}

CT_EXPORT CT_Vec3f *ct_triangle3f_normal(CT_Triangle3f *t, CT_Vec3f *out,
                                         size_t normalize) {
  CT_Vec3f ba, ca;
  ct_cross3fv(ct_sub3fv(&t->b, &t->a, &ba), ct_sub3fv(&t->c, &t->a, &ca), out);
  if (normalize) {
    ct_normalize3f_imm(out, 1.f);
  }
  return out;
}

float ct_triangle3f_normsign(CT_Triangle3f *t) {
  CT_Vec3f n;
  return ct_mag3f(ct_triangle3f_normal(t, &n, 0));
}

CT_EXPORT float ct_triangle3f_area(CT_Triangle3f *t) {
  return 0.5f * ct_triangle3f_normsign(t);
}

CT_EXPORT float ct_triangle3f_circumference(CT_Triangle3f *t) {
  return ct_dist3fv(&t->a, &t->b) + ct_dist3fv(&t->b, &t->c) +
         ct_dist3fv(&t->c, &t->a);
}

CT_EXPORT size_t ct_triangle3f_is_clockwise(CT_Triangle3f *t, CT_Vec3f *n) {
  CT_Vec3f tn;
  return ct_dot3fv(ct_triangle3f_normal(t, &tn, 0), n) > 0.f;
}
