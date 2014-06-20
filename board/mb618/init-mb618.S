#include "asm/stx7111reg.h"
#include "../../cpu/sh/init_ram.S"

/*
 * This is derived from STMicroelectronics gnu toolchain example:
 *   sh-superh-elf/examples/os21/romdynamic/memory_mb618.S
 */

/*
 * The poke table is a series of long words, in the format
 *
 *	opcode, address, operand, ...
 *
 * An opcode of 0 marks the table end
 */

/*
 * For compatibility with old poke table code, we define some of the
 * new names, to map onto the old names. Ultimately, the old poke table
 * code will be updated to the "new order", and we can just delete
 * the following mappings.
 */
#define POKE8(A, VAL)				POKE_CHAR(A, VAL)
#define POKE16(A, VAL)				POKE_SHORT(A, VAL)
#define POKE32(A, VAL)				POKE_LONG(A, VAL)
#define OR32(A, VAL)				OR_LONG(A, VAL)
#define UPDATE32(A, AND, OR)			UPDATE_LONG(A, AND, OR)
#define POKE_UPDATE32(A1, A2, AND, SHIFT, OR)	POKE_UPDATE_LONG(A1, A2, AND, SHIFT, OR)
#define WHILE_NE32(A, AND, VAL)			WHILE_NE(A, AND, VAL)
#define DELAY(VAL)				/* do nothing */

.balign 32


__memory_setup_table:

#if 1
/*
stx7111_sysconf_regs.SYSCONF_DEVICEID0
*/
/* PEEK(0xfe001000) (used target peek value 0x2d43b041) */
/* PEEK(0xfe00d060) (used target peek value 0x00000000) */
/* PEEK(0xfe00d05c) (used target peek value 0x01100110) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_sysconf_regs.SYSCONF_DEVICEID0
*/
/* PEEK(0xfe001000) (used target peek value 0x2d43b041) */
/* PEEK(0xfe00d05c) (used target peek value 0x01100110) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
POKE32(0xfe213014, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG2
*/
POKE32(0xfe213024, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_PLL0_ENABLE_FB
*/
/* PEEK(0xfe21301c) (used target peek value 0x00000000) */


/*
stx7111_clockgena_regs.CKGA_PLL0_ENABLE_FB
*/
WHILE_NE32(0xfe21301c, 0xffffffff, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_PLL1_ENABLE_FB
*/
/* PEEK(0xfe213020) (used target peek value 0x00000000) */


/*
stx7111_clockgena_regs.CKGA_PLL1_ENABLE_FB
*/
WHILE_NE32(0xfe213020, 0xffffffff, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80001402) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
POKE32(0xfe213000, 0x80101402)


/*
stx7111_clockgena_regs.CKGA_POWER_CFG
*/
/* PEEK(0xfe213010) (used target peek value 0x00000000) */


/*
stx7111_clockgena_regs.CKGA_POWER_CFG
*/
POKE32(0xfe213010, 0x00000001)


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x00181402) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
POKE32(0xfe213000, 0x00180f01)


/*
stx7111_clockgena_regs.CKGA_POWER_CFG
*/
/* PEEK(0xfe213010) (used target peek value 0x00000001) */


/*
stx7111_clockgena_regs.CKGA_POWER_CFG
*/
POKE32(0xfe213010, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80100f01) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
WHILE_NE32(0xfe213000, 0x80000000, 0x80000000)


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80100f01) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
POKE32(0xfe213000, 0x80000f01)


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
POKE32(0xfe213004, 0x80102803)


/*
stx7111_clockgena_regs.CKGA_POWER_CFG
*/
/* PEEK(0xfe213010) (used target peek value 0x00000000) */


/*
stx7111_clockgena_regs.CKGA_POWER_CFG
*/
POKE32(0xfe213010, 0x00000002)


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x00182803) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
POKE32(0xfe213004, 0x00182803)


/*
stx7111_clockgena_regs.CKGA_POWER_CFG
*/
/* PEEK(0xfe213010) (used target peek value 0x00000002) */


/*
stx7111_clockgena_regs.CKGA_POWER_CFG
*/
POKE32(0xfe213010, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80102803) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
WHILE_NE32(0xfe213004, 0x80000000, 0x80000000)


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80102803) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
POKE32(0xfe213004, 0x80002803)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV0_CFG
*/
POKE32(0xfe213b00, 0x00000001)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV1_CFG
*/
POKE32(0xfe213b04, 0x00000001)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV2_CFG
*/
POKE32(0xfe213b08, 0x00000001)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV3_CFG
*/
POKE32(0xfe213b0c, 0x00000003)


