#include <iostream>
#include <string>
#include <cstdlib> //srand and rand are part of the c standard library
#include <vector> //the vector standard library
#include <time.h> //required for seeding the random function

//use all names in standard library
using namespace std;

  //a function that takes the parameters of a vector with values in order: 1234 and an empty vector to be filled with 1 of each value 1234 in a random order
  void randomizeRowOrColumn(vector<int>& whichVectorToRand, vector<int>& oneThroughFourVector) {
  //vectors passed as parameters have to be passed as reference so that the function's actions are reflected in the vectors in the main function (same citation as the top: https://www.geeksforgeeks.org/passing-vector-function-cpp/)
    int numForWhileLoop = 3;
    while (numForWhileLoop >= 0) {
      int numForWhileLoopPlus1 = numForWhileLoop + 1;
      if (numForWhileLoop == 0) {
       whichVectorToRand.push_back(oneThroughFourVector.at(0));
      } 
      else {
       int randValueInRange = rand() % numForWhileLoopPlus1;
       whichVectorToRand.push_back(oneThroughFourVector.at(randValueInRange));
       oneThroughFourVector.erase (oneThroughFourVector.begin()+randValueInRange);
      }

      numForWhileLoop--;
  }
  }

  void addAColumnToTotalVector(vector<int> columnVect, vector<int>& allValueVector, int columnNumber)
  //the column to be added to the total vector is passed as a parameter without being refrenced because this function doesn't change any of the values in the vector. The second parameter is a number 
  //the all value vector is passed by refrence because it is modifyed and not defined above this function in the code order.
  {
    int numForWhileLoop2 = 0;
    while (numForWhileLoop2 < 4) {
      if (numForWhileLoop2 == 0) {
        allValueVector.insert(allValueVector.begin()+columnNumber-1, columnVect.at(0));
        allValueVector.erase(allValueVector.begin()+columnNumber); 
      }
      else {
        int positionNum = columnNumber - 1 + 4*numForWhileLoop2;
        allValueVector.insert(allValueVector.begin()+positionNum, columnVect.at(numForWhileLoop2));
        allValueVector.erase(allValueVector.begin()+positionNum+1);
      }

      numForWhileLoop2++;
    }

  }

  void fillInColumn2(vector<int>& randCol2, vector<int> randCol1)
  //a function to randomly fill the second to left column with values that don't violate the rules of having one of each number: 1234 in each box and row
  {
    if (rand() % 2 == 0) { 
      randCol2.push_back(randCol1.at(2));
      randCol2.push_back(randCol1.at(3));
    }
    else {
      randCol2.push_back(randCol1.at(3));
      randCol2.push_back(randCol1.at(2));
    }

    if (rand() % 2 == 0) {
      randCol2.push_back(randCol1.at(0));
      randCol2.push_back(randCol1.at(1));
    }
    else {
      randCol2.push_back(randCol1.at(1));
      randCol2.push_back(randCol1.at(0));
    }
  }

  void fillInRemainingRows(vector<int> column1Vect, vector<int> column2Vect, vector<int>& allValueVector) 
  //a function to randomly fill in the remaining left half of every row while abiding the 1234 once per column, row, and box rules, and adding said values to the vector with all values
  //Ms. Garnier, I found a way to optimize this function by making another function for the insertion and deleting of values in the allValueVector, however it is complicated and very difficult to explain, so I am not including it.
  {
    int numForWhileLoop3 = 1;
    while (numForWhileLoop3 < 5) {
      int tempPosValue = (2*numForWhileLoop3)+(2*(numForWhileLoop3 - 1));
      if (numForWhileLoop3 % 2 == 0) {
        if (rand() % 2 == 0) {
          allValueVector.insert(allValueVector.begin()+ tempPosValue, column1Vect.at(numForWhileLoop3-2));
          allValueVector.erase(allValueVector.begin()+tempPosValue+1); 

          allValueVector.insert(allValueVector.begin()+ tempPosValue+1, column2Vect.at(numForWhileLoop3-2));
          allValueVector.erase(allValueVector.begin()+tempPosValue+2); 
        }
        else {
          allValueVector.insert(allValueVector.begin()+ tempPosValue, column2Vect.at(numForWhileLoop3-2));
          allValueVector.erase(allValueVector.begin()+tempPosValue+1); 

          allValueVector.insert(allValueVector.begin()+ tempPosValue+1, column1Vect.at(numForWhileLoop3-2));
          allValueVector.erase(allValueVector.begin()+tempPosValue+2); 
        }
      }
      
      else {
        if (rand() % 2 == 0) {
          allValueVector.insert(allValueVector.begin()+ tempPosValue, column1Vect.at(numForWhileLoop3));
          allValueVector.erase(allValueVector.begin()+tempPosValue+1); 

          allValueVector.insert(allValueVector.begin()+ tempPosValue+1, column2Vect.at(numForWhileLoop3));
          allValueVector.erase(allValueVector.begin()+tempPosValue+2); 
        }
        else {
          allValueVector.insert(allValueVector.begin()+ tempPosValue, column2Vect.at(numForWhileLoop3));
          allValueVector.erase(allValueVector.begin()+tempPosValue+1); 

          allValueVector.insert(allValueVector.begin()+ tempPosValue+1, column1Vect.at(numForWhileLoop3));
          allValueVector.erase(allValueVector.begin()+tempPosValue+2); 
        }
      }

      numForWhileLoop3++;
    }
  }

  void switchColumn3And4Values(vector<int>& allValueVector, int numPositionValue, int columnNum)
  //a function to switch the values in the same row from columns 3 to 4 and vice versa
  {
    if (columnNum == 4) {
      numPositionValue--;
    }
    allValueVector.insert(allValueVector.begin()+ numPositionValue, allValueVector.at(numPositionValue+1));
    allValueVector.erase(allValueVector.begin()+numPositionValue+2); 
  }

  void correctTheBottomHalfOfColsThreeAndFour( vector<int>& allValueVector, int columnNumber)
  //a function to swicth the bottom half values of columns three and four such that they don't violate the 1234 once per column rule
  {
    int numForWhileLoop4 = 0;
    while (numForWhileLoop4 < 4) {
      int numPositionValue = (columnNumber-1) + (4*numForWhileLoop4);
      for (int tempNum = 0; tempNum < 4; tempNum++) {
        int tempNumPosInTotalVector = (columnNumber-1) + (4*tempNum);
        if (tempNumPosInTotalVector != numPositionValue && allValueVector.at(numPositionValue) == allValueVector.at(tempNumPosInTotalVector)){
          switchColumn3And4Values(allValueVector, numPositionValue,columnNumber);
        }
      } 

      numForWhileLoop4++;
    }
  }

  void takeOutElevenRandomValues(vector<int>& allValueVector, int difficultyLevel) 
  //a function to remove 11 random values from the entire puzzle vector
  {
    vector<int> tempVector; 
    for(int tempNum1 = 0; tempNum1 < 16; tempNum1++) {
      tempVector.push_back(tempNum1);
    } 

    int numForWhileLoop5 = 0;
    while (numForWhileLoop5 < difficultyLevel) {
      int randValueInRange = rand() % tempVector.size();

      allValueVector.insert(allValueVector.begin()+tempVector.at(randValueInRange), 0); 
      allValueVector.erase(allValueVector.begin()+tempVector.at(randValueInRange)+1); 

      tempVector.erase(tempVector.begin()+ randValueInRange); 

      numForWhileLoop5++;
    }
  }

  void askDifficultyAndGenerateHoles(vector<int>& allValueVector)
  //a function that takes in an input from the user that determines the difficulty of the puzzle by how many holes are generated
  {
    cout << "Welcome to the Sudoku Puzzle Generator! What difficulty would you like your puzzle, easy, medium, or hard?" << endl;
    int tempValue2 = 0;
    while (tempValue2 == 0) {
      string userInput;
      cin >> userInput;
      if (userInput == "easy") {
        takeOutElevenRandomValues(allValueVector,4);
        tempValue2 = 1;
      }
      else if (userInput == "medium") {
        takeOutElevenRandomValues(allValueVector,7);
        tempValue2 = 1;
      }
      else if (userInput == "hard") {
        takeOutElevenRandomValues(allValueVector,11);
        tempValue2 = 1;
      }
      else {
        cout << "That is not a difficulty, please select easy, medium, or hard" << endl;
      }
    }
  }

  vector<int> generatedFilledInPuzzle(vector<int>& allValuesFilledInVector)
  //a function who's value is the vector that contains the filled in puzzle
  {
    return allValuesFilledInVector;
  }

  vector<int> generatedPuzzleWithHoles(vector<int>& puzzleWithHolesVector)
  //a function who's value is the vector that contains the puzzle with the holes
  {
    return puzzleWithHolesVector;
  }

int generate() {
//main function

  srand(time(0));
  //Seed the random function using 0 as the time such that multiple random numbers can be gennerated in the code

  vector<int> allValueVector(16,0);
  //filling a vector with 16 positions defined as 0
  //top row from position 0 to 3, second to top 4 to 7, third from top 8 to 11, bottom from 12 to 15

  //values in the same column occur every 4 values
  //leftmost column 0,4,8,12 second to leftmost 1,5,9,13, third to leftmost 2,6,10,14

  vector<int> oneThroughFourValues1 {1,2,3,4};
  //generating a vector with 4 defined values, 1-4

  vector<int> randCol1; 
  //defining an empty vector

  randomizeRowOrColumn(randCol1, oneThroughFourValues1);
  //filling the vector for the first/leftmost column randomly with values 1234

  addAColumnToTotalVector(randCol1, allValueVector, 1);
  //adding the values from the first column to the vector with all values in the puzzle

  vector<int> randCol2; 
  //defining an empty vector

  fillInColumn2(randCol2, randCol1);
  //filling the vector for the second column with values 1234 that don't violate the rules of having one of each number 1234 per row and box

  addAColumnToTotalVector(randCol2, allValueVector, 2);
  //adding the values from the second column to the vector with all values in the puzzle

  fillInRemainingRows(randCol1, randCol2, allValueVector);

  correctTheBottomHalfOfColsThreeAndFour(allValueVector,3);
  correctTheBottomHalfOfColsThreeAndFour(allValueVector,4);

  vector<int> allValuesFilledInVector = allValueVector;

  askDifficultyAndGenerateHoles(allValueVector);

  vector<int> puzzleWithHolesVector = allValueVector;

 return 0;
 //finish the function by returning its value to 0
}

int main(){
  generate();
  generatedFilledInPuzzle();
  generatedPuzzleWithHoles();
}