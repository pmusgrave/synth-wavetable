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
	* Wavetables and wave selection mux
	*************************************************************************/
	wire [23:0] sine_val_wire;
 	wire [23:0] pos_saw_val_wire;
 	wire [23:0] neg_saw_val_wire;
 	wire [23:0] tri_val_wire;
 	wire [23:0] sq_val_wire;
 	reg [4:0] wave_sel;
 	reg [23:0] output_val;
	reg [23:0] output_val2;
	reg [23:0] output_val3;
	reg [23:0] output_val4;
	reg [23:0] output_val5;
	reg [23:0] output_val6;
	reg [23:0] output_val7;
	reg [23:0] output_val8;
	wire [23:0] output_val_wire;
	sine_table  sine(
		.address (phase_accumulator_wire),
		.clock (clk),
		.q (sine_val_wire)
	);
	pos_saw  pos_saw_table(
		.address (phase_accumulator_wire),
		.clock (clk),
		.q (pos_saw_val_wire)
	);
	neg_saw  neg_saw_table(
		.address (phase_accumulator_wire),
		.clock (clk),
		.q (neg_saw_val_wire)
	);
	base_tri  triangle_table(
		.address (phase_accumulator_wire),
		.clock (clk),
		.q (tri_val_wire)
	);
	base_sq  square_table(
		.address (phase_accumulator_wire),
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
	reg [2:0] phase_accumulator_sel;
	wire [31:0]  phase_accumulator_wire;
	reg [31:0]  phase_accumulator;
	reg [31:0]  phase_accumulator2;
	reg [31:0]  phase_accumulator3;
	reg [31:0]  phase_accumulator4;
	reg [31:0]  phase_accumulator5;
	reg [31:0]  phase_accumulator6;
	reg [31:0]  phase_accumulator7;
	reg [31:0]  phase_accumulator8;
	rom_table_addr_mux phase_accumulator_mux (
		.data0x ( phase_accumulator>>10 ),
		.data1x ( phase_accumulator2>>10 ),
		.data2x ( phase_accumulator>>10 ),
		.data3x ( phase_accumulator2>>10 ),
		.data4x ( phase_accumulator>>10 ),
		.data5x ( phase_accumulator2>>10 ),
		.data6x ( phase_accumulator>>10 ),
		.data7x ( phase_accumulator2>>10 ),
		.sel ( phase_accumulator_sel ),
		.result ( phase_accumulator_wire )
	);

	/************************************************************************
	* Main
	*************************************************************************/
	reg [31:0] counter;
	always@(posedge clk) begin
		wave_sel = 0;
		nreset = 1;
		if(source_valid) begin
			mosi_data <= mosi_data_bus;
			nreset = 0;
	    end

	    if(note_on) begin
			case(phase_accumulator_sel)
				0:	output_val <= output_val_wire;
				1:	output_val2 <= output_val_wire;
				// 2:	output_val <= output_val_wire;
				// 3:	output_val2 <= output_val_wire;
				// 4:	output_val <= output_val_wire;
				// 5:	output_val2 <= output_val_wire;
				// 6:	output_val <= output_val_wire;
				// 7:	output_val2 <= output_val_wire;
				default: output_val <= output_val_wire;
			endcase
			// phase_accumulator_sel <= 0;
		    phase_accumulator_sel = phase_accumulator_sel + 1;
		    if(phase_accumulator_sel == 1) begin
		    	wave_sel <= 1;
		    end else begin
		    	wave_sel <= 0;
		    end
		end else begin
			output_val2 <= 24'd0;
		end
		
		R2R_out <= ((output_val>>8)*(output_val2>>16))>>16;

	    // update sine wave table address.
		// this clock divider (counter) controls the audio
		// sample rate.
		if(counter < 100) begin
			counter <= counter + 1;
		end else begin
			counter <= 0;
			//phase_accumulator <= phase_accumulator + freq;
			//phase_accumulator2 <= phase_accumulator2 + freq2;
			if(note_on) begin
				phase_accumulator <= phase_accumulator + 1000;
				phase_accumulator2 <= phase_accumulator2 + 1;
			end
			if (!note_on) begin
				phase_accumulator <= 0;
				phase_accumulator2 <= 0;
				output_val2 <= 0;
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
	always@(posedge source_valid) begin
		spi_byte_counter = spi_byte_counter + 1;
		case(spi_byte_counter)
			1: begin
				if(mosi_data == 8'h90
				|| mosi_data == 8'h80) begin
					spi_current_command <= mosi_data;
				end else begin
					// reset byte counter until a valid command comes through
					spi_byte_counter = 0;
				end
			end
			2: begin 
				midi_note <= mosi_data;
			end
			3: begin 
				midi_velocity <= mosi_data;
				spi_byte_counter = 0;
			end
			default: begin
				spi_byte_counter = 0;
			end
		endcase

		
	end

	/************************************************************************
	* Testing envelope
	*************************************************************************/
	reg note_on;
	always@* begin
		if(spi_current_command == 8'h90) begin
			note_on <= 1;
			led <= 8'hFF;
		end else if(spi_current_command == 8'h80) begin
			note_on <= 0;
			led <= 8'h00;
		end
	end
endmodule
