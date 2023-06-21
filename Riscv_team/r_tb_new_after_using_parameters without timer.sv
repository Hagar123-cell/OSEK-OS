//`timescale 1ns / 1ps
module tb_riscv_steel_core();

  reg           clock;
  reg           reset;
  reg   [31:0]  instruction_in;
  reg   [31:0]  data_in;
  reg   [31:0]  ram [0:524287]; // 2 MB RAM memory
  //reg   [31:0]  mem [0:524287]; // 2 MB data memory
  wire          data_write_request;
  wire  [31:0]  instruction_address;
  wire  [31:0]  data_rw_address;
  wire  [31:0]  data_out;
  wire  [3:0 ]  data_write_mask;
  
  
  
    wire   [31:0]  context_register_x1;
    wire   [31:0]  context_register_x2;
    wire   [31:0]  context_register_x3;
    wire   [31:0]  context_register_x4;	
    wire   [31:0]  context_register_x5;
    wire   [31:0]  context_register_x6;
    wire   [31:0]  context_register_x7;
    wire   [31:0]  context_register_x8;
    wire   [31:0]  context_register_x9;
    wire   [31:0]  context_register_x10;
    wire   [31:0]  context_register_x11;
    wire   [31:0]  context_register_x12;
    wire   [31:0]  context_register_x13;
    wire   [31:0]  context_register_x14;
    wire   [31:0]  context_register_x15;
    wire   [31:0]  context_register_x16;
    wire   [31:0]  context_register_x17;
    wire   [31:0]  context_register_x18;
    wire   [31:0]  context_register_x19;
    wire   [31:0]  context_register_x20;
    wire   [31:0]  context_register_x21;
    wire   [31:0]  context_register_x22;
    wire   [31:0]  context_register_x23;
    wire   [31:0]  context_register_x24;
    wire   [31:0]  context_register_x25;
    wire   [31:0]  context_register_x26;
    wire   [31:0]  context_register_x27;
    wire   [31:0]  context_register_x28;
    wire   [31:0]  context_register_x29;
    wire   [31:0]  context_register_x30;
    wire   [31:0]  context_register_x31;
    wire           save_context;
    wire           load_context;
    reg   [31:0]  stack_pointer;
	reg   [31:0]  sp;
  
  
	reg   [31:0]  context_registers_selction;
  riscv_steel_core dut (

    // Basic system signals
    .clock                      (clock                ),
    .reset                      (reset                ),
    .boot_address               (32'h00000000         ), // boot address of all test programs

    // Instruction fetch interface
    .instruction_address        (instruction_address  ),
    .instruction_in             (instruction_in       ),
      
    // Data fetch/write interface
	.context_registers_selction (context_registers_selction            ),
	.context_register_x1  (context_register_x1                         ),
	.context_register_x2  (context_register_x2                         ),
	.context_register_x3  (context_register_x3                         ),
	.context_register_x4  (context_register_x4                         ),
	.context_register_x5  (context_register_x5                         ),
	.context_register_x6  (context_register_x6                         ),
	.context_register_x7 (context_register_x7                         ),
	.context_register_x8 (context_register_x8                         ),
	.context_register_x9 (context_register_x9                         ),
	.context_register_x10 (context_register_x10                         ),
	.context_register_x11 (context_register_x11                         ),
	.context_register_x12 (context_register_x12                         ),
	.context_register_x13 (context_register_x13                         ),
	.context_register_x14 (context_register_x14                         ),
	.context_register_x15 (context_register_x15                         ),
	.context_register_x16 (context_register_x16                         ),
	.context_register_x17 (context_register_x17                         ),
	.context_register_x18 (context_register_x18                         ),
	.context_register_x19 (context_register_x19                         ),
	.context_register_x20 (context_register_x20                         ),
	.context_register_x21 (context_register_x21                         ),
	.context_register_x22 (context_register_x22                         ),
	.context_register_x23 (context_register_x23                         ),
	.context_register_x24 (context_register_x24                         ),
	.context_register_x25 (context_register_x25                         ),
	.context_register_x26 (context_register_x26                         ),
	.context_register_x27 (context_register_x27                         ),
	.context_register_x28 (context_register_x28                         ),
	.context_register_x29 (context_register_x29                         ),
	.context_register_x30 (context_register_x30                         ),
	.context_register_x31 (context_register_x31                         ),
	.save_context         (         save_context                                    ),
	.load_context         (          load_context                                   ),
	.stack_pointer        (            stack_pointer                                 ),
    .data_rw_address            (data_rw_address      ),
    .data_out                   (data_out             ),
    .data_write_request         (data_write_request   ),
    .data_write_mask            (data_write_mask      ),
    .data_in                    (data_in              ),
    
    // Interrupt signals (hardwired to zero because they're not needed for the tests)
    .interrupt_request_external (1'b0                 ),
    .interrupt_request_timer    (1'b0                 ),
    .interrupt_request_software (1'b0                 ),

    // Real Time Counter (hardwired to zero because they're not needed too)
    .real_time                  (64'b0                )

  );
  memory data_memory (.clock(clock),
			.reset              (reset              ),
			.context_registers_selction(context_registers_selction),
			.context_register_x1(context_register_x1),
			.context_register_x2(context_register_x2),
			.context_register_x3(context_register_x3),
			.context_register_x4(context_register_x4),
			.context_register_x5(context_register_x5),
			.context_register_x6(context_register_x6),
			.context_register_x7(context_register_x7),
			.context_register_x8(context_register_x8),
			.context_register_x9(context_register_x9),
			.context_register_x10(context_register_x10),
			.context_register_x11(context_register_x11),
			.context_register_x12(context_register_x12),
			.context_register_x13(context_register_x13),
			.context_register_x14(context_register_x14),
			.context_register_x15(context_register_x15),
			.context_register_x16(context_register_x16),
			.context_register_x17(context_register_x17),
			.context_register_x18(context_register_x18),
			.context_register_x19(context_register_x19),
			.context_register_x20(context_register_x20),
			.context_register_x21(context_register_x21),
			.context_register_x22(context_register_x22),
			.context_register_x23(context_register_x23),
			.context_register_x24(context_register_x24),
			.context_register_x25(context_register_x25),
			.context_register_x26(context_register_x26),
			.context_register_x27(context_register_x27),
			.context_register_x28(context_register_x28),
			.context_register_x29(context_register_x29),
			.context_register_x30(context_register_x30),
			.context_register_x31(context_register_x31),
			.save_context(save_context),
			.load_context(load_context),
			.stack_pointer(stack_pointer),
			.data_rw_address(data_rw_address),
			.data_out(data_out),
			.data_write_request(data_write_request),
			.data_in(data_in),
			.data_write_mask(data_write_mask));
  
  // RAM output registers
  always @(posedge clock) begin
    if (reset) begin
      //data_in            <= 32'h00000000;
      instruction_in     <= 32'h00000000;
    end
    else begin
      //data_in            <= mem[data_rw_address     [24:2]];
      instruction_in     <= ram[instruction_address [24:2]];
    end
  end

  
  // 50MHz clock signal
initial begin
  clock=0;
  context_registers_selction = 32'hFFFFFFE2 ;// context registers to be saved 
  forever
  #1clock=~clock;
end  
  initial begin
  
    reset = 1'b0;        
    clock = 1'b0;
    $display("Running test programs from RISC-V Compatibility Test Framework v2.0.");
    
      reset = 1'b1;
      #20;
      reset = 1'b0;
      // Clear RAM
      for(int i = 0; i < 524287; i++) ram[i] = 32'b0;
      // Load test program into RAM
      $readmemh("testriscv.mem",ram); 
      #200;
      $stop;
      
   
  end
  initial begin
    //$monitor("address=%0d,data=%0d",data_rw_address,mem_associative[data_rw_address]);
  end
  
endmodule

module memory #( parameter x1_offset = 2 ,
				parameter x2_offset = 2 ,
				parameter x3_offset = 3 ,
				parameter x4_offset = 4 ,
				parameter x5_offset = 3 ,
				parameter x6_offset = 4 ,
				parameter x7_offset = 5 ,
				parameter x8_offset = 6 ,
				parameter x9_offset = 7 ,
				parameter x10_offset = 8 ,
				parameter x11_offset = 9 ,
				parameter x12_offset = 10 ,
				parameter x13_offset = 11 ,
				parameter x14_offset = 12 ,
				parameter x15_offset = 13 ,
				parameter x16_offset = 14 ,
				parameter x17_offset = 15 ,
				parameter x18_offset = 16 ,
				parameter x19_offset = 17 ,
				parameter x20_offset = 18 ,
				parameter x21_offset = 19 ,
				parameter x22_offset = 20 ,
				parameter x23_offset = 21 ,
				parameter x24_offset = 22 ,
				parameter x25_offset = 23 ,
				parameter x26_offset = 24 ,
				parameter x27_offset = 25 ,
				parameter x28_offset = 26 ,
				parameter x29_offset = 27 ,
				parameter x30_offset = 28 ,
				parameter x31_offset = 29 
				) 
				(input wire clock,
			input wire reset,
			input  wire   [31:0]  context_registers_selction,
			inout  wire   [31:0]  context_register_x1,
			inout  wire   [31:0]  context_register_x2,
			inout  wire   [31:0]  context_register_x3,
			inout  wire   [31:0]  context_register_x4,
			inout  wire   [31:0]  context_register_x5,
			inout  wire   [31:0]  context_register_x6,
			inout  wire   [31:0]  context_register_x7,
			inout  wire   [31:0]  context_register_x8,
			inout  wire   [31:0]  context_register_x9,
			inout  wire   [31:0]  context_register_x10,
			inout  wire   [31:0]  context_register_x11,
			inout  wire   [31:0]  context_register_x12,
			inout  wire   [31:0]  context_register_x13,
			inout  wire   [31:0]  context_register_x14,
			inout  wire   [31:0]  context_register_x15,
			inout  wire   [31:0]  context_register_x16,
			inout  wire   [31:0]  context_register_x17,
			inout  wire   [31:0]  context_register_x18,
			inout  wire   [31:0]  context_register_x19,
			inout  wire   [31:0]  context_register_x20,
			inout  wire   [31:0]  context_register_x21,
			inout  wire   [31:0]  context_register_x22,
			inout  wire   [31:0]  context_register_x23,
			inout  wire   [31:0]  context_register_x24,
			inout  wire   [31:0]  context_register_x25,
			inout  wire   [31:0]  context_register_x26,
			inout  wire   [31:0]  context_register_x27,
			inout  wire   [31:0]  context_register_x28,
			inout  wire   [31:0]  context_register_x29,
			inout  wire   [31:0]  context_register_x30,
			inout  wire   [31:0]  context_register_x31,
			input wire           save_context,
			input wire           load_context,
			input reg   [31:0]  stack_pointer,
			input wire   [31:0]  data_rw_address,
			input wire   [31:0]  data_out,
			input wire           data_write_request,
			input wire   [3:0 ]  data_write_mask,
			output  reg   [31:0]  data_in);
  
  reg   [31:0]  mem [0:524287]; // 2 MB data memory
  reg   [31:0]  sp = 0;
  
  
  
  
assign context_register_x1 = ((load_context==1'b1) && (context_registers_selction[1] ==1 ))  ? mem[stack_pointer     [24:2] + x1_offset ]   :  'bz ;
assign context_register_x2 = ((load_context==1'b1) && (context_registers_selction[2] ==1 ))  ? mem[stack_pointer     [24:2] +x2_offset ]   :  'bz ;
assign context_register_x3 = ((load_context==1'b1) && (context_registers_selction[3] ==1 ))  ? mem[stack_pointer     [24:2] +x3_offset ]   :  'bz ;
assign context_register_x4 = ((load_context==1'b1) && (context_registers_selction[4] ==1 ))  ? mem[stack_pointer     [24:2] +x4_offset ]   :  'bz ;
assign context_register_x5 = ((load_context==1'b1) && (context_registers_selction[5] ==1 ))  ? mem[stack_pointer     [24:2] +x5_offset ]    :  'bz ;
assign context_register_x6 = ((load_context==1'b1) && (context_registers_selction[6] ==1 ))  ? mem[stack_pointer     [24:2] +x6_offset ]   :  'bz ;
assign context_register_x7 = ((load_context==1'b1) && (context_registers_selction[7] ==1 ))  ? mem[stack_pointer     [24:2] +x7_offset ] : 'bz ;
assign context_register_x8 = ((load_context==1'b1) && (context_registers_selction[8] ==1 ))  ? mem[stack_pointer     [24:2] +x8_offset ]  : 'bz ;
assign context_register_x9 = ((load_context==1'b1) && (context_registers_selction[9] ==1 ))  ? mem[stack_pointer     [24:2] +x9_offset ]  : 'bz ;
assign context_register_x10 = ((load_context==1'b1) && (context_registers_selction[10] ==1 ))  ? mem[stack_pointer     [24:2] +x10_offset ]  : 'bz ;
assign context_register_x11 = ((load_context==1'b1) && (context_registers_selction[11] ==1 ))  ? mem[stack_pointer     [24:2] +x11_offset ]  : 'bz ;
assign context_register_x12 = ((load_context==1'b1) && (context_registers_selction[12] ==1 ))  ? mem[stack_pointer     [24:2] +x12_offset ] : 'bz ;
assign context_register_x13 = ((load_context==1'b1) && (context_registers_selction[13] ==1 ))  ? mem[stack_pointer     [24:2] +x13_offset ]  : 'bz ;
assign context_register_x14 = ((load_context==1'b1) && (context_registers_selction[14] ==1 ))  ? mem[stack_pointer     [24:2] +x14_offset ]  : 'bz ;
assign context_register_x15 = ((load_context==1'b1) && (context_registers_selction[15] ==1 ))  ? mem[stack_pointer     [24:2] +x15_offset ]  : 'bz ;
assign context_register_x16 = ((load_context==1'b1) && (context_registers_selction[16] ==1 ))  ? mem[stack_pointer     [24:2] +x16_offset ] : 'bz ;
assign context_register_x17 = ((load_context==1'b1) && (context_registers_selction[17] ==1 ))  ? mem[stack_pointer     [24:2] +x17_offset ]  : 'bz ;
assign context_register_x18 = ((load_context==1'b1) && (context_registers_selction[18] ==1 ))  ? mem[stack_pointer     [24:2] +x18_offset ]  : 'bz ;
assign context_register_x19 = ((load_context==1'b1) && (context_registers_selction[19] ==1 ))  ? mem[stack_pointer     [24:2] +x19_offset ]  : 'bz ;
assign context_register_x20 = ((load_context==1'b1) && (context_registers_selction[20] ==1 ))  ? mem[stack_pointer     [24:2] +x20_offset ]  : 'bz ;
assign context_register_x21 = ((load_context==1'b1) && (context_registers_selction[21] ==1 ))  ? mem[stack_pointer     [24:2] +x21_offset ]  : 'bz ;
assign context_register_x22 = ((load_context==1'b1) && (context_registers_selction[22] ==1 ))  ? mem[stack_pointer     [24:2] +x22_offset ]  : 'bz ;
assign context_register_x23 = ((load_context==1'b1) && (context_registers_selction[23] ==1 ))  ? mem[stack_pointer     [24:2] +x23_offset ]  : 'bz ;
assign context_register_x24 = ((load_context==1'b1) && (context_registers_selction[24] ==1 ))  ? mem[stack_pointer     [24:2] +x24_offset ]  : 'bz ;
assign context_register_x25 = ((load_context==1'b1) && (context_registers_selction[25] ==1 ))  ? mem[stack_pointer     [24:2] +x25_offset ]  : 'bz ;
assign context_register_x26 = ((load_context==1'b1) && (context_registers_selction[26] ==1 ))  ? mem[stack_pointer     [24:2] +x26_offset ]  : 'bz ;
assign context_register_x27 = ((load_context==1'b1) && (context_registers_selction[27] ==1 ))  ? mem[stack_pointer     [24:2] +x27_offset ]  : 'bz ;
assign context_register_x28 = ((load_context==1'b1) && (context_registers_selction[28] ==1 ))  ? mem[stack_pointer     [24:2] +x28_offset ]  : 'bz ;
assign context_register_x29 = ((load_context==1'b1) && (context_registers_selction[29] ==1 ))  ? mem[stack_pointer     [24:2] +x29_offset ]  : 'bz ;
assign context_register_x30 = ((load_context==1'b1) && (context_registers_selction[30] ==1 ))  ? mem[stack_pointer     [24:2] +x30_offset ]  : 'bz ;
assign context_register_x31 = ((load_context==1'b1) && (context_registers_selction[31] ==1 ))  ? mem[stack_pointer     [24:2] +x31_offset ]  : 'bz ;

  
  
  
  
  // RAM output registers
  always @(posedge clock) begin
    if (reset) begin
      data_in            <= 32'h00000000;
    end
    else begin
      data_in            <= mem[data_rw_address     [24:2]];
    end
  end
  
  // 64 KB RAM memory implementation
  always @(posedge clock) begin
    if(data_write_request) begin
      if(data_write_mask[0])begin
        mem[data_rw_address[24:2] ][7:0  ]  <= data_out[7:0  ];
      end
      if(data_write_mask[1]) begin
        mem[data_rw_address[24:2] ][15:8 ]  <= data_out[15:8 ];
      end
      if(data_write_mask[2])begin
        mem[data_rw_address[24:2] ][23:16]  <= data_out[23:16];
      end
      if(data_write_mask[3])begin
        mem[data_rw_address[24:2] ][31:24]  <= data_out[31:24];
      end
    end
	else if(save_context)begin
		mem[stack_pointer     [24:2] + x1_offset ] = (context_registers_selction[1] ==1 ) ? context_register_x1 :mem[stack_pointer     [24:2] + x1_offset ];
		mem[stack_pointer     [24:2] + x2_offset ] = (context_registers_selction[2] ==1 ) ? context_register_x2: mem[stack_pointer     [24:2] + x2_offset ] ;
		mem[stack_pointer     [24:2] + x3_offset ] = (context_registers_selction[3] ==1 ) ? context_register_x3: mem[stack_pointer     [24:2] + x3_offset ]  ;
		mem[stack_pointer     [24:2] + x4_offset ] = (context_registers_selction[4] ==1 ) ? context_register_x4: mem[stack_pointer     [24:2] + x4_offset ] ;
		mem[stack_pointer     [24:2] + x5_offset ] = (context_registers_selction[5] ==1 ) ? context_register_x5: mem[stack_pointer     [24:2] + x5_offset ] ;
		mem[stack_pointer     [24:2] + x6_offset] = (context_registers_selction[6] ==1 ) ? context_register_x6: mem[stack_pointer     [24:2] + x6_offset] ;
		mem[stack_pointer     [24:2] +x7_offset] = (context_registers_selction[7] ==1 ) ? context_register_x7: mem[stack_pointer     [24:2] +x7_offset] ;
		mem[stack_pointer     [24:2] +x8_offset] = (context_registers_selction[8] ==1 ) ? context_register_x8: mem[stack_pointer     [24:2] +x8_offset] ;
		mem[stack_pointer     [24:2] +x9_offset] = (context_registers_selction[9] ==1 ) ? context_register_x9: mem[stack_pointer     [24:2] +x9_offset] ;
		mem[stack_pointer     [24:2] +x10_offset] = (context_registers_selction[10] ==1 ) ? context_register_x10: mem[stack_pointer     [24:2] +x10_offset] ;
		mem[stack_pointer     [24:2] +x11_offset] = (context_registers_selction[11] ==1 ) ? context_register_x11: mem[stack_pointer     [24:2] +x11_offset] ;
		mem[stack_pointer     [24:2] +x12_offset] = (context_registers_selction[12] ==1 ) ? context_register_x12: mem[stack_pointer     [24:2] +x12_offset]  ;
		mem[stack_pointer     [24:2] +x13_offset] = (context_registers_selction[13] ==1 ) ? context_register_x13: mem[stack_pointer     [24:2] +x13_offset]  ;
		mem[stack_pointer     [24:2] +x14_offset] = (context_registers_selction[14] ==1 ) ? context_register_x14: mem[stack_pointer     [24:2] +x14_offset] ;
		mem[stack_pointer     [24:2] +x15_offset] = (context_registers_selction[15] ==1 ) ? context_register_x15: mem[stack_pointer     [24:2] +x15_offset] ;
		mem[stack_pointer     [24:2] +x16_offset] = (context_registers_selction[16] ==1 ) ? context_register_x16: mem[stack_pointer     [24:2] +x16_offset] ;
		mem[stack_pointer     [24:2] +x17_offset] = (context_registers_selction[17] ==1 ) ? context_register_x17: mem[stack_pointer     [24:2] +x17_offset] ;
		mem[stack_pointer     [24:2] +x18_offset] = (context_registers_selction[18] ==1 ) ? context_register_x18: mem[stack_pointer     [24:2] +x18_offset] ;
		mem[stack_pointer     [24:2] +x19_offset] = (context_registers_selction[19] ==1 ) ? context_register_x19: mem[stack_pointer     [24:2] +x19_offset] ;
		mem[stack_pointer     [24:2] +x20_offset] = (context_registers_selction[20] ==1 ) ? context_register_x20: mem[stack_pointer     [24:2] +x20_offset] ;
		mem[stack_pointer     [24:2] +x21_offset] = (context_registers_selction[21] ==1 ) ? context_register_x21: mem[stack_pointer     [24:2] +x21_offset] ;
		mem[stack_pointer     [24:2] +x22_offset] = (context_registers_selction[22] ==1 ) ? context_register_x22: mem[stack_pointer     [24:2] +x22_offset] ;
		mem[stack_pointer     [24:2] +x23_offset] = (context_registers_selction[23] ==1 ) ? context_register_x23: mem[stack_pointer     [24:2] +x23_offset]  ;
		mem[stack_pointer     [24:2] +x24_offset] = (context_registers_selction[24] ==1 ) ? context_register_x24: mem[stack_pointer     [24:2] +x24_offset] ;
		mem[stack_pointer     [24:2] +x25_offset] = (context_registers_selction[25] ==1 ) ? context_register_x25: mem[stack_pointer     [24:2] +x25_offset] ;
		mem[stack_pointer     [24:2] +x26_offset] = (context_registers_selction[26] ==1 ) ? context_register_x26: mem[stack_pointer     [24:2] +x26_offset] ;
		mem[stack_pointer     [24:2] +x27_offset] = (context_registers_selction[27] ==1 ) ? context_register_x27: mem[stack_pointer     [24:2] +x27_offset] ;
		mem[stack_pointer     [24:2] +x28_offset] = (context_registers_selction[28] ==1 ) ? context_register_x28: mem[stack_pointer     [24:2] +x28_offset] ;
		mem[stack_pointer     [24:2] +x29_offset] = (context_registers_selction[29] ==1 ) ? context_register_x29: mem[stack_pointer     [24:2] +x29_offset] ;
		mem[stack_pointer     [24:2] +x30_offset] = (context_registers_selction[30] ==1 ) ? context_register_x30: mem[stack_pointer     [24:2] +x30_offset] ;
		mem[stack_pointer     [24:2] +x31_offset] = (context_registers_selction[31] ==1 ) ? context_register_x31: mem[stack_pointer     [24:2] +x31_offset] ;
	end
  end
endmodule