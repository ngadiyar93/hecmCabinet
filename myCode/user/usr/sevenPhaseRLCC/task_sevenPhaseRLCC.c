#ifdef APP_SEVENPHASERLCC

#include "usr/sevenPhaseRLCC/task_sevenPhaseRLCC.h"
#include "usr/user_config.h"
#include <math.h>
#include <stdint.h>
#include "drv/pwm.h"
#include "sys/scheduler.h"
#include "drv/motherboard.h"
#include "usr/sevenPhaseRLCC/autogen/CurrentControl.h"
#include "drv/encoder.h"
#include "drv/analog.h"
#include "usr/encoderTest/task_encoderTest.h"
//#include "sys/injection.h"
//#include "sys/util.h"
//#include "sys/defines.h"
//#include "sys/cmd/cmd_inj.h"


// Scheduler TCB which holds task "context"
static task_control_block_t tcb;

// Initialize signal injection points
static inj_ctx_t inj_ctx_ctrl[6] = { 0 };

// Example logging variables for testing
double LOG_Iu = 0;
double LOG_Iv = 0;
double LOG_Iw = 0;
double LOG_Ix = 0;
double LOG_Iy = 0;
double LOG_Iz = 0;
double LOG_Ia = 0;
double LOG_rawIx = 0;
double LOG_Iq1ref = 0;
double LOG_Id1ref = 0;
double LOG_Iq5ref = 0;
double LOG_Id5ref = 0;
double LOG_Iq3ref = 0;
double LOG_Id3ref = 0;
double LOG_Id1 = 0;
double LOG_Iq1 = 0;
double LOG_Id3 = 0;
double LOG_Iq3 = 0;
double LOG_Id5 = 0;
double LOG_Iq5 = 0;
double LOG_Vd1ref = 0;
double LOG_Vq1ref = 0;
double LOG_Vd3ref = 0;
double LOG_Vq3ref = 0;
double LOG_Vd5ref = 0;
double LOG_Vq5ref = 0;

double LOG_theta_enc = 0;

static double f_sw = 60000.0; // [sec]
static double omega = 2*3.14*50;       // [rad/s]sevenPhaseRLCC freq 50


int task_sevenPhaseRLCC_init(void)
{
	  if (scheduler_tcb_is_registered(&tcb)) {
	        return FAILURE;
	    }

	    // Fill TCB with parameters
	    scheduler_tcb_init(&tcb, task_sevenPhaseRLCC_callback, NULL, "sevenPhaseRLCC", TASK_SEVENPHASERLCC_INTERVAL_USEC);
	    pwm_disable();
	    pwm_set_switching_freq(f_sw);
		//pwm_set_all_duty_midscale();
		pwm_enable();


	    // initialize autogen step
		CurrentControl_U.we = omega;
		CurrentControl_U.i1 = 0;
		CurrentControl_U.i2 = 0;
		CurrentControl_U.i3 = 0;
		CurrentControl_U.i4 = 0;
		CurrentControl_U.i5 = 0;
		CurrentControl_U.i6 = 0;
		CurrentControl_U.i7 = 0;
		CurrentControl_U.V_dc = Vdc;
		CurrentControl_U.id_ref = 0;
		CurrentControl_U.iq_ref = 0;
		CurrentControl_U.id3_ref = 0;
		CurrentControl_U.iq3_ref = 0;
		CurrentControl_U.id5_ref = 0;
		CurrentControl_U.iq5_ref = 0;


//		CurrentControl_initialize();
		encoder_set_pulses_per_rev_bits(14);

//	    injection_ctx_init(&inj_ctx_ctrl[0], "Id*");
//	    injection_ctx_init(&inj_ctx_ctrl[1], "Iq*");
//	    injection_ctx_init(&inj_ctx_ctrl[2], "Id3*");
//	    injection_ctx_init(&inj_ctx_ctrl[3], "Iq3*");
//	    injection_ctx_init(&inj_ctx_ctrl[4], "Id5*");
//	    injection_ctx_init(&inj_ctx_ctrl[5], "Iq5*");


//	    // Register all signal injection points
//	    for (int i = 0; i < ARRAY_SIZE(inj_ctx_ctrl); i++) {
//	        injection_ctx_register(&inj_ctx_ctrl[i]);
//	    }

	    // Register task with scheduler
	    return scheduler_tcb_register(&tcb);
}

int task_sevenPhaseRLCC_deinit(void)
{
//	for (int i = 0; i < ARRAY_SIZE(inj_ctx_ctrl); i++) {
//		        injection_ctx_clear(&inj_ctx_ctrl[i]);
//		    }
        //Unregister task with scheduler
    return scheduler_tcb_unregister(&tcb);
}


