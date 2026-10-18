#ifndef EE_REGS_H
#define EE_REGS_H

/*
 * Addresses of the PlayStation 2's Emotion Engine and GS hardware registers that the main program reads and
 * writes, under the names the EE User's Manual and the GS User's Manual give them (Sony's eeregs.h uses the
 * same names for pointers; here they are plain addresses, so each access keeps its own type:
 * `*(volatile u32 *)D_STAT_ADDR`). Only preprocessor names: nothing here reaches the compiler's output.
 */

/* Timers */
#define T1_COUNT_ADDR   0x10000800
#define T1_MODE_ADDR    0x10000810
#define T3_MODE_ADDR    0x10001810

/* IPU (the MPEG decoder) */
#define IPU_CMD_ADDR    0x10002000
#define IPU_CTRL_ADDR   0x10002010
#define IPU_BP_ADDR     0x10002020
#define IPU_TOP_ADDR    0x10002030
#define IPU_IN_FIFO_ADDR 0x10007010

/* GIF and VIF */
#define GIF_CTRL_ADDR   0x10003000
#define VIF0_STAT_ADDR  0x10003800
#define VIF0_FBRST_ADDR 0x10003810
#define VIF0_ERR_ADDR   0x10003820
#define VIF0_MARK_ADDR  0x10003830
#define VIF0_CYCLE_ADDR 0x10003840
#define VIF0_MODE_ADDR  0x10003850
#define VIF0_NUM_ADDR   0x10003860
#define VIF0_MASK_ADDR  0x10003870
#define VIF0_CODE_ADDR  0x10003880
#define VIF0_ITOPS_ADDR 0x10003890
#define VIF0_ITOP_ADDR  0x100038D0
#define VIF0_R0_ADDR    0x10003900
#define VIF0_R1_ADDR    0x10003910
#define VIF0_R2_ADDR    0x10003920
#define VIF0_R3_ADDR    0x10003930
#define VIF0_C0_ADDR    0x10003940
#define VIF0_C1_ADDR    0x10003950
#define VIF0_C2_ADDR    0x10003960
#define VIF0_C3_ADDR    0x10003970
#define VIF1_STAT_ADDR  0x10003C00
#define VIF1_FBRST_ADDR 0x10003C10
#define VIF1_ERR_ADDR   0x10003C20
#define VIF0_FIFO_ADDR  0x10004000
#define VIF1_FIFO_ADDR  0x10005000

/* DMA channels: 1 VIF1, 2 GIF, 3 from IPU, 4 to IPU, 5 SIF0, 8 from scratchpad, 9 to scratchpad */
#define D1_CHCR_ADDR    0x10009000
#define D1_MADR_ADDR    0x10009010
#define D1_QWC_ADDR     0x10009020
#define D1_TADR_ADDR    0x10009030
#define D2_CHCR_ADDR    0x1000A000
#define D2_MADR_ADDR    0x1000A010
#define D2_QWC_ADDR     0x1000A020
#define D3_CHCR_ADDR    0x1000B000
#define D3_MADR_ADDR    0x1000B010
#define D3_QWC_ADDR     0x1000B020
#define D4_CHCR_ADDR    0x1000B400
#define D4_MADR_ADDR    0x1000B410
#define D4_QWC_ADDR     0x1000B420
#define D4_TADR_ADDR    0x1000B430
#define D5_CHCR_ADDR    0x1000C000
#define D8_CHCR_ADDR    0x1000D000
#define D8_MADR_ADDR    0x1000D010
#define D8_QWC_ADDR     0x1000D020
#define D8_SADR_ADDR    0x1000D080
#define D9_CHCR_ADDR    0x1000D400
#define D9_MADR_ADDR    0x1000D410
#define D9_QWC_ADDR     0x1000D420
#define D9_TADR_ADDR    0x1000D430
#define D9_SADR_ADDR    0x1000D480

/* DMA controller */
#define D_CTRL_ADDR     0x1000E000
#define D_STAT_ADDR     0x1000E010
#define D_PCR_ADDR      0x1000E020
#define D_SQWC_ADDR     0x1000E030
#define D_RBSR_ADDR     0x1000E040
#define D_RBOR_ADDR     0x1000E050
#define D_STADR_ADDR    0x1000E060
#define D_ENABLER_ADDR  0x1000F520
#define D_ENABLEW_ADDR  0x1000F590

/* Interrupt controller and serial port */
#define INTC_STAT_ADDR  0x1000F000
#define SIO_ISR_ADDR    0x1000F130
#define SIO_TXFIFO_ADDR 0x1000F180

/* GS privileged registers */
#define GS_PMODE_ADDR   0x12000000
#define GS_SMODE2_ADDR  0x12000020
#define GS_DISPFB1_ADDR 0x12000070
#define GS_DISPLAY1_ADDR 0x12000080
#define GS_DISPFB2_ADDR 0x12000090
#define GS_DISPLAY2_ADDR 0x120000A0
#define GS_EXTDATA_ADDR 0x120000C0
#define GS_EXTWRITE_ADDR 0x120000D0
#define GS_BGCOLOR_ADDR 0x120000E0
#define GS_CSR_ADDR     0x12001000
#define GS_BUSDIR_ADDR  0x12001040

/* The scratchpad: 16 KB of fast memory inside the EE */
#define SCRATCHPAD_ADDR 0x70000000

#endif
