********************************************************************************
*             TMS320C55x DSPLIB Release Version 3.00.00                                                                              *
*                               Release Notes                                                                                                         *
********************************************************************************
 C55x DSPLIB is a DSP function library for the TMS320C55x containing over 50 
 C-callable hand assembly optimized routines.
 
 DSPLIB is a free-of-charge product to facilitate your programming in C.

 You can download DSPLIB free-of-charge at:
 http://www.ti.com/sc/docs/products/dsp/c5000/index.htm

================================================================================
Table of Contents
================================================================================
 1. Scope
 2. Bugs fixed in this release and previous releases
 3. Open bugs
 4. For bug reports/ suggestions/ user contribued code
 5. C models
 6. Installation Guide
 7. Benchmarks
================================================================================
 1. Scope
================================================================================

 This package contains release 3.00.00 of the Texas Instruments TMS320C55x core 3.0
 DSP Library (DSPLIB).

 The User's Guide is located at: \docs\pdf\ in your CCS install folder.
 Read the standard license agreement contained in the User's Guide (Appendix)

 Please notice that the library is built under options -vcore:3.0 and --memory_model=huge. 


================================================================================
 2. Bugs Fixed in this release and previously releases
================================================================================
 ** Bugs fixed in this release (version 3.00.00) 
 -----------------------------------------
(1) abias.asm:
    There was incorrect handling of odd number of output elements.
    T2 and T3 were used but not restored.  This is not compatible with C.
    AR5 was modified but not restored correctly (due to bug in stack alignment).
    Code told compiler that ARMS was off, but it never turned it off, and compiler expects it on.
    AC0 and AC3 were checked for overflow, but ACOV0 and ACOV3 were are not cleared at entry.
(2) add.asm:
    AR1 was set to a circular buffer but not intentionally.  If BSA01 isn't 0 and BK03 not 
    huge (or 0), then resultant array would be written in wrong place.
(3) araw.asm:
    Test "T8.H" failed.
    If NR is odd, one too many output elements were written (unless NR+1=NX)
    If NX < 4, output was incorrect (NX=1 and NX=2 fixed)
    AR5 was modified but not restored correctly (due to bug in stack alignment)
    AC0 and AC3 were checked for overflow, but ACOV0 and ACOV3 were not cleared at entry.
(4) aubias.asm:
    AR4 (a.k.a. "odd") was read prior to being set.
    AR5 was modified but not restored correctly (due to bug is stack alignment).
    AC0 and AC3 are checked for overflow, but ACOV0 and ACOV3 were not cleared at entry.
    T2 was used but was not saved and restored.
    T3 was used but was not saved and restored.
    When the number of output elements is an odd number, function did not work correctly.
    Code told compiler that ARMS was off, but it never turned it off, and compiler expects it on.
(5) cbias.asm:
    *CDP was used before CDPH is set.
    AR5 was modified but not restored correctly. (It was saved, but the saved value was incremented).
    T3 was used but was not saved and restored.  (This was due to c54 MPY syntax that implicitly sets T3.)
    AC0 and AC1 were checked for overflow, but ACOV0 and ACOV1 were not cleared at entry.
(7) cbrev.asm:
    AR4 was used as circular pointer, but BK47 was never set.
(8) convol1.asm:
    SMUL in ST3 was cleared, but not set on exit.
    Overflow test needed to also look at ACOV1.
(9) convol2.asm:
    SMUL in ST3 was cleared, but not set on exit.
    Overflow test needed to also look at ACOV1.
(10) convol.asm:
    SMUL in ST3 was cleared, but not set on exit.
(11) craw.asm:
    T3 was used but was not saved and restored.  (This was due to c54 MPY syntax that implicitly sets T3.)
    AC0 and AC1 were checked for overflow, but ACOV0 and ACOV1 were not cleared at entry.
    Code told compiler that ARMS was off, but it never turned it off, and compiler expects it on.
(12) cubias.asm:
    T3 was modified, but not saved and restored.
    AC0 and AC1 were checked for overflow, but ACOV0 and ACOV1 were not cleared at entry.
    The overflow flag was always return as 32 (because the value was returned in AC0 instead of T0).
    Code told compiler that ARMS was off, but it never turned it off, and compiler expects it on.
(13) dlms.asm:
    AR5 was used as pointer, but AR5H was never set.