/*
stx7111_clockgena_regs.CKGA_PLL0LS_DIV4_CFG
*/
POKE32(0xfe213a10, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV5_CFG
*/
POKE32(0xfe213b14, 0x00000007)


/*
stx7111_clockgena_regs.CKGA_PLL0LS_DIV6_CFG
*/
POKE32(0xfe213a18, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_PLL0LS_DIV7_CFG
*/
POKE32(0xfe213a1c, 0x00000000)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV8_CFG
*/
POKE32(0xfe213b20, 0x00000003)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV9_CFG
*/
POKE32(0xfe213b24, 0x00000003)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV10_CFG
*/
POKE32(0xfe213b28, 0x00000003)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV11_CFG
*/
POKE32(0xfe213b2c, 0x00000003)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV12_CFG
*/
POKE32(0xfe213b30, 0x00000002)


/*
stx7111_clockgena_regs.CKGA_PLL0LS_DIV13_CFG
*/
POKE32(0xfe213a34, 0x00000011)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV14_CFG
*/
POKE32(0xfe213b38, 0x0000000b)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV15_CFG
*/
POKE32(0xfe213b3c, 0x00000007)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV16_CFG
*/
POKE32(0xfe213b40, 0x00000003)


/*
stx7111_clockgena_regs.CKGA_PLL1_DIV17_CFG
*/
POKE32(0xfe213b44, 0x00000003)
POKE32(0xfe702010, 0x00000004)


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
POKE32(0xfe213014, 0xa6aa59aa)


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG2
*/
POKE32(0xfe213024, 0x0000000a)


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
/* PEEK(0xfe00112c) (used target peek value 0x00000d28) */


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
POKE32(0xfe00112c, 0x00001d28)


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
/* PEEK(0xfe00112c) (used target peek value 0x00001d28) */


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
POKE32(0xfe00112c, 0x000016a0)


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
/* PEEK(0xfe00112c) (used target peek value 0x000016a0) */


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
POKE32(0xfe00112c, 0x000006a0)


/*
stx7111_sysconf_regs.SYSCONF_STA3
*/
/* PEEK(0xfe001014) (used target peek value 0x0000d670) */


/*
stx7111_sysconf_regs.SYSCONF_STA3
*/
WHILE_NE32(0xfe001014, 0x00000001, 0x00000000)


/*
stx7111_clockgenb_regs.CLOCKGENB_LOCK
*/
POKE32(0xfe000010, 0x0000c0de)


/*
stx7111_clockgenb_regs.CLOCKGENB_CRISTAL_SEL
*/
POKE32(0xfe0000b8, 0x00000000)


/*
stx7111_clockgenb_regs.CLOCKGENB_LOCK
*/
POKE32(0xfe000010, 0x0000c1a0)


/*
stx7111_audio_regs.AUDCFG_FSYNA_CFG
*/
/* PEEK(0xfe210000) (used target peek value 0x00000000) */


/*
stx7111_audio_regs.AUDCFG_FSYNA_CFG
*/
POKE32(0xfe210000, 0x00000000)


/*
stx7111_sysconf_regs.SYSCONF_CFG40
*/
POKE32(0xfe0011a0, 0x00000000)


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213a10) (used target peek value 0x00000000) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213a18) (used target peek value 0x00000000) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213a1c) (used target peek value 0x00000000) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b04) (used target peek value 0x00000001) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b08) (used target peek value 0x00000001) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b00) (used target peek value 0x00000001) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b20) (used target peek value 0x00000003) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b24) (used target peek value 0x00000003) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b28) (used target peek value 0x00000003) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG2
*/
/* PEEK(0xfe213024) (used target peek value 0x0000000a) */
/* PEEK(0xfe213b40) (used target peek value 0x00000003) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG2
*/
/* PEEK(0xfe213024) (used target peek value 0x0000000a) */
/* PEEK(0xfe213b44) (used target peek value 0x00000003) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b14) (used target peek value 0x00000007) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b2c) (used target peek value 0x00000003) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b30) (used target peek value 0x00000002) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213a34) (used target peek value 0x00000011) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b38) (used target peek value 0x0000000b) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL0_CFG
*/
/* PEEK(0xfe213000) (used target peek value 0x80000f01) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_PLL1_CFG
*/
/* PEEK(0xfe213004) (used target peek value 0x80002803) */


/*
stx7111_sysconf_regs.SYSCONF_STA1
*/
/* PEEK(0xfe00100c) (used target peek value 0x0000292c) */


/*
stx7111_clockgena_regs.CKGA_CLKOPSRC_SWITCH_CFG
*/
/* PEEK(0xfe213014) (used target peek value 0xa6aa59aa) */
/* PEEK(0xfe213b3c) (used target peek value 0x00000007) */


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
/* PEEK(0xfe00112c) (used target peek value 0x000006a0) */


/*
stx7111_sysconf_regs.SYSCONF_CFG04
*/
/* PEEK(0xfe001110) (used target peek value 0x00000006) */


/*
stx7111_sysconf_regs.SYSCONF_CFG04
*/
POKE32(0xfe001110, 0x00000002)


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
/* PEEK(0xfe00112c) (used target peek value 0x000006a0) */


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
POKE32(0xfe00112c, 0x080006a1)
DELAY(200)


/*
stx7111_sysconf_regs.SYSCONF_CFG04
*/
/* PEEK(0xfe001110) (used target peek value 0x00000002) */


