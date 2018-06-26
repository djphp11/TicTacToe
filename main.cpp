//Midterm
//CSIT 139 - Summer 2017 - Philip Jung

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <ctime>   //for time
#include <stdlib.h> //for macOS sys pause
using namespace std;

//prototypes
//GAME FUNCTIONS
void credits(bool& start); //splash screen
void randomInts(int&num1, int&num2); //generate random Ints
void menu(string name, float& correct, float& wrong, float& money); //generate menu
//FUNCTIONS WITH USER VALIDATIONG
void validateUserResponse(string& choice); // Validate user input from the menu. Options NOT in the menu are not allowed.
void validateUserAnswer(int& yourAnswer); // Validate user input, ONLY positive integers are allowed
void validateUserName(string& name); //validate username is a single string only alpha characters
//MATH FUNCTIONS
void add(string name, float& correct, float& wrong, float& money); // generate an addition problem where answer >= 0
void subtract(string name, float& correct, float& wrong, float& money); // generate a subtraction problem where answer >= 0
void multiply(string name, float& correct, float& wrong, float& money); // generate a mult problem where answer >= 0
void divide(string name, float& correct, float& wrong, float& money); // generate a division problem where answer >= 0
//FUNCTIONS WITH STATS
void updateStats(float& correct, float& wrong, float& money, bool rightAnswer); // Save player statistics in RAM
void saveStats(string name, float correct, float wrong, float money); // Save player statistics on an external txt file.
void retrieveStats(string name, ifstream& inputFile, ofstream& outputFile, float& correct, float& wrong, float& money);
//  Retrieve player statistics from external txt file when the game starts, else (if it doesnt exist) make new file
void displayStats(string name, float correct, float wrong, float money); // Display stats on screen
void afterDisplayPause();


int main()
{
    ifstream inputFile;
    ofstream outputFile;
    float correct = 0;  //initialize correct counter in case no retrieveable file
    float wrong = 0; //initialize wrong counter in case no retrieveable file
    float money = 0; //initialize money in case no retrieveable file
    bool start; //game only starts if this bool returns true from credits()
    string name = "";
    
    credits(start);
    if (!start)
    {
        return EXIT_SUCCESS;
    }
    validateUserName(name); //only takes single string [must be alpha characters]
    retrieveStats(name, inputFile, outputFile, correct, wrong, money);
    menu(name, correct, wrong, money); //rest of gaming functions inside main()
    
    return 0;
}

void credits(bool& start)
{
    string go; //go will take user input, if y/Y, then returns true bool
    cout << "******************************\n";
    cout << "******************************\n";
    cout << "******************************\n";
    cout << "******" << "                  " << "******\n";
    cout << "******" << "   TheMathGame    " << "******\n";
    cout << "******" << "     By Jung,     " << "******\n";
    cout << "******" << "      Philip      " << "******\n";
    cout << "******" << "                  " << "******\n";
    cout << "******************************\n";
    cout << "******************************\n";
    cout << "******************************\n\n";
    
    
    cout << "y/Y to continue, any other char to exit";
    getline(cin, go);
    if (go == "y" || go == "Y")
    {
        start = true;
    }
    else
    {
        start = false;
    }
}

void validateUserName(string& name)
{
    int counter = 0;
    cout << "Enter your name and press <ENTER>\n";
    getline(cin, name);
    while (counter < name.length() || name.length() == 0)
    {
        if (!isalpha(name[counter]))
        {
            cout << "Enter your name and press <ENTER>\n";
            getline(cin, name);
            counter = 0; //restart while loop if invalid input
        }
        else if (name.length() == 0)
        {
            cout << "Enter your name and press <ENTER>\n";
            getline(cin, name); //restart while loop if invalid input
            counter = 0;
        }
        else
        {
            counter++;
        }
    }
}

