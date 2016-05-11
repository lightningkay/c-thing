#include <math.h>
#include <stdint.h>
#include "ct_math.h"
#include "vec.h"

CT_EXPORT CT_Vec2f *ct_vec2f(float x, float y, CT_MPool *mpool) {
    CT_Vec2f *v = ALLOCATE_TYPE(mpool, CT_Vec2f);
    if (v != NULL) {
        v->x = x;
        v->y = y;
    }
    return v;
}

CT_EXPORT CT_Vec2f *ct_vec2fn(float n, CT_MPool *mpool) {
    return ct_vec2f(n, n, mpool);
}

CT_EXPORT CT_Vec2f *ct_set2fv(CT_Vec2f *a, CT_Vec2f *b) {
    a->x = b->x;
    a->y = b->y;
    return a;
}

CT_EXPORT CT_Vec2f *ct_set2fxy(CT_Vec2f *v, float x, float y) {
    v->x = x;
    v->y = y;
    return v;
}

VEC2_SWIZZLE(CT_Vec2f, float, xx, f, 0, 0)
VEC2_SWIZZLE(CT_Vec2f, float, xy, f, 0, 1)
VEC2_SWIZZLE(CT_Vec2f, float, yx, f, 1, 0)
VEC2_SWIZZLE(CT_Vec2f, float, yy, f, 1, 1)

VEC2OP(CT_Vec2f, float, ct_add2f, +)
VEC2OP(CT_Vec2f, float, ct_sub2f, -)
VEC2OP(CT_Vec2f, float, ct_mul2f, *)
VEC2OP(CT_Vec2f, float, ct_div2f, / )

CT_EXPORT uint8_t ct_deltaeq2fv(CT_Vec2f *a, CT_Vec2f *b, float eps) {
    return (ct_deltaeqf(a->x, b->x, eps) && ct_deltaeqf(a->y, b->y, eps));
}

CT_EXPORT CT_Vec2f *ct_madd2fv_imm(CT_Vec2f *a, CT_Vec2f *b, CT_Vec2f *c) {
    a->x = a->x * b->x + c->x;
    a->y = a->y * b->y + c->y;
    return a;
}

CT_EXPORT CT_Vec2f *ct_madd2fv(CT_Vec2f *a, CT_Vec2f *b, CT_Vec2f *c,
                               CT_MPool *mpool) {
    return ct_madd2fv_imm(ct_set2fv(ALLOCATE_TYPE(mpool, CT_Vec2f), a), b, c);
}

CT_EXPORT float ct_dot2fv(CT_Vec2f *a, CT_Vec2f *b) {
    return a->x * b->x + a->y * b->y;
}

CT_EXPORT float ct_distsq2fv(CT_Vec2f *a, CT_Vec2f *b) {
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    return dx * dx + dy * dy;
}

CT_EXPORT float ct_dist2fv(CT_Vec2f *a, CT_Vec2f *b) {
    return sqrtf(ct_distsq2fv(a, b));
}

CT_EXPORT float ct_magsq2f(CT_Vec2f *v) {
    return v->x * v->x + v->y * v->y;
}

CT_EXPORT float ct_mag2f(CT_Vec2f *v) {
    return sqrtf(v->x * v->x + v->y * v->y);
}

CT_EXPORT CT_Vec2f *ct_mix2fv_imm(CT_Vec2f *a, CT_Vec2f *b, float t) {
    a->x = ct_mixf(a->x, b->x, t);
    a->y = ct_mixf(a->y, b->y, t);
    return a;
}

CT_EXPORT CT_Vec2f *ct_mix2fv(CT_Vec2f *a, CT_Vec2f *b, float t,
                              CT_MPool *mpool) {
    return ct_mix2fv_imm(ct_set2fv(ALLOCATE_TYPE(mpool, CT_Vec2f), a), b, t);
}

CT_EXPORT CT_Vec2f *ct_normalize2f_imm(CT_Vec2f *v, float len) {
    float m = ct_mag2f(v);
    if (m > 0.0) {
        len /= m;
        v->x *= len;
        v->y *= len;
    }
    return v;
}

CT_EXPORT CT_Vec2f *ct_normalize2f(CT_Vec2f *v, float len, CT_MPool *mpool) {
    return ct_normalize2f_imm(ct_set2fv(ALLOCATE_TYPE(mpool, CT_Vec2f), v),
                              len);
}

CT_EXPORT uint8_t ct_is_normalized2f(CT_Vec2f *v) {
    return ct_deltaeqf(ct_mag2f(v) - 1.f, 0.f, EPS);
}

////// Vec3f

CT_EXPORT CT_Vec3f *ct_vec3f(float x, float y, float z, CT_MPool *mpool) {
    CT_Vec3f *v = ALLOCATE_TYPE(mpool, CT_Vec3f);
    if (v != NULL) {
        v->x = x;
        v->y = y;
        v->z = z;
    }
    return v;
}

CT_EXPORT CT_Vec3f *ct_vec3fn(float n, CT_MPool *mpool) {
    return ct_vec3f(n, n, n, mpool);
}

