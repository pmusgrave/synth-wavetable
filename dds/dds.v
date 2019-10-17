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
	reg [4:0] phase_accumulator_sel;
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
	reg [15:0] freq;
	reg [15:0] freq2;
	reg [7:0] env;
	reg [7:0] env2;
	always@(posedge clk) begin
		wave_sel = 0;
		nreset = 1;
		if(source_valid) begin
			mosi_data <= mosi_data_bus;
			nreset = 0;
	    end

	    phase_accumulator_sel <= phase_accumulator_sel + 1;
		case(phase_accumulator_sel)
			0:	output_val <= output_val_wire;
			1:	output_val2 <= output_val_wire;
			2:	output_val <= output_val_wire;
			3:	output_val2 <= output_val_wire;
			4:	output_val <= output_val_wire;
			5:	output_val2 <= output_val_wire;
			6:	output_val <= output_val_wire;
			7:	output_val2 <= output_val_wire;
			default: output_val <= output_val_wire;
		endcase
		
		R2R_out <= ((output_val>>8)*env + (output_val2>>8)*env2)>>16;

	    // update sine wave table address.
		// this clock divider (counter) controls the audio
		// sample rate.
		if(counter < 100) begin
			counter <= counter + 1;
		end else begin
			counter <= 0;
			phase_accumulator <= phase_accumulator + freq;
			phase_accumulator2 <= phase_accumulator2 + freq2;
		end
	end

	/************************************************************************
	* SPI Rx
	*************************************************************************/
	reg [7:0] spi_current_command;
	reg [4:0] spi_byte_counter;
	reg [4:0] spi_byte_counter_max;
	reg [7:0] mosi_data;
	reg [15:0] mosi_data_16bit;
	reg freq_update_start;
	reg freq2_update_start;
	reg freq3_update_start;
	reg freq4_update_start;
	reg freq_update_complete;
	reg freq2_update_complete;
	reg freq3_update_complete;
	reg freq4_update_complete;
	reg env_update_start;
	reg env2_update_start;
	reg env3_update_start;
	reg env4_update_start;
	reg env_update_complete;
	reg env2_update_complete;
	reg env3_update_complete;
	reg env4_update_complete;
	always@(posedge source_valid) begin
		spi_byte_counter = spi_byte_counter + 1;
		mosi_data_16bit <= (mosi_data_16bit<<8) + mosi_data;

		if(spi_byte_counter == 1) begin
			// first byte is a command message
			// this indicates what data will follow
			spi_current_command = mosi_data;
			//mosi_data_16bit <= 0;
			freq_update_start = 0;
			freq_update_complete = 0;
			freq2_update_start = 0;
			freq2_update_complete = 0;
			env_update_start = 0;
			env_update_complete = 0;
			led<=0;
		end else begin
			if(spi_byte_counter > spi_byte_counter_max) begin
				spi_byte_counter = 0;
				if(freq_update_start) begin
					freq_update_start = 0;
					freq_update_complete = 1;
				end
				if(freq2_update_start) begin
					freq2_update_start = 0;
					freq2_update_complete = 1;
				end
				if(env_update_start) begin
					env_update_start = 0;
					env_update_complete = 1;
				end
				if(env2_update_start) begin
					env2_update_start = 0;
					env2_update_complete = 1;
				end
			end
		end

		case(spi_current_command)
			1: begin
				spi_current_command <= 0; // not sure why, but this is necessary
				freq_update_start = 1;
				spi_byte_counter_max <= 3;
			end

			2: begin
				spi_current_command <= 0;
				env_update_start = 1;
				spi_byte_counter_max <= 1;
			end
			
			3: begin
				spi_current_command <= 0;
				freq2_update_start = 1;
				spi_byte_counter_max <= 3;
			end

			4: begin
				spi_current_command <= 0;
				env2_update_start = 1;
				spi_byte_counter_max <= 1;
			end
			5: begin
				spi_current_command <= 0;
				freq3_update_start = 1;
				spi_byte_counter_max <= 1;
			end

			6: begin
				spi_current_command <= 0;
				env3_update_start = 1;
				spi_byte_counter_max <= 1;
			end
			7: begin
				spi_current_command <= 0;
				freq4_update_start = 1;
				spi_byte_counter_max <= 1;
			end

			8: begin
				spi_current_command <= 0;
				env4_update_start = 1;
				spi_byte_counter_max <= 1;
			end

			// if the current command is not a known command in the above list,
			// reset byte counter to wait for a new command
			default: begin
				spi_current_command = 0;
				//spi_byte_counter = 0;
				//spi_byte_counter_max <= 0;
			end
			
		endcase

		if(freq_update_complete) begin
			freq <= mosi_data_16bit;
			freq_update_complete = 0;
		end
		if(freq2_update_complete) begin
			freq2 <= mosi_data_16bit;
			freq2_update_complete = 0;
		end
		if(env_update_complete) begin
			env <= mosi_data;
			env_update_complete = 0;
		end
		if(env2_update_complete) begin
			env2 <= mosi_data;
			env2_update_complete = 0;
		end
	end
endmodule