void validateUserAnswer(int& yourAnswer)
{
    string input;
    getline(cin, input);
    int counter = 0;
    while (counter < input.length() || input.length() == 0)
    {
        if (!isdigit(input[counter]))
        {
            cout << "Invalid entry\n";
            cout << "Enter a positive integer and press <ENTER>";
            getline(cin, input);
            counter = 0; //restart while loop if invalid input
        }
        else
        {
            counter++;
        }
    }
    yourAnswer = std::stoi(input); //turn your userinput into an int
}

void retrieveStats(string name, ifstream& inputFile, ofstream& outputFile, float& correct, float& wrong, float& money)
{
    //
    inputFile.open(name + ".txt");
    
    if (inputFile)
    {
        inputFile >> correct >> wrong >> money;
    }
    else
    {
        outputFile.open(name + ".txt");
        outputFile.close();
    }
}

void menu(string name, float& correct, float& wrong, float& money)
{
    cout << "*******CHOOSE A PROBLEM*******\n";
    cout << "******************************\n";
    cout << "******************************\n";
    cout << "******" << "                  " << "******\n";
    cout << "******" << "  1. ADD          " << "******\n";
    cout << "******" << "  2. SUBTRACT     " << "******\n";
    cout << "******" << "  3. MULTIPLY     " << "******\n";
    cout << "******" << "  4. DIVIDE       " << "******\n";
    cout << "******" << "  5. STATS        " << "******\n";
    cout << "******" << "  n/N to QUIT     " << "******\n";
    cout << "******" << "                  " << "******\n";
    cout << "******************************\n";
    cout << "******************************\n";
    string choice;
    validateUserResponse(choice);
    //after choices have been validated, appropriate choices passed in if/else below
    
    if (choice == "1")
    {
        add(name, correct, wrong, money);
    }
    else if (choice == "2")
    {
        subtract(name, correct, wrong, money);
    }
    else if (choice == "3")
    {
        multiply(name, correct, wrong, money);
    }
    else if (choice == "4")
    {
        divide(name, correct, wrong, money);
    }
    else if (choice == "5")
    {
        displayStats(name, correct, wrong, money);
    }
    else if (choice == "n" || choice == "N")
    {
        cout << "goodbye";
        saveStats(name, correct, wrong, money);
    }
}

void validateUserResponse(string& choice)
{
    int counter = 0;
    while (counter == 0)
    {
        getline(cin, choice);
        if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "n" || choice == "N")
        {
            counter++; //we accept user response, and push out of while loop
        }
        else
        {
            cout << "This is not a valid menu response";
            counter = 0; //reset counter, and rebegin while loop
        }
    }
}

void add(string name, float& correct, float& wrong, float& money)
{
    int num1, num2, answer, yourAnswer;
    bool rightAnswer;
    randomInts(num1, num2);
    answer = num1 + num2;
    cout << "*****ADDITION******\n";
    cout << "*******************\n";
    cout << "*******************\n";
    cout << "****" << "   " << num1 << " + " << num2 << "   " << "****\n";
    cout << "*******************\n";
    cout << "*******************\n";
    validateUserAnswer(yourAnswer);
    if (answer == yourAnswer)
    {
        rightAnswer = 1;
    }
    else
    {
        rightAnswer = 0;
    }
    updateStats(correct, wrong, money, rightAnswer);
    menu(name, correct, wrong, money);
}

void subtract(string name, float& correct, float& wrong, float& money)
{
    int num1, num2, answer, yourAnswer;
    int first, second;
    bool rightAnswer;
    randomInts(num1, num2);
    if (num1 > num2)
    {
        answer = num1 - num2;
        first = num1;
        second = num2;
    }
    else //this case will include when num1 == num2
    {
        answer = num2 - num1;
        first = num2;
        second = num1;
    }
    cout << "****SUBTRACTION****\n";
    cout << "*******************\n";
    cout << "*******************\n";
    cout << "****" << "   " << first << " - " << second << "   " << "****\n";
    cout << "*******************\n";
    cout << "*******************\n";
    validateUserAnswer(yourAnswer);
    if (answer == yourAnswer)
    {
        rightAnswer = 1;
    }
    else
    {
        rightAnswer = 0;
    }
    updateStats(correct, wrong, money, rightAnswer);
    menu(name, correct, wrong, money);
}

