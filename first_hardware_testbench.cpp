#include <iostream>
#include "Vcounter_8bit.h" // This header is created by --top-module option (check README.md)
#include "verilated.h"
#include "verilated_vcd_c.h"


int main(int argc, char** argv, char** env) {
  // Initialize Verilator - passing command line arguments
  Verilated::commandArgs(argc, argv);

  // Instantiate our design
  Vcounter_8bit* top = new Vcounter_8bit;

  // If tracing is enabled, prepare the VCD output
  VerilatedVcdC* tfp = nullptr;
  const bool trace_on = true; // Setting trace
  if (trace_on) {
    Verilated::traceEverOn(true);
    tfp = new VerilatedVcdC;
    top->trace(tfp, 99); // Trace 99 levels of hierarchy
    tfp->open("dump.vcd");
  }

  // Define a simulation time and a clock toggle function
  vluint64_t sim_time = 0;
  auto toggle_clock = [&](int cycles = 1) { // Lambda function to push the simulation forward
    for (int i = 0; i < cycles; i++) {
      // Toggle clock: rising edge
      top->clk = 1;
      top->eval();
      if (tfp) tfp->dump(sim_time++);

      // Toggle clock: falling edge
      top->clk = 0;
      top->eval();
      if (tfp) tfp->dump(sim_time++);
    }
  };

  // Initial conditions
  top->rst = 1;
  top->clk = 0;
  top->eval();

  // Apply reset for a few cycles
  toggle_clock(2);

  // Release reset
  top->rst = 0;
  top->eval();

  // Run the simulation for a few cycles and print the counter
  for (int cycle = 0; cycle < 20; cycle++) {
    toggle_clock(1);
    std::cout << "Cycle " << cycle << ": count = " << (int)top->count << std::endl;
  }

  // Final cleanup
  top->final();
  if (tfp) {
    tfp->close();
    delete tfp;
  }
  delete top;

  return 0;
}
