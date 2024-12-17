module counter_8bit (
  input  logic       clk, // Clock input
  input  logic       rst, // Active-high synchronous reset
  output logic [7:0] count // 8-bit counter ouput
);

  // Synchronous process triggered on the rising edge of clk
  always_ff @(posedge clk) begin
    if (rst) begin
      // Reset the counter to zero when rst is high
      count <= 8'h00;
    end else begin
      count <= count + 1'b1;
    end
  end

endmodule 