/*
stx7111_sysconf_regs.SYSCONF_CFG04
*/
POKE32(0xfe001110, 0x00000006)


/*
stx7111_sysconf_regs.SYSCONF_STA3
*/
/* PEEK(0xfe001014) (used target peek value 0x0015f678) */


/*
stx7111_sysconf_regs.SYSCONF_STA3
*/
WHILE_NE32(0xfe001014, 0x00100400, 0x00100400)


/*
stx7111_sysconf_regs.SYSCONF_CFG12
*/
POKE32(0xfe001130, 0xa200687f)


/*
stx7111_sysconf_regs.SYSCONF_CFG38
*/
POKE32(0xfe001198, 0x002ffe0c)


/*
stx7111_sysconf_regs.SYSCONF_CFG13
*/
POKE32(0xfe001134, 0x00600000)


/*
stx7111_sysconf_regs.SYSCONF_CFG14
*/
POKE32(0xfe001138, 0x00000000)
/* PEEK(0xfe00d060) (used target peek value 0x00000000) */


/*
stx7111_sysconf_regs.SYSCONF_CFG55
*/
POKE32(0xfe0011dc, 0x07fc22c4)


/*
stx7111_sysconf_regs.SYSCONF_CFG42
*/
POKE32(0xfe0011a8, 0x2fbbddee)


/*
stx7111_sysconf_regs.SYSCONF_CFG43
*/
POKE32(0xfe0011ac, 0x180001ee)


/*
st40_emi_regs.EMI_BANK_ENABLE
*/
POKE32(0xfe700860, 0x00000005)


/*
st40_emi_regs.EMI_BANK0_BASEADDRESS
*/
POKE32(0xfe700800, 0x00000000)


/*
st40_emi_regs.EMI_BANK1_BASEADDRESS
*/
POKE32(0xfe700810, 0x00000010)


/*
st40_emi_regs.EMI_BANK2_BASEADDRESS
*/
POKE32(0xfe700820, 0x00000012)


/*
st40_emi_regs.EMI_BANK3_BASEADDRESS
*/
POKE32(0xfe700830, 0x00000014)


/*
st40_emi_regs.EMI_BANK4_BASEADDRESS
*/
POKE32(0xfe700840, 0x0000001c)


/*
st40_emi_regs.EMI_BANK0_EMICONFIGDATA0
*/
POKE32(0xfe700100, 0x001016d1)


/*
st40_emi_regs.EMI_BANK0_EMICONFIGDATA1
*/
POKE32(0xfe700108, 0x9d200000)


/*
st40_emi_regs.EMI_BANK0_EMICONFIGDATA2
*/
POKE32(0xfe700110, 0x9d220000)


/*
st40_emi_regs.EMI_BANK0_EMICONFIGDATA3
*/
POKE32(0xfe700118, 0x00000000)


/*
st40_emi_regs.EMI_BANK1_EMICONFIGDATA0
*/
POKE32(0xfe700140, 0x002016d1)


/*
st40_emi_regs.EMI_BANK1_EMICONFIGDATA1
*/
POKE32(0xfe700148, 0x9d222200)


/*
st40_emi_regs.EMI_BANK1_EMICONFIGDATA2
*/
POKE32(0xfe700150, 0x9d220044)


/*
st40_emi_regs.EMI_BANK1_EMICONFIGDATA3
*/
POKE32(0xfe700158, 0x00000000)


/*
st40_emi_regs.EMI_BANK2_EMICONFIGDATA0
*/
POKE32(0xfe700180, 0x002046f9)


/*
st40_emi_regs.EMI_BANK2_EMICONFIGDATA1
*/
POKE32(0xfe700188, 0xa5a00000)


/*
st40_emi_regs.EMI_BANK2_EMICONFIGDATA2
*/
POKE32(0xfe700190, 0xa5a20000)


/*
st40_emi_regs.EMI_BANK2_EMICONFIGDATA3
*/
POKE32(0xfe700198, 0x00000000)


/*
st40_emi_regs.EMI_BANK3_EMICONFIGDATA0
*/
POKE32(0xfe7001c0, 0x002016d1)


/*
st40_emi_regs.EMI_BANK3_EMICONFIGDATA1
*/
POKE32(0xfe7001c8, 0x9d222200)


/*
st40_emi_regs.EMI_BANK3_EMICONFIGDATA2
*/
POKE32(0xfe7001d0, 0x9d220044)


/*
st40_emi_regs.EMI_BANK3_EMICONFIGDATA3
*/
POKE32(0xfe7001d8, 0x00000000)


/*
st40_emi_regs.EMI_BANK4_EMICONFIGDATA0
*/
POKE32(0xfe700200, 0x002016d1)


/*
st40_emi_regs.EMI_BANK4_EMICONFIGDATA1
*/
POKE32(0xfe700208, 0x9d222200)


/*
st40_emi_regs.EMI_BANK4_EMICONFIGDATA2
*/
POKE32(0xfe700210, 0x9d220044)


/*
st40_emi_regs.EMI_BANK4_EMICONFIGDATA3
*/
POKE32(0xfe700218, 0x00000000)


