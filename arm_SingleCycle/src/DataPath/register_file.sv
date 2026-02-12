module register_file(
    input logic         i_rst_w,
    input logic         i_clk_w,
    input logic         i_reg_write_w,
    input logic[3:0]    i_read_addr_a_w,
    input logic[3:0]    i_read_addr_b_w,
    input logic[3:0]    i_write_addr_w,
    input logic[31:0]   i_write_data_w,
    input logic[31:0]   i_r15_w,
    output logic[31:0]  o_data_out_a_w,
    output logic[31:0]  o_data_out_b_w,
    output logic        o_r15_written_w
);
    logic[31:0] registers_m[15:0];

    assign o_data_out_a_w = (i_read_addr_a_w != 4'd15) ? registers_m[i_read_addr_a_w] : i_r15_w;
    assign o_data_out_b_w = (i_read_addr_b_w != 4'd15) ? registers_m[i_read_addr_b_w] : i_r15_w;

    always_ff @(posedge i_clk_w or posedge i_rst_w) begin
        if(i_rst_w) begin
            for( int i = 0; i < 16; i = i+1 ) begin
                registers_m[i] <= 'b0;
            end
        end
        else if(i_reg_write_w) begin
            if(i_write_addr_w != 4'd15) begin
                registers_m[i_write_addr_w] <= i_write_data_w;
            end
        end
    end

endmodule // register_file