CT_EXPORT CT_Vec3f *ct_set3fv(CT_Vec3f *a, CT_Vec3f *b) {
#ifdef CT_USE_SSE
    a->mmval = b->mmval;
#else
    a->x = b->x;
    a->y = b->y;
    a->z = b->z;
#endif
    return a;
}

CT_EXPORT CT_Vec3f *ct_set3fxyz(CT_Vec3f *v, float x, float y, float z) {
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

#ifdef CT_USE_SSE
VEC3OP_SSE(CT_Vec3f, float, ct_add3f, +)
VEC3OP_SSE(CT_Vec3f, float, ct_sub3f, -)
VEC3OP_SSE(CT_Vec3f, float, ct_mul3f, *)
VEC3OP_SSE(CT_Vec3f, float, ct_div3f, / )

VEC3_SWIZZLE_SSE(CT_Vec3f, xxx, f, 0, 0, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, xxy, f, 0, 0, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, xxz, f, 0, 0, 2)
VEC3_SWIZZLE_SSE(CT_Vec3f, xyx, f, 0, 1, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, xyy, f, 0, 1, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, xyz, f, 0, 1, 2)
VEC3_SWIZZLE_SSE(CT_Vec3f, xzx, f, 0, 2, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, xzy, f, 0, 2, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, xzz, f, 0, 2, 2)

VEC3_SWIZZLE_SSE(CT_Vec3f, yxx, f, 1, 0, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, yxy, f, 1, 0, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, yxz, f, 1, 0, 2)
VEC3_SWIZZLE_SSE(CT_Vec3f, yyx, f, 1, 1, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, yyy, f, 1, 1, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, yyz, f, 1, 1, 2)
VEC3_SWIZZLE_SSE(CT_Vec3f, yzx, f, 1, 2, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, yzy, f, 1, 2, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, yzz, f, 1, 2, 2)

VEC3_SWIZZLE_SSE(CT_Vec3f, zxx, f, 2, 0, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, zxy, f, 2, 0, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, zxz, f, 2, 0, 2)
VEC3_SWIZZLE_SSE(CT_Vec3f, zyx, f, 2, 1, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, zyy, f, 2, 1, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, zyz, f, 2, 1, 2)
VEC3_SWIZZLE_SSE(CT_Vec3f, zzx, f, 2, 2, 0)
VEC3_SWIZZLE_SSE(CT_Vec3f, zzy, f, 2, 2, 1)
VEC3_SWIZZLE_SSE(CT_Vec3f, zzz, f, 2, 2, 2)

#else

VEC3OP(CT_Vec3f, float, ct_add3f, +)
VEC3OP(CT_Vec3f, float, ct_sub3f, -)
VEC3OP(CT_Vec3f, float, ct_mul3f, *)
VEC3OP(CT_Vec3f, float, ct_div3f, / )

VEC3_SWIZZLE(CT_Vec3f, float, xxx, f, 0, 0, 0)
VEC3_SWIZZLE(CT_Vec3f, float, xxy, f, 0, 0, 1)
VEC3_SWIZZLE(CT_Vec3f, float, xxz, f, 0, 0, 2)
VEC3_SWIZZLE(CT_Vec3f, float, xyx, f, 0, 1, 0)
VEC3_SWIZZLE(CT_Vec3f, float, xyy, f, 0, 1, 1)
VEC3_SWIZZLE(CT_Vec3f, float, xyz, f, 0, 1, 2)
VEC3_SWIZZLE(CT_Vec3f, float, xzx, f, 0, 2, 0)
VEC3_SWIZZLE(CT_Vec3f, float, xzy, f, 0, 2, 1)
VEC3_SWIZZLE(CT_Vec3f, float, xzz, f, 0, 2, 2)

VEC3_SWIZZLE(CT_Vec3f, float, yxx, f, 1, 0, 0)
VEC3_SWIZZLE(CT_Vec3f, float, yxy, f, 1, 0, 1)
VEC3_SWIZZLE(CT_Vec3f, float, yxz, f, 1, 0, 2)
VEC3_SWIZZLE(CT_Vec3f, float, yyx, f, 1, 1, 0)
VEC3_SWIZZLE(CT_Vec3f, float, yyy, f, 1, 1, 1)
VEC3_SWIZZLE(CT_Vec3f, float, yyz, f, 1, 1, 2)
VEC3_SWIZZLE(CT_Vec3f, float, yzx, f, 1, 2, 0)
VEC3_SWIZZLE(CT_Vec3f, float, yzy, f, 1, 2, 1)
VEC3_SWIZZLE(CT_Vec3f, float, yzz, f, 1, 2, 2)

VEC3_SWIZZLE(CT_Vec3f, float, zxx, f, 2, 0, 0)
VEC3_SWIZZLE(CT_Vec3f, float, zxy, f, 2, 0, 1)
VEC3_SWIZZLE(CT_Vec3f, float, zxz, f, 2, 0, 2)
VEC3_SWIZZLE(CT_Vec3f, float, zyx, f, 2, 1, 0)
VEC3_SWIZZLE(CT_Vec3f, float, zyy, f, 2, 1, 1)
VEC3_SWIZZLE(CT_Vec3f, float, zyz, f, 2, 1, 2)
VEC3_SWIZZLE(CT_Vec3f, float, zzx, f, 2, 2, 0)
VEC3_SWIZZLE(CT_Vec3f, float, zzy, f, 2, 2, 1)
VEC3_SWIZZLE(CT_Vec3f, float, zzz, f, 2, 2, 2)
#endif

CT_EXPORT uint8_t ct_deltaeq3fv(CT_Vec3f *a, CT_Vec3f *b, float eps) {
    return (ct_deltaeqf(a->x, b->x, eps) && ct_deltaeqf(a->y, b->y, eps) &&
            ct_deltaeqf(a->z, b->z, eps));
}

CT_EXPORT CT_Vec3f *ct_madd3fv_imm(CT_Vec3f *a, CT_Vec3f *b, CT_Vec3f *c) {
    a->x = a->x * b->x + c->x;
    a->y = a->y * b->y + c->y;
    a->z = a->z * b->z + c->z;
    return a;
}

CT_EXPORT CT_Vec3f *ct_madd3fv(CT_Vec3f *a, CT_Vec3f *b, CT_Vec3f *c,
                               CT_MPool *mpool) {
    return ct_madd3fv_imm(ct_set3fv(ALLOCATE_TYPE(mpool, CT_Vec3f), a), b, c);
}

CT_EXPORT float ct_dot3fv(CT_Vec3f *a, CT_Vec3f *b) {
#ifdef CT_USE_SSE
    __m128 d = a->mmval * b->mmval;
    return d[0] + d[1] + d[2];
#else
    return a->x * b->x + a->y * b->y + a->z * b->z;
#endif
}

CT_EXPORT CT_Vec3f *ct_cross3fv_imm(CT_Vec3f *a, CT_Vec3f *b) {
#ifdef CT_USE_SSE
    __m128 v = _mm_sub_ps(
        _mm_mul_ps(a->mmval,
                   _mm_shuffle_ps(b->mmval, b->mmval, _MM_SHUFFLE(3, 0, 2, 1))),
        _mm_mul_ps(b->mmval, _mm_shuffle_ps(a->mmval, a->mmval,
                                            _MM_SHUFFLE(3, 0, 2, 1))));
    a->mmval = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1));
    return a;
#else
    float x = a->y * b->z - a->z * b->y;
    float y = a->z * b->x - a->x * b->z;
    a->z = a->x * b->y - a->y * b->x;
    a->y = y;
    a->x = x;
    return a;
#endif
}

CT_EXPORT CT_Vec3f *ct_cross3fv(CT_Vec3f *a, CT_Vec3f *b, CT_MPool *mpool) {
    CT_Vec3f *v = ALLOCATE_TYPE(mpool, CT_Vec3f);
    v->x = a->y * b->z - a->z * b->y;
    v->y = a->z * b->x - a->x * b->z;
    v->z = a->x * b->y - a->y * b->x;
    return v;
}

CT_EXPORT float ct_distsq3fv(CT_Vec3f *a, CT_Vec3f *b) {
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;
    return dx * dx + dy * dy + dz * dz;
}

CT_EXPORT float ct_dist3fv(CT_Vec3f *a, CT_Vec3f *b) {
    return sqrtf(ct_distsq3fv(a, b));
}

CT_EXPORT float ct_magsq3f(CT_Vec3f *v) {
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

CT_EXPORT float ct_mag3f(CT_Vec3f *v) {
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

CT_EXPORT CT_Vec3f *ct_mix3fv_imm(CT_Vec3f *a, CT_Vec3f *b, float t) {
    a->x = ct_mixf(a->x, b->x, t);
    a->y = ct_mixf(a->y, b->y, t);
    a->z = ct_mixf(a->z, b->z, t);
    return a;
}

CT_EXPORT CT_Vec3f *ct_mix3fv(CT_Vec3f *a, CT_Vec3f *b, float t,
                              CT_MPool *mpool) {
    return ct_mix3fv_imm(ct_set3fv(ALLOCATE_TYPE(mpool, CT_Vec3f), a), b, t);
}

CT_EXPORT CT_Vec3f *ct_normalize3f_imm(CT_Vec3f *v, float len) {
    float m = ct_mag3f(v);
    if (m > 0.0) {
        len /= m;
        v->x *= len;
        v->y *= len;
        v->z *= len;
    }
    return v;
}

CT_EXPORT CT_Vec3f *ct_normalize3f(CT_Vec3f *v, float len, CT_MPool *mpool) {
    return ct_normalize3f_imm(ct_set3fv(ALLOCATE_TYPE(mpool, CT_Vec3f), v),
                              len);
}

CT_EXPORT uint8_t ct_is_normalized3f(CT_Vec3f *v) {
    return ct_deltaeqf(ct_mag3f(v) - 1.f, 0.f, EPS);
}
