#pragma once

#if defined (__cplusplus)
extern "C" {
#endif

/**************************************
   Version
**************************************/
#define LZ4_VERSION_MAJOR    1
#define LZ4_VERSION_MINOR    1
#define LZ4_VERSION_RELEASE  3
/**************************************
   Compiler Options
**************************************/
#if (defined(__GNUC__) && defined(__STRICT_ANSI__)) || (defined(_MSC_VER) && !defined(__cplusplus))   /* Visual Studio */
#  define inline __inline
#endif
/**************************************
   Simple Functions
**************************************/
int LZ4_compress        (const char* source, char* dest, int inputSize);
int LZ4_decompress_safe (const char* source, char* dest, int inputSize, int maxOutputSize);
/**************************************
   Advanced Functions
**************************************/
#define LZ4_MAX_INPUT_SIZE        0x7E000000   /* 2 113 929 216 bytes */
#define LZ4_COMPRESSBOUND(isize)  ((unsigned int)(isize) > (unsigned int)LZ4_MAX_INPUT_SIZE ? 0 : (isize) + ((isize)/255) + 16)

int LZ4_compressBound(int isize);
int LZ4_compress_limitedOutput (const char* source, char* dest, int inputSize, int maxOutputSize);
int LZ4_decompress_fast (const char* source, char* dest, int originalSize);
int LZ4_decompress_safe_partial (const char* source, char* dest, int inputSize, int targetOutputSize, int maxOutputSize);
int LZ4_sizeofState(void);
int LZ4_compress_withState               (void* state, const char* source, char* dest, int inputSize);
int LZ4_compress_limitedOutput_withState (void* state, const char* source, char* dest, int inputSize, int maxOutputSize);

/**************************************
   Streaming Functions
**************************************/
void* LZ4_create (const char* inputBuffer);
int   LZ4_compress_continue (void* LZ4_Data, const char* source, char* dest, int inputSize);
int   LZ4_compress_limitedOutput_continue (void* LZ4_Data, const char* source, char* dest, int inputSize, int maxOutputSize);
char* LZ4_slideInputBuffer (void* LZ4_Data);
int   LZ4_free (void* LZ4_Data);
int LZ4_sizeofStreamState(void);
int LZ4_resetStreamState(void* state, const char* inputBuffer);
int LZ4_decompress_safe_withPrefix64k (const char* source, char* dest, int inputSize, int maxOutputSize);
int LZ4_decompress_fast_withPrefix64k (const char* source, char* dest, int outputSize);
int LZ4_uncompress (const char* source, char* dest, int outputSize);
int LZ4_uncompress_unknownOutputSize (const char* source, char* dest, int isize, int maxOutputSize);


#if defined (__cplusplus)
}
#endif
