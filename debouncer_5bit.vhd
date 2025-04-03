library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity debouncer_5bit is
    Port (
        clk      : in  STD_LOGIC;  -- Clock signal
        btn_in   : in  STD_LOGIC_VECTOR(4 downto 0); -- Noisy button inputs
        btn_out  : out STD_LOGIC_VECTOR(4 downto 0)  -- Debounced outputs
    );
end debouncer_5bit;

architecture Behavioral of debouncer_5bit is
    constant MAX_COUNT : integer := 50000000; -- Adjust for desired debounce time 50 ms hold time
    type Counter_Array is array (4 downto 0) of integer range 0 to MAX_COUNT;
    signal counter     : Counter_Array := (others => 0);signal btn_stable  : STD_LOGIC_VECTOR(4 downto 0) := (others => '0');

begin
    process (clk)
    begin
        if rising_edge(clk) then
            for i in 0 to 4 loop
                if btn_in(i) /= btn_stable(i) then
                        -- Input differs from stable value
                        if counter(i) = MAX_COUNT-1 then
                            -- Debounce period complete
                            btn_stable(i) <= btn_in(i);
                            counter(i) <= 0;
                        else
                            -- Increment counter
                            counter(i) <= counter(i) + 1;
                        end if;
                    else
                        -- Input matches stable value - reset counter
                        counter(i) <= 0;
                    end if;
            end loop;
         end if;
    end process;
    
    btn_out <= btn_stable;
end Behavioral;