int read_cs(cabinet_cs_e cs, double *adc_volts_out)
{
    int err = FAILURE;
    int32_t out = 0;

    switch (cs) {
    case CABINET_CS_PH_U:
        err = motherboard_get_data(MOTHERBOARD_1_BASE_ADDR, MB_IN1, &out);
        *adc_volts_out = 0.00125 * (double) out;
        break;

    case CABINET_CS_PH_V:
        err = motherboard_get_data(MOTHERBOARD_1_BASE_ADDR, MB_IN2, &out);
        *adc_volts_out = 0.00125 * (double) out;
        break;

    case CABINET_CS_PH_W:
        err = motherboard_get_data(MOTHERBOARD_1_BASE_ADDR, MB_IN3, &out);
        *adc_volts_out = 0.00125 * (double) out;
        break;

    case CABINET_CS_PH_X:
		err = motherboard_get_data(MOTHERBOARD_1_BASE_ADDR, MB_IN4, &out);
		*adc_volts_out = 0.00125 * (double) out;
		break;

	case CABINET_CS_PH_Y:
		err = motherboard_get_data(MOTHERBOARD_1_BASE_ADDR, MB_IN5, &out);
		*adc_volts_out = 0.00125 * (double) out;
		break;

	case CABINET_CS_PH_Z:
		err = motherboard_get_data(MOTHERBOARD_1_BASE_ADDR, MB_IN6, &out);
		*adc_volts_out = 0.00125 * (double) out;
		break;

	case CABINET_CS_PH_A:
		err = motherboard_get_data(MOTHERBOARD_1_BASE_ADDR, MB_IN7, &out);
		*adc_volts_out = 0.00125 * (double) out;
		break;

    default:
        err = FAILURE;
    }

    // Magic delta value to deal with odd analog design... :(
    // Specific to CurrentCard design, perhaps VoltageCard as well.
    //
    // ==> at 0A input, the CurrentCard ADC voltage input is mid-rail,
    //     about 2.4V, and -FS current is about 0.2V, +FS is ~4.8V.
    //
    //     The binary ADC codes for these are odd, they go from
    //     negative to positive weirdly. I haven't debugged if
    //     this is actually correct of not... So, this DELTA value
    //     shifts them around to get a nice linear output
    //     relative to the current input value.
    double DELTA = (double) 0xFFFF * 0.00125 / 2.0;
    if (*adc_volts_out > 0) {
        *adc_volts_out -= DELTA;
    } else {
        *adc_volts_out += DELTA;
    }

    return err;
}

//static double Id_star = 0;
//static double Iq_star = 0;
//static double Id3_star = 0;
//static double Iq3_star = 0;
//static double Id5_star = 0;
//static double Iq5_star = 0;

double Ts_local = 1.0/(double)TASK_SEVENPHASERLCC_UPDATES_PER_SEC;

int task_read_Bfield(void)

{//   float V_gain = 1.03;

//    float V_offset = 2.536;
      float V_gain = 1.1;

      float V_offset = 2.524;

      float V_meas;

        int err = analog_getf(ANALOG_IN1, &V_meas);

        if (err == SUCCESS) {

               float flux_density = (V_meas - V_offset)/V_gain;

               cmd_resp_printf("%f\r\n", flux_density);

        }

        return err;

}


