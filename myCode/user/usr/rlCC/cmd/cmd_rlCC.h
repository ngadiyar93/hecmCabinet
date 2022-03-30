#ifndef CMD_RLCC_H
#define CMD_RLCC_H

#define IdLim (3)
#define IqLim (3)

// Called in app init function to register command with system
void cmd_rlCC_register(void);

// Function called when user types "rlCC" command into command prompt
// i.e., this is the rlCC command handler function
int cmd_rlCC(int argc, char **argv);

#endif // CMD_RLCC_H