void multiply(string name, float& correct, float& wrong, float& money)
{
    int num1, num2, answer, yourAnswer;
    bool rightAnswer;
    randomInts(num1, num2);
    answer = num1*num2;
    
    cout << "**MULTIPLICATION**\n";
    cout << "******************\n";
    cout << "******************\n";
    cout << "***" << "   " << num1 << " * " << num2 << "   " << "****\n";
    cout << "******************\n";
    cout << "******************\n";
    validateUserAnswer(yourAnswer);
    
    if(answer == yourAnswer)
    {
        rightAnswer = 1;
    }
    else
    {
        rightAnswer = 0;
    }
    updateStats(correct, wrong, money, rightAnswer);
    menu(name, correct, wrong, money);
    
}

void divide(string name, float& correct, float& wrong, float& money)
{
    int num1, num2, numerator, denominator, answer, yourAnswer;
    bool rightAnswer;
    randomInts(num1, num2);
    numerator = num1*num2;
    denominator = num2;
    answer = numerator/denominator;
    
    cout << "*****DIVISION*****\n";
    cout << "******************\n";
    cout << "******************\n";
    cout << "***" << "   " << numerator << " / " << denominator << "   " << "***\n";
    cout << "******************\n";
    cout << "******************\n";
    validateUserAnswer(yourAnswer);
    if(answer == yourAnswer)
    {
        rightAnswer = 1;
    }
    else
    {
        rightAnswer = 0;
    }
    updateStats(correct, wrong, money, rightAnswer);
    menu(name, correct, wrong, money);
    
}




void randomInts(int& num1, int& num2)
{
    //has to be passed by reference into math functions or skyrockets
    //set constants
    const int MAX = 10, MIN = 1;
    //set variables to hold random nums
    //plant the seed
    unsigned seed = time(0);
    srand(seed);
    //generate random numbs
    num1 = (rand() % (MAX - MIN + 1)) + MIN;
    num2 = (rand() % (MAX - MIN + 1)) + MIN;
}

void displayStats(string name, float correct, float wrong, float money)
{
    cout << "**********************************\n";
    cout << "**********************************\n";
    cout << "**********************************\n";
    cout << "***" << name << "                   ******\n";
    cout << setprecision(2) << fixed;
    cout << "***" << "Total earnings: $" <<money << "    ******\n";
    cout << setprecision(0) << fixed;
    cout << "***" << "Total correct: " << correct << "         ******\n";
    cout << "***" << "Total wrong: " << wrong << "           ******\n";
    cout << "**********************************\n";
    cout << "**********************************\n";
    
    
    afterDisplayPause(); //let user view and move on function; depends on system
    menu(name, correct, wrong, money);
}

void saveStats(string name, float correct, float wrong, float money)
{
    ofstream outputFile;
    outputFile.open(name + ".txt");
    outputFile << correct << endl;
    outputFile << wrong << endl;
    outputFile << money << endl;
    outputFile.close();
}

void updateStats(float& correct, float& wrong, float& money, bool rightAnswer)
{
    if (rightAnswer) //if right bool, add correct counter and .05c
    {
        correct++;
        money += .05;
    }
    else if (!rightAnswer) //if wrong answer, take away .03c unless newtotal negative
    {
        wrong++;
        if (money < .03)
        {
            money = 0;
        }
        else
        {
            money -= .03;
        }
    }
}

void afterDisplayPause()
{
    //Mac
    //system("read");
    
    //Linux
    //string whatever;
    //cout << "Press any key twice to continue. . .";
    //string whatever;
    //getline(cin,whatever);
    //cin.ignore();
    //cout << endl;
    
    //Windows
    system("pause");
    system("CLS");
}



















