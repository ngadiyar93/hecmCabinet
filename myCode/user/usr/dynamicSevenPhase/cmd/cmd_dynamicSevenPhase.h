#ifndef CMD_DYNAMICSEVENPHASE_H
#define CMD_DYNAMICSEVENPHASE_H

#define IdLim (5)
#define IqLim (100)

// Called in app init function to register command with system
void cmd_dynamicSevenPhase_register(void);

// Function called when user types "dynamicSevenPhase" command into command prompt
// i.e., this is the dynamicSevenPhase command handler function
int cmd_dynamicSevenPhase(int argc, char **argv);

#endif // CMD_DYNAMICSEVENPHASE_H

