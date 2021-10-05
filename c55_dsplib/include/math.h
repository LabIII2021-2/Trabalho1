/********************************************************************************************
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************************************
*/

/***********************************************************/
/* Version 2.30.00                                         */
/***********************************************************/
#ifndef _MATH
#define _MATH

#if _INLINE
#define __INLINE static inline
#else
#define __INLINE
#endif

#define HUGE_VAL  3.40232347E+38F

/***************************************************************/
/* FUNCTION DECLARATIONS.                                      */
/***************************************************************/
         double asin(double _x);
         double acos(double _x);
         double atan(double _x);
         double atan2(double _y, double _x);
__INLINE double ceil(double _x);
         double cos(double _x);
         double cosh(double _x);
         double exp(double _x);
         double fabs(double _x);
__INLINE double floor(double _x);
__INLINE double fmod(double _x, double _y);
         double frexp(double _x, int *_exp);
         double ldexp(double _x, int _exp);
         double log(double _x);
         double log10(double _x);
         double modf(double _x, double *_iptr);
         double pow(double _x, double _y);
         double sin(double _x);
         double sinh(double _x);
         double sqrt(double _x);
         double tan(double _x);
         double tanh(double _x);

#if _INLINE
/****************************************************************************/
/*  ceil()       				                            */
/****************************************************************************/
static inline double ceil(double x)
{
     double y; 
     return (modf(x, &y) > 0 ? y + 1.0 : y);
}

/****************************************************************************/
/*  floor()      				                            */
/****************************************************************************/
static inline double floor(double x)
{
     double y; 
     return (modf(x, &y) < 0 ? y - 1.0 : y);
}

/****************************************************************************/
/*  fmod()       				                            */
/****************************************************************************/
static inline double fmod(double x, double y)
{
   double d = fabs(x); 

   if (d - fabs(y) == d) return (0.0);
   modf(x/y, &d);
   return (x - d * y);
}
#endif /* _INLINE */
#undef __INLINE

#endif /* _MATH   */
