#include <iostream>
#include <memory>
#include <cstdint>

#include "Vpc.h"
#include "Vpc___024root.h"
#include "../utils/TracerHelp.h"
#include "verilated.h"

typedef std::shared_ptr<Vpc> DUTPtr;

int 
main(int argc, char** argv)
{
    Verilated::commandArgs(argc,argv);
    DUTPtr DUT       = std::make_shared<Vpc>();
    TracerPtr tracer = GetTracer();
    DUT->trace(tracer.get(), TRACE_LEVEL);
    tracer->open(DUMP_FILE);

    for(int i = 0; i < 50; i++){
        DUT->i_rst_w = 0;
        DUT->i_clk_w ^=1;
        DUT->i_data_w = 0;
        if(i < 5){
            DUT->i_rst_w = 0b1 & 0x0001;
        }
        if(i >= 7 && i <= 10){
            DUT->i_data_w = 42 & 0xFFFF'FFFF;
        }

        DUT->eval();
        tracer->dump(i);
    }
    
    return 0;
}