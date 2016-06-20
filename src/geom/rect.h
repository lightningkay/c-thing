#pragma once

#include "cthing.h"
#include "math/vec.h"
#include "mem/mpool.h"

CT_BEGIN_DECLS

typedef union {
  struct {
    CT_Vec2f p;
    CT_Vec2f q;
  };
  float buf[4];
} CT_Rect2f;

CT_Rect2f *ct_rect2fv(CT_Vec2f *p, CT_Vec2f *size, CT_MPool *mpool);
CT_Rect2f *ct_rect2fn(CT_Vec2f *p, float size, CT_MPool *mpool);

float ct_rect2f_area(CT_Rect2f *a);
int ct_rect2f_classify_point(CT_Rect2f *a, CT_Vec2f *p);

CT_END_DECLS
