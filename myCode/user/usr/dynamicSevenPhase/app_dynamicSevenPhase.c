#ifdef APP_DYNAMICSEVENPHASE

#include "usr/dynamicSevenPhase/app_dynamicSevenPhase.h"
#include "usr/dynamicSevenPhase/cmd/cmd_dynamicSevenPhase.h"
#include "usr/dynamicSevenPhase/task_dynamicSevenPhase.h"
#include "drv/gpio_mux.h"

void app_dynamicSevenPhase_init(void)
{
    // Register "dynamicSevenPhase" command with system
    cmd_dynamicSevenPhase_register();

    // Initialize dynamicSevenPhase task with system
    task_dynamicSevenPhase_init();


    // Set up GPIO mux for the AMDS board
    // 0 means top AMDC port
    // GPIO_MUX_DEVICE2 means which mux I/O in the fpga that the AMDS driver is hooked up to.
    gpio_mux_set_device(0, GPIO_MUX_DEVICE2);

}

#endif // APP_DYNAMICSEVENPHASE
