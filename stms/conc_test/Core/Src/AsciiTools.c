/*******************************************************************************
* Title                 :   AsciiTools
* Filename              :   AsciiTools.c
* Author                :   Marco Casado
* Origin Date           :   04/06/2021
* Version               :   1.0.0
* Compiler              :   ARM GCC
* Target                :   STM32F7
* Notes                 :   None
*
* THIS SOFTWARE IS PROVIDED BY RBA ENGINEERING "AS IS" AND ANY EXPRESSED
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL RBA ENGINEERING OR ITS CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author         Description
*  09/06/21   1.0.0   Marco Casado   Initial Release.
*  10/06/21   1.0.0   Marco Casado   Refactoring and formatting.
*******************************************************************************/
/** @file TODO: MODULE.c
 *  @brief This is the source file for TODO: WHAT DO I DO?
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "AsciiTools.h"
#include <string.h>

/******************************************************************************
* Function Definitions
*******************************************************************************/
/**
  * @brief convert hex value to ascii representation
  * @param npos: pointer to the hex value to convert
  * @param digs: number of bits to be converted
  * @param mode: padding zeroes
  * @retval *s pointer to output ascii representation buff
  */
int hex2asc(void *npos, int digs, int mode, char *s)
{
	int i,zero;
	char dig;
	char *spos=s;
	char *n=(char *)npos;

	zero=1;
#if LITTLEENDIAN
	n+=(digs-1)>>1;
#else
	n+=(16-digs)>>1;
#endif
	for (i=digs-1;i>=0;--i) {
		if (i&1) {
			dig=(*(char *)n>>4)&15;
		} else {
			dig=*(char *)n&15;
#if LITTLEENDIAN
			--n;
#else
			++n;
#endif
		}
		if (zero&&dig)
			zero=0;
		if (zero) {
			switch(mode) {
			case 1:
				*spos++=' ';
				break;
			case 2:
				*spos++='0';
				break;
			default:
				break;
			}
		} else
			*spos++=h2a(dig);
	}
	if (zero&&mode==1)
		*(spos-1)='0';
	else if (zero&&mode==0)
		*spos++='0';
	*spos=0;
	return spos-s;
}
/*************** END OF FUNCTIONS ***************************************************************************/
