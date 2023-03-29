// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ENCRYPT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ENCRYPT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef WIN32
#ifdef ENCRYPT_EXPORTS
#define ENCRYPT_API __declspec(dllexport)
#else
#define ENCRYPT_API __declspec(dllimport)
#endif
#else //UNIX,LINUX
#define ENCRYPT_API extern
#endif
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif
/*
* Function for encrypting message.
*/
ENCRYPT_API void GetEncryptedMessage(const unsigned char* mesg, /* string to encryption */
              int length,                           
 /* length of the string */

              unsigned char result[16]); /* digest to store */

/*
* Function for comparing raw message with encrypted message.
*/
ENCRYPT_API bool IsEqual(const unsigned char* data, /* string to compare. */
	int length,   /* length of the string. */
        unsigned char encrypted[16]); /* encrypted string to compare. */


ENCRYPT_API void Init(void);
ENCRYPT_API void Append(const unsigned char* data,int len);
ENCRYPT_API void Finish(unsigned char data[]);

#ifdef __cplusplus
}  /* end extern "C" */
#endif
