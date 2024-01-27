#include "stdio.h"

#include "program.h"
#include "common.h"


int main(int argc, char *argv[])
{
    /*put your initializations here*/
    PROG_init();
    //game init

    /*pass your logic and redner functions here */
    //PROG_setRenderCbk(void (*vidRenderFPTR)(void));
    //PROG_setUpdateCbk(void (*vidLogicFPTR)(void));

    PROG_run();//game running

    /*put your deinitialization here*/
    PROG_deinit();
    //game deinit

    return 0;
}
