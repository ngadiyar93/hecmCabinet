/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: currentControlDynamic_private.h
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

#ifndef RTW_HEADER_currentControlDynamic_private_h_
#define RTW_HEADER_currentControlDynamic_private_h_
#include "rtwtypes.h"
#include "currentControlDynamic.h"

extern real_T rt_modd_snf(real_T u0, real_T u1);
extern void cur_InverseParkTransformationdq(real_T rtu_u, real_T rtu_u_b, real_T
  rtu_theta, real_T rty_y[2]);
extern void currentCon_ParkTransformationdq(const real_T rtu_u[2], real_T
  rtu_theta, real_T rty_y[2]);

#endif                         /* RTW_HEADER_currentControlDynamic_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
