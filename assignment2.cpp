#include <iostream>
using namespace std;
#include <cstring>
#include <cmath>

const int MAX_SIZE = 12;
const int LINE_SIZE = 64;
const char Liar = 'L';
const char Truth_Teller = 'T';

// Function to identify the solution and check if each person sees one liar                         
void classifySolution(char grid[MAX_SIZE][MAX_SIZE], int size);
bool isTrivialSolution(char grid[MAX_SIZE][MAX_SIZE], int size);
bool isLineSolution(char grid[MAX_SIZE][MAX_SIZE], int size);
bool hasAdjacentL(char grid[MAX_SIZE][MAX_SIZE], int size);
bool isIrregularSolution(char grid[MAX_SIZE][MAX_SIZE], int size);
void displayGrid(char grid[MAX_SIZE][MAX_SIZE], int size);

int main() {
  // Read the grid from the input file                                                              
  int numRows = 0;
  int numColumns = -1;
  char grid[MAX_SIZE][MAX_SIZE];

  while (!cin.eof() && numRows < MAX_SIZE) {
    char line[LINE_SIZE];
    cin.getline(line, sizeof(line)); //Read a line of input from cin into the 'line' array          
    if (line[0] == '\0') {
      continue; //Skip empty lines                                                                  
    }
    int linelength = 0; //Initialize length of current line                                         
    for (int i = 0; line[i] != '\0'; i++) {
      char character = line[i];
      if (character == Truth_Teller || character == Liar) { //Check if character is 'L' or 'T'      
        grid[numRows][linelength] = character;
        linelength++;
      } else if (character != ' ' && character != 'T' && character != 'L') { //Report invalid char  
        cout << "Invalid Character: " << character << endl;
        return 1; //Exit with error code                                                            
      }
    }
    if (numColumns == -1) {
      numColumns = linelength;
    }else if (linelength != numColumns) { //Check if current line has same number of columns        
      cout << "Not a square grid" << endl;
      return 1; //Exit with error code                                                              
    }
    numRows++; //Increment the row count                                                            
  }
// Read the grid from the input file                                                              
  int numRows = 0;
  int numColumns = -1;
  char grid[MAX_SIZE][MAX_SIZE];

  while (!cin.eof() && numRows < MAX_SIZE) {
    char line[LINE_SIZE];
    cin.getline(line, sizeof(line)); //Read a line of input from cin into the 'line' array          
    if (line[0] == '\0') {
      continue; //Skip empty lines                                                                  
    }
    int linelength = 0; //Initialize length of current line                                         
    for (int i = 0; line[i] != '\0'; i++) {
      char character = line[i];
      if (character == Truth_Teller || character == Liar) { //Check if character is 'L' or 'T'      
        grid[numRows][linelength] = character;
        linelength++;
      } else if (character != ' ' && character != 'T' && character != 'L') { //Report invalid char  
        cout << "Invalid Character: " << character << endl;
        return 1; //Exit with error code                                                            
      }
    }
    if (numColumns == -1) {
      numColumns = linelength;
    }else if (linelength != numColumns) { //Check if current line has same number of columns        
      cout << "Not a square grid" << endl;
      return 1; //Exit with error code                                                              
    }
    numRows++; //Increment the row count                                                            
  }
  //Check if the grid is a square grid by ensuring their is a = nunber of columns and rows          
  displayGrid(grid, numRows);
  if (numRows != numColumns) {
    cout << "Not a square grid" << endl;
    return 1; //Exit with error code                                                                
  }
  int size = numRows;
  classifySolution(grid, size); //Call classify solution function to analyze grid                   

  return 0;
}

