/*******************************************************************************
* Title                 :   AsciiTools header
* Filename              :   AsciiTools.h
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
#ifndef UTILITIES_ASCIITOOLS_H_
#define UTILITIES_ASCIITOOLS_H_
/******************************************************************************
* Includes
*******************************************************************************/
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define LITTLEENDIAN 1

/******************************************************************************
* Macros
*******************************************************************************/
#define h2a(d) ((d>9)?(d+'A'-10):(d+'0'))

/******************************************************************************
* Function Prototypes
*******************************************************************************/
int hex2asc(void *npos, int digs, int mode, char *s);

#endif /* UTILITIES_ASCIITOOLS_H_ */
/*** End of File **************************************************************/