(14) dlmsfast.asm:
    AR6 and AR7 were used as pointers, but AR6H and AR7H were never set.
    DP was modified but not restored
(15) expn.asm:
    expn_coeffs in .data was not aligned but was accessed as a dbl(). 
    AC0 was checked for overflow, but ACOV0 was not cleared at entry.
(16) fir2.asm:
    SMUL in ST3 was cleared, but not set on exit.
(17) fir.asm:
    SMUL in ST3 was cleared, but not set on exit.
(18) firlat.asm:
    T0 was not cleared before checking for overflow.
    ACOV1 needed to be checked for overflow.
(19) firs.asm:
    AC0 should have been cleared prior to start of loop1. Otherwise first element was not bit-exact.
(20) fltoq15.asm:
    Returned an error condition but the value of the error condition was never initialized 
    on the stack *SP(4) or *SP(10).  So if both errors didn't occur, garbage would be returned.
    Code told compiler that ARMS was off, but it never turned it off, and compiler expects it on.
(21) iircas4.asm:
    Didn't set index in dbuffer[] correctly, so 2nd call would fail.
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
(22) iircas5.asm:
    Failed on 2nd call if there was an odd number of elements.
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
(23) iircas32.asm:
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
	Overflow flag was often being turned on incorrectly because 32-bit multiplication 
	normally overflows 32 bits when adding the two unsigned multiplies.
    The arithmetic should have been done in 40-bit space.
(24) iircas51.asm:
    Failed on 2nd call if there was an odd number of elements.
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
(25) iirlat.asm:
    Overflow test needed to also look at ACOV1.
(26) interp.asm:
    T2 was modified, but not saved and restored.
    Bug fixed where T3 is tested but never set within function:
         BCC    No_Interp, T3<0    
(27) log_2.asm:
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
(28) log_10.asm:
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
(30) maxidx34.asm:
    DP was used to access memory-mapped registers, but DPH was never set.
(31) maxidx.asm:
    DP was used to access memory-mapped registers, but DPH was never set.
    AR5 and AR6 were used as pointers to TRN0 and TRN1, but AR5H and AR6H were never set.
    Bug fixed on first iteration of outer_loop. TRN0 was not first set to 0. 
    Thus, if CSR < 15, and maximum value is 1st element, then returned index could be incorrect.
    If first element was maximum and T2 was non-zero, index would be incorrect.
(32) maxval.asm:
    DP was used to access memory-mapped registers, but DPH was never set.
(33) minidx.asm:
    DP was used to access memory-mapped registers, but DPH was never set.
    AR5 and AR6 were used as pointers to TRN0 and TRN1, but AR5H and AR6H were never set.
    Bug fixed on first iteration of outer_loop. TRN0 was not first set to 0. 
    Thus, if CSR < 15, and maximum value is 1st element, then returned index could be incorrect.
(34) minval.asm:
    DP was used to access memory-mapped registers, but DPH was never set.
(35) mmul.asm:
    T2 was modified, but not saved and restored.
    T3 was modified, but not saved and restored.
(36) mtrans.asm:
    T2 was modified, but not saved and restored.
(37) mul32.asm:
    AR5 was modified, but not saved and restored.
    T3 was modified, but not saved and restored.
(38) neg32.asm:
    SATD in ST1 was set on entry but not cleared on exit.
    AR1 was set to a circular buffer, but not intentionally.  If BSA01 wasn't 0 
    and BK03 was not huge (or 0), then resultant array will be written in wrong place.
(39) neg.asm:
    AR1 was set to a circular buffer, but not intentionally.  If BSA01 wasn't 0 
    and BK03 was not huge (or 0), then resultant array will be written in wrong place.
(40) power.asm:
    If AR3H != AR1H on entry, then the output array would be written to the wrong page.
