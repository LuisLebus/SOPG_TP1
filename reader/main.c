/*=====[Module Name]===========================================================
 * Copyright YYYY Author Compelte Name <author@mail.com>
 * All rights reserved.
 * License: license text or at least name and link
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Creation Date: YYYY/MM/DD
 */

/*=====[Inclusion of own header]=============================================*/
#include <stdbool.h>
#include <stdlib.h>

#include "reader.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/
int main(void)
{
  if( readerInit() == false )
    exit(1);

  return 0;
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/
