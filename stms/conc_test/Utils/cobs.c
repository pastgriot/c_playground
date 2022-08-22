/******************************************************************************
* Includes
*******************************************************************************/
#include "cobs.h"
#include <stdint.h>
#include <stddef.h>

/******************************************************************************
* Function Definitions
*******************************************************************************/
/**
   @brief  StuffData byte stuffs "length" bytes of data
 * at the location pointed to by "ptr", writing
 * the output to the location pointed to by "dst".
   @param	ptr: pointer to a buff with data to encode.
   @param	length: size of the buff to be encoded, pointed by ptr.
   @param   dst: pointer to a buff that will hold the decoded data.
   @return Returns the length of the encoded data.
**/
size_t COBS_enCode(const uint8_t *ptr, size_t length, uint8_t *dst) {
    uint8_t code;
	const uint8_t *start = dst;
    const uint8_t *end = ptr + length;
    uint8_t *code_ptr;   // Where to insert the leading count

    StartBlock();
	while (ptr < end) {
        if (code != 0xFF) {
            uint8_t c = *ptr++;
            if (c != 0) {
				*dst++ = c;
				code++;
				continue;
			}
		}
		FinishBlock();
		StartBlock();
	}
	FinishBlock();
	return  dst - start;
}

/**
   @brief 	decodes "srcBuffLen" bytes of data at the location pointed to by "pSrcBuff", writing the
   			output to the location pointed to by "pDstBuff".
   @param	pSrcBuff: pointer to a buff with encode data.
   @param	srcBuffLen: size of the buff to be decoded, pointed by pSrcBuff.
   @param	pDstBuff: pointer to a buff that will hold the decoded data.
   @return	returns the srcBuffLen of the decoded data (which is guaranteed to be <= srcBuffLen).
 */
size_t COBS_deCode(const uint8_t *pSrcBuff, size_t srcBuffLen, uint8_t *pDstBuff) {
	const uint8_t *start = pDstBuff;
    const uint8_t   *end = pSrcBuff + srcBuffLen;
	uint8_t code = 0xFF;
    uint8_t copy = 0x00;

	for (; pSrcBuff < end; copy--) {
		if (copy != 0) {
			*pDstBuff++ = *pSrcBuff++;
		}
        else {
    		if (code != 0xFF) {
    			*pDstBuff++ = 0;
    		}
    		copy = code = *pSrcBuff++;
    		if (code == 0) {
    			break; /* Source length too long */
    		}
		}
	}
	return pDstBuff - start;
}
/*************** END OF FUNCTIONS ***************************************************************************/
