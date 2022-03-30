/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PMSMController.c
 *
 * Code generated for Simulink model 'PMSMController'.
 *
 * Model version                  : 2.36
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Mar 29 20:33:52 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "PMSMController.h"
#include "PMSMController_private.h"

/* Block states (default storage) */
DW_PMSMController_T PMSMController_DW;

/* External inputs (root inport signals with default storage) */
ExtU_PMSMController_T PMSMController_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_PMSMController_T PMSMController_Y;

/* Real-time model */
static RT_MODEL_PMSMController_T PMSMController_M_;
RT_MODEL_PMSMController_T *const PMSMController_M = &PMSMController_M_;

/* Model step function */
void PMSMController_step(void)
{
  real_T rtb_Integrator_f;
  real_T rtb_Sum1_b;
  real_T rtb_Sum1_f;
  real_T rtb_Sum4;
  real_T rtb_Sum5;
  real_T rtb_Sum6;
  real_T rtb_Sum7;
  real_T rtb_Sum_e;
  real_T rtb_Sum_p;
  real_T rtb_y;

  /* Gain: '<S155>/Gain' incorporates:
   *  Gain: '<S155>/Gain2'
   *  Gain: '<S155>/Gain4'
   *  Inport: '<Root>/I_a'
   *  Inport: '<Root>/I_b'
   *  Inport: '<Root>/I_c'
   *  Sum: '<S155>/Sum'
   */
  rtb_Sum_p = ((-0.5 * PMSMController_U.I_b + PMSMController_U.I_a) + -0.5 *
               PMSMController_U.I_c) * 0.66666666666666663;

  /* MATLAB Function: '<Root>/wrap2pi' incorporates:
   *  Gain: '<Root>/Gain8'
   *  Inport: '<Root>/theta_m'
   */
  for (rtb_y = 8.0 * PMSMController_U.theta_m; rtb_y > 6.2831853071795862; rtb_y
       -= 6.2831853071795862) {
  }

  while (rtb_y < 0.0) {
    rtb_y += 6.2831853071795862;
  }

  /* End of MATLAB Function: '<Root>/wrap2pi' */

  /* Trigonometry: '<S154>/Trigonometric Function1' incorporates:
   *  Gain: '<S154>/Gain'
   */
  rtb_Sum6 = cos(-rtb_y);

  /* Gain: '<S155>/Gain1' incorporates:
   *  Gain: '<S155>/Gain3'
   *  Gain: '<S155>/Gain5'
   *  Inport: '<Root>/I_b'
   *  Inport: '<Root>/I_c'
   *  Sum: '<S155>/Sum1'
   */
  rtb_Sum4 = (0.8660254037844386 * PMSMController_U.I_b + -0.8660254037844386 *
              PMSMController_U.I_c) * 0.66666666666666663;

  /* Trigonometry: '<S154>/Trigonometric Function' incorporates:
   *  Gain: '<S154>/Gain'
   */
  rtb_Integrator_f = sin(-rtb_y);

  /* Sum: '<S154>/Sum' incorporates:
   *  Product: '<S154>/Product'
   *  Product: '<S154>/Product1'
   */
  rtb_Sum7 = rtb_Sum_p * rtb_Sum6 - rtb_Sum4 * rtb_Integrator_f;

  /* Sum: '<S5>/Sum1' incorporates:
   *  Delay: '<S5>/Delay'
   *  Delay: '<S5>/Delay1'
   *  Gain: '<S5>/Gain1'
   */
  rtb_Sum1_f = 0.030927573695189392 * PMSMController_DW.Delay_DSTATE +
    PMSMController_DW.Delay1_DSTATE;

  /* Gain: '<Root>/Gain11' */
  PMSMController_Y.omega_e = 8.0 * rtb_Sum1_f;

  /* Sum: '<S154>/Sum1' incorporates:
   *  Product: '<S154>/Product2'
   *  Product: '<S154>/Product3'
   */
  rtb_Sum4 = rtb_Sum_p * rtb_Integrator_f + rtb_Sum4 * rtb_Sum6;

  /* Sum: '<Root>/Sum6' incorporates:
   *  Inport: '<Root>/omega_ref'
   */
  rtb_Sum6 = PMSMController_U.omega_ref - rtb_Sum1_f;

  /* Sum: '<S50>/Sum' incorporates:
   *  DiscreteIntegrator: '<S41>/Integrator'
   *  Gain: '<S46>/Proportional Gain'
   */
  rtb_Sum_p = 9.42477796076938 * rtb_Sum6 + PMSMController_DW.Integrator_DSTATE;

  /* Saturate: '<S48>/Saturation' */
  if (rtb_Sum_p > 25.2) {
    /* Saturate: '<S48>/Saturation' */
    PMSMController_Y.T_ref = 25.2;
  } else if (rtb_Sum_p < -25.2) {
    /* Saturate: '<S48>/Saturation' */
    PMSMController_Y.T_ref = -25.2;
  } else {
    /* Saturate: '<S48>/Saturation' */
    PMSMController_Y.T_ref = rtb_Sum_p;
  }

  /* End of Saturate: '<S48>/Saturation' */

  /* Sum: '<Root>/Sum8' incorporates:
   *  Gain: '<Root>/Gain5'
   */
  rtb_Integrator_f = 7.9365079365079367 * PMSMController_Y.T_ref - rtb_Sum4;

  /* Sum: '<Root>/Sum5' incorporates:
   *  Constant: '<S4>/Constant'
   *  DiscreteIntegrator: '<S137>/Integrator'
   *  Fcn: '<S4>/Fcn1'
   *  Gain: '<S142>/Proportional Gain'
   *  Sum: '<S146>/Sum'
   */
  rtb_Sum5 = (5.29e-5 * rtb_Sum7 + 0.0105) * PMSMController_Y.omega_e +
    (0.24928537706235007 * rtb_Integrator_f +
     PMSMController_DW.Integrator_DSTATE_d);

  /* Trigonometry: '<S156>/Trigonometric Function' */
  rtb_Sum1_b = sin(rtb_y);

  /* Sum: '<Root>/Sum7' incorporates:
   *  Inport: '<Root>/Id_ref'
   */
  rtb_Sum7 = PMSMController_U.Id_ref - rtb_Sum7;

  /* Sum: '<Root>/Sum4' incorporates:
   *  DiscreteIntegrator: '<S89>/Integrator'
   *  Fcn: '<S4>/Fcn'
   *  Gain: '<S94>/Proportional Gain'
   *  Sum: '<S98>/Sum'
   */
  rtb_Sum4 = (0.24928537706235007 * rtb_Sum7 +
              PMSMController_DW.Integrator_DSTATE_e) + -PMSMController_Y.omega_e
    * 5.29e-5 * rtb_Sum4;

  /* Trigonometry: '<S156>/Trigonometric Function1' */
  rtb_y = cos(rtb_y);

  /* Sum: '<S156>/Sum' incorporates:
   *  Product: '<S156>/Product'
   *  Product: '<S156>/Product1'
   */
  rtb_Sum_e = rtb_Sum4 * rtb_y - rtb_Sum5 * rtb_Sum1_b;

  /* Sum: '<S156>/Sum1' incorporates:
   *  Product: '<S156>/Product2'
   *  Product: '<S156>/Product3'
   */
  rtb_y = rtb_Sum4 * rtb_Sum1_b + rtb_Sum5 * rtb_y;

  /* Outport: '<Root>/normalized voltages' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant6'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain3'
   *  Gain: '<Root>/Gain4'
   *  Gain: '<S157>/Gain1'
   *  Gain: '<S157>/Gain2'
   *  Gain: '<S157>/Gain4'
   *  Gain: '<S157>/Gain5'
   *  Inport: '<Root>/V_dc'
   *  Product: '<Root>/Divide'
   *  Product: '<Root>/Divide1'
   *  Product: '<Root>/Divide2'
   *  Sum: '<Root>/Sum'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<S157>/Sum'
   *  Sum: '<S157>/Sum1'
   */
  PMSMController_Y.normalizedvoltages[0] = rtb_Sum_e / (0.5 *
    PMSMController_U.V_dc) + 0.5;
  PMSMController_Y.normalizedvoltages[1] = (0.8660254037844386 * rtb_y - 0.5 *
    rtb_Sum_e) / (0.5 * PMSMController_U.V_dc) + 0.5;
  PMSMController_Y.normalizedvoltages[2] = ((0.0 - 0.5 * rtb_Sum_e) -
    0.8660254037844386 * rtb_y) / (0.5 * PMSMController_U.V_dc) + 0.5;

  /* Gain: '<S5>/Gain2' incorporates:
   *  Delay: '<S5>/Delay1'
   */
  PMSMController_DW.Delay1_DSTATE = 0.96907242630481061 * rtb_Sum1_f;

  /* MATLAB Function: '<Root>/speed_calc' incorporates:
   *  Delay: '<Root>/Delay2'
   *  Inport: '<Root>/theta_m'
   */
  for (rtb_Sum4 = PMSMController_U.theta_m - PMSMController_DW.Delay2_DSTATE;
       rtb_Sum4 > 3.1415926535897931; rtb_Sum4 -= 6.2831853071795862) {
  }

  while (rtb_Sum4 < -3.1415926535897931) {
    rtb_Sum4 += 6.2831853071795862;
  }

  /* End of MATLAB Function: '<Root>/speed_calc' */

  /* Gain: '<Root>/Gain9' incorporates:
   *  Delay: '<S5>/Delay'
   */
  PMSMController_DW.Delay_DSTATE = 10000.0 * rtb_Sum4;

  /* Update for DiscreteIntegrator: '<S41>/Integrator' incorporates:
   *  Gain: '<S34>/Kb'
   *  Gain: '<S38>/Integral Gain'
   *  Sum: '<S34>/SumI2'
   *  Sum: '<S34>/SumI4'
   */
  PMSMController_DW.Integrator_DSTATE += ((PMSMController_Y.T_ref - rtb_Sum_p) *
    1.25E-6 + 1.1780972450961725E-5 * rtb_Sum6) * 0.0001;

  /* Update for DiscreteIntegrator: '<S137>/Integrator' incorporates:
   *  Gain: '<S134>/Integral Gain'
   */
  PMSMController_DW.Integrator_DSTATE_d += 212.05750411731103 * rtb_Integrator_f
    * 0.0001;

  /* Update for DiscreteIntegrator: '<S89>/Integrator' incorporates:
   *  Gain: '<S86>/Integral Gain'
   */
  PMSMController_DW.Integrator_DSTATE_e += 212.05750411731103 * rtb_Sum7 *
    0.0001;

  /* Update for Delay: '<Root>/Delay2' incorporates:
   *  Inport: '<Root>/theta_m'
   */
  PMSMController_DW.Delay2_DSTATE = PMSMController_U.theta_m;
}

/* Model initialize function */
void PMSMController_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void PMSMController_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
