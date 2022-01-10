    const static char* font_name = "";
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

    font_name = HPDF_LoadTTFontFromFile (pdf, "ComicSansMS3.ttf", HPDF_TRUE);
    font = HPDF_GetFont (pdf, font_name, "CP1250");

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
