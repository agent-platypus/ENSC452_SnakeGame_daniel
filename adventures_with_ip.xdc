# LedBoard LED Constraints
set_property PACKAGE_PIN T22 [get_ports {LEDs_out_0[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs_out_0[0]}]
set_property PACKAGE_PIN T21 [get_ports {LEDs_out_0[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs_out_0[1]}]
set_property PACKAGE_PIN U22 [get_ports {LEDs_out_0[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs_out_0[2]}]
set_property PACKAGE_PIN U21 [get_ports {LEDs_out_0[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs_out_0[3]}]
set_property PACKAGE_PIN V22 [get_ports {LEDs_out_0[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs_out_0[4]}]
set_property PACKAGE_PIN W22 [get_ports {LEDs_out_0[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs_out_0[5]}]
set_property PACKAGE_PIN U19 [get_ports {LEDs_out_0[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs_out_0[6]}]
set_property PACKAGE_PIN U14 [get_ports {LEDs_out_0[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs_out_0[7]}]

# ZedBoard Audio Codec Constraints
set_property PACKAGE_PIN AA6 [get_ports BCLK_0]
set_property IOSTANDARD LVCMOS33 [get_ports BCLK_0]

set_property PACKAGE_PIN Y6 [get_ports LRCLK_0]
set_property IOSTANDARD LVCMOS33 [get_ports LRCLK_0]

set_property PACKAGE_PIN AA7 [get_ports SDATA_I_0]
set_property IOSTANDARD LVCMOS33 [get_ports SDATA_I_0]

set_property PACKAGE_PIN Y8 [get_ports SDATA_O_0]
set_property IOSTANDARD LVCMOS33 [get_ports SDATA_O_0]

#MCLK
set_property PACKAGE_PIN AB2 [get_ports FCLK_CLK1]
set_property IOSTANDARD LVCMOS33 [get_ports FCLK_CLK1]

set_property PACKAGE_PIN AB4 [get_ports IIC_0_0_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports IIC_0_0_scl_io]

set_property PACKAGE_PIN AB5 [get_ports IIC_0_0_sda_io]
set_property IOSTANDARD LVCMOS33 [get_ports IIC_0_0_sda_io]

set_property PACKAGE_PIN AB1 [get_ports {GPIO_0_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_tri_io[0]}]

set_property PACKAGE_PIN Y5 [get_ports {GPIO_0_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_tri_io[1]}]

set_property PACKAGE_PIN Y21  [get_ports {VGA_B_0[0]}];  # "VGA-B1"
set_property PACKAGE_PIN Y20  [get_ports {VGA_B_0[1]}];  # "VGA-B2"
set_property PACKAGE_PIN AB20 [get_ports {VGA_B_0[2]}];  # "VGA-B3"
set_property PACKAGE_PIN AB19 [get_ports {VGA_B_0[3]}];  # "VGA-B4"
set_property PACKAGE_PIN AB22 [get_ports {VGA_G_0[0]}];  # "VGA-G1"
set_property PACKAGE_PIN AA22 [get_ports {VGA_G_0[1]}];  # "VGA-G2"
set_property PACKAGE_PIN AB21 [get_ports {VGA_G_0[2]}];  # "VGA-G3"
set_property PACKAGE_PIN AA21 [get_ports {VGA_G_0[3]}];  # "VGA-G4"
set_property PACKAGE_PIN AA19 [get_ports {VGA_HS_0}];  # "VGA-HS"
set_property PACKAGE_PIN V20  [get_ports {VGA_R_0[0]}];  # "VGA-R1"
set_property PACKAGE_PIN U20  [get_ports {VGA_R_0[1]}];  # "VGA-R2"
set_property PACKAGE_PIN V19  [get_ports {VGA_R_0[2]}];  # "VGA-R3"
set_property PACKAGE_PIN V18  [get_ports {VGA_R_0[3]}];  # "VGA-R4"
set_property PACKAGE_PIN Y19  [get_ports {VGA_VS_0}];  # "VGA-VS"


set_property PACKAGE_PIN P16 [get_ports {raw_in_0[0]}];  # "BTNC"
set_property PACKAGE_PIN R16 [get_ports {raw_in_0[1]}];  # "BTND"
set_property PACKAGE_PIN N15 [get_ports {raw_in_0[2]}];  # "BTNL"
set_property PACKAGE_PIN R18 [get_ports {raw_in_0[3]}];  # "BTNR"
set_property PACKAGE_PIN T18 [get_ports {raw_in_0[4]}];  # "BTNU"

# Note that the bank voltage for IO Bank 33 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 33]];

# Set the bank voltage for IO Bank 34 to 1.8V by default.
# set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 34]];
# set_property IOSTANDARD LVCMOS25 [get_ports -of_objects [get_iobanks 34]];
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 34]];

# Set the bank voltage for IO Bank 35 to 1.8V by default.
# set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 35]];
# set_property IOSTANDARD LVCMOS25 [get_ports -of_objects [get_iobanks 35]];
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 35]];

# Note that the bank voltage for IO Bank 13 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 13]];