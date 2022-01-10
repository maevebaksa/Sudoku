#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "include/hpdf.h"
#include "generator/generator.cpp"
#include <math.h>

jmp_buf env;



//this is part of the required setup listed in the begining of every example piece of code, allowing
//for error checking capabilities
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

    //set our PDF object to be named pdf
    HPDF_Doc  pdf;
    //set our font to the variable, font
    HPDF_Font font;
    //set our page to the variable, page
    HPDF_Page page;

    //create a float for handling the width of the title element
    HPDF_REAL title_width;



    //create the const char that will hold the font data for the three individual fonts
    const char * calibri_bold;
    const char * calibri_italic;
    const char * calibri_regular;

    //setup a vector to hold the generated values from the generation code
    std::vector <int> filledPuzzle = {};
    std::vector <int> holePuzzle = {};


    //run the generator code
    generate();
    //save the return values
    filledPuzzle = generatedFilledInPuzzle();
    holePuzzle = generatedPuzzleWithHoles();


    //CREATE THE FIRST PDF WITHOUT THE SOLUTIONS

    //create a PDF object (using the given sample code to handle errors)
    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    //load the three fonts from the files in the font folder
    calibri_bold = HPDF_LoadTTFontFromFile (pdf, "fonts/Calibri_Bold_Italic.ttf", HPDF_TRUE);
    calibri_italic = HPDF_LoadTTFontFromFile (pdf, "fonts/Calibri_Italic.ttf", HPDF_TRUE);
    calibri_regular = HPDF_LoadTTFontFromFile (pdf, "fonts/Calibri_Regular.ttf", HPDF_TRUE);

    //select the first font
    font = HPDF_GetFont (pdf, calibri_bold, "CP1250");

    //create a new page on the pdf defined as a landscape letter
    page = HPDF_AddPage (pdf);
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);

    //start the first piece of text (aka, the title)

    //start text
    HPDF_Page_BeginText (page);
    //set to calibri bold 20
    HPDF_Page_SetFontAndSize (page, font, 20);
    //figure out the width of the title
    title_width = HPDF_Page_TextWidth (page, "Your Random Sudoku!");
    //move to the center of the page, as the corrdinate plane (0,0) as the bottom left and having it as inputs to a function with the page, x coord and y coord
    HPDF_Page_MoveTextPos (page, (HPDF_Page_GetWidth (page) - title_width) / 2, HPDF_Page_GetHeight(page) - 40);
    //print the text onto the piece of paper
    HPDF_Page_ShowText (page, "Your Random Sudoku!");
    //finish this piece of text
    HPDF_Page_EndText (page);



    //start by making the grid

    //know the page width and height, as understood before, we have to 
    cout << HPDF_Page_GetWidth(page) << endl;
    cout << HPDF_Page_GetHeight(page) << endl;

    //figure out how many spaces there are in the puzzle
    int lenOfFilledPuzzle;
    lenOfFilledPuzzle = filledPuzzle.size();

    //figure out what that means in terms of a sidelength
    int sideLengthOfFilledPuzzle;
    sideLengthOfFilledPuzzle = sqrt (lenOfFilledPuzzle);

    //figure out how many subdivisions there are
    int numOfSubdivisions;
    numOfSubdivisions = sqrt (sideLengthOfFilledPuzzle);

    cout << numOfSubdivisions << endl;
    cout << sideLengthOfFilledPuzzle << endl;
    cout << lenOfFilledPuzzle << endl;

    //knowing we want to make the title 20px as a standard, want a 20px buffer from the title and the wall, 80px of vertical space is lost.
    //now we are able to make the calculations for the gridlines. Vertical first. 
    //we use 1px for the thin lines, and 2px for the thick lines. We can calculate the total.

    int boxHeight;
    boxHeight = ((HPDF_Page_GetHeight(page) - 80 + (sideLengthOfFilledPuzzle + lenOfFilledPuzzle)) / sideLengthOfFilledPuzzle);
    std::cout << boxHeight << endl;

    



    //print out the vector source: https://www.tutorialspoint.com/how-to-print-out-the-contents-of-a-vector-in-cplusplus
    for(int i=0; i < filledPuzzle.size(); i++) std::cout << filledPuzzle.at(i) << ' ';
    std::cout << endl;
    for(int i=0; i < holePuzzle.size(); i++) std::cout << holePuzzle.at(i) << ' ';
    std::cout << endl;












    /* save the document to a file */
    HPDF_SaveToFile (pdf, "fname.pdf");

    /* clean up */
    HPDF_Free (pdf);



    return 0;

}