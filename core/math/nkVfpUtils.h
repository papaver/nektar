//------------------------------------------------------------------------------
// nkVfpUtils.h
//
// -- VFP math stuff --
//
// - 's' stands for short-vector ops, 8 single persicion ops are available at once!
// - all data operations support conditional execution
//   - fcmp for example sets the bits, other ops will clear them
//   - 'eq' - equal
//   - 'ne' - not equal
//   - 'lt' - less than
//   - 'gt' - greater than
//   - 'le' - less than or equal
//   - 'ge' - greater than or equal
// - fcmp - compare and set control bits accordingly
// - fmrs - float move from general register to float register
// - fmsr - float move from float register to general register
// - fstat - stalls the processor till compare bit is set in register
//   - great for waiting on a compare to start a conditional op
// - using a ! in a ld/st will increment the basereg 
//   - so one can load one vec at a time from an array
//
//------------------------------------------------------------------------------

#ifndef _NKVFPUTILS_H_
#define _NKVFPUTILS_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nkMath.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

//
// --- Control Register Map ---
//
//             xxxx xx  x  x    xx     xx x xxx   
//  [31-16] :: NZCV 00 DN FZ RMODE STRIDE 0 LEN  
//
//               x xx   x   x   x   x   x   x xx   x   x   x   x   x
//  [15-00] :: IDE 00 IXE UFE OFE DZE IOE IDC 00 IXC UFC OFC DZC IOC 
//

#define VFP_CBIT_RESET            0x0C086060   // set all known control bits to 0

#define VFP_CBIT_DEFAULT_NAN      0x02000000   // enable default Nan mode
#define VFP_CBIT_FLUSH_TO_ZERO    0x01000000   // enable flush-to-zero-mode
#define VFP_CBIT_RUN_FAST         0x03000000   // 'runfast' mode

#define VFP_CBIT_ROUND_NEAREST    0x00000000   // b00 - round to nearest (RN) mode
#define VFP_CBIT_ROUND_PLUS_INF   0x00400000   // b01 - round towards plus infinity (RP) mode
#define VFP_CBIT_ROUND_MINUS_INF  0x00800000   // b10 - round towards minus infinity (RM) mode
#define VFP_CBIT_ROUND_ZERO       0x00C00000   // b11 - round towards zero (RZ) mode

#define VFP_CBIT_VEC_LEN_1        0x00000000   // b000 - scalar
#define VFP_CBIT_VEC_LEN_2        0x00010000   // b001 - v2 single precision floats
#define VFP_CBIT_VEC_LEN_3        0x00020000   // b010 - v3 single precision floats
#define VFP_CBIT_VEC_LEN_4        0x00030000   // b011 - v4 single precision floats
#define VFP_CBIT_VEC_LEN_5        0x00040000   // b100 - v5 single precision floats
#define VFP_CBIT_VEC_LEN_6        0x00050000   // b101 - v6 single precision floats
#define VFP_CBIT_VEC_LEN_7        0x00060000   // b110 - v7 single precision floats
#define VFP_CBIT_VEC_LEN_8        0x00070000   // b111 - v8 single precision floats

//
// register clobber lists
//

#define VFP_CLOBBER_S00_S03  "s0",  "s1",  "s2",  "s3"  // bank 0 (scalar)
#define VFP_CLOBBER_S04_S07  "s4",  "s5",  "s6",  "s7"  // bank 0 (scalar)
#define VFP_CLOBBER_S08_S11  "s8",  "s9", "s10", "s11"  // bank 1 (vector)
#define VFP_CLOBBER_S12_S15 "s12", "s13", "s14", "s15"  // bank 1 (vector)
#define VFP_CLOBBER_S16_S19 "s16", "s17", "s18", "s19"  // bank 2 (vector)
#define VFP_CLOBBER_S20_S23 "s20", "s21", "s22", "s23"  // bank 2 (vector)
#define VFP_CLOBBER_S24_S27 "s24", "s25", "s26", "s27"  // bank 3 (vector)
#define VFP_CLOBBER_S28_S31 "s28", "s29", "s30", "s31"  // bank 3 (vector)

#define VFP_CLOBBER_S00_S07 VFP_CLOBBER_S00_S03, VFP_CLOBBER_S04_S07  // bank 0 (scalar)
#define VFP_CLOBBER_S08_S15 VFP_CLOBBER_S08_S11, VFP_CLOBBER_S12_S15  // bank 1 (vector)
#define VFP_CLOBBER_S16_S23 VFP_CLOBBER_S16_S19, VFP_CLOBBER_S20_S23  // bank 2 (vector)
#define VFP_CLOBBER_S24_S31 VFP_CLOBBER_S24_S27, VFP_CLOBBER_S28_S31  // bank 3 (vector)

#define VFP_CLOBBER_S08_S23 VFP_CLOBBER_S08_S15, VFP_CLOBBER_S16_S23  // bank     1 & 2
#define VFP_CLOBBER_S08_S31 VFP_CLOBBER_S08_S23, VFP_CLOBBER_S28_S31  // bank     1 & 2 & 3
#define VFP_CLOBBER_S00_S31 VFP_CLOBBER_S00_S07, VFP_CLOBBER_S08_S31  // bank 0 & 1 & 2 & 3

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

NK_MATH_INLINE u32 vfp_mode_set(u32 mode)
{
  static const u32 reset = VFP_CBIT_RESET;

  u32 fpscr;
  __asm__ __volatile__ (
    "fmrx  %0, fpscr   \n\t"  // r0 = FPSCR
    "and   %1, %0, %1  \n\t"  // r1 = r0 & reset
    "orr   %1, %1, %2  \n\t"  // r1 = r1 | mask
    "fmxr  fpscr, %1   \n\t"  // FPSCR = r1
    : "+r"(fpscr)
    : "r" (reset), "r" (mode)
  );
  return fpscr;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vfp_mode_reset()
{
  vfp_mode_set(0);
}

//------------------------------------------------------------------------------

#endif // _NKVFPUTILS_H_
