/**********************************************************/
/*                                                        */
/*         LINKER command file for LEAD3 memory map       */
/*                                                        */
/**********************************************************/

-stack      0x1000   /* PRIMARY STACK SIZE    */
-sysstack   0x0400   /* SECONDARY STACK SIZE  */
-heap       0x1000   /* HEAP AREA SIZE        */  
 
MEMORY
{
    PAGE 0:

        MMR     : origin = 0000000h, length = 00000c0h 
        SPRAM   : origin = 00000c0h, length = 0000040
        DARAM0  : origin = 0000100h, length = 0003F00h
        DARAM1  : origin = 0004000h, length = 0004000h
        DARAM2  : origin = 0008000h, length = 0004000h
        DARAM3  : origin = 000c000h, length = 0004000h

        SARAM01 : origin = 0010000h, length = 0008000h
        SARAM2  : origin = 0018000h, length = 0004000h
        SARAM3  : origin = 001c000h, length = 0004000h
        SARAM4  : origin = 0020000h, length = 0004000h
        SARAM5  : origin = 0024000h, length = 0004000h
        SARAM6  : origin = 0028000h, length = 0004000h
        SARAM7  : origin = 002c000h, length = 0004000h
        SARAM8  : origin = 0030000h, length = 0004000h
        SARAM9  : origin = 0034000h, length = 0004000h
        SARAM10 : origin = 0038000h, length = 0004000h
        SARAM11 : origin = 003c000h, length = 0004000h
        SARAM12 : origin = 0040000h, length = 0004000h
        SARAM13 : origin = 0044000h, length = 0004000h
        SARAM14 : origin = 0048000h, length = 0004000h
        SARAM15 : origin = 004c000h, length = 0004000h

        CE0     : origin = 0050000h, length = 03b0000h 
        CE1     : origin = 0400000h, length = 0400000h
        CE2     : origin = 0800000h, length = 0400000h
        CE3     : origin = 0c00000h, length = 03f8000h

        PDROM   : origin = 0ff8000h, length = 07f00h
        VECS    : origin = 0ffff00h, length = 00100h  /* reset vector */
}	

 
SECTIONS
{
        vectors (NOLOAD) : {} > DARAM0  PAGE 0         /* interrupt vector table */ /* was VECS */
        .cinit   : {} > SARAM01 PAGE 0
        .text    : {} > SARAM01 PAGE 0
        isrs     : {} > SARAM2  PAGE 0

        .stack   : {} > DARAM0  PAGE 0 ALIGN = 4
        .sysstack: {} > DARAM0  PAGE 0 ALIGN = 4
        .sysmem  : {} > DARAM1  PAGE 0 ALIGN = 4
        .data    : {} > SARAM8  PAGE 0        /* force .data to not be on Page 0 */
        .bss:saram  : {} > DARAM2  PAGE 0     /* must be a different on-chip block than .bss */
        .bss:saram2 : {} > SARAM3  PAGE 0     /* must be a different on-chip block than .bss */
        //.bss     : {} > SARAM15 PAGE 0      /* for normal testing, move .bss off of DARAM */
        .bss     : {} > DARAM3  PAGE 0        /* for optimal timing tests, put .bss in DARAM */
        .input   : {} > DARAM3  PAGE 0        /* for optimal timing tests, put .input in DARAM */
        .coeffs  : {} > DARAM0  PAGE 0        /* for optimal timing tests, put .coeffs in DARAM */
        .dbuffer : {} > DARAM1  PAGE 0        /* for optimal timing tests, put .dbuffer in DARAM */
        .const   : {} > SARAM8  PAGE 0        
        .cio     : {} > DARAM2  PAGE 0
}