module dds (
	input            clk,
	input            spi_mosi,
	output           spi_miso,
	input            spi_nss,
	input            spi_sclk,
	output reg [0:7] led,
  output reg [0:7] R2R_out
);

	 reg [31:0] sine_val;
	 reg [31:0] sine_val2;
	 wire [31:0] sine_val_wire;
	 wire [11:0]  phase_accumulator_wire;
   reg [11:0]  phase_accumulator;
	 reg [11:0]  phase_accumulator2;
	 reg [4:0] phase_accumulator_sel;
   reg [15:0]   freq;
	 reg [15:0]   freq2;
	 reg [7:0] env;

	 reg [31:0] counter;
	 reg spi_rx_in_progress;
	 reg freq_update_start;
	 reg freq_update_complete;
	 reg env_update_flag;
	 reg [4:0] spi_byte_counter;
	 reg [4:0] spi_byte_counter_max;
	 reg [7:0] spi_current_command;

   wire       source_ready;
   wire       source_valid;
   wire [7:0] mosi_data_bus;
   reg [7:0] mosi_data;
	 reg [15:0] mosi_data_16bit;
	 reg nreset;

	 reg [7:0] config_raddr;
	 reg [7:0] config_waddr;
	 reg [15:0] config_ram_input_data;
	 wire [15:0] config_ram_output_data;
	 reg config_wren;

   rom  sine_table(
		.address (phase_accumulator_wire),
		.clock (clk),
		.q (sine_val_wire)
   );

	 // not sure if ram module is necessary.
	 // This was to ensure persistent storage
	 // of ADSR values while SPI transactions
	 // are in progress.
	 config_ram	config_ram_inst (
	 	.clock ( clk ),
	 	.data ( config_ram_input_data ),
	 	.rdaddress ( config_raddr ),
	 	.wraddress ( config_waddr ),
	 	.wren ( config_wren ),
	 	.q ( config_ram_output_data )
 	);

	 rom_table_addr_mux phase_accumulator_mux (
	 	.data0x ( phase_accumulator ),
	 	.data1x ( phase_accumulator2 ),
	 	.data2x ( phase_accumulator ),
	 	.data3x ( phase_accumulator2 ),
	 	.data4x ( phase_accumulator ),
	 	.data5x ( phase_accumulator2 ),
	 	.data6x ( phase_accumulator ),
	 	.data7x ( phase_accumulator2 ),
	 	.sel ( phase_accumulator_sel ),
	 	.result ( phase_accumulator_wire )
 	);

	// sink = tx (miso), source = rx (mosi)
   spi_slave spi0 (
     .sysclk        (clk),   				    //              clock_sink.clk
     .nreset        (nreset),    		    //        clock_sink_reset.reset_n
     .mosi          (spi_mosi),         //                export_0.mosi
     .nss           (spi_nss),          //                        .nss
     .miso          (spi_miso),         //                        .miso
     .sclk          (spi_sclk),         //                        .sclk
     .stsourceready (source_ready), 		// avalon_streaming_source.ready
     .stsourcevalid (source_valid), 		//                        .valid
     .stsourcedata  (mosi_data_bus),  	//                        .data
     .stsinkvalid   (1),   							//   avalon_streaming_sink.valid
     .stsinkdata    (mosi_data_bus),    //                        .data
     .stsinkready   (1)    							//                        .ready
   );

	always@(posedge clk) begin
		nreset = 1;
		// phase_accumulator_sel = phase_accumulator_sel + 1;
		phase_accumulator_sel = 0;
		case(phase_accumulator_sel)
			0:	sine_val <= sine_val_wire;
			1:	sine_val2 <= sine_val_wire;
			2:	sine_val <= sine_val_wire;
			3:	sine_val2 <= sine_val_wire;
			4:	sine_val <= sine_val_wire;
			5:	sine_val2 <= sine_val_wire;
			6:	sine_val <= sine_val_wire;
			7:	sine_val2 <= sine_val_wire;
			default: sine_val <= sine_val_wire;
		endcase

		config_raddr <= 2;
		env <= config_ram_output_data;
		// config_raddr <= config_raddr + 1;
		// if(config_raddr >= 32) begin
		// 	config_raddr <= 0;
		// end
		// case(config_raddr)
		// 	2: env <= config_ram_output_data;
		// 	default:
		// endcase


		//led[0] <= source_valid;
		//led[1] <= set_freq_flag;
		led <= env;
		// freq <= mosi_data;
    R2R_out <= ((sine_val>>7)*env)>>16;// + (sine_val2>>16))>>1;

    if(source_valid) begin
			mosi_data <= mosi_data_bus;
			nreset = 0;
    end

		// update sine wave table address
		if(counter <= 500) begin
			counter <= counter + 1;
		end else begin
			counter <= 0;
			phase_accumulator <= phase_accumulator + freq;
			//phase_accumulator2 <= phase_accumulator2 + freq2;
		end
	end

	always@(posedge source_valid) begin
		case(spi_byte_counter)
			0:	begin
				spi_current_command = mosi_data;
				spi_byte_counter <= spi_byte_counter + 1;
				mosi_data_16bit = 0;
				freq_update_start <= 0;
				freq_update_complete = 0;
				env_update_flag <= 0;
				config_wren = 0;
			end

			default: begin
				if(spi_byte_counter <= spi_byte_counter_max) begin
					spi_byte_counter <= spi_byte_counter + 1;
					if(freq_update_start) begin
						mosi_data_16bit = (mosi_data_16bit << 8) + mosi_data;
					end
				end else begin
					env_update_flag <= 0;
					spi_byte_counter <= 0;
					if(freq_update_start) begin
						freq_update_start <= 0;
						freq_update_complete = 1;
					end
				end
			end

		endcase

		case(spi_current_command)
			1:begin
					freq_update_start <= 1;
					spi_byte_counter_max <= 2'b10;
					config_waddr <= 1;
				end
			2:begin
					config_wren = 1;
					env_update_flag <= 1;
					spi_byte_counter_max <= 2'b00;
					config_waddr <= 2;
				end
		endcase

		if(freq_update_complete) begin
			freq <= mosi_data_16bit;
			freq_update_complete = 0;
		end
		if(env_update_flag) begin
			//env <= mosi_data;
			config_wren = 1;
			config_ram_input_data <= mosi_data;
			env_update_flag <= 0;
		end
	end
endmodule
