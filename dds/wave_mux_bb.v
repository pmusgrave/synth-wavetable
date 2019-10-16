// megafunction wizard: %LPM_MUX%VBB%
// GENERATION: STANDARD
// VERSION: WM1.0
// MODULE: LPM_MUX 

// ============================================================
// File Name: wave_mux.v
// Megafunction Name(s):
// 			LPM_MUX
//
// Simulation Library Files(s):
// 			lpm
// ============================================================
// ************************************************************
// THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
//
// 18.1.0 Build 625 09/12/2018 SJ Lite Edition
// ************************************************************

//Copyright (C) 2018  Intel Corporation. All rights reserved.
//Your use of Intel Corporation's design tools, logic functions 
//and other software and tools, and its AMPP partner logic 
//functions, and any output files from any of the foregoing 
//(including device programming or simulation files), and any 
//associated documentation or information are expressly subject 
//to the terms and conditions of the Intel Program License 
//Subscription Agreement, the Intel Quartus Prime License Agreement,
//the Intel FPGA IP License Agreement, or other applicable license
//agreement, including, without limitation, that your use is for
//the sole purpose of programming logic devices manufactured by
//Intel and sold by Intel or its authorized distributors.  Please
//refer to the applicable agreement for further details.

module wave_mux (
	data0x,
	data1x,
	data2x,
	data3x,
	data4x,
	sel,
	result);

	input	[23:0]  data0x;
	input	[23:0]  data1x;
	input	[23:0]  data2x;
	input	[23:0]  data3x;
	input	[23:0]  data4x;
	input	[2:0]  sel;
	output	[23:0]  result;

endmodule

// ============================================================
// CNX file retrieval info
// ============================================================
// Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Cyclone IV E"
// Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "0"
// Retrieval info: PRIVATE: new_diagram STRING "1"
// Retrieval info: LIBRARY: lpm lpm.lpm_components.all
// Retrieval info: CONSTANT: LPM_SIZE NUMERIC "5"
// Retrieval info: CONSTANT: LPM_TYPE STRING "LPM_MUX"
// Retrieval info: CONSTANT: LPM_WIDTH NUMERIC "24"
// Retrieval info: CONSTANT: LPM_WIDTHS NUMERIC "3"
// Retrieval info: USED_PORT: data0x 0 0 24 0 INPUT NODEFVAL "data0x[23..0]"
// Retrieval info: USED_PORT: data1x 0 0 24 0 INPUT NODEFVAL "data1x[23..0]"
// Retrieval info: USED_PORT: data2x 0 0 24 0 INPUT NODEFVAL "data2x[23..0]"
// Retrieval info: USED_PORT: data3x 0 0 24 0 INPUT NODEFVAL "data3x[23..0]"
// Retrieval info: USED_PORT: data4x 0 0 24 0 INPUT NODEFVAL "data4x[23..0]"
// Retrieval info: USED_PORT: result 0 0 24 0 OUTPUT NODEFVAL "result[23..0]"
// Retrieval info: USED_PORT: sel 0 0 3 0 INPUT NODEFVAL "sel[2..0]"
// Retrieval info: CONNECT: @data 0 0 24 0 data0x 0 0 24 0
// Retrieval info: CONNECT: @data 0 0 24 24 data1x 0 0 24 0
// Retrieval info: CONNECT: @data 0 0 24 48 data2x 0 0 24 0
// Retrieval info: CONNECT: @data 0 0 24 72 data3x 0 0 24 0
// Retrieval info: CONNECT: @data 0 0 24 96 data4x 0 0 24 0
// Retrieval info: CONNECT: @sel 0 0 3 0 sel 0 0 3 0
// Retrieval info: CONNECT: result 0 0 24 0 @result 0 0 24 0
// Retrieval info: GEN_FILE: TYPE_NORMAL wave_mux.v TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL wave_mux.inc FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL wave_mux.cmp FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL wave_mux.bsf TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL wave_mux_inst.v FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL wave_mux_bb.v TRUE
// Retrieval info: LIB_FILE: lpm
