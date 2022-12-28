/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: currentControlDynamic.c
 *
 * Code generated for Simulink model 'currentControlDynamic'.
 *
 * Model version                  : 2.37
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Dec 26 17:40:06 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "currentControlDynamic.h"
#include "rtwtypes.h"
#include "currentControlDynamic_private.h"
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include <float.h>

/* Block states (default storage) */
DW_currentControlDynamic_T currentControlDynamic_DW;

/* External inputs (root inport signals with default storage) */
ExtU_currentControlDynamic_T currentControlDynamic_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_currentControlDynamic_T currentControlDynamic_Y;

/* Real-time model */
static RT_MODEL_currentControlDynami_T currentControlDynamic_M_;
RT_MODEL_currentControlDynami_T *const currentControlDynamic_M =
  &currentControlDynamic_M_;

/* Forward declaration for local functions */
static real_T currentControlDynamic_xnrm2(int32_T n, const real_T x[42], int32_T
  ix0);
static void currentControlDynamic_xscal(int32_T n, real_T a, real_T x[42],
  int32_T ix0);
static real_T currentControlDynamic_xnrm2_l(int32_T n, const real_T x[6],
  int32_T ix0);
static void currentControlDynamic_xscal_o(int32_T n, real_T a, real_T x[6],
  int32_T ix0);
static void currentControlDynamic_xaxpy_bk(int32_T n, real_T a, const real_T x[7],
  int32_T ix0, real_T y[42], int32_T iy0);
static void currentControlDynamic_xaxpy_b(int32_T n, real_T a, const real_T x[42],
  int32_T ix0, real_T y[7], int32_T iy0);
static real_T currentControlDynamic_xdotc(int32_T n, const real_T x[42], int32_T
  ix0, const real_T y[42], int32_T iy0);
static void currentControlDynamic_xaxpy(int32_T n, real_T a, int32_T ix0, real_T
  y[42], int32_T iy0);
static real_T currentControlDynamic_xdotc_b(int32_T n, const real_T x[36],
  int32_T ix0, const real_T y[36], int32_T iy0);
static void currentControlDynamic_xaxpy_bk4(int32_T n, real_T a, int32_T ix0,
  real_T y[36], int32_T iy0);
static void currentControlDynamic_xscal_op(real_T a, real_T x[42], int32_T ix0);
static void currentControlDynamic_xscal_opv(real_T a, real_T x[36], int32_T ix0);
static void currentControlDynamic_xswap(real_T x[36], int32_T ix0, int32_T iy0);
static void currentControlDynamic_xswap_n(real_T x[42], int32_T ix0, int32_T iy0);
static void currentControlDynamic_xrotg(real_T *a, real_T *b, real_T *c, real_T *
  s);
static void currentControlDynamic_xrot(real_T x[36], int32_T ix0, int32_T iy0,
  real_T c, real_T s);
static void currentControlDynamic_xrot_i(real_T x[42], int32_T ix0, int32_T iy0,
  real_T c, real_T s);
static void currentControlDynamic_svd(const real_T A[42], real_T U[42], real_T
  s[6], real_T V[36]);

/*
 * Output and update for atomic system:
 *    '<Root>/Inverse Park Transformation dq'
 *    '<Root>/Inverse Park Transformation xy'
 *    '<Root>/Inverse Park Transformation xy1'
 */
void cur_InverseParkTransformationdq(real_T rtu_u, real_T rtu_u_b, real_T
  rtu_theta, real_T rty_y[2])
{
  real_T ab_tmp;
  real_T ab_tmp_0;
  ab_tmp = sin(rtu_theta);
  ab_tmp_0 = cos(rtu_theta);

  /* SignalConversion generated from: '<S3>/ SFunction ' */
  rty_y[0] = ab_tmp_0 * rtu_u + -ab_tmp * rtu_u_b;
  rty_y[1] = ab_tmp * rtu_u + ab_tmp_0 * rtu_u_b;
}

/*
 * Output and update for atomic system:
 *    '<Root>/Park Transformation dq'
 *    '<Root>/Park Transformation xy'
 *    '<Root>/Park Transformation xy1'
 */
