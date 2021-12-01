#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"

const static char* text = "she no likey 😊";
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
    HPDF_Doc  pdf;
    HPDF_Font font;
    HPDF_Page page;
    HPDF_REAL tw;

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    /* create default-font */
    font = HPDF_GetFont (pdf, "Helvetica", NULL);

    /* add a new page object. */
    page = HPDF_AddPage (pdf);

    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);

    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 20);
    tw = HPDF_Page_TextWidth (page, text);
    HPDF_Page_MoveTextPos (page, (HPDF_Page_GetWidth (page) - tw) / 2,
                (HPDF_Page_GetHeight (page)  - 20) / 2);
    HPDF_Page_ShowText (page, text);
    HPDF_Page_EndText (page);

    //HPDF_SetPassword (pdf, owner_passwd, user_passwd);

    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;

}