/*
st40_emi_regs.EMI_GENCFG
*/
POKE32(0xfe700028, 0x00000000)


/*
stx7111_sysconf_regs.SYSCONF_CFG11
*/
/* PEEK(0xfe00112c) (used target peek value 0x080006a1) */
/* PEEK(0xfe00d060) (used target peek value 0x00000000) */


/*
st40_lmigp_regs.LMI_MIM_0
*/
POKE32(0xfe901008, 0x0b30017b)


/*
st40_lmigp_regs.LMI_MIM_1
*/
POKE32(0xfe90100c, 0xffff0500)


/*
st40_lmigp_regs.LMI_MIM_1
*/
/* PEEK(0xfe90100c) (used target peek value 0xffff0500) */


/*
st40_lmigp_regs.LMI_STR_0
*/
POKE32(0xfe901018, 0xcf35b424)


/*
st40_lmigp_regs.LMI_STR_1
*/
POKE32(0xfe90101c, 0x00242e58)


/*
st40_lmigp_regs.LMI_SDRA0_0
*/
POKE32(0xfe901030, 0x2c001e20)


/*
st40_lmigp_regs.LMI_SDRA1_0
*/
POKE32(0xfe901038, 0x2c001e20)
DELAY(200000)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020023)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020022)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SDMR0_0
*/
POKE32(0xfe901048, 0x00010000)


/*
st40_lmigp_regs.LMI_SDMR0_0
*/
POKE32(0xfe901048, 0x00018000)


/*
st40_lmigp_regs.LMI_SDMR0_0
*/
POKE32(0xfe901048, 0x00008006)


/*
st40_lmigp_regs.LMI_SDMR0_0
*/
POKE32(0xfe901048, 0x00000b63)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020022)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020024)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020024)


/*
st40_lmigp_regs.LMI_SDMR0_0
*/
POKE32(0xfe901048, 0x00000a63)


/*
st40_lmigp_regs.LMI_SDMR0_0
*/
POKE32(0xfe901048, 0x00008386)


/*
st40_lmigp_regs.LMI_SDMR0_0
*/
POKE32(0xfe901048, 0x00008006)


/*
st40_lmigp_regs.LMI_MIM_0
*/
/* PEEK(0xfe901008) (used target peek value 0x0b30017b) */


/*
st40_lmigp_regs.LMI_MIM_0
*/
POKE32(0xfe901008, 0x0b30037b)


/*
st40_lmigp_regs.LMI_MIM_0
*/
/* PEEK(0xfe901008) (used target peek value 0x0b30037b) */


/*
st40_lmigp_regs.LMI_MIM_0
*/
POKE32(0xfe901008, 0x0b30037b)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_SCR_0
*/
POKE32(0xfe901010, 0x00020021)


/*
st40_lmigp_regs.LMI_GCC_0
*/
POKE32(0xfe901028, 0x00000000)
POKE32(0xfe216000, 0x00000007)
POKE32(0xfe216008, 0x00000006)
POKE32(0xfe21600c, 0x00000004)
POKE32(0xfe216030, 0x00000505)
POKE32(0xfe216038, 0x00000001)
POKE32(0xfe21603c, 0x00000000)
POKE32(0xfe2410fc, 0x00000001)
POKE32(0xfe20a0ec, 0x00000002)
POKE32(0xfe20a0f0, 0x00000005)
POKE32(0xfe20a0f4, 0x00000003)
POKE32(0xfe20a0f8, 0x00000003)
POKE32(0xfe20a1ec, 0x00000002)
POKE32(0xfe20a1f0, 0x00000005)
POKE32(0xfe20a1f4, 0x00000003)
POKE32(0xfe20a1f8, 0x00000003)
POKE32(0xfe20a2ec, 0x00000002)
POKE32(0xfe20a2f0, 0x00000005)
POKE32(0xfe20a2f4, 0x00000003)
POKE32(0xfe20a2f8, 0x00000003)
POKE32(0xfe20a3ec, 0x00000002)
POKE32(0xfe20a3f0, 0x00000005)
POKE32(0xfe20a3f4, 0x00000003)
POKE32(0xfe20a3f8, 0x00000003)
POKE32(0xfe20aefc, 0x00000005)
POKE32(0xfe540034, 0x00000003)
POKE32(0xfe540038, 0x00000000)
POKE32(0xfe540110, 0x00010303)
POKE32(0xfe540114, 0x00000000)
POKE32(0xfe20bb04, 0x00000005)
POKE32(0xfe20bb08, 0x00000003)
POKE32(0xfe20bb10, 0x00000002)
POKE32(0xfe20bb24, 0x00000005)
POKE32(0xfe20bb28, 0x00000003)
POKE32(0xfe20bb2c, 0x00000003)
POKE32(0xfe20bb30, 0x00000002)
POKE32(0xfe20bb44, 0x00000005)
POKE32(0xfe20bb48, 0x00000003)
POKE32(0xfe20bb4c, 0x00000004)
POKE32(0xfe20bb50, 0x00000002)
POKE32(0xfe20bb84, 0x00000005)
POKE32(0xfe20bb88, 0x00000003)
POKE32(0xfe20bb8c, 0x00000003)
POKE32(0xfe20bb90, 0x00000002)
POKE32(0xfe231010, 0x00000008)
POKE32(0xfe231080, 0x00000221)
POKE32(0xfd101824, 0x0003c000)
POKE32(0xfd102024, 0x0003c000)
/* PEEK(0xfe001180) (used target peek value 0x00000015) */
POKE32(0xfe001180, 0x00000005)
POKE32(0xfe1fff04, 0x00254608)
/* PEEK(0xfe001180) (used target peek value 0x00000005) */
POKE32(0xfe001180, 0x00000001)
POKE32(0xfe401744, 0x0025c005)


