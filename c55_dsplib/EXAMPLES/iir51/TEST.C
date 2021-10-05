/*
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
 *
*/

//*****************************************************************************
//  Filename:	 test.c
//  Version:	 0.01
//  Description: test r against rtest (array of n elements)
//		 Returns eflag
//-----------------------------------------------------------------------------
//  Revision History:	 
//    0.01, R. Piedra, 06/15/98, - Original release
//*****************************************************************************
#include <tms320.h>

short test(DATA *r, DATA *rtest, short n, DATA maxerror)
{
    short i;
    short eflag = PASS;		// error flag or index into r vector where error
    DATA elevel = 0;		// error level at failing eflag index location
    DATA emax = 0;			// max error level detected across when NOERROR

    for (i=0;i<n;i++)
    {
        if ( (elevel = ABSVAL(rtest[i] - r[i])) > maxerror)
        {
           eflag =i;	// if error --> eflag = index and emax= max error
           emax = elevel;	// if no error --> eflag = -1 and emax = max error
           break;
        }
        else
        if (elevel>emax) emax = elevel;
    }
			// Pass to Host: eflag and emax
    return(eflag);
}
