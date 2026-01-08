/*
 * MSVC compatibility header for liquid-dsp
 *
 * Provides complex number operations for MSVC which doesn't support C99 _Complex
 */

#ifndef LIQUID_MSVC_COMPAT_H
#define LIQUID_MSVC_COMPAT_H

#ifdef _MSC_VER

#include <math.h>

/* Math constants not defined in MSVC */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2 0.70710678118654752440
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifndef M_LN2
#define M_LN2 0.69314718055994530942
#endif

#ifndef M_LN10
#define M_LN10 2.30258509299404568402
#endif

/* Complex number type (struct-based for MSVC C) */
typedef struct { float real; float imag; } liquid_float_complex;
typedef struct { double real; double imag; } liquid_double_complex;

/* Imaginary unit */
static const liquid_float_complex _Complex_I_f = {0.0f, 1.0f};
static const liquid_double_complex _Complex_I_d = {0.0, 1.0};
#define _Complex_I _Complex_I_f

/* Complex constructors */
static __inline liquid_float_complex liquid_float_complex_create(float r, float i) {
    liquid_float_complex c = {r, i};
    return c;
}

static __inline liquid_double_complex liquid_double_complex_create(double r, double i) {
    liquid_double_complex c = {r, i};
    return c;
}

/* Real and imaginary part access */
#define crealf(z) ((z).real)
#define cimagf(z) ((z).imag)
#define creal(z)  ((z).real)
#define cimag(z)  ((z).imag)

/* Complex absolute value */
static __inline float cabsf(liquid_float_complex z) {
    return sqrtf(z.real * z.real + z.imag * z.imag);
}

static __inline double cabs(liquid_double_complex z) {
    return sqrt(z.real * z.real + z.imag * z.imag);
}

/* Complex argument (phase) */
static __inline float cargf(liquid_float_complex z) {
    return atan2f(z.imag, z.real);
}

static __inline double carg(liquid_double_complex z) {
    return atan2(z.imag, z.real);
}

/* Complex conjugate */
static __inline liquid_float_complex conjf(liquid_float_complex z) {
    liquid_float_complex c = {z.real, -z.imag};
    return c;
}

static __inline liquid_double_complex conj(liquid_double_complex z) {
    liquid_double_complex c = {z.real, -z.imag};
    return c;
}

/* Complex exponential */
static __inline liquid_float_complex cexpf(liquid_float_complex z) {
    float r = expf(z.real);
    liquid_float_complex c = {r * cosf(z.imag), r * sinf(z.imag)};
    return c;
}

static __inline liquid_double_complex cexp(liquid_double_complex z) {
    double r = exp(z.real);
    liquid_double_complex c = {r * cos(z.imag), r * sin(z.imag)};
    return c;
}

/* Complex logarithm */
static __inline liquid_float_complex clogf(liquid_float_complex z) {
    liquid_float_complex c = {logf(cabsf(z)), cargf(z)};
    return c;
}

static __inline liquid_double_complex clog(liquid_double_complex z) {
    liquid_double_complex c = {log(cabs(z)), carg(z)};
    return c;
}

/* Complex square root */
static __inline liquid_float_complex csqrtf(liquid_float_complex z) {
    float r = cabsf(z);
    float t = cargf(z) / 2.0f;
    float sr = sqrtf(r);
    liquid_float_complex c = {sr * cosf(t), sr * sinf(t)};
    return c;
}

static __inline liquid_double_complex csqrt(liquid_double_complex z) {
    double r = cabs(z);
    double t = carg(z) / 2.0;
    double sr = sqrt(r);
    liquid_double_complex c = {sr * cos(t), sr * sin(t)};
    return c;
}

/* Complex sine/cosine */
static __inline liquid_float_complex csinf(liquid_float_complex z) {
    liquid_float_complex c = {sinf(z.real) * coshf(z.imag), cosf(z.real) * sinhf(z.imag)};
    return c;
}

static __inline liquid_float_complex ccosf(liquid_float_complex z) {
    liquid_float_complex c = {cosf(z.real) * coshf(z.imag), -sinf(z.real) * sinhf(z.imag)};
    return c;
}

/* Complex arithmetic - addition */
static __inline liquid_float_complex liquid_cf_add(liquid_float_complex a, liquid_float_complex b) {
    liquid_float_complex c = {a.real + b.real, a.imag + b.imag};
    return c;
}

static __inline liquid_double_complex liquid_cd_add(liquid_double_complex a, liquid_double_complex b) {
    liquid_double_complex c = {a.real + b.real, a.imag + b.imag};
    return c;
}

/* Complex arithmetic - subtraction */
static __inline liquid_float_complex liquid_cf_sub(liquid_float_complex a, liquid_float_complex b) {
    liquid_float_complex c = {a.real - b.real, a.imag - b.imag};
    return c;
}

static __inline liquid_double_complex liquid_cd_sub(liquid_double_complex a, liquid_double_complex b) {
    liquid_double_complex c = {a.real - b.real, a.imag - b.imag};
    return c;
}

/* Complex arithmetic - multiplication */
static __inline liquid_float_complex liquid_cf_mul(liquid_float_complex a, liquid_float_complex b) {
    liquid_float_complex c = {a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real};
    return c;
}

static __inline liquid_double_complex liquid_cd_mul(liquid_double_complex a, liquid_double_complex b) {
    liquid_double_complex c = {a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real};
    return c;
}

/* Complex arithmetic - division */
static __inline liquid_float_complex liquid_cf_div(liquid_float_complex a, liquid_float_complex b) {
    float denom = b.real * b.real + b.imag * b.imag;
    liquid_float_complex c = {(a.real * b.real + a.imag * b.imag) / denom,
                               (a.imag * b.real - a.real * b.imag) / denom};
    return c;
}

static __inline liquid_double_complex liquid_cd_div(liquid_double_complex a, liquid_double_complex b) {
    double denom = b.real * b.real + b.imag * b.imag;
    liquid_double_complex c = {(a.real * b.real + a.imag * b.imag) / denom,
                                (a.imag * b.real - a.real * b.imag) / denom};
    return c;
}

/* Scalar multiplication */
static __inline liquid_float_complex liquid_cf_mulf(liquid_float_complex a, float s) {
    liquid_float_complex c = {a.real * s, a.imag * s};
    return c;
}

static __inline liquid_double_complex liquid_cd_muld(liquid_double_complex a, double s) {
    liquid_double_complex c = {a.real * s, a.imag * s};
    return c;
}

/* Negation */
static __inline liquid_float_complex liquid_cf_neg(liquid_float_complex a) {
    liquid_float_complex c = {-a.real, -a.imag};
    return c;
}

static __inline liquid_double_complex liquid_cd_neg(liquid_double_complex a) {
    liquid_double_complex c = {-a.real, -a.imag};
    return c;
}

#endif /* _MSC_VER */

#endif /* LIQUID_MSVC_COMPAT_H */