(41) q15tofl.asm:
    T3 was modified, but not saved and restored.
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
(42) rand16.asm:
    T3 was modified, but not saved and restored.
    Used *abs16(#rndseed) to access a value in .bss which may not have succeeded due to:  
        1. DPH was not set to 0. It is used to define the address.
        2. .bss doesn't necessarily have an address less than 0x10000
(43) recip16.asm:
    Both the inner and outer Repeat Blocks used "RPTB loop" syntax rather than "RPTB loop-1".
    One extra unintentional instruction was executed per block.  Fortunately the particular 
    instructions were relatively harmless. 
(44) sine.asm:
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
(45) sqrtv.asm:
    Code checked AC0 for overflow, but did not clear ACOV0 on entry.
    The rounding method at end of outer loop was incorrect.  Its round adder was shifted up by one extra bit.
(46) sub.asm:
    AR1 was set to a circular buffer but not intentionally.  If BSA01 wasn't 0 and BK03 wasn't huge (or 0),
      then the resultant array would be incorrect.
(47) unpack.asm:
    The stack was aligned on odd but the code to save T2 and T3 was performed as follows:
            MOV        pair(T2),dbl(*SP(#00h))
    That put T3 in *SP(-1).  If an interrupt occured, it would overwrite the saved value of T3, 
	and hence T3 would not be restored correctly.
(48) unpacki.asm:
    The stack was aligned on odd but the code to save T2 and T3 was performed as follows:
            MOV        pair(T2),dbl(*SP(#00h))
    That put T3 in *SP(-1).  If an interrupt occured, it would overwrite the saved value of T3, 
	and hence T3 would not be restored correctly.

 ** Bugs fixed in this release (version 2.40.00) 
 -----------------------------------------
(1) abias, araw, aubias, cbias, craw, expn: added overflow checking and return overflow value is in T0 instead of AC0.
(2) IIR4, IIR5, IIR32, IIR51: XDP is cleared instead of only clearing DP.
(3) power.asm: return overflow value is in T0 instead of AC0. Output vector is returned.
(4) fltoq15.asm: T2 registered is used and saved in the function. 


 ** Bugs fixed in this release (version 2.30.00) 
 -----------------------------------------
 (1) Fixed twiddle table addition bug, affects FFT, UNPACK and CBREV routines
 (2) Added 8-point support to cfft_scale() and improved butterfly Kernel to 5 cycles.
 (3) ldiv16(): optimized
 (4) recip16(): optimized
 (5) q15tofl() fixed bug for min and max q15 values
 (6) sine() fixed bug for value 1
 (7) Added unpack32() and unpacki32() for rfft32() and rifft32() support
 (8) acorr_bias(): added psh/pop st1
 (9) add(): added psh/pop st1
 (10) accor_raw(): added psh/pop st1
 (11) accor_unbias(): added psh/pop st1
 (12) cbrev(): improved code performance for inplace version.
 (13) cfir(): added psh/pop st1
 (14) cfir(): added extended register initialization for large memory model
 (15) cor_raw(): added extended register initialization for large memory model
 (16) cor_unbias(): added extended register initialization for large memory model
 (17) firdec(): added psh/pop t2
 (18) dmlsfast(): added extended register initialization for large memory model
 (19) firlat(): added psh/pop st3
 (20) firs(): added psh/pop st3
 (21) iircas4(): added extended register initialization for large memory model
 (22) iircas5(): removed delay buffer index
 (23) iircas51(): removed delay buffer index
 (24) iirlat(): added psh/pop st3
 (25) iirlat(): added extended register initialization for large memory model
 (26) ldiv16(): added psh/pop st3
 (27) recip16(): added psh/pop st3
 (28) log_10(): added psh/pop st1
 (29) log_10(): added extended register initialization for large memory model
 (30) log_2(): added psh/pop st1
 (31) log_2(): added extended register initialization for large memory model
 (32) logn(): added psh/pop st1
 (33) logn(): added extended register initialization for large memory model
 (34) maxidx34(): removed unnecessary .bss section allocation.
 (35) minidx(): replaced "CMP AC1<AC0, TC1" with "CMP AC0>=AC1, TC1"
 (36) neg(): added psh/pop st3
 (37) neg32(): added psh/pop st3
 (38) power(): added psh/pop st3
 (39) sqrt_16(): added psh/pop t2,t3
 (40) sqrt_16(): added extended register initialization for large memory model
 (41) sub(): added psh/pop st3
 (41) sub(): added psh/pop st3
 (41) sub(): added psh/pop st3
 (41) unpack(): modified way twiddle table included
 (42) unpacki(): modified way twiddle table is included




 ** Bugs fixed in this release (version 2.20.02) 
 -----------------------------------------
 (1) added new function: cfft32(cfft32_scale.asm, cfft32_noscale.asm) which does
     32-bit CFFT. 

 (2) added new function: cifft32(cifft32_scale.asm, cifft32_noscale.asm) which does
     32-bit inversed CFFT. 

 (3) added new function: dlmsfast(dlmsfast.asm) which has better performs on large tap filters(
     1.5 cycles per filter tap).



 ** Bugs fixed in version 2.20.01 release 
 -----------------------------------------
 (1) added new functions: cfft_offplace(cfft_o_s.asm, cfft_o_nos.asm) 
     and cifft_offplace(cifft_o_s.asm, cifft_o_nos.asm) which have better benchmark than cfft/cifft fucntions.

 ** Bugs fixed in version 2.20 release 
 -----------------------------------------
 (1) functions: cfft_scale.asm, cfft_noscale.asm, cifft_scale.asm, cifft_noscale.asm
     Fixed bugs in cfft_scale/cfft_noscale/cifft_scale/cifft_noscale functions.

 (2) functions: iir51.asm, iir5.asm, iir32.asm
     Added st0 register save/restore.

 (3) function: minval.asm
     optimized minval function for better benchmark purpose.

 (4) function: minidx.asm
     optimized minidx function for better benchmark purpose, also the funtion prototype changed.

 (5) function: maxidx.asm
     fixed code to make it works when the first element is the max.

 (6). Added project for each function in example directory.


 ** Bugs Fixed in version 2.10.03 release 
 -----------------------------------------
 (1) added 4096 twiddle table to src as a option.
     fixed cfft.cmd/rfft.cmd .input/.twiddle alignment comment.
 
 (2) function: unpack.asm and unpacki.asm
     fixed T2/T3 restore problem in unpack/unpacki funcions.

 (3) function sqrvt.asm
     fixed the bug where NX should be stored in register T0 instead of AR2.
     fixed code to work in large block memory by correct XAR loading.

 (4) funtions: cbrev.asm cfft.asm and cifft.asm
  	For cbrev.asm:
	- reset C54CM bit
	- push/pop ST2, ST1
	
	For CIFFT
	cifft_noscale.asm: 
		- Changed the Radix 4 stage and radix 2 stages according to IFFT C model
		- Corrected the context save
	cifft_scale.asm: 
		- Modified stack to make correct XAR restore (this problem was found by visual inspection of the XAR5, 6, 7 - not detected by the test)

        Added test vectors for NOSCALE version

	For CFFT:
	cfft_noscale.asm: 
		- Corrected the context save

	cfft_scale.asm: 
		- Modified stack 

        Added test vectors for NOSCALE version


 (5)functions: abias.asm, cbias.asm, fltoq15.asm, mul32.asm, and q15tofl.asm
    fixed assembly code to make them work in large memory module(XAR fixes).


================================================================================
 3. Open Bugs
================================================================================
(1) Functions craw.asm, cbias.asm, and craw.asm are only supported for values
    of the arguments 'nx' equal to 'ny'.


================================================================================
 4. For bug reports/ suggestions/ user contribued code
================================================================================

 For bug reports/ suggestions/ user contribued code
 email to:  dsph@ti.com

================================================================================
 5. C models
================================================================================

 C models are provided for the following functions

 (1) fir()
 (2) acorr_raw()
 (3) acorr_bias()
 (4) acorr_unbias()
 (5) dlms()
 (6) iir5()
 (7) iir51()
 (8) iir4() 


================================================================================
 6. Installation Guide
================================================================================

 (1) The Windows Batch Files (.bat) provided are set up to build the C55_DSPLIB with different memory models:

 * Blt55x_r3.bat - small memory model
 * Blt55xh_r3.bat - huge memory model
 * Blt55xx_r3.bat - large memory model
 
 (2) Running the DSPLIB using Code Composer v5.2 or later:

 Each example has the configurations for both CCS v3.3 and CCS v5.2. 
 With the Code Composer Window open, import the desired example along with the project dsplib under the build directory.
 Every example is dependent on the library, so building any or all of the projects will call the dsplib project, and therefore, build the library.
 The default settings for the examples and the dsplib project are for the huge memory model. The settings can be changed on the configurations of each project.
 
================================================================================
 7. Benchmarks
================================================================================

Every function has been profiled for cycle count as well as code size in its respective .asm file.
The benchmark numbers and formulas have been tested, and they are accurate to 1% and/or 20 cycles.
To check cycle count, use the profiling clock provided by Code Composer Studio around the assembler instruction that calls the function. 
Profiling around the C function will lead to an average of 20-30 extra cycles used by C to call the function and return to the test code.
