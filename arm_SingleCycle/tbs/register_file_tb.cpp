#include <cassert>
#include <cstdint>
#include <iostream>
#include "Vregister_file.h"
#include "../utils/TracerHelp.h"
#include "../utils/RandomHelp.h"
#include <limits>

#include "verilated.h"

typedef Vregister_file DUT;
typedef std::shared_ptr<DUT> DUTPtr;

void RandomizeDut(const DUTPtr& dut);

int
main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);
    DUTPtr dut = std::make_shared<DUT>();
    TracerPtr tracer = GetTracer();
    dut->trace(tracer.get(), TRACE_LEVEL);
    tracer->open(DUMP_FILE);

    RandomizeDut(dut);
    dut->i_clk_w = 1;
    for(int i = 0; i < 100; i++)
    {
        dut->i_clk_w ^= 1; // cc0 = 0; cc1 = 1 ->> odd cc = posedge
        dut->i_rst_w = 0;
        if(i < 3){
            dut->i_rst_w = 0b1 & 0b0001;
        }

        if(i == 5){
            dut->i_write_addr_w = 3 & 0xF;
            dut->i_write_data_w = 0x0012 & 0xFFFF'FFFF;
            dut->i_reg_write_w = 0b0001; 
        }
        if(i == 7){
            dut->i_write_addr_w = 0;
            dut->i_write_data_w = 0;
            dut->i_reg_write_w = 0;
        }
        if(i == 9){
            dut->i_read_addr_a_w = 3 & 0xF;
            dut->i_read_addr_b_w = 15 & 0xF;
            dut->i_r15_w = 104;
            assert( (dut->o_data_out_a_w == (0x0012 & 0xFFFF'FFFF)) );
        }
        if(i == 19){
            assert( (dut->o_data_out_b_w == 104) );
            dut->i_read_addr_a_w = 0;
            dut->i_read_addr_b_w = 0;
            dut->i_r15_w = 0;
            dut->i_write_addr_w = 15 & 0xF;
            dut->i_write_data_w = 50;
            dut->i_reg_write_w = 1;
        }
        if(i == 25){
            dut->i_reg_write_w = 0;
            dut->i_write_addr_w = 0;
            dut->i_write_data_w = 0;
            dut->i_read_addr_a_w = 15 & 0xF;
            assert( (dut->o_data_out_a_w != 50));
        }

        dut->eval();
        tracer->dump(i);
    }

    std::rand();
    return 0;
}

void
RandomizeDut(const DUTPtr& dut)
{
    dut->i_clk_w         = GetRandomU32(0, 1);
    dut->i_rst_w         = GetRandomU32(0, 1);
    dut->i_reg_write_w   = GetRandomU32(0, 1);
    dut->i_r15_w         = GetRandomU32(0, std::numeric_limits<uint32_t>::max());
    dut->i_write_data_w  = GetRandomU32(0, std::numeric_limits<uint32_t>::max());
    dut->i_read_addr_a_w = GetRandomU32(0, 15);
    dut->i_read_addr_b_w = GetRandomU32(0, 15);
    dut->i_write_addr_w  = GetRandomU32(0, 15);
}