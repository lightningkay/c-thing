#pragma once

#define CT_VERSION_MAJOR 0
#define CT_VERSION_MINOR 1

#if !defined(NO_SSE) && defined(__SSE__)
#define CT_USE_SSE
#endif

#if defined(CT_USE_SSE) && defined(__SSE2__)
#define CT_USE_SSE2
#endif

#define ct_inline static inline

#ifdef __EMSCRIPTEN__
#define CT_EXPORT __attribute__((used))
#else
#define CT_EXPORT
#endif