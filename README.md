# First hardware - Verilator, C++ testbench, Simulation

## Commands

1. ```verilator --cc first_hardware.sv --top-module counter_8bit --trace --exe first_hardware_testbench.cpp```
2. ```make -C obj_dir/ -f Vcounter_8bit.mk```

## Running simulation

- Binary file is produces in ```./obj_dir/Vcounter_8bit```. Just run it.

## Viewing simulation

- ```gtkwave dump.vcd```. Check testbench code, because dumping this data requires additional code in it.