/*
stx7111_sysconf_regs.SYSCONF_DEVICEID0
*/
/* PEEK(0xfe001000) (used target peek value 0x2d43b041) */
/* PEEK(0xfe00d05c) (used target peek value 0x01100110) */


/*
stx7111_sysconf_regs.SYSCONF_CFG25
*/
POKE32(0xfe001164, 0x00000001)


/*
stx7111_sysconf_regs.SYSCONF_CFG25
*/
POKE32(0xfe001164, 0x00000000)


/*
st40_ccn_regs.CCN_CCR
*/
POKE32(0xff00001c, 0x8000090d)


/*
stx7111_sysconf_regs.SYSCONF_CFG09
*/
/* PEEK(0xfe001124) (used target peek value 0x205265c0) */


/*
stx7111_sysconf_regs.SYSCONF_CFG09
*/
POKE32(0xfe001124, 0x285265c0)


/*
stx7111_sysconf_regs.SYSCONF_CFG05
*/
/* PEEK(0xfe001114) (used target peek value 0x3f800000) */


/*
stx7111_sysconf_regs.SYSCONF_CFG05
*/
POKE32(0xfe001114, 0x3f800000)


/*
stx7111_sysconf_regs.SYSCONF_CFG27
*/
/* PEEK(0xfe00116c) (used target peek value 0x00001fd0) */


/*
stx7111_sysconf_regs.SYSCONF_CFG26
*/
POKE32(0xfe001168, 0xfe804001)


/*
stx7111_sysconf_regs.SYSCONF_CFG27
*/
/* PEEK(0xfe00116c) (used target peek value 0x00001fd0) */


/*
stx7111_sysconf_regs.SYSCONF_CFG27
*/
POKE32(0xfe00116c, 0x00001fd1)


/*
stx7111_sysconf_regs.SYSCONF_CFG27
*/
/* PEEK(0xfe00116c) (used target peek value 0x00001fd1) */


/*
stx7111_sysconf_regs.SYSCONF_CFG27
*/
POKE32(0xfe00116c, 0x00001fd0)


/*
stx7111_sysconf_regs.SYSCONF_CFG09
*/
/* PEEK(0xfe001124) (used target peek value 0x285265c0) */


/*
stx7111_sysconf_regs.SYSCONF_CFG09
*/
POKE32(0xfe001124, 0x285265c0)


/*
stx7111_sysconf_regs.SYSCONF_CFG05
*/
/* PEEK(0xfe001114) (used target peek value 0x3f800000) */


/*
stx7111_sysconf_regs.SYSCONF_CFG05
*/
POKE32(0xfe001114, 0x3f800000)


/*
stx7111_sysconf_regs.SYSCONF_CFG29
*/
/* PEEK(0xfe001174) (used target peek value 0x00001fcc) */


/*
stx7111_sysconf_regs.SYSCONF_CFG28
*/
POKE32(0xfe001170, 0xfe604001)


/*
stx7111_sysconf_regs.SYSCONF_CFG29
*/
/* PEEK(0xfe001174) (used target peek value 0x00001fcc) */


/*
stx7111_sysconf_regs.SYSCONF_CFG29
*/
POKE32(0xfe001174, 0x00001fcd)


/*
stx7111_sysconf_regs.SYSCONF_CFG29
*/
/* PEEK(0xfe001174) (used target peek value 0x00001fcd) */


/*
stx7111_sysconf_regs.SYSCONF_CFG29
*/
POKE32(0xfe001174, 0x00001fcc)

#else
#endif
#if 0

	/* ----- STx7111 Clocks ----- */

	/* Clockgen A initial setup */

	/* Set PLL0 clock to 450MHz */
	/* PLL0 of clockgenA = PLL1600 */

	/* Set CLOCKGENA PLL0 into BYPASS... */
//QQQ	OR32(STX7111_CLOCKGENA_PLL0_CFG, 0x00100000)

	/* Power down CLOCKGENA PLL0... */
