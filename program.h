#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

void PROG_init();
void PROG_run();
void PROG_deinit();
void PROG_setRenderCbk(void (*vidRenderFPTR)(void));
void PROG_setUpdateCbk(void (*vidLogicFPTR)(void));


#endif // PROGRAM_H_INCLUDED
