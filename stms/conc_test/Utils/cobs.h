#ifndef INC_COBS_H_
#define INC_COBS_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>

/******************************************************************************
* Macros
*******************************************************************************/
#define StartBlock() (code_ptr = dst++, code = 1)
#define FinishBlock() (*code_ptr = code)

/******************************************************************************
* Function Prototypes
*******************************************************************************/
size_t COBS_enCode (const uint8_t *ptr, size_t length, uint8_t *dst);
size_t COBS_deCode (const uint8_t *ptr, size_t length, uint8_t *dst);

#endif /* INC_COBS_H_ */
/*** End of File **************************************************************/