//QQQ	OR32(STX7111_CLOCKGENA_POWER_CFG, 0x00000001)

	/* Configure CLOCKGENA PLL0... */
	UPDATE32(STX7111_CLOCKGENA_PLL0_CFG, 0xfff80000, (0xf << 8) | (0x01 & 0x7))

	/* Enable CLOCKGENA PLL0... */
	UPDATE32(STX7111_CLOCKGENA_POWER_CFG, 0xfffffffe, 0)

	/* Wait for CLOCKGENA PLL0 to lock... */
	WHILE_NE32(STX7111_CLOCKGENA_PLL0_CFG, 0x80000000, 0x80000000)

	/* Clear CLOCKGENA PLL0 from BYPASS... */
//QQQ	UPDATE32(STX7111_CLOCKGENA_PLL0_CFG, 0xffefffff, 0)

	/* Set PLL1 clock to 800MHz */
	/* PLL1 of clockgenA = PLL800 */

	/* Set CLOCKGENA PLL1 into BYPASS... */
//QQQ	OR32(STX7111_CLOCKGENA_PLL1_CFG, 0x00100000)

	/* Set dividers clocks */
	POKE32(STX7111_CLOCKGENA_PLL1_DIV0_CFG, 0x00000001)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV1_CFG, 0x00000001)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV2_CFG, 0x00000001)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV3_CFG, 0x00000003)
	POKE32(STX7111_CLOCKGENA_PLL0LS_DIV4_CFG, 0x00000000)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV5_CFG, 0x00000007)
	POKE32(STX7111_CLOCKGENA_PLL0LS_DIV6_CFG, 0x00000000)
	POKE32(STX7111_CLOCKGENA_PLL0LS_DIV7_CFG, 0x00000000)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV8_CFG, 0x00000003)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV9_CFG, 0x00000003)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV10_CFG, 0x00000003)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV11_CFG, 0x00000003)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV12_CFG, 0x00000002)
	POKE32(STX7111_CLOCKGENA_PLL0LS_DIV13_CFG, 0x00000011)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV14_CFG, 0x0000000B)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV15_CFG, 0x00000007)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV16_CFG, 0x00000003)
	POKE32(STX7111_CLOCKGENA_PLL1_DIV17_CFG, 0x00000003)

	POKE32(0xfe702010, 0x00000004)

	/* Power down CLOCKGENA PLL1... */
//QQQ	OR32(STX7111_CLOCKGENA_POWER_CFG, 0x00000002)

	/* Configure CLOCKGENA PLL1... */
	UPDATE32(STX7111_CLOCKGENA_PLL1_CFG, 0xfff80000, (0x0 << 16) | (0x28 << 8) | (0x03))

	/* Enable CLOCKGENA PLL1... */
	UPDATE32(STX7111_CLOCKGENA_POWER_CFG, 0xfffffffd, 0)

	/* Wait for CLOCKGENA PLL1 to lock... */
	WHILE_NE32(STX7111_CLOCKGENA_PLL1_CFG, 0x80000000, 0x80000000)

	/* Clear CLOCKGENA PLL1 from BYPASS... */
//QQQ	UPDATE32(STX7111_CLOCKGENA_PLL1_CFG, 0xffefffff, 0)

	/* Set clock sources */
	POKE32(STX7111_CLOCKGENA_CLKOPSRC_SWITCH_CFG, 0xA6AA59AA)
	POKE32(STX7111_CLOCKGENA_CLKOPSRC_SWITCH_CFG2, 0x0000000A)

	/* Clockgen D (LMI) initial setup (lmi2xfreq = 540) */
	/* Power down PLL... */
	OR32(STX7111_SYSCONF_SYS_CFG11, 0x00001000)

	/* Configure PLL... */
	UPDATE32(STX7111_SYSCONF_SYS_CFG11, 0xfffff001, (0x03 << 9) | (0x50 << 1))

	/* Enable CLOCKGENA PLL1... */
	UPDATE32(STX7111_SYSCONF_SYS_CFG11, 0xffffefff, 0)

	/* Wait for CLOCKGENA PLL1 to lock... (polarity inverted on lock bit) */
	WHILE_NE32(STX7111_SYSCONF_SYS_STA03, 0x00000001, 0)


	/* ----- STX7111 SysConf ----- */
	/* PLI_CLOCK_ENABLE set to 0 */
	OR32(STX7111_SYSCONF_SYS_CFG04, ~(1 << 2))

	/* LMI sub-sys & pl exit from reset */
	OR32(STX7111_SYSCONF_SYS_CFG11, (0x00000001 | 1 << 27))

	/* Delay ~ 200 microseconds (assume 30MHz CPU clock) */
	DELAY(200 * 30)

	/* PLI_CLOCK_ENABLE set to 1 */
	OR32(STX7111_SYSCONF_SYS_CFG04, (1 << 2))

	/* Check both DLL on LMI0 are locked */
	WHILE_NE32(STX7111_SYSCONF_SYS_STA03, (1 << 10) | (1 << 20), (1 << 10) | (1 << 20))

	/* Adjust proga, progb, zoutproga, and receiver mode for LMI0 */
	POKE32(STX7111_SYSCONF_SYS_CFG12, (0xa2007801 | (0x7 << 1) | (0x0 << 4) | (0x0 << 7) | (0x0 << 10)))

	/* Enable AutoPrecharge */
	POKE32(STX7111_SYSCONF_SYS_CFG38, 0x000FFE0C)

	/* Force DLL1 and DLL2 command of LMI0 */
	POKE32(STX7111_SYSCONF_SYS_CFG13, 0x00600000) /*Charly Oct11, was 0000*/
	POKE32(STX7111_SYSCONF_SYS_CFG14, 0x00000000)

	/* Set cfg55 */
