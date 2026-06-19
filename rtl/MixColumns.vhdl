library ieee;
use ieee.std_logic_1164.all;

entity MixColumns is
    port (
        inState : in std_logic_vector(127 downto 0);
        sel : in std_logic_vector(1 downto 0);
        clk, enable : in std_logic;
        outState : out std_logic_vector(127 downto 0)
    );
end MixColumns;

architecture arch of MixColumns is
    signal a0, a1, a2, a3, mul2a0out, mul2a1out, mul2a2out, mul2a3out : std_logic_vector(7 downto 0);
    signal demux11, demux12, demux13, demux14, demux21, demux22, demux23, demux24, demux31, demux32, demux33, demux34, demux41, demux42, demux43, demux44 : std_logic_vector(7 downto 0);
begin
    -- 127 downto 0

    -- 127 downto 96
    -- 95 downto 64
    -- 63 downto 32
    -- 31 downto 0

    muxa0 : entity work.Mux4x2_8bits(arch)
        port map(
            sel => sel, 
            in00 => inState(127 downto 120), 
            in01 => inState(119 downto 112), 
            in10 => inState(111 downto 104), 
            in11 => inState(103 downto 96), 
            z => a0
        );
    
    muxa1 : entity work.Mux4x2_8bits(arch)
        port map(
            sel => sel, 
            in00 => inState(95 downto 88), 
            in01 => inState(87 downto 80), 
            in10 => inState(79 downto 72), 
            in11 => inState(71 downto 64), 
            z => a1
        );

    muxa2 : entity work.Mux4x2_8bits(arch)
        port map(
            sel => sel, 
            in00 => inState(63 downto 56), 
            in01 => inState(55 downto 48), 
            in10 => inState(47 downto 40), 
            in11 => inState(39 downto 32), 
            z => a2
        );

    muxa3 : entity work.Mux4x2_8bits(arch)
        port map(
            sel => sel, 
            in00 => inState(31 downto 24), 
            in01 => inState(23 downto 16), 
            in10 => inState(15 downto 8), 
            in11 => inState(7 downto 0), 
            z => a3
        );

    mul2a0 : entity work.Mul2(arch)
        port map(
            entrada => a0,
            saida => mul2a0out
        );
    
    mul2a1 : entity work.Mul2(arch)
        port map(
            entrada => a1,
            saida => mul2a1out
        );

    mul2a2 : entity work.Mul2(arch)
        port map(
            entrada => a2,
            saida => mul2a2out
        );
    
    mul2a3 : entity work.Mul2(arch)
        port map(
            entrada => a3,
            saida => mul2a3out
        );

    demux1 : entity work.Demux4x1(arch)
        port map(
            sel => sel,
            a => mul2a0out xor (mul2a1out xor a1) xor a2 xor a3,
            out00 => demux11,
            out01 => demux12,
            out10 => demux13,
            out11 => demux14
        );

    demux2 : entity work.Demux4x1(arch)
        port map(
            sel => sel,
            a => a0 xor mul2a1out xor (mul2a2out xor a2) xor a3,
            out00 => demux21,
            out01 => demux22,
            out10 => demux23,
            out11 => demux24
        );

    demux3 : entity work.Demux4x1(arch)
        port map(
            sel => sel,
            a => a0 xor a1 xor mul2a2out xor (mul2a3out xor a3),
            out00 => demux31,
            out01 => demux32,
            out10 => demux33,
            out11 => demux34
        );

    demux4 : entity work.Demux4x1(arch)
        port map(
            sel => sel,
            a => (mul2a0out xor a0) xor a1 xor a2 xor mul2a3out,
            out00 => demux41,
            out01 => demux42,
            out10 => demux43,
            out11 => demux44
        );
    
    stateRegister : entity VectorRegister(arch)
        port map(
            clk => clk,
            enable => enable,
            inVector => demux11 & demux12 & demux13 & demux14 & demux21 & demux22 & demux23 & demux24 & demux31 & demux32 & demux33 & demux34 & demux41 & demux42 & demux43 & demux44,
            outVector => outState
        );
    
end architecture arch;