module dds (
	input clk,
	input spi_mosi,
	output spi_miso,
	input spi_nss,
	input spi_sclk,
	output reg [0:7] led,
	output reg [0:7] R2R_out
);
	/************************************************************************
	* SPI Config
	* sink = tx (miso), source = rx (mosi)
	* Reset pin must be pulsed low to clock in new data.
	*************************************************************************/
	reg nreset;
	wire source_ready;
	wire source_valid;
	wire [7:0] mosi_data_bus;
	spi_slave spi0 (
		.sysclk        (clk),   	    //              clock_sink.clk
		.nreset        (nreset),        //        clock_sink_reset.reset_n
		.mosi          (spi_mosi),      //                export_0.mosi
		.nss           (spi_nss),       //                        .nss
		.miso          (spi_miso),      //                        .miso
		.sclk          (spi_sclk),      //                        .sclk
		.stsourceready (source_ready),  // avalon_streaming_source.ready
		.stsourcevalid (source_valid), 	//                        .valid
		.stsourcedata  (mosi_data_bus), //                        .data
		.stsinkvalid   (1),   			//   avalon_streaming_sink.valid
		.stsinkdata    (mosi_data_bus), //.data
		.stsinkready   (1)    			// .ready
	);

	/************************************************************************
	* MIDI Note to Frequency Conversion table
	*************************************************************************/	
	reg note_on[60];
	reg [15:0]notes[88];
	initial begin
		notes[0] = 275;
		notes[1] = 291;
		notes[2] = 309;
		notes[3] = 327;
		notes[4] = 346;
		notes[5] = 367;
		notes[6] = 389;
		notes[7] = 412;
		notes[8] = 437;
		notes[9] = 462;
		notes[10] = 490;
		notes[11] = 519;
		notes[12] = 550;
		notes[13] = 583;
		notes[14] = 617;
		notes[15] = 654;
		notes[16] = 693;
		notes[17] = 734;
		notes[18] = 778;
		notes[19] = 824;
		notes[20] = 873;
		notes[21] = 925;
		notes[22] = 980;
		notes[23] = 1038;
		notes[24] = 1100;
		notes[25] = 1165;
		notes[26] = 1235;
		notes[27] = 1308;
		notes[28] = 1386;
		notes[29] = 1468;
		notes[30] = 1556;
		notes[31] = 1648;
		notes[32] = 1746;
		notes[33] = 1850;
		notes[34] = 1960;
		notes[35] = 2077;
		notes[36] = 2200;
		notes[37] = 2331;
		notes[38] = 2469;
		notes[39] = 2616;
		notes[40] = 2772;
		notes[41] = 2937;
		notes[42] = 3111;
		notes[43] = 3296;
		notes[44] = 3492;
		notes[45] = 3700;
		notes[46] = 3920;
		notes[47] = 4153;
		notes[48] = 4400;
		notes[49] = 4662;
		notes[50] = 4939;
		notes[51] = 5233;
		notes[52] = 5544;
		notes[53] = 5873;
		notes[54] = 6223;
		notes[55] = 6593;
		notes[56] = 6985;
		notes[57] = 7400;
		notes[58] = 7840;
		notes[59] = 8306;
		notes[60] = 8800;
		notes[61] = 9323;
		notes[62] = 9878;
		notes[63] = 10465;
		notes[64] = 11087;
		notes[65] = 11747;
		notes[66] = 12445;
		notes[67] = 13185;
		notes[68] = 13969;
		notes[69] = 14800;
		notes[70] = 15680;
		notes[71] = 16612;
		notes[72] = 17600;
		notes[73] = 18647;
		notes[74] = 19755;
		notes[75] = 20930;
		notes[76] = 22175;
		notes[77] = 23493;
		notes[78] = 24890;
		notes[79] = 26370;
		notes[80] = 27938;
		notes[81] = 29600;
		notes[82] = 31360;
		notes[83] = 33224;
		notes[84] = 35200;
		notes[85] = 37293;
		notes[86] = 39511;
		notes[87] = 41860;
	end

	/************************************************************************
	* Wavetables and wave selection mux
	*************************************************************************/
	wire [23:0] sine_val_wire;
 	wire [23:0] pos_saw_val_wire;
 	wire [23:0] neg_saw_val_wire;
 	wire [23:0] tri_val_wire;
 	wire [23:0] sq_val_wire;
 	reg [4:0] wave_sel;
 	reg [23:0] output_val[8];
	reg [23:0] envelope;
	wire [23:0] output_val_wire;
	sine_table  sine(
		.address (current_phase_accumulator>>10),
		.clock (clk),
		.q (sine_val_wire)
	);
	pos_saw  pos_saw_table(
		.address (current_phase_accumulator>>10),
		.clock (clk),
		.q (pos_saw_val_wire)
	);
	neg_saw  neg_saw_table(
		.address (current_phase_accumulator>>10),
		.clock (clk),
		.q (neg_saw_val_wire)
	);
	base_tri  triangle_table(
		.address (current_phase_accumulator>>10),
		.clock (clk),
		.q (tri_val_wire)
	);
	base_sq  square_table(
		.address (current_phase_accumulator>>10),
		.clock (clk),
		.q (sq_val_wire)
	);
	wave_mux wavetable_selector(
		.data0x ( sine_val_wire ),
	 	.data1x ( pos_saw_val_wire ),
	 	.data2x ( neg_saw_val_wire ),
	 	.data3x ( tri_val_wire ),
	 	.data4x ( sq_val_wire ),
	 	.sel ( wave_sel ),
	 	.result ( output_val_wire )
	);

	/************************************************************************
	* Voice selection
	*************************************************************************/
	reg [7:0] phase_accumulator_sel;
	wire [31:0]  phase_accumulator_wire;
	reg [31:0]  current_phase_accumulator;
	reg [31:0]  phase_accumulator[8];
	reg [31:0]  envelope_accumulator;
	// rom_table_addr_mux phase_accumulator_mux (
	// 	.data0x ( envelope_accumulator>>10 ),
	// 	.data1x ( envelope_accumulator>>10 ),
	// 	.data2x ( envelope_accumulator>>10 ),
	// 	.data3x ( envelope_accumulator>>10 ),
	// 	.data4x ( envelope_accumulator>>10 ),
	// 	.data5x ( envelope_accumulator>>10 ),
	// 	.data6x ( phase_accumulator>>10 ), // ???
	// 	.data7x ( envelope_accumulator>>10 ),
	// 	.sel ( phase_accumulator_sel ),
	// 	.result ( phase_accumulator_wire )
	// );

	/************************************************************************
	* Main
	*************************************************************************/
	wire led_wire[7:0];
	assign led_wire[0] = (voice_note[0] != 0);
	assign led_wire[1] = (voice_note[1] != 0);
	assign led_wire[2] = (voice_note[2] != 0);
	assign led_wire[3] = (voice_note[3] != 0);
	assign led_wire[4] = (voice_note[4] != 0);
	assign led_wire[5] = (voice_note[5] != 0);
	assign led_wire[6] = (voice_note[6] != 0);
	assign led_wire[7] = (voice_note[7] != 0);

	reg [31:0] counter;
	reg [4:0] phase_counter;
	always@(posedge clk) begin
		// led <= voice_note[7];
		// led[0] <= led_wire[0];
		// led[1] <= led_wire[1];
		// led[2] <= led_wire[2];
		// led[3] <= led_wire[3];
		// led[4] <= led_wire[4];
		// led[5] <= led_wire[5];
		// led[6] <= led_wire[6];
		// led[7] <= led_wire[7];

		wave_sel = 0;
		nreset = 1;
		if(source_valid) begin
			mosi_data <= mosi_data_bus;
			nreset = 0;
	    end

		output_val[phase_accumulator_sel] = output_val_wire;

		phase_counter <= phase_counter + 1;
		if(phase_counter >= 3) begin
			phase_counter <= 0;
			// phase_accumulator_sel <= 0;
		    phase_accumulator_sel = phase_accumulator_sel + 1;
		    current_phase_accumulator = phase_accumulator[phase_accumulator_sel];
		    // if(phase_accumulator_sel == 1) begin
		    // 	wave_sel <= 1;
		    // end else begin
		    // 	wave_sel <= 2;
		    // end
		end
		
		// R2R_out <= (note_on[midi_note] * (output_val>>8) * (envelope>>16))>>16;
		R2R_out <= (
			((output_val[0])>>3) +
			((output_val[1])>>3) +
			((output_val[2])>>3) +
			((output_val[3])>>3) +
			((output_val[4])>>3) +
			((output_val[5])>>3) +
			((output_val[6])>>3) +
			((output_val[7])>>3)
			)>>16;

	    // update sine wave table address.
		// this clock divider (counter) controls the audio
		// sample rate.
		if(counter < 99) begin
			counter <= counter + 1;
		end else begin
			counter <= 0;
			//phase_accumulator <= phase_accumulator + freq;
			//envelope_accumulator <= envelope_accumulator + freq2;
			for(i = 0; i < 8; i = i + 1) begin
				 if(note_on[voice_note[i]] && (voice_note[i] != 0)) begin
					phase_accumulator[i] <= phase_accumulator[i] + notes[voice_note[i]];
					envelope_accumulator <= envelope_accumulator + 5;
				 end else begin
					 //phase_accumulator[i] <= 0;
					 //envelope_accumulator <= envelope_accumulator + 5;
					 //output_val[i] = 0;
					 envelope <= 0;
				 end
			end
			
		end
	end

	/************************************************************************
	* SPI Rx
	*************************************************************************/
	reg [7:0] spi_current_command;
	reg [4:0] spi_byte_counter;
	reg [7:0] midi_note;
	reg [7:0] midi_velocity;
	reg [7:0] mosi_data;
	reg [7:0] voice_note[8];
	reg [3:0] i;
	reg note_unassigned;
	always@(posedge source_valid) begin
		spi_byte_counter = spi_byte_counter + 1;
		note_unassigned = 1;
		case(spi_byte_counter)
			1: begin
				if(mosi_data == 8'h90
				|| mosi_data == 8'h80) begin
					spi_current_command = mosi_data;
					// if(spi_current_command == 8'h90) begin
					// 	note_on[midi_note] <= 1;
					// 	// led <= midi_note;
					// end else if(spi_current_command == 8'h80) begin
					// 	note_on[midi_note] <= 0;
					// 	// led <= midi_note;
					// end
				end else begin
					// reset byte counter until a valid command comes through
					spi_byte_counter = 0;
				end
			end
			2: begin 
				midi_note = mosi_data;
				if(spi_current_command == 8'h90) begin
					if(voice_note[0] == 0 && note_on[midi_note] == 0) begin
						voice_note[0] = midi_note;
						note_on[midi_note] = 1;
					end
					if(voice_note[1] == 0 && note_on[midi_note] == 0) begin
						voice_note[1] = midi_note;
						note_on[midi_note] = 1;
					end
					if(voice_note[2] == 0 && note_on[midi_note] == 0) begin
						voice_note[2] = midi_note;
						note_on[midi_note] = 1;
					end
					if(voice_note[3] == 0 && note_on[midi_note] == 0) begin
						voice_note[3] = midi_note;
						note_on[midi_note] = 1;
						note_unassigned = 0;
					end
					if(voice_note[4] == 0 && note_on[midi_note] == 0) begin
						voice_note[4] = midi_note;
						note_on[midi_note] = 1;
					end
					if(voice_note[5] == 0 && note_on[midi_note] == 0) begin
						voice_note[5] = midi_note;
						note_on[midi_note] = 1;
					end
					if(voice_note[6] == 0 && note_on[midi_note] == 0) begin
						voice_note[6] = midi_note;
						note_on[midi_note] = 1;
					end
					if(voice_note[7] == 0 && note_on[midi_note] == 0) begin
						voice_note[7] = midi_note;
						note_on[midi_note] = 1;
					end
				end else if(spi_current_command == 8'h80) begin
					for(i = 0; i < 8; i = i + 1) begin
						if(voice_note[i] == midi_note) begin
							voice_note[i] = 0;
							note_on[midi_note] = 0;
						end
					end
				end
			end
			3: begin 
				midi_velocity = mosi_data;
				spi_byte_counter = 0;
			end
			default: begin
				spi_byte_counter = 0;
			end
		endcase

		led <= midi_note;		
	end
endmodule
