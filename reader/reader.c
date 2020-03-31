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
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "reader.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/
#define FIFO_NAME         "../myfifo"
#define BUFFER_SIZE       256

#define LOG_FILE_NAME     "Log.txt"
#define SIGN_FILE_NAME    "Sign.txt"

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/
bool readerInit(void)
{
    char inputBuffer[BUFFER_SIZE];
  	int32_t bytesRead, err;
    int32_t fd = -1;
    FILE* fp;

    /* Create named fifo. -1 means already exists so no action if already exists */
    if ( (err = mknod(FIFO_NAME, S_IFIFO | 0666, 0) ) < -1  )
    {
        printf("Error creating named fifo: %d\n", err);
        return false;
    }

    /* Open named fifo. Blocks until other process opens it */
  	printf("\nWaiting for writers...\n\n");
  	if ( (fd = open(FIFO_NAME, O_RDONLY) ) < 0 )
    {
        printf("Error opening named fifo file: %d\n", fd);
        return false;
    }

      /* open syscalls returned without error -> other process attached to named fifo */
  	printf("Got a writer...\n\n");

    /* Loop until read syscall returns a value <= 0 */
  	do
  	{
      memset(inputBuffer, 0, sizeof(inputBuffer));

      /* read data into local buffer */
  		if( ( bytesRead = read(fd, inputBuffer, BUFFER_SIZE) ) == -1 )
      {
        perror("read");
      }
      else
  		{
  			printf("reader: %s\n", inputBuffer);

        if( strncmp(inputBuffer, "DATA", 4) == 0)
        {
          fp = fopen (LOG_FILE_NAME, "a");

          if(fp != NULL)
          {
            fputs(inputBuffer, fp);
            fclose(fp);
          }
          else
          {
            printf("Error al abrir el archivo %s\n\n", LOG_FILE_NAME);
          }
        }
        else if( strncmp(inputBuffer, "SIGN", 4) == 0)
        {
          fp = fopen(SIGN_FILE_NAME, "a");

          if(fp != NULL)
          {
            fputs(inputBuffer, fp);
            fclose(fp);
          }
          else
          {
            printf("Error al abrir el archivo %s\n\n", SIGN_FILE_NAME);
          }
        }
        else
        {
          printf("Header invalido\n");
        }
  		}
  	}
  	while (bytesRead > 0);
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/
