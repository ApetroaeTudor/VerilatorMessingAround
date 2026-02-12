#pragma once

#include "verilated_fst_c.h"

typedef std::shared_ptr<VerilatedFstC>   TracerPtr;

constexpr const char* const DUMP_FILE = "waveform.fst";
constexpr int TRACE_LEVEL = 5;

TracerPtr
GetTracer()
{
    TracerPtr tracer = std::make_shared<VerilatedFstC>();
    Verilated::traceEverOn(true);

    return tracer;
}