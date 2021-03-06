#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "include/hpdf.h"
#include "generator/generator.cpp"
#include <math.h>
#include <time.h>
#include <ctime>

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


int make_pdf(std::vector<int> valueVector, int lineWidth, int fontSize, int numberBuffer, const char * fileName){
//SETUP VARIABLES

    //set our PDF object to be named pdf
    HPDF_Doc  pdf;
    //set our font to the variable, font
    HPDF_Font font;
    //set our page to the variable, page
    HPDF_Page page;

    //create a float for handling the width of the title element
    HPDF_REAL titleWidth;

    //create a const char * for holding the number data
   

    //the buffer is to make sure that everything looks neat and correct, and is 4 times the font size
    int buffer = (fontSize * 4);


    //create the const char that will hold the font data for the three individual fonts
    const char * calibri_bold;
    const char * calibri_italic;
    const char * calibri_regular;
   
//CREATE PDF

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
    HPDF_Page_SetFontAndSize (page, font, fontSize);
    //figure out the width of the title
    titleWidth = HPDF_Page_TextWidth (page, "Your Random Sudoku!");
    //move to the center of the page, as the corrdinate plane (0,0) as the bottom left and having it as inputs to a function with the page, x coord and y coord
    HPDF_Page_MoveTextPos (page, (HPDF_Page_GetWidth (page) - titleWidth) / 2, HPDF_Page_GetHeight(page) - buffer/2);
    //print the text onto the piece of paper
    HPDF_Page_ShowText (page, "Your Random Sudoku!");
    //finish this piece of text
    HPDF_Page_EndText (page);



    //start by making the grid
    //know the page width and height, as understood before, we have to 
    //cout << HPDF_Page_GetWidth(page) << endl;
    //cout << HPDF_Page_GetHeight(page) << endl;

    //figure out how many spaces there are in the puzzle
    int lenOfFilledPuzzle;
    lenOfFilledPuzzle = valueVector.size();

    //figure out what that means in terms of a sidelength
    int sideLengthOfFilledPuzzle;
    sideLengthOfFilledPuzzle = sqrt (lenOfFilledPuzzle);

    //figure out how many subdivisions there are
    int numOfSubdivisions;
    numOfSubdivisions = sqrt (sideLengthOfFilledPuzzle);

    //cout << numOfSubdivisions << endl;
    //cout << sideLengthOfFilledPuzzle << endl;
    //cout << lenOfFilledPuzzle << endl;

    //calculate what the box height will be, which is the total page height, then minus the buffer, 
    //the total widths of the lines divided by the number of boxes on one side 

    int boxHeight;
    boxHeight = ((HPDF_Page_GetHeight(page) - buffer - lineWidth*(sideLengthOfFilledPuzzle + numOfSubdivisions -1)) / sideLengthOfFilledPuzzle);
    //std::cout << boxHeight << endl;

    //set line widths
    HPDF_Page_SetLineWidth (page, lineWidth);

    //first vertical
    //set the first of the y positions 
    int ypos = (buffer/4);
    //set the first of the x positions
    // for the xposition, calculate the width of the page, subtract the width of the rectangle, (getHeight-buffer) then center by div 2
    int xpos = ((HPDF_Page_GetWidth(page) - (HPDF_Page_GetHeight(page) - buffer)) / 2);
    //run it the amount of times as there are squares of the puzzle (4 for a 4x4)
    for(int i=0; i <= sideLengthOfFilledPuzzle; i++){
        //move to start point
        HPDF_Page_MoveTo (page, xpos, ypos);
        //draw line, accounting for the the thickness of the lines
        HPDF_Page_LineTo (page, xpos, (ypos + (HPDF_Page_GetHeight(page) - buffer - lineWidth*(numOfSubdivisions+2))));
        //draw it
        HPDF_Page_Stroke (page);
        //move by the previously calculated box height
        xpos = xpos + boxHeight;
    };

    //thicken the verical lines
    //reset parameters
    ypos = (buffer/4);
    xpos = ((HPDF_Page_GetWidth(page) - (HPDF_Page_GetHeight(page) - buffer)) / 2);
    
    for(int i=0; i <= numOfSubdivisions; i++){
        //same except have the +lineWidth to offset slightly
        HPDF_Page_MoveTo (page, xpos+lineWidth, ypos);
        HPDF_Page_LineTo (page, xpos+lineWidth, (ypos + (HPDF_Page_GetHeight(page) - buffer - lineWidth*(numOfSubdivisions+2))));
        HPDF_Page_Stroke (page);
        //same except, move by boxes / subdivisions * box height (aka 3 for 9x9, 2 for 2x2)
        xpos = xpos + (sideLengthOfFilledPuzzle/numOfSubdivisions)*(boxHeight);
    };

    //reset and repeat for the first horizontal
    ypos = (buffer/4);
    xpos = ((HPDF_Page_GetWidth(page) - (HPDF_Page_GetHeight(page) - buffer)) / 2);
    for(int i=0; i <= sideLengthOfFilledPuzzle; i++){
        HPDF_Page_MoveTo (page, xpos, ypos);
        HPDF_Page_LineTo (page, (xpos + (HPDF_Page_GetHeight(page) - buffer - lineWidth*(numOfSubdivisions+2))), ypos);
        HPDF_Page_Stroke (page);
        ypos = ypos + boxHeight;
    };

    //thick horizontal
    ypos = (buffer/4);
    xpos = ((HPDF_Page_GetWidth(page) - (HPDF_Page_GetHeight(page) - buffer)) / 2);
    for(int i=0; i <= sideLengthOfFilledPuzzle; i++){
        HPDF_Page_MoveTo (page, xpos, ypos + lineWidth);
        HPDF_Page_LineTo (page, (xpos + (HPDF_Page_GetHeight(page) - buffer - lineWidth*(numOfSubdivisions+2))), ypos + lineWidth);
        HPDF_Page_Stroke (page);
        ypos = ypos + (sideLengthOfFilledPuzzle/numOfSubdivisions)*(boxHeight);
    };

    //cout << "lines drawn" << endl;
    //add text

    //reset our x and y positions back to the start (plus linewidth this time, and numberBuffer)
    ypos = ((buffer/4) + numberBuffer + lineWidth);
    xpos = (((HPDF_Page_GetWidth(page) - (HPDF_Page_GetHeight(page) - buffer)) / 2) + numberBuffer);

    //save another copy for later usage (this is probably able to be done with pointers or something)
    int yposOriginal = ((buffer/4) + numberBuffer + lineWidth);
    int xposOriginal = ((HPDF_Page_GetWidth(page) - (HPDF_Page_GetHeight(page) - buffer)) / 2);

    //start another counter to see when we're done with a column
    int columnValue = 0;

    //create another variable for storing the width of the number
    int numberWidth=0;

    //create the number variable
    const char * number;

    for(int i=0; i < lenOfFilledPuzzle; i++){
        
        if (valueVector.at(i) == 0){
            //this is just if the hole is meant to be blank
        }
        else{
            //typecast int to char source: https://www.codegrepper.com/code-examples/cpp/c%2B%2B+convert+int+to+const+char%2A
            std::string s = std::to_string(valueVector.at(i));
            const char * number = s.c_str();
            //set font
            font = HPDF_GetFont (pdf, calibri_regular, "CP1250");
            //start text
            HPDF_Page_BeginText (page);
            //set to calibri regular and font size is box height minus buffer
            HPDF_Page_SetFontAndSize (page, font, (boxHeight - numberBuffer*2));
            //figure out the width of the number
            numberWidth = HPDF_Page_TextWidth (page, number);
            //move text to center of box by moving it to half of the total box height (incorpeating buffer)
            // then moving it back by half the value of the number, also move the y position by 2x number buffer
            HPDF_Page_MoveTextPos (page, xpos + ((boxHeight-2*numberBuffer)/2) - (numberWidth/2), ypos + 2* numberBuffer);
            //print the text onto the piece of paper
            HPDF_Page_ShowText (page, number);
            //finish this piece of text
            HPDF_Page_EndText (page);
        }

        //now figure out where the next move should be, either just movement in Y, or in X also
        //if you're not at the end of the column yet, only move up by box height 
        if (columnValue < sideLengthOfFilledPuzzle -1){
            ypos = ypos + boxHeight;
            columnValue ++;
        }
        //if you're at the end of the y axis, move both x and y
        else{
            ypos = yposOriginal;
            xpos = xpos + boxHeight;
            columnValue = 0;
        }
    }

    //save the pdf
    HPDF_SaveToFile (pdf, fileName);

    //clean the pdf and make the object for reuse
    HPDF_Free (pdf);

    return 0;
}

int main(int argc, char **argv){


    //setup a vector to hold the generated values from the generation code
    std::vector <int> filledPuzzle = {};
    std::vector <int> holePuzzle = {};
    std::vector <int> hintPuzzle = {};

    //create linewidth and fontsize variables
    int fontSize;
    int lineWidth;

    //ask questions to determine the fontSize and lineWidth, if the user doesn't input the correct values, 
    //it will continually ask, ergo, make sure you actually listen to the computer :>
    cout << "Here's some questions for the generation of the PDF's formatting before the generator is complete! \n" << "What would you like your fontsize, in px? (must be nonzero and less than 40, typically 20.): ";
    cin >> fontSize;

    cout << "What would you like the line width for the seperator lines? (must be nonzero and less than 10, typically 4.): ";
    cin >> lineWidth; 

    while (lineWidth <= 0 || lineWidth >= 10 || fontSize <= 0 || fontSize >= 40){
        cout << "Sorry, that's not valid. \n";
        cout << "Here's some questions for the generation of the PDF! \n" << "What would you like your fontsize, in px? (must be nonzero and less than 40, typically 20.): ";
        cin >> fontSize;
        cout << "What would you like the line width for the seperator lines? (must be nonzero and less than 10, typically 4.): ";
        cin >> lineWidth;
    }

    //ask if you'd like hint pdfs and make sure input is valid
    int enableHints;
    cout << "Would you like to generate a hint PDF? (1 for Yes, 0 for No): ";
    cin >> enableHints;

    while (enableHints != 0 && enableHints != 1){
        cout << "Sorry, that's not valid. \nWould you like to generate a hint PDF? (1 for Yes, 0 for No): ";
        cin >> enableHints;
    }

    //ask how many you'd like and save to pdfsToGenerate
    int pdfsToGenerate;
    cout << "How many PDF's Would you like to generate (please input a non zero number): ";
    cin >> pdfsToGenerate;

    //for loop for generating pdfs
    for (int i=0; i < pdfsToGenerate; i++){

        //run the generator code
        generate();
        
        //save the return values
        filledPuzzle = generatedFilledInPuzzle();
        holePuzzle = generatedPuzzleWithHoles();

        //uncomment the following 2 lines if you would like to create an example 9x9.
        //filledPuzzle = {1,2,6,4,3,7,9,5,8,8,9,5,6,2,1,4,7,3,3,7,4,9,8,5,1,2,6,4,5,7,1,9,3,8,6,2,9,8,3,2,4,6,5,1,7,6,1,2,5,7,8,3,9,4,2,6,9,3,1,4,7,8,5,5,4,8,7,6,9,2,3,1,7,3,1,8,5,2,6,4,9};
        //holePuzzle = {1,0,6,4,3,7,9,5,8,8,9,5,0,2,1,4,7,0,3,0,0,9,0,5,1,2,6,4,5,7,1,9,0,8,6,0,9,0,8,2,0,6,5,0,7,0,1,2,0,7,8,3,9,4,2,6,9,3,0,4,0,0,5,0,4,8,7,6,0,2,3,1,7,3,1,8,5,2,6,0,9};
        
        //create a string out off the i value
        std::string iString = std::to_string(i+1);

        //build up the individual string values, for the base and answer ones
        std::string filledName = "sudokuanswers";
        filledName = filledName +"_" + iString + ".pdf";
        const char * filledNameChar = filledName.c_str();

        std::string puzzleName = "sudoku";
        puzzleName = puzzleName +"_" + iString + ".pdf";
        const char * puzzleNameChar = puzzleName.c_str();

        //call make pdf function, with all important parameters
        make_pdf(filledPuzzle,lineWidth,fontSize,5,filledNameChar);
        make_pdf(holePuzzle,lineWidth,fontSize,5,puzzleNameChar);

        //print out the generated pdf to terminal, for answer, and puzzle
        cout << "Answer " << iString << endl;
        //print out the vector source: https://www.tutorialspoint.com/how-to-print-out-the-contents-of-a-vector-in-cplusplus
        for(int i=0; i < filledPuzzle.size(); i++) std::cout << filledPuzzle.at(i) << ' ';
        std::cout << endl;

        cout << "Puzzle " << iString << endl;
        for(int i=0; i < holePuzzle.size(); i++) std::cout << holePuzzle.at(i) << ' ';
        std::cout << endl;


        //if hints are enabled, repeat the above code for the hints, setting the name of the file, making pdf, and printing.
        if(enableHints == 1){
            std::string hintName = "sudokuhint";
            hintName = hintName +"_" + iString + ".pdf";
            const char * hintNameChar = hintName.c_str();


            hintPuzzle = giveAHint();
            make_pdf(hintPuzzle,lineWidth,fontSize,5,hintNameChar);

            cout << "Hint " << iString << endl;
            for(int i=0; i < hintPuzzle.size(); i++) std::cout << holePuzzle.at(i) << ' ';
            std::cout << endl;
        }
    }
    return 0;
}