void currentCon_ParkTransformationdq(const real_T rtu_u[2], real_T rtu_theta,
  real_T rty_y[2])
{
  real_T dq_tmp;
  real_T dq_tmp_0;
  dq_tmp = sin(rtu_theta);
  dq_tmp_0 = cos(rtu_theta);
  rty_y[0] = dq_tmp_0 * rtu_u[0] + dq_tmp * rtu_u[1];
  rty_y[1] = -dq_tmp * rtu_u[0] + dq_tmp_0 * rtu_u[1];
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      real_T q;
      q = fabs(u0 / u1);
      yEq = !(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static real_T currentControlDynamic_xnrm2(int32_T n, const real_T x[42], int32_T
  ix0)
{
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        real_T absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xscal(int32_T n, real_T a, real_T x[42],
  int32_T ix0)
{
  int32_T b;
  int32_T k;
  b = (ix0 + n) - 1;
  for (k = ix0; k <= b; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static real_T currentControlDynamic_xnrm2_l(int32_T n, const real_T x[6],
  int32_T ix0)
{
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        real_T absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xscal_o(int32_T n, real_T a, real_T x[6],
  int32_T ix0)
{
  int32_T b;
  int32_T k;
  b = (ix0 + n) - 1;
  for (k = ix0; k <= b; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xaxpy_bk(int32_T n, real_T a, const real_T x[7],
  int32_T ix0, real_T y[42], int32_T iy0)
{
  int32_T k;
  if ((n >= 1) && (!(a == 0.0))) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xaxpy_b(int32_T n, real_T a, const real_T x[42],
  int32_T ix0, real_T y[7], int32_T iy0)
{
  int32_T k;
  if ((n >= 1) && (!(a == 0.0))) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static real_T currentControlDynamic_xdotc(int32_T n, const real_T x[42], int32_T
  ix0, const real_T y[42], int32_T iy0)
{
  real_T d;
  int32_T k;
  d = 0.0;
  if (n >= 1) {
    int32_T ix;
    int32_T iy;
    ix = ix0;
    iy = iy0;
    for (k = 0; k < n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xaxpy(int32_T n, real_T a, int32_T ix0, real_T
  y[42], int32_T iy0)
{
  int32_T k;
  if ((n >= 1) && (!(a == 0.0))) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static real_T currentControlDynamic_xdotc_b(int32_T n, const real_T x[36],
  int32_T ix0, const real_T y[36], int32_T iy0)
{
  real_T d;
  int32_T k;
  d = 0.0;
  if (n >= 1) {
    int32_T ix;
    int32_T iy;
    ix = ix0;
    iy = iy0;
    for (k = 0; k < n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xaxpy_bk4(int32_T n, real_T a, int32_T ix0,
  real_T y[36], int32_T iy0)
{
  int32_T k;
  if ((n >= 1) && (!(a == 0.0))) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xscal_op(real_T a, real_T x[42], int32_T ix0)
{
  int32_T k;
  for (k = ix0; k <= ix0 + 6; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xscal_opv(real_T a, real_T x[36], int32_T ix0)
{
  int32_T k;
  for (k = ix0; k <= ix0 + 5; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xswap(real_T x[36], int32_T ix0, int32_T iy0)
{
  int32_T k;
  for (k = 0; k < 6; k++) {
    real_T temp;
    int32_T temp_tmp;
    int32_T tmp;
    temp_tmp = (ix0 + k) - 1;
    temp = x[temp_tmp];
    tmp = (iy0 + k) - 1;
    x[temp_tmp] = x[tmp];
    x[tmp] = temp;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xswap_n(real_T x[42], int32_T ix0, int32_T iy0)
{
  int32_T k;
  for (k = 0; k < 7; k++) {
    real_T temp;
    int32_T temp_tmp;
    int32_T tmp;
    temp_tmp = (ix0 + k) - 1;
    temp = x[temp_tmp];
    tmp = (iy0 + k) - 1;
    x[temp_tmp] = x[tmp];
    x[tmp] = temp;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xrotg(real_T *a, real_T *b, real_T *c, real_T *
  s)
{
  real_T absa;
  real_T absb;
  real_T roe;
  real_T scale;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    *a = 0.0;
    *b = 0.0;
  } else {
    real_T ads;
    real_T bds;
    ads = absa / scale;
    bds = absb / scale;
    scale *= sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }

    *a = scale;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xrot(real_T x[36], int32_T ix0, int32_T iy0,
  real_T c, real_T s)
{
  int32_T k;
  for (k = 0; k < 6; k++) {
    real_T temp_tmp_0;
    real_T temp_tmp_2;
    int32_T temp_tmp;
    int32_T temp_tmp_1;
    temp_tmp = (iy0 + k) - 1;
    temp_tmp_0 = x[temp_tmp];
    temp_tmp_1 = (ix0 + k) - 1;
    temp_tmp_2 = x[temp_tmp_1];
    x[temp_tmp] = temp_tmp_0 * c - temp_tmp_2 * s;
    x[temp_tmp_1] = temp_tmp_2 * c + temp_tmp_0 * s;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_xrot_i(real_T x[42], int32_T ix0, int32_T iy0,
  real_T c, real_T s)
{
  int32_T k;
  for (k = 0; k < 7; k++) {
    real_T temp_tmp_0;
    real_T temp_tmp_2;
    int32_T temp_tmp;
    int32_T temp_tmp_1;
    temp_tmp = (iy0 + k) - 1;
    temp_tmp_0 = x[temp_tmp];
    temp_tmp_1 = (ix0 + k) - 1;
    temp_tmp_2 = x[temp_tmp_1];
    x[temp_tmp] = temp_tmp_0 * c - temp_tmp_2 * s;
    x[temp_tmp_1] = temp_tmp_2 * c + temp_tmp_0 * s;
  }
}

/* Function for MATLAB Function: '<Root>/Inverse Clarke Transformation' */
static void currentControlDynamic_svd(const real_T A[42], real_T U[42], real_T
  s[6], real_T V[36])
{
  real_T b_A[42];
  real_T Vf[36];
  real_T work[7];
  real_T b_s[6];
  real_T e[6];
  real_T nrm;
  real_T r;
  real_T rt;
  real_T smm1;
  real_T sqds;
  int32_T i;
  int32_T qjj;
  int32_T qp1jj;
  int32_T qp1q;
  int32_T qq;
  memcpy(&b_A[0], &A[0], 42U * sizeof(real_T));
  for (i = 0; i < 6; i++) {
    b_s[i] = 0.0;
    e[i] = 0.0;
  }

  for (i = 0; i < 7; i++) {
    work[i] = 0.0;
  }

  memset(&U[0], 0, 42U * sizeof(real_T));
  memset(&Vf[0], 0, 36U * sizeof(real_T));
  for (i = 0; i < 6; i++) {
    boolean_T apply_transform;
    qq = 7 * i + i;
    apply_transform = false;
    nrm = currentControlDynamic_xnrm2(7 - i, b_A, qq + 1);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq] < 0.0) {
        b_s[i] = -nrm;
      } else {
        b_s[i] = nrm;
      }

      if (fabs(b_s[i]) >= 1.0020841800044864E-292) {
        currentControlDynamic_xscal(7 - i, 1.0 / b_s[i], b_A, qq + 1);
      } else {
        qp1q = (qq - i) + 7;
        for (qjj = qq; qjj < qp1q; qjj++) {
          b_A[qjj] /= b_s[i];
        }
      }

      b_A[qq]++;
      b_s[i] = -b_s[i];
    } else {
      b_s[i] = 0.0;
    }

    for (qp1q = i + 1; qp1q + 1 < 7; qp1q++) {
      qjj = 7 * qp1q + i;
      if (apply_transform) {
        currentControlDynamic_xaxpy(7 - i, -(currentControlDynamic_xdotc(7 - i,
          b_A, qq + 1, b_A, qjj + 1) / b_A[i + 7 * i]), qq + 1, b_A, qjj + 1);
      }

      e[qp1q] = b_A[qjj];
    }

    for (qq = i; qq + 1 < 8; qq++) {
      U[qq + 7 * i] = b_A[7 * i + qq];
    }

    if (i + 1 <= 4) {
      nrm = currentControlDynamic_xnrm2_l(5 - i, e, i + 2);
      if (nrm == 0.0) {
        e[i] = 0.0;
      } else {
        if (e[i + 1] < 0.0) {
          e[i] = -nrm;
        } else {
          e[i] = nrm;
        }

        nrm = e[i];
        if (fabs(e[i]) >= 1.0020841800044864E-292) {
          currentControlDynamic_xscal_o(5 - i, 1.0 / e[i], e, i + 2);
        } else {
          for (qq = i + 1; qq < 6; qq++) {
            e[qq] /= nrm;
          }
        }

        e[i + 1]++;
        e[i] = -e[i];
        for (qq = i + 1; qq + 1 < 8; qq++) {
          work[qq] = 0.0;
        }

        for (qq = i + 1; qq + 1 < 7; qq++) {
          currentControlDynamic_xaxpy_b(6 - i, e[qq], b_A, (i + 7 * qq) + 2,
            work, i + 2);
        }

        for (qq = i + 1; qq + 1 < 7; qq++) {
          currentControlDynamic_xaxpy_bk(6 - i, -e[qq] / e[i + 1], work, i + 2,
            b_A, (i + 7 * qq) + 2);
        }
      }

      for (qq = i + 1; qq + 1 < 7; qq++) {
        Vf[qq + 6 * i] = e[qq];
      }
    }
  }

  i = 4;
  e[4] = b_A[39];
  e[5] = 0.0;
  for (qp1q = 5; qp1q >= 0; qp1q--) {
    qq = 7 * qp1q + qp1q;
    if (b_s[qp1q] != 0.0) {
      for (qp1jj = qp1q + 1; qp1jj + 1 < 7; qp1jj++) {
        qjj = (7 * qp1jj + qp1q) + 1;
        currentControlDynamic_xaxpy(7 - qp1q, -(currentControlDynamic_xdotc(7 -
          qp1q, U, qq + 1, U, qjj) / U[qq]), qq + 1, U, qjj);
      }

      for (qjj = qp1q; qjj + 1 < 8; qjj++) {
        qp1jj = 7 * qp1q + qjj;
        U[qp1jj] = -U[qp1jj];
      }

      U[qq]++;
      for (qq = 0; qq < qp1q; qq++) {
        U[qq + 7 * qp1q] = 0.0;
      }
    } else {
      for (qjj = 0; qjj < 7; qjj++) {
        U[qjj + 7 * qp1q] = 0.0;
      }

      U[qq] = 1.0;
    }
  }

  for (qq = 5; qq >= 0; qq--) {
    if ((qq + 1 <= 4) && (e[qq] != 0.0)) {
      qp1q = (6 * qq + qq) + 2;
      for (qjj = qq + 1; qjj + 1 < 7; qjj++) {
        qp1jj = (6 * qjj + qq) + 2;
        currentControlDynamic_xaxpy_bk4(5 - qq, -(currentControlDynamic_xdotc_b
          (5 - qq, Vf, qp1q, Vf, qp1jj) / Vf[qp1q - 1]), qp1q, Vf, qp1jj);
      }
    }

    for (qp1q = 0; qp1q < 6; qp1q++) {
      Vf[qp1q + 6 * qq] = 0.0;
    }

    Vf[qq + 6 * qq] = 1.0;
  }

  for (qq = 0; qq < 6; qq++) {
    nrm = e[qq];
    if (b_s[qq] != 0.0) {
      rt = fabs(b_s[qq]);
      r = b_s[qq] / rt;
      b_s[qq] = rt;
      if (qq + 1 < 6) {
        nrm /= r;
      }

      currentControlDynamic_xscal_op(r, U, 7 * qq + 1);
    }

    if ((qq + 1 < 6) && (nrm != 0.0)) {
      rt = fabs(nrm);
      r = rt / nrm;
      nrm = rt;
      b_s[qq + 1] *= r;
      currentControlDynamic_xscal_opv(r, Vf, 6 * (qq + 1) + 1);
    }

    e[qq] = nrm;
  }

  qq = 0;
  nrm = 0.0;
  for (qp1q = 0; qp1q < 6; qp1q++) {
    nrm = fmax(nrm, fmax(fabs(b_s[qp1q]), fabs(e[qp1q])));
  }

  while ((i + 2 > 0) && (qq < 75)) {
    boolean_T exitg1;
    qp1q = i + 1;
    exitg1 = false;
    while (!(exitg1 || (qp1q == 0))) {
      rt = fabs(e[qp1q - 1]);
      if (rt <= (fabs(b_s[qp1q - 1]) + fabs(b_s[qp1q])) * 2.2204460492503131E-16)
      {
        e[qp1q - 1] = 0.0;
        exitg1 = true;
      } else if ((rt <= 1.0020841800044864E-292) || ((qq > 20) && (rt <=
                   2.2204460492503131E-16 * nrm))) {
        e[qp1q - 1] = 0.0;
        exitg1 = true;
      } else {
        qp1q--;
      }
    }

    if (i + 1 == qp1q) {
      qp1jj = 4;
    } else {
      qjj = i + 2;
      qp1jj = i + 2;
      exitg1 = false;
      while ((!exitg1) && (qp1jj >= qp1q)) {
        qjj = qp1jj;
        if (qp1jj == qp1q) {
          exitg1 = true;
        } else {
          rt = 0.0;
          if (qp1jj < i + 2) {
            rt = fabs(e[qp1jj - 1]);
          }

          if (qp1jj > qp1q + 1) {
            rt += fabs(e[qp1jj - 2]);
          }

          r = fabs(b_s[qp1jj - 1]);
          if ((r <= 2.2204460492503131E-16 * rt) || (r <=
               1.0020841800044864E-292)) {
            b_s[qp1jj - 1] = 0.0;
            exitg1 = true;
          } else {
            qp1jj--;
          }
        }
      }

      if (qjj == qp1q) {
        qp1jj = 3;
      } else if (i + 2 == qjj) {
        qp1jj = 1;
      } else {
        qp1jj = 2;
        qp1q = qjj;
      }
    }

    switch (qp1jj) {
     case 1:
      rt = e[i];
      e[i] = 0.0;
      for (qjj = i; qjj + 1 >= qp1q + 1; qjj--) {
        currentControlDynamic_xrotg(&b_s[qjj], &rt, &sqds, &smm1);
        if (qjj + 1 > qp1q + 1) {
          r = e[qjj - 1];
          rt = r * -smm1;
          e[qjj - 1] = r * sqds;
        }

        currentControlDynamic_xrot(Vf, 6 * qjj + 1, 6 * (i + 1) + 1, sqds, smm1);
      }
      break;

     case 2:
      rt = e[qp1q - 1];
      e[qp1q - 1] = 0.0;
      for (qjj = qp1q; qjj < i + 2; qjj++) {
        currentControlDynamic_xrotg(&b_s[qjj], &rt, &r, &sqds);
        rt = -sqds * e[qjj];
        e[qjj] *= r;
        currentControlDynamic_xrot_i(U, 7 * qjj + 1, 7 * (qp1q - 1) + 1, r, sqds);
      }
      break;

     case 3:
      {
        real_T emm1;
        real_T shift;
        rt = b_s[i + 1];
        r = fmax(fmax(fmax(fmax(fabs(rt), fabs(b_s[i])), fabs(e[i])), fabs
                      (b_s[qp1q])), fabs(e[qp1q]));
        rt /= r;
        smm1 = b_s[i] / r;
        emm1 = e[i] / r;
        sqds = b_s[qp1q] / r;
        smm1 = ((smm1 + rt) * (smm1 - rt) + emm1 * emm1) / 2.0;
        emm1 *= rt;
        emm1 *= emm1;
        if ((smm1 != 0.0) || (emm1 != 0.0)) {
          shift = sqrt(smm1 * smm1 + emm1);
          if (smm1 < 0.0) {
            shift = -shift;
          }

          shift = emm1 / (smm1 + shift);
        } else {
          shift = 0.0;
        }

        rt = (sqds + rt) * (sqds - rt) + shift;
        r = e[qp1q] / r * sqds;
        for (qjj = qp1q + 1; qjj <= i + 1; qjj++) {
          currentControlDynamic_xrotg(&rt, &r, &sqds, &smm1);
          if (qjj > qp1q + 1) {
            e[qjj - 2] = rt;
          }

          r = e[qjj - 1];
          emm1 = b_s[qjj - 1];
          e[qjj - 1] = r * sqds - emm1 * smm1;
          rt = smm1 * b_s[qjj];
          b_s[qjj] *= sqds;
          currentControlDynamic_xrot(Vf, 6 * (qjj - 1) + 1, 6 * qjj + 1, sqds,
            smm1);
          b_s[qjj - 1] = emm1 * sqds + r * smm1;
          currentControlDynamic_xrotg(&b_s[qjj - 1], &rt, &sqds, &smm1);
          rt = e[qjj - 1] * sqds + smm1 * b_s[qjj];
          b_s[qjj] = e[qjj - 1] * -smm1 + sqds * b_s[qjj];
          r = smm1 * e[qjj];
          e[qjj] *= sqds;
          currentControlDynamic_xrot_i(U, 7 * (qjj - 1) + 1, 7 * qjj + 1, sqds,
            smm1);
        }

        e[i] = rt;
        qq++;
      }
      break;

     default:
      if (b_s[qp1q] < 0.0) {
        b_s[qp1q] = -b_s[qp1q];
        currentControlDynamic_xscal_opv(-1.0, Vf, 6 * qp1q + 1);
      }

      qq = qp1q + 1;
      while ((qp1q + 1 < 6) && (b_s[qp1q] < b_s[qq])) {
        rt = b_s[qp1q];
        b_s[qp1q] = b_s[qq];
        b_s[qq] = rt;
        currentControlDynamic_xswap(Vf, 6 * qp1q + 1, 6 * (qp1q + 1) + 1);
        currentControlDynamic_xswap_n(U, 7 * qp1q + 1, 7 * (qp1q + 1) + 1);
        qp1q = qq;
        qq++;
      }

      qq = 0;
      i--;
      break;
    }
  }

  for (qq = 0; qq < 6; qq++) {
    s[qq] = b_s[qq];
    for (i = 0; i < 6; i++) {
      V[i + 6 * qq] = Vf[6 * qq + i];
    }
  }
}

/* Model step function */
void currentControlDynamic_step(void)
{
  creal_T a[28];
  creal_T x_0[7];
  creal_T vec[4];
  real_T A[42];
  real_T Clarke[42];
  real_T U[42];
  real_T V[36];
  real_T rtb_y_im[8];
  real_T rtb_TmpSignalConversionAtSFun_j[7];
  real_T x[7];
  real_T s[6];
  real_T rtb_y_a[2];
  real_T rtb_y_c[2];
  real_T rtb_y_fw[2];
  real_T rtb_y_g[2];
  real_T rtb_y_mm[2];
  real_T rtb_y_oh[2];
  real_T rtb_Delay;
  real_T rtb_Sum;
  real_T rtb_Sum1_i;
  int32_T ar;
  int32_T b_ic;
  int32_T br;
  int32_T ib;
  int32_T r;
  int32_T vcol;

  /* SignalConversion generated from: '<S1>/ SFunction ' incorporates:
   *  Inport generated from: '<Root>/i1'
   *  Inport generated from: '<Root>/i2'
   *  Inport generated from: '<Root>/i3'
   *  Inport generated from: '<Root>/i4'
   *  Inport generated from: '<Root>/i5'
   *  Inport generated from: '<Root>/i6'
   *  Inport generated from: '<Root>/i7'
   *  MATLAB Function: '<Root>/Clarke Transformation'
   */
  rtb_TmpSignalConversionAtSFun_j[0] = currentControlDynamic_U.i1;
  rtb_TmpSignalConversionAtSFun_j[1] = currentControlDynamic_U.i2;
  rtb_TmpSignalConversionAtSFun_j[2] = currentControlDynamic_U.i3;
  rtb_TmpSignalConversionAtSFun_j[3] = currentControlDynamic_U.i4;
  rtb_TmpSignalConversionAtSFun_j[4] = currentControlDynamic_U.i5;
  rtb_TmpSignalConversionAtSFun_j[5] = currentControlDynamic_U.i6;
  rtb_TmpSignalConversionAtSFun_j[6] = currentControlDynamic_U.i7;

  /* MATLAB Function: '<Root>/Clarke Transformation' incorporates:
   *  Constant: '<Root>/Constant'
   */
  for (br = 0; br < 7; br++) {
    x[br] = rtb_TmpSignalConversionAtSFun_j[br];
  }

  for (br = 0; br < 4; br++) {
    for (ar = 0; ar < 7; ar++) {
      rtb_Sum1_i = (real_T)(br * ar) * 0.89759790102565518;
      if (rtb_Sum1_i == 0.0) {
        rtb_Sum = 1.0;
      } else {
        rtb_Sum = cos(rtb_Sum1_i);
        rtb_Sum1_i = sin(rtb_Sum1_i);
      }

      vcol = (ar << 2) + br;
      a[vcol].re = 0.2857142857142857 * rtb_Sum;
      a[vcol].im = 0.2857142857142857 * rtb_Sum1_i;
    }
  }

  for (vcol = 0; vcol < 7; vcol++) {
    x_0[vcol].re = x[vcol];
    x_0[vcol].im = 0.0;
  }

  for (vcol = 0; vcol < 4; vcol++) {
    vec[vcol].re = 0.0;
    vec[vcol].im = 0.0;
    for (br = 0; br < 7; br++) {
      creal_T vec_0;
      real_T vec_tmp;
      vec_0 = vec[vcol];
      ar = (br << 2) + vcol;
      rtb_Sum1_i = a[ar].re;
      rtb_Sum = x_0[br].im;
      rtb_Delay = a[ar].im;
      vec_tmp = x_0[br].re;
      vec_0.re += rtb_Sum1_i * vec_tmp - rtb_Delay * rtb_Sum;
      vec_0.im += rtb_Sum1_i * rtb_Sum + rtb_Delay * vec_tmp;
      vec[vcol] = vec_0;
    }
  }

  vec[0].re *= 0.5;
  vec[0].im *= 0.5;
  rtb_y_im[0] = vec[0].re;
  rtb_y_im[1] = vec[0].im;
  rtb_y_im[2] = vec[1].re;
  rtb_y_im[3] = vec[1].im;
  rtb_y_im[4] = vec[2].re;
  rtb_y_im[5] = vec[2].im;
  rtb_y_im[6] = vec[3].re;
  rtb_y_im[7] = vec[3].im;

  /* MATLAB Function: '<Root>/wrap2pi' incorporates:
   *  Gain: '<Root>/Gain27'
   *  Inport generated from: '<Root>/theta_m'
   */
  currentControlDynamic_Y.LOG1_pos_theta = 8.0 * currentControlDynamic_U.theta_m;
  while (currentControlDynamic_Y.LOG1_pos_theta > 6.2831853071795862) {
    currentControlDynamic_Y.LOG1_pos_theta -= 6.2831853071795862;
  }

  while (currentControlDynamic_Y.LOG1_pos_theta < 0.0) {
    currentControlDynamic_Y.LOG1_pos_theta += 6.2831853071795862;
  }

  /* End of MATLAB Function: '<Root>/wrap2pi' */

  /* MATLAB Function: '<Root>/Park Transformation dq' */
  currentCon_ParkTransformationdq(&rtb_y_im[2],
    currentControlDynamic_Y.LOG1_pos_theta, rtb_y_mm);

  /* Sum: '<S9>/Sum1' incorporates:
   *  Delay: '<S9>/Delay'
   *  Delay: '<S9>/Delay1'
   *  Gain: '<S9>/Gain1'
   */
  rtb_Sum1_i = 0.049023076705685065 * currentControlDynamic_DW.Delay_DSTATE +
    currentControlDynamic_DW.Delay1_DSTATE;

  /* Gain: '<Root>/Gain26' */
  currentControlDynamic_Y.LOG1_pos_we = 8.0 * rtb_Sum1_i;

  /* Sum: '<S10>/Sum' incorporates:
   *  Inport generated from: '<Root>/id_ref'
   */
  rtb_Sum = currentControlDynamic_U.id_ref - rtb_y_mm[0];

  /* Sum: '<S10>/Sum2' incorporates:
   *  Delay: '<S10>/Delay'
   */
  currentControlDynamic_DW.Delay_DSTATE_g += rtb_Sum;

  /* Sum: '<Root>/Subtract' incorporates:
   *  Delay: '<S10>/Delay'
   *  Gain: '<Root>/Gain'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain2'
   *  Product: '<Root>/Product'
   *  Sum: '<S10>/Sum1'
   */
  currentControlDynamic_Y.LOG1_v_sv_vd_ref = (4.0E-5 *
    currentControlDynamic_DW.Delay_DSTATE_g * 90.477868423386042 +
    0.1884955592153876 * rtb_Sum) + -5.0E-5 *
    currentControlDynamic_Y.LOG1_pos_we * rtb_y_mm[1];

  /* Sum: '<S11>/Sum' incorporates:
   *  Inport generated from: '<Root>/iq_ref'
   */
  rtb_Sum = currentControlDynamic_U.iq_ref - rtb_y_mm[1];

  /* Sum: '<S11>/Sum2' incorporates:
   *  Delay: '<S11>/Delay'
   */
  currentControlDynamic_DW.Delay_DSTATE_d += rtb_Sum;

  /* Sum: '<Root>/Subtract1' incorporates:
   *  Delay: '<S11>/Delay'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain21'
   *  Gain: '<S11>/Gain'
   *  Gain: '<S11>/Gain1'
   *  Gain: '<S11>/Gain2'
   *  Product: '<Root>/Product1'
   *  Sum: '<S11>/Sum1'
   */
  currentControlDynamic_Y.LOG1_v_sv_vq_ref = ((4.0E-5 *
    currentControlDynamic_DW.Delay_DSTATE_d * 90.477868423386042 +
    0.1884955592153876 * rtb_Sum) + 5.0E-5 * currentControlDynamic_Y.LOG1_pos_we
    * rtb_y_mm[0]) + 0.0033 * currentControlDynamic_Y.LOG1_pos_we;

  /* MATLAB Function: '<Root>/Inverse Park Transformation dq' */
  cur_InverseParkTransformationdq(currentControlDynamic_Y.LOG1_v_sv_vd_ref,
    currentControlDynamic_Y.LOG1_v_sv_vq_ref,
    currentControlDynamic_Y.LOG1_pos_theta, rtb_y_g);

  /* Math: '<Root>/Math Function5' incorporates:
   *  Constant: '<Root>/Constant11'
   *  Gain: '<Root>/Gain30'
   */
  currentControlDynamic_Y.LOG1_pos_theta5 = rt_modd_snf(5.0 *
    currentControlDynamic_Y.LOG1_pos_theta, 6.2831853071795862);

  /* MATLAB Function: '<Root>/Park Transformation xy1' */
  currentCon_ParkTransformationdq(&rtb_y_im[4],
    currentControlDynamic_Y.LOG1_pos_theta5, rtb_y_oh);

  /* Sum: '<S15>/Sum' incorporates:
   *  Inport generated from: '<Root>/id5_ref'
   */
  rtb_Sum = currentControlDynamic_U.id5_ref - rtb_y_oh[0];

  /* Sum: '<S15>/Sum2' incorporates:
   *  Delay: '<S15>/Delay'
   */
  currentControlDynamic_DW.Delay_DSTATE_i += rtb_Sum;

  /* Sum: '<Root>/Subtract4' incorporates:
   *  Delay: '<S15>/Delay'
   *  Gain: '<Root>/Gain17'
   *  Gain: '<Root>/Gain24'
   *  Gain: '<S15>/Gain'
   *  Gain: '<S15>/Gain1'
   *  Gain: '<S15>/Gain2'
   *  Product: '<Root>/Product4'
   *  Sum: '<S15>/Sum1'
   */
  currentControlDynamic_Y.LOG1_v_sv_vd5_ref = 5.0 *
    currentControlDynamic_Y.LOG1_pos_we * -5.0E-5 * rtb_y_oh[1] + (4.0E-5 *
    currentControlDynamic_DW.Delay_DSTATE_i * 90.477868423386042 +
    0.1884955592153876 * rtb_Sum);

  /* Gain: '<Root>/Gain25' */
  rtb_Sum = 5.0 * currentControlDynamic_Y.LOG1_pos_we;

  /* Sum: '<S17>/Sum' incorporates:
   *  Inport generated from: '<Root>/iq5_ref'
   */
  rtb_Delay = currentControlDynamic_U.iq5_ref - rtb_y_oh[1];

  /* Sum: '<S17>/Sum2' incorporates:
   *  Delay: '<S17>/Delay'
   */
  currentControlDynamic_DW.Delay_DSTATE_m += rtb_Delay;

  /* Sum: '<Root>/Subtract5' incorporates:
   *  Delay: '<S17>/Delay'
   *  Gain: '<Root>/Gain18'
   *  Gain: '<Root>/Gain9'
   *  Gain: '<S17>/Gain'
   *  Gain: '<S17>/Gain1'
   *  Gain: '<S17>/Gain2'
   *  Product: '<Root>/Product5'
   *  Sum: '<S17>/Sum1'
   */
  currentControlDynamic_Y.LOG1_v_sv_vq5_ref = ((4.0E-5 *
    currentControlDynamic_DW.Delay_DSTATE_m * 90.477868423386042 +
    0.1884955592153876 * rtb_Delay) + 5.0E-5 * rtb_Sum * rtb_y_oh[0]) + 0.0006 *
    rtb_Sum;

  /* MATLAB Function: '<Root>/Inverse Park Transformation xy1' */
  cur_InverseParkTransformationdq(currentControlDynamic_Y.LOG1_v_sv_vd5_ref,
    currentControlDynamic_Y.LOG1_v_sv_vq5_ref,
    currentControlDynamic_Y.LOG1_pos_theta5, rtb_y_a);

  /* Math: '<Root>/Math Function4' incorporates:
   *  Constant: '<Root>/Constant11'
   *  Gain: '<Root>/Gain29'
   *  Inport generated from: '<Root>/Theta_3Offset'
   *  Sum: '<Root>/Sum'
   */
  currentControlDynamic_Y.LOG1_pos_theta3 = rt_modd_snf(3.0 *
    currentControlDynamic_Y.LOG1_pos_theta +
    currentControlDynamic_U.Theta_3Offset, 6.2831853071795862);

  /* MATLAB Function: '<Root>/Park Transformation xy' */
  currentCon_ParkTransformationdq(&rtb_y_im[6],
    currentControlDynamic_Y.LOG1_pos_theta3, rtb_y_c);

  /* Sum: '<S14>/Sum' incorporates:
   *  Inport generated from: '<Root>/id3_ref'
   */
  rtb_Sum = currentControlDynamic_U.id3_ref - rtb_y_c[0];

  /* Sum: '<S14>/Sum2' incorporates:
   *  Delay: '<S14>/Delay'
   */
  currentControlDynamic_DW.Delay_DSTATE_c += rtb_Sum;

  /* Sum: '<Root>/Subtract2' incorporates:
   *  Delay: '<S14>/Delay'
   *  Gain: '<Root>/Gain2'
   *  Gain: '<Root>/Gain22'
   *  Gain: '<S14>/Gain'
   *  Gain: '<S14>/Gain1'
   *  Gain: '<S14>/Gain2'
   *  Product: '<Root>/Product2'
   *  Sum: '<S14>/Sum1'
   */
  currentControlDynamic_Y.LOG1_v_sv_vd3_ref = 3.0 *
    currentControlDynamic_Y.LOG1_pos_we * -5.0E-5 * rtb_y_c[1] + (4.0E-5 *
    currentControlDynamic_DW.Delay_DSTATE_c * 90.477868423386042 +
    0.1884955592153876 * rtb_Sum);

  /* Gain: '<Root>/Gain23' */
  rtb_Delay = 3.0 * currentControlDynamic_Y.LOG1_pos_we;

  /* Sum: '<S16>/Sum' incorporates:
   *  Inport generated from: '<Root>/iq3_ref'
   */
  rtb_Sum = currentControlDynamic_U.iq3_ref - rtb_y_c[1];

  /* Sum: '<S16>/Sum2' incorporates:
   *  Delay: '<S16>/Delay'
   */
  currentControlDynamic_DW.Delay_DSTATE_gq += rtb_Sum;

  /* Sum: '<Root>/Subtract3' incorporates:
   *  Delay: '<S16>/Delay'
   *  Gain: '<Root>/Gain20'
   *  Gain: '<Root>/Gain3'
   *  Gain: '<S16>/Gain'
   *  Gain: '<S16>/Gain1'
   *  Gain: '<S16>/Gain2'
   *  Product: '<Root>/Product3'
   *  Sum: '<S16>/Sum1'
   */
  currentControlDynamic_Y.LOG1_v_sv_vq3_ref = ((4.0E-5 *
    currentControlDynamic_DW.Delay_DSTATE_gq * 90.477868423386042 +
    0.1884955592153876 * rtb_Sum) + 5.0E-5 * rtb_Delay * rtb_y_c[0]) + 0.001 *
    rtb_Delay;

  /* MATLAB Function: '<Root>/Inverse Park Transformation xy' */
  cur_InverseParkTransformationdq(currentControlDynamic_Y.LOG1_v_sv_vd3_ref,
    currentControlDynamic_Y.LOG1_v_sv_vq3_ref,
    currentControlDynamic_Y.LOG1_pos_theta3, rtb_y_fw);

  /* MATLAB Function: '<Root>/Inverse Clarke Transformation' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  for (br = 0; br < 7; br++) {
    rtb_Sum = (((real_T)br + 1.0) - 1.0) * 0.89759790102565518;
    Clarke[6 * br] = cos(rtb_Sum) * 0.2857142857142857;
    Clarke[6 * br + 1] = sin(rtb_Sum) * 0.2857142857142857;
    rtb_Sum = (((real_T)br + 1.0) - 1.0) * 1.7951958020513104;
    Clarke[6 * br + 2] = cos(rtb_Sum) * 0.2857142857142857;
    Clarke[6 * br + 3] = sin(rtb_Sum) * 0.2857142857142857;
    rtb_Sum = (((real_T)br + 1.0) - 1.0) * 2.6927937030769655;
    Clarke[6 * br + 4] = cos(rtb_Sum) * 0.2857142857142857;
    Clarke[6 * br + 5] = sin(rtb_Sum) * 0.2857142857142857;
  }

  for (vcol = 0; vcol < 6; vcol++) {
    for (br = 0; br < 7; br++) {
      A[br + 7 * vcol] = Clarke[6 * br + vcol];
    }
  }

  memset(&Clarke[0], 0, 42U * sizeof(real_T));
  currentControlDynamic_svd(A, U, s, V);
  rtb_Sum = fabs(s[0]);
  if ((!rtIsInf(rtb_Sum)) && (!rtIsNaN(rtb_Sum))) {
    if (rtb_Sum <= 2.2250738585072014E-308) {
      rtb_Sum = 4.94065645841247E-324;
    } else {
      frexp(rtb_Sum, &r);
      rtb_Sum = ldexp(1.0, r - 53);
    }
  } else {
    rtb_Sum = (rtNaN);
  }

  rtb_Sum *= 7.0;
  r = -1;
  br = 0;
  while ((br < 6) && (s[br] > rtb_Sum)) {
    r++;
    br++;
  }

  if (r + 1 > 0) {
    vcol = 0;
    for (br = 0; br <= r; br++) {
      rtb_Sum = 1.0 / s[br];
      for (ar = vcol; ar < vcol + 6; ar++) {
        V[ar] *= rtb_Sum;
      }

      vcol += 6;
    }

    br = 0;
    for (vcol = 0; vcol <= 37; vcol += 6) {
      for (ar = vcol; ar < vcol + 6; ar++) {
        Clarke[ar] = 0.0;
      }
    }

    for (vcol = 0; vcol <= 37; vcol += 6) {
      int32_T b;
      ar = -1;
      br++;
      b = 7 * r + br;
      for (ib = br; ib <= b; ib += 7) {
        int32_T ia;
        ia = ar;
        for (b_ic = vcol; b_ic < vcol + 6; b_ic++) {
          ia++;
          Clarke[b_ic] += U[ib - 1] * V[ia];
        }

        ar += 6;
      }
    }
  }

  /* SignalConversion generated from: '<S2>/ SFunction ' incorporates:
   *  MATLAB Function: '<Root>/Inverse Clarke Transformation'
   */
  s[0] = rtb_y_g[0];
  s[2] = rtb_y_a[0];
  s[4] = rtb_y_fw[0];
  s[1] = rtb_y_g[1];
  s[3] = rtb_y_a[1];
  s[5] = rtb_y_fw[1];

  /* MATLAB Function: '<Root>/Inverse Clarke Transformation' */
  for (vcol = 0; vcol < 7; vcol++) {
    x[vcol] = 0.0;
    for (br = 0; br < 6; br++) {
      x[vcol] += Clarke[6 * vcol + br] * s[br];
    }

    rtb_TmpSignalConversionAtSFun_j[vcol] = x[vcol];
  }

  /* Gain: '<S9>/Gain2' incorporates:
   *  Delay: '<S9>/Delay1'
   */
  currentControlDynamic_DW.Delay1_DSTATE = 0.95097692329431494 * rtb_Sum1_i;

  /* MATLAB Function: '<Root>/speed_calc' incorporates:
   *  Delay: '<Root>/Delay2'
   *  Inport generated from: '<Root>/theta_m'
   */
  for (rtb_Sum1_i = currentControlDynamic_U.theta_m -
       currentControlDynamic_DW.Delay2_DSTATE; rtb_Sum1_i > 3.1415926535897931;
       rtb_Sum1_i -= 6.2831853071795862) {
  }

  while (rtb_Sum1_i < -3.1415926535897931) {
    rtb_Sum1_i += 6.2831853071795862;
  }

  /* End of MATLAB Function: '<Root>/speed_calc' */

  /* Gain: '<Root>/Gain28' incorporates:
   *  Delay: '<S9>/Delay'
   */
  currentControlDynamic_DW.Delay_DSTATE = 24999.999999999996 * rtb_Sum1_i;

  /* Update for Delay: '<Root>/Delay2' incorporates:
   *  Inport generated from: '<Root>/theta_m'
   */
  currentControlDynamic_DW.Delay2_DSTATE = currentControlDynamic_U.theta_m;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/i1'
   */
  currentControlDynamic_Y.LOG1_i_ph_i1 = currentControlDynamic_U.i1;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/i2'
   */
  currentControlDynamic_Y.LOG1_i_ph_i2 = currentControlDynamic_U.i2;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/i3'
   */
  currentControlDynamic_Y.LOG1_i_ph_i3 = currentControlDynamic_U.i3;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/i4'
   */
  currentControlDynamic_Y.LOG1_i_ph_i4 = currentControlDynamic_U.i4;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/i5'
   */
  currentControlDynamic_Y.LOG1_i_ph_i5 = currentControlDynamic_U.i5;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/i6'
   */
  currentControlDynamic_Y.LOG1_i_ph_i6 = currentControlDynamic_U.i6;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/i7'
   */
  currentControlDynamic_Y.LOG1_i_ph_i7 = currentControlDynamic_U.i7;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/id_ref'
   */
  currentControlDynamic_Y.LOG1_i_sv_id1_ref = currentControlDynamic_U.id_ref;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/iq_ref'
   */
  currentControlDynamic_Y.LOG1_i_sv_iq1_ref = currentControlDynamic_U.iq_ref;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/id3_ref'
   */
  currentControlDynamic_Y.LOG1_i_sv_id3_ref = currentControlDynamic_U.id3_ref;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/iq3_ref'
   */
  currentControlDynamic_Y.LOG1_i_sv_iq3_ref = currentControlDynamic_U.iq3_ref;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/id5_ref'
   */
  currentControlDynamic_Y.LOG1_i_sv_id5_ref = currentControlDynamic_U.id5_ref;

  /* Outport generated from: '<Root>/LOG1_Outport_2' incorporates:
   *  Inport generated from: '<Root>/iq5_ref'
   */
  currentControlDynamic_Y.LOG1_i_sv_iq5_ref = currentControlDynamic_U.iq5_ref;

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_i_sv_id1 = rtb_y_mm[0];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_i_sv_iq1 = rtb_y_mm[1];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_i_sv_id3 = rtb_y_c[0];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_i_sv_iq3 = rtb_y_c[1];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_i_sv_id5 = rtb_y_oh[0];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_i_sv_iq5 = rtb_y_oh[1];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_v_ph_v1 = rtb_TmpSignalConversionAtSFun_j[0];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_v_ph_v2 = rtb_TmpSignalConversionAtSFun_j[1];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_v_ph_v3 = rtb_TmpSignalConversionAtSFun_j[2];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_v_ph_v4 = rtb_TmpSignalConversionAtSFun_j[3];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_v_ph_v5 = rtb_TmpSignalConversionAtSFun_j[4];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_v_ph_v6 = rtb_TmpSignalConversionAtSFun_j[5];

  /* Outport generated from: '<Root>/LOG1_Outport_2' */
  currentControlDynamic_Y.LOG1_v_ph_v7 = rtb_TmpSignalConversionAtSFun_j[6];

  /* Outport generated from: '<Root>/Normalized Voltages1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant7'
   *  Constant: '<Root>/Constant8'
   *  Constant: '<Root>/Constant9'
   *  Inport generated from: '<Root>/V_dc'
   *  Product: '<Root>/Divide'
   *  Product: '<Root>/Divide1'
   *  Product: '<Root>/Divide2'
   *  Product: '<Root>/Divide3'
   *  Product: '<Root>/Divide4'
   *  Product: '<Root>/Divide5'
   *  Product: '<Root>/Divide6'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<Root>/Sum2'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<Root>/Sum4'
   *  Sum: '<Root>/Sum5'
   *  Sum: '<Root>/Sum6'
   *  Sum: '<Root>/Sum8'
   */
  currentControlDynamic_Y.NormalizedVoltages1[0] =
    rtb_TmpSignalConversionAtSFun_j[0] / currentControlDynamic_U.V_dc + 0.5;
  currentControlDynamic_Y.NormalizedVoltages1[1] =
    rtb_TmpSignalConversionAtSFun_j[1] / currentControlDynamic_U.V_dc + 0.5;
  currentControlDynamic_Y.NormalizedVoltages1[2] =
    rtb_TmpSignalConversionAtSFun_j[2] / currentControlDynamic_U.V_dc + 0.5;
  currentControlDynamic_Y.NormalizedVoltages1[3] =
    rtb_TmpSignalConversionAtSFun_j[3] / currentControlDynamic_U.V_dc + 0.5;
  currentControlDynamic_Y.NormalizedVoltages1[4] =
    rtb_TmpSignalConversionAtSFun_j[4] / currentControlDynamic_U.V_dc + 0.5;
  currentControlDynamic_Y.NormalizedVoltages1[5] =
    rtb_TmpSignalConversionAtSFun_j[5] / currentControlDynamic_U.V_dc + 0.5;
  currentControlDynamic_Y.NormalizedVoltages1[6] =
    rtb_TmpSignalConversionAtSFun_j[6] / currentControlDynamic_U.V_dc + 0.5;

  /* Outport generated from: '<Root>/omega_e' */
  currentControlDynamic_Y.omega_e = currentControlDynamic_Y.LOG1_pos_we;
}

/* Model initialize function */
void currentControlDynamic_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
}

/* Model terminate function */
void currentControlDynamic_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
