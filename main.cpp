#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "include/hpdf.h"
#include "generator/generator.cpp"

const static char* text = "she no likey";
const static char* owner_passwd = "owner";
const static char* user_passwd = "user";
const static char* fname = "hi.pdf";

jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler  (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}


int main(int argc, char **argv){


    std::cout << generate;
}