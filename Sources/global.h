#ifndef GLOBAL_H_
#define GLOBAL_H_

/*
************************************************************************
*                         Include Files
************************************************************************
*/      

#include "PE_Types.h"					/* Data Type Definitions */
#include "io_map.h"
#include "MKL25Z4.h"

/*
************************************************************************
*                         Constant and Macros
************************************************************************
*/      

/* Boolean Type Definition */
typedef enum BOOL_STATES{
    bFalse = 0,
    bTrue,
}BOOLEAN;


/* Port A Definitions */
#define set_RS()      			( GPIOA_PSOR |= ( 1 << 1 ) )	
#define reset_RS()    			( GPIOA_PCOR |= ( 1 << 1 ) )	

#define set_READ()      		( GPIOA_PSOR |= ( 1 << 2 ) )	
#define set_WRITE()    			( GPIOA_PCOR |= ( 1 << 2 ) )	

#define set_EN()      			( GPIOA_PSOR |= ( 1 << 5 ) )	
#define reset_EN()    			( GPIOA_PCOR |= ( 1 << 5 ) )	

/* Port B Definitions */
#define set_DB(x)      			( GPIOB_PSOR |= ( 1 << x ) )	
#define reset_DB(x)   			( GPIOB_PCOR |= ( 1 << x ) )	

	
/*
************************************************************************
*                      Global Function Prototypes
************************************************************************
*/     

void initGPIOpins( void );									/* Initialize all General Purpose Input/Output (GPIO) pins */

#endif /* GLOBAL_H_ */

