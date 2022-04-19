#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>

class BWT{
    
    public:

        //bwt: Burrow-Wheelers Transform    
        //create a table, rows are all possible rotations of s
        //sort rows alphabetically
        //return (last column of the table)   
        std::string bwt(std::string input);


        //ibwt: Inverse Burrow-Wheelers Transform
        //create empty table
        //repeat length(s) times
            // first insert creates first column
            //insert s as a column of table before first column of the table
            //sort rows of the table alphabetically
        //return (row that ends with the 'EOF' character)
        std::string ibwt(const std::string input);

    private:

        //STX = start of text character
        const int STX = 0x02;

        //ETX = end of text character
        const int ETX = 0x03;
};

//bwt: Burrow-Wheelers Transform
//create a table, rows are all possible rotations of s
//sort rows alphabetically
//return (last column of the table)
std::string BWT::bwt(std::string input){
    
    //While the characters in input are not STX or ETX       
    for(int i = 0; i < input.length(); i++){
        // IF STX or ETX exists in string, regard it as invalid input
        if(input[i] == STX || input[i] == ETX){
            std::cout << "Invalid Input" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

   
    //Else, make a new string and prepend input with STX and append input with ETX
    std::string newString;
    // newString = STX + input + ETX
    newString += STX;
    newString += input;
    newString += ETX;
    //For the length of the new string with the prepends and appended STX and ETX, 
    //  create a new vector of strings as the table
    std::vector<std::string> table;
    int length = newString.length();
    for(int i = 0; i < length; i++){
        
        //push back the string and then do a rotate of the string. (This occurs string.length() times)
        table.push_back(newString);
        
        //rotate newString to the right by one("$BANANA" --> "A$BANAN")
        char lastChar = newString[length - 1];
        for(int j = length - 1; j > 0; j--){
            newString[j] = newString[j-1];
        }
        
        newString[0] = lastChar;

    }

    //Sort the vector with all the new rotated strings
    std::sort(table.begin(), table.end());

    //For the length of the table, create a new sti[length - 1]]ring of the last character
    //  of each string in the table
    std::string output;
    std::string temp;
    char holder;
    for(int i = 0; i < table.size(); i++){
        temp = table.at(i);
        holder = temp[length - 1];
        output += holder;
    }

    //return the transformed string
    return output;
}



//ibwt: Inverse Burrow-Wheelers Transform
//create empty table
//repeat length(input) times
    // first insert creates first column
    //insert s as a column of table before first column of the table
    //sort rows of the table alphabetically
//return (row that ends with the 'EOF' character)
std::string BWT::ibwt(std::string input){
    
    //Similarily to bwt, we create a table to hold all our string variations
    std::vector<std::string> table;
    std::string inverseInput ;

    //Reconstruct our original table by prepending each row with each letter in one column
    //  Ex. If our original string is BANANA, BWT will give us the input paramter ^|ANNBAA , 
    //      where ^ is STX and | is ETX, then we create a "column vector" where each row is 
    //      an independent string. We then sort our column vector lexicographically and then 
    //      prepend the same input string to each row. We keep doing this input.length()^2 times.
    //
    //          |           ^           |^         
    //          A           |           A|
    //          N   Sort    A   Prepend NA  Sort       Keep doing this
    //          N   --->    A   ------> NA  --->  .... -------------->  
    //          B           A           BA             until all input.length()^2
    //          ^           B           ^B             iterations are complete.
    //          A           N           AN
    //          A           N           AN
    //
    //      At the end, we will recieve our original string, which in this case would be ^BANANA|     
    for(int i = 0; i < input.length(); i++){
        if(i == 0){
            //First iteration creates the column vector
            for(int j = 0; j < input.length(); j++){
                inverseInput = input[j];
                table.push_back(inverseInput);
            }
        }else{
            //After the first iteration, prepend to the already existing vector.
            for(int j = 0; j < input.length(); j++){
                table.at(j) = input[j] + table.at(j); 
            }
        }
        //Sort the vector every time we finish a round of prepending the input.
        std::sort(table.begin(), table.end());
    }

    //This part looks for the original string, which will always end with ETX.
    // So we search for the string ending with ETX and then we trim off STX and ETX on both ends
    // and we achieve our expected result!
    std::string output;
    for(int i = 0; i < input.length(); i++){
        
        output = table.at(i);
        if(output[input.length() - 1] == ETX){
            
            //Erase STX and ETX from output string.
            output.erase(output.begin());
            output.erase(output.end() - 1);
            
            //We don't need to worry about missing the return value of the function as
            //the functions are created to safe-proof that each string that passes by has
            //ETX at the end.
            return output;
        }
    }
}
