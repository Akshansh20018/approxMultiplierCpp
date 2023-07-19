`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 17.07.2023 16:41:18
// Design Name: 
// Module Name: tb_top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_top();

reg [31:0] a,b;
wire [31:0] result;

top t1(a,b,result);

initial begin
a = {1'b0,{6'b0,2'b10}, 23'b11110011001100110011010};
b = {1'b0,{6'b0,2'b10}, 23'b11110011001100110011010};
// 7.8 given explicitly
//a = 32'b0_00000010_11110011001100110011010;
//b = 32'b0_00000010_11110011001100110011010;
#10

// 7.5 * 7.5
a = {1'b0,{6'b0,2'b10}, {3'b111, 20'b0}}; // Try inverting the number order.
b = {1'b0,{6'b0,2'b10}, {3'b111, 20'b0}}; 

#10
// 2.5 *1.5 (to check when not transferred)
a = {1'b0,7'b0, 1'b1,2'b01,21'b0 }; 
b = {1'b0,8'b0,1'b1,22'b0 }; 

#10 $finish;
end

endmodule
