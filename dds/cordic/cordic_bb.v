
module cordic (
	clk,
	areset,
	a,
	c,
	s);	

	input		clk;
	input		areset;
	input	[12:0]	a;
	output	[9:0]	c;
	output	[9:0]	s;
endmodule