void task_sevenPhaseRLCC_callback(void *arg)
{
	// Injection active
//		 injection_inj(&Id_star, &inj_ctx_ctrl[0], Ts_local);
//		 injection_inj(&Iq_star, &inj_ctx_ctrl[1], Ts_local);
//		 injection_inj(&Id3_star, &inj_ctx_ctrl[0], Ts_local);
//		 injection_inj(&Iq3_star, &inj_ctx_ctrl[1], Ts_local);
//		 injection_inj(&Id5_star, &inj_ctx_ctrl[0], Ts_local);
//		 injection_inj(&Iq5_star, &inj_ctx_ctrl[1], Ts_local);
//
//		 CurrentControl_U.id_ref = Id_star;
//		 CurrentControl_U.iq_ref = Iq_star;
//		 CurrentControl_U.id3_ref= Id3_star;
//		 CurrentControl_U.iq3_ref = Iq3_star;
//		 CurrentControl_U.id5_ref = Id5_star;
//		 CurrentControl_U.iq5_ref = Iq5_star;
		 //

	// call the current controller

	 // Update theta
		double VuDuty, VvDuty, VwDuty, VxDuty, VyDuty, VzDuty, VaDuty;

		// get currents
		double Iu, Iv, Iw, Ix, Iy, Iz, Ia;


		read_cs(CABINET_CS_PH_U, &Iu);
		read_cs(CABINET_CS_PH_V, &Iv);
		read_cs(CABINET_CS_PH_W, &Iw);
		read_cs(CABINET_CS_PH_X, &Ix);
		read_cs(CABINET_CS_PH_Y, &Iy);
		read_cs(CABINET_CS_PH_Z, &Iz);
		read_cs(CABINET_CS_PH_A, &Ia);

		// scale currents
		CurrentControl_U.i1 = (double)PHASE_U_CURRENT_GAIN*(Iu) - PHASE_U_CURRENT_OFFSET;
		CurrentControl_U.i2 = (double)PHASE_V_CURRENT_GAIN*(Iv) - PHASE_V_CURRENT_OFFSET;
		CurrentControl_U.i3 = (double)PHASE_W_CURRENT_GAIN*(Iw) - PHASE_W_CURRENT_OFFSET;
		CurrentControl_U.i4 = (double)PHASE_X_CURRENT_GAIN*(Ix) - PHASE_X_CURRENT_OFFSET;
		CurrentControl_U.i5 = (double)PHASE_Y_CURRENT_GAIN*(Iy) - PHASE_Y_CURRENT_OFFSET;
		CurrentControl_U.i6 = (double)PHASE_Z_CURRENT_GAIN*(Iz) - PHASE_Z_CURRENT_OFFSET;
		CurrentControl_U.i7 = (double)PHASE_A_CURRENT_GAIN*(Ia) - PHASE_A_CURRENT_OFFSET;

		LOG_rawIx = (float)Ix;

		// Input voltage. Replace with sensed voltage
		CurrentControl_U.V_dc = Vdc;

		// Update logging variables
		LOG_Iu = (float) (CurrentControl_U.i1);
		LOG_Iv = (float) (CurrentControl_U.i2);
		LOG_Iw = (float) (CurrentControl_U.i3);
		LOG_Ix = (float) (CurrentControl_U.i4);
		LOG_Iy = (float) (CurrentControl_U.i5);
		LOG_Iz = (float) (CurrentControl_U.i6);
		LOG_Ia = (float) (CurrentControl_U.i7);

		LOG_Id1 =(float)(CurrentControl_Y.LOG1_i_sv_id1);
		LOG_Iq1 =(float)(CurrentControl_Y.LOG1_i_sv_iq1);
		LOG_Id3 =(float)(CurrentControl_Y.LOG1_i_sv_id3);
		LOG_Iq3 =(float)(CurrentControl_Y.LOG1_i_sv_iq3);
		LOG_Id5 =(float)(CurrentControl_Y.LOG1_i_sv_id5);
		LOG_Iq5 =(float)(CurrentControl_Y.LOG1_i_sv_iq5);


		LOG_Iq1ref = (float)(CurrentControl_U.iq_ref);
		LOG_Id1ref = (float)(CurrentControl_U.id_ref);
		LOG_Iq3ref = (float)(CurrentControl_U.iq3_ref);
		LOG_Id3ref = (float)(CurrentControl_U.id3_ref);
		LOG_Iq5ref = (float)(CurrentControl_U.iq5_ref);
		LOG_Id5ref = (float)(CurrentControl_U.id5_ref);

		LOG_Vq1ref = (float)(CurrentControl_Y.LOG1_v_sv_vq_ref);
		LOG_Vd1ref = (float)(CurrentControl_Y.LOG1_v_sv_vd_ref);
		LOG_Vq3ref = (float)(CurrentControl_Y.LOG1_v_sv_vq3_ref);
		LOG_Vd3ref = (float)(CurrentControl_Y.LOG1_v_sv_vd3_ref);
		LOG_Vq5ref = (float)(CurrentControl_Y.LOG1_v_sv_vq5_ref);
		LOG_Vd5ref = (float)(CurrentControl_Y.LOG1_v_sv_vd5_ref);

		// execute code
		CurrentControl_step();

		// assign duty cycle
		VuDuty = CurrentControl_Y.NormalizedVoltages1[0];
		VvDuty = CurrentControl_Y.NormalizedVoltages1[1];
		VwDuty = CurrentControl_Y.NormalizedVoltages1[2];
		VxDuty = CurrentControl_Y.NormalizedVoltages1[3];
		VyDuty = CurrentControl_Y.NormalizedVoltages1[4];
		VzDuty = CurrentControl_Y.NormalizedVoltages1[5];
		VaDuty = CurrentControl_Y.NormalizedVoltages1[6];

		pwm_set_duty(3, VuDuty);
		pwm_set_duty(4, VvDuty);
		pwm_set_duty(5, VwDuty);
		pwm_set_duty(6, VxDuty);
		pwm_set_duty(7, VyDuty);
		pwm_set_duty(8, VzDuty);
		pwm_set_duty(9, VaDuty);

		LOG_theta_enc = read_encoder();

}

//void task_sevenPhaseRLCC_stats_print(void)
//{
//    task_stats_print(&tcb.stats);
//}
//
//void task_sevenPhaseRLCC_stats_reset(void)
//{
//    task_stats_reset(&tcb.stats);
//}

#endif // APP_SEVENPHASERLCC