#ifndef LMI_16BITS_MODE
#define LMI_16BITS_MODE 0
#endif
        POKE32(STX7111_SYSCONF_SYS_CFG55, 0x03fc22c4)
	/* PDL offsets */
	POKE32(STX7111_SYSCONF_SYS_CFG42, 0x07afd7eb)
	POKE32(STX7111_SYSCONF_SYS_CFG43, 0x000001eb)

	/* ----- STX7111 EMI configuration ----- */


	POKE32(ST40_EMI_BANK_ENABLE, 0x00000005)

	/* NOTE: bits [0,5] define bottom address bits [22,27] of bank */
	POKE32(ST40_EMI_BANK0_BASEADDRESS, 0x00000000)
	POKE32(ST40_EMI_BANK1_BASEADDRESS, 0x00000010)
	POKE32(ST40_EMI_BANK2_BASEADDRESS, 0x00000012)
	POKE32(ST40_EMI_BANK3_BASEADDRESS, 0x00000014)
	POKE32(ST40_EMI_BANK4_BASEADDRESS, 0x0000001C)

	/* Bank 0 - On-board 32MiB Flash at address 0x00000000 -> 0x01ffffff */
	POKE32(ST40_EMI_BANK0_EMICONFIGDATA0, 0x001016d1)
	POKE32(ST40_EMI_BANK0_EMICONFIGDATA1, 0x9d200000)
	POKE32(ST40_EMI_BANK0_EMICONFIGDATA2, 0x9d220000)
	POKE32(ST40_EMI_BANK0_EMICONFIGDATA3, 0x00000000)

	/* Bank 1 - STEM 8 MiB 0x04000000 -> 0x047fffff */
	POKE32(ST40_EMI_BANK1_EMICONFIGDATA0, 0x002016d1)
	POKE32(ST40_EMI_BANK1_EMICONFIGDATA1, 0x9d222200)
	POKE32(ST40_EMI_BANK1_EMICONFIGDATA2, 0x9d220044)
	POKE32(ST40_EMI_BANK1_EMICONFIGDATA3, 0x00000000)

	/* Bank 2 - DVB-CI at address 0x04000000 -> 0x04FFFFFF */
	POKE32(ST40_EMI_BANK2_EMICONFIGDATA0, 0x002046f9)
	POKE32(ST40_EMI_BANK2_EMICONFIGDATA1, 0xa5a00000)
	POKE32(ST40_EMI_BANK2_EMICONFIGDATA2, 0xa5a20000)
	POKE32(ST40_EMI_BANK2_EMICONFIGDATA3, 0x00000000)

	/* Bank 3 - 32MiB Boards register and either DVBCI notCe2 or
		STEM notCS1 (16MiB + 16MiB split bank) 0x05000000 -> 0x06ffffff
	 */
	POKE32(ST40_EMI_BANK3_EMICONFIGDATA0, 0x002016d1)
	POKE32(ST40_EMI_BANK3_EMICONFIGDATA1, 0x9d222200)
	POKE32(ST40_EMI_BANK3_EMICONFIGDATA2, 0x9d220044)
	POKE32(ST40_EMI_BANK3_EMICONFIGDATA3, 0x00000000)

	/* Bank 4 - EPLD Registers at address 0x07000000 -> 0x07FFFFFF */
	POKE32(ST40_EMI_BANK4_EMICONFIGDATA0, 0x002016d1)
	POKE32(ST40_EMI_BANK4_EMICONFIGDATA1, 0x9d222200)
	POKE32(ST40_EMI_BANK4_EMICONFIGDATA2, 0x9d220044)
	POKE32(ST40_EMI_BANK4_EMICONFIGDATA3, 0x00000000)

	/* Program other EMI registers */
	POKE32(ST40_EMI_GENCFG, 0x00000000)


	/* ----- STX7111 LMI0 configuration ----- */

	/* Configuring LMI0 for DDR2 SDRAM Elpida EDE5116AHBG-8E-E
	 # Refresh interval compute (from Ignazio, 11jan08)
	 # 300 MHz --->  T=3.4ns => MIM[28:16]=2038 ((2294-256)+ACo-3.4ns<+AH4-7.8us)
	 # 330 MHz --->  T=3.1ns => MIM[28:16]=2260 ((2516-256)+ACo-3.1ns<+AH4-7.8us)
	 # 360 MHz --->  T=2.8ns => MIM[28:16]=2529 ((2785-256)+ACo-2.8ns<+AH4-7.8us)
	 # 400 MHz --->  T=2.5ns => MIM[28:16]=2864 ((3120-256)+ACo-2.5ns=7.8us)
	 */
	POKE32(ST40_LMI_MIM_0(), 0x0b30017b)
	/* Note: refresh is enabled in later steps */

	POKE32(ST40_LMI_MIM_1(), 0x00000500)

	/* SDRAM Timing Register
	 # lmi.LMI_STR_0.poke(0x4c2db41b)
	 # FCh, 19/mar/08: change according to Raffaele G feebacks
	 #		1-cycle additional delay between RD and WR
	 */
	POKE32(ST40_LMI_STR_0(), 0xcf35b424)
	POKE32(ST40_LMI_STR_1(), 0x00242e58)

	/* SDRAM Array Attribute Register
	 # Upper LMI addr=0x0C000000 + 128MiB=0x14000000, 13x10
	 */
	POKE32(ST40_LMI_SDRA0_0(), 0x2c001e20)

	/* SDRAM Array Attribute Register
	 # Upper LMI addr=0x0C000000 + 128MiB=0x14000000, 13x10
	 */
	POKE32(ST40_LMI_SDRA1_0(), 0x2c001e20)

	/* SDRAM Control Register */
	/* Delay ~ 200 milliseconds (assume 450MHz CPU clock) */
	DELAY(200000 * 450)

	/* Enable clock with NOP command */
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020023)
	/* Wait NOP command for 400 nsec */
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)

	/* Precharge all */
	POKE32(ST40_LMI_SCR_0(), 0x00020022)
	/* Wait NOP command for 400 nsec */
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)

	/* Issue EMRS2 */
	POKE32(ST40_LMI_SDMR0(), 0x00010000)

	/* Issue EMRS3 */
	POKE32(ST40_LMI_SDMR0(), 0x00018000)

	/* Issue EMRS1 to enable DLL */
	POKE32(ST40_LMI_SDMR0(), 0x00008006)

	/* Issue MRS with DLL reset, CAS 5, Write recovery 5, Sequentiel, Burst lengh 8
	 # lmi.LMI_SDMR0_0.poke(0x00000953)
	 # FCh, 19/mar/08: change according to Raffaele G feebacks
	 */
	POKE32(ST40_LMI_SDMR0(), 0x00000b63)

	/* Wait NOP command for 400 nsec */
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)

	/* Precharge all */
	POKE32(ST40_LMI_SCR_0(), 0x00020022)
	/* 2 CBR (auto refresh) */
	POKE32(ST40_LMI_SCR_0(), 0x00020024)
	POKE32(ST40_LMI_SCR_0(), 0x00020024)

	/* Issue MRS with CAS 5, Write recovery 5, Sequentiel, Burst lengh 8
	 # lmi.LMI_SDMR0_0.poke(0x00000853)
	 # FCh, 19/mar/08: change according to Raffaele G feebacks
	 */
	POKE32(ST40_LMI_SDMR0(), 0x00000a63)

	/* Issue EMRS1 for OCD calibration default */
	/* lmi.LMI_SDMR0_0.poke(0x000007c4) */
	POKE32(ST40_LMI_SDMR0(), 0x00008386)

	/* Issue EMRS1 for OCD calibration exit */
	/* lmi.LMI_SDMR0_0.poke(0x00000444) */
	POKE32(ST40_LMI_SDMR0(), 0x00008006)

	/* Enable auto refresh
	 # lmi.LMI_MIM_0.poke(0x0c30037b)
	 # FCh, 12/feb/08: cleaner to modify only refresh bit
	 */
	POKE32(ST40_LMI_MIM_0(), 0xb30037b)
	/*OR32(ST40_LMI_MIM_0(), (1 << 9))*/

	/* DQS recovery mechanism (1=enabled)
	 # lmi.LMI_MIM_0.poke(lmi.LMI_MIM_0.peek() | (1 << 5))
	 # FCh, 14/jan/08, NO DQS recovery
	 */
	POKE32(ST40_LMI_MIM_0(), 0xb30037b)
	/*UPDATE32(ST40_LMI_MIM_0(), ~(1 << 5), 0)*/

	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)
	POKE32(ST40_LMI_SCR_0(), 0x00020021)

	POKE32(ST40_LMI_GCC_0(), 0x00000000)

#endif
#ifdef CONFIG_SH_SE_MODE
	/*
	 * Note that we also manually need to move the LMI base addresses to
	 * their 32-bit SE mode locations as defined in the datasheet and change the
	 * 'upper bound addresses' (in row attribute registers) for the LMIs.
	 */
	UPDATE_LONG(STX7111_SYSCONF_SYS_CFG38, 0xFFFFFF00, 0x00000040)
	/*UPDATE_LONG(STX7111_SYSCONF_SYS_CFG39, 0xFFFFFF00, 0x00000080)*/
	POKE_LONG(ST40_LMI_SDRA0_0(), 0x60001e20)
	POKE_LONG(ST40_LMI_SDRA1_0(), 0x60001e20)
#endif	/* CONFIG_SH_SE_MODE */

	END_MARKER

__memory_setup_table_end:

	.end
