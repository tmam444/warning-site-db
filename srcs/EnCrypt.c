// EnCrypt.cpp : Defines the entry point for the DLL application.

#include "EnCrypt.h"
#include "MD5.h"
#include <memory.h>

md5_state_t g_state;

ENCRYPT_API void GetEncryptedMessage(const unsigned char* data,
 	int length,
         unsigned char result[16]) 
{
        md5_init(&g_state);
        md5_append(&g_state,data,length);
        md5_finish(&g_state,result);
}
ENCRYPT_API bool IsEqual(const unsigned char* data, /* string to compare. */
 int length,                            /* length of the string. */
 unsigned char encrypted[16]) /* encrypted string to compare. */
{
        unsigned char result[16];
        GetEncryptedMessage(data,length,result);
        if ( !memcmp( result,encrypted, 16) ) return true;
        else return false;
}
ENCRYPT_API void Init()
{
        md5_init(&g_state);
}
ENCRYPT_API void Append(const md5_byte_t* data, int len)
{
        md5_append(&g_state,data,len);
}
ENCRYPT_API void Finish(md5_byte_t data[])
{
        md5_finish(&g_state,data);
}
