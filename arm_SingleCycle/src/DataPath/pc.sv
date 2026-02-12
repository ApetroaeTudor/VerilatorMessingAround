module pc(
    input logic i_clk_w,
    input logic i_rst_w,
    input logic[31:0] i_data_w,
    output logic[31:0] o_data_w
);
    logic [31:0] data_r;
    assign o_data_w = data_r;
    always_ff @(posedge i_clk_w or posedge i_rst_w) begin
        if(i_rst_w) begin
            data_r   <= 'b0;
        end
        else begin
            data_r   <= i_data_w;
        end
    end

endmodule // pc

// 32 bit register, write on clk, read comb