// Function implementations here                                                                    
//Function to display the contents of the grid                                                      
void displayGrid(char grid[MAX_SIZE][MAX_SIZE], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      //Output character at position (i,j) folloed by a space                                      \
                                                                                                   \
                                                                                                    
      cout << grid[i][j] << " ";
    }
    cout << endl; //Move to next line to represent new row in the grid                             \
                                                                                                   \
                                                                                                    
  }
}
//Function to check if any character has adjacent 'L' character or else return false                
bool hasAdjacentL(char grid[MAX_SIZE][MAX_SIZE], int size) {
 //Define the possible directions to check for the adjacent points                                            
int directions[4][2] = {{0, 1}, {0,-1}, {1,0}, {-1,0}};

  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if (grid[row][col] == Truth_Teller || grid[row][col] == Liar) {
        int adjacentL = 0;
        //Check adjacent positions in all directions                                                
        for (int i = 0; i < 4; i++) {
          int newRow = row + directions[i][0];
          int newCol = col + directions[i][1];
          //Ensure the new position is within the grid                                              
          if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size && grid[newRow][newCol]
              == Liar) {
            adjacentL++;
          }
        }
        //If no adjacent found return false                                                         
        if (adjacentL == 0) {
          return false;
        }
      }
    }
  }
  //If all characters in the grid have atleast one adjacent return true                             
  return true;
}
//Function to check if the grid represents a trivial solution                                       
bool isTrivialSolution(char grid[MAX_SIZE][MAX_SIZE], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (grid[i][j] != Liar) {
        return false; //If any point is not a liar, it is not a trivial solution                    
      }
    }
  }
  return true; // trivial solution if all points are liars                                          
}
//Function to check if the grid represents a line solution                                          
bool isLineSolution(char grid[MAX_SIZE][MAX_SIZE], int size) {
  bool lineflag = true;//Initialize a flag for the line solution check                              

  //Check Rows                                                                                      
  for (int i = 0; i < size; i++) {
    bool hasTruthTeller = false;
    bool hasLiar = false;
    //Check each character in the current tow                                                       
    for (int j = 0; j < size; j++) {
      if (grid[i][j] == Truth_Teller) {
        hasTruthTeller = true;
      }
      if (grid[i][j] == Liar) {
        hasLiar = true;
      }
      //If both T and L are found in the same row it is not a line solution                         
      if (hasTruthTeller && hasLiar) {
        lineflag = false;
        break;
      }
    }
  }
  //If flag is true it is true based or the rows                                                    
  if (lineflag) {
    return true;
  }
  lineflag = true;

  //Check columns                                                                                   
  for (int j = 0; j < size; j++) {
    bool hasTruthTeller = false;
    bool hasLiar = false;
    //Check each character in the column                                                            
    for (int i = 0; i < size; i++) {
      if (grid[i][j] == Truth_Teller) {
        hasTruthTeller = true;
      }
      if (grid[i][j] == Liar) {
        hasLiar = true;
      }
       //If both T and L are found in the same row it is not a line solution                        
      if (hasTruthTeller && hasLiar) {
        lineflag = false;
        break;
      }
    }
  }
  //Return the line flag which indicates a Line solution based on if the columns are true           
  return lineflag;
}
//Checks if is a irregular solution                                                                 
bool isIrregularSolution(char grid[MAX_SIZE][MAX_SIZE], int size) {
  if (!isTrivialSolution(grid, size) && !isLineSolution(grid, size)) {
    // It's not a trivial or line solution, so it could be irregular.                               
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        // Check if the current person is a liar                                                    
        if (grid[i][j] == Liar) {
          // Check if the liar has an adjacent liar                                                 
          if (!hasAdjacentL(grid, size)) {
            // If not, return false, it's not an irregular solution                                 
            return false;
          }
        }
      }
    }
    // If no violation found, it's an irregular solution                                            
    return true;
  }
  return false; // Not an irregular solution                                                        
}
//Classifies the solution                                                                           
void classifySolution(char grid[MAX_SIZE][MAX_SIZE], int size) {
  if (isLineSolution(grid,size) && hasAdjacentL (grid,size)) {
    cout << "Line Solution" << endl;
  } else if (isTrivialSolution(grid,size)) {
    cout << "Trivial solution" << endl;
  } else if (isIrregularSolution(grid, size)) {
    cout << "Irregular Solution" << endl;
  } else {
    cout << "Not a solution" << endl;
    // Print the people who violated the solution                                                   
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (grid[i][j] == 'T') {
          int adjacentLiars = 0;

          // Check adjacent positions for 'L'                                                       
          if (i > 0 && grid[i - 1][j] == 'L') {
            adjacentLiars++;
          }
          if (i < size - 1 && grid[i + 1][j] == 'L') {
            adjacentLiars++;
          }
          if (j > 0 && grid[i][j - 1] == 'L') {
            adjacentLiars++;
          }
          if (j < size - 1 && grid[i][j + 1] == 'L') {
            adjacentLiars++;
          }
          //Prints information about truth tellers                                                  
          cout << "T at [" << i+1 << ", " << j+1 << "] sees " << adjacentLiars << " liars" << endl;
        } else if (grid[i][j] == 'L') {
          int adjacentLiars = 0;

          // Check adjacent positions for 'L'                                                       
          if (i > 0 && grid[i - 1][j] == 'L') {
            adjacentLiars++;
          }
          if (i < size - 1 && grid[i + 1][j] == 'L') {
            adjacentLiars++;
          }
          if (j > 0 && grid[i][j - 1] == 'L') {
            adjacentLiars++;
          }
          if (j < size - 1 && grid[i][j + 1] == 'L') {
            adjacentLiars++;
          }
          //Prints information about liar                                                           
          cout << "L at [" << i+1 << ", " << j+1 << "] sees " << adjacentLiars << " liars" << endl;
        }
      }
    }
  }
}
