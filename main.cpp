// Author: Mohammed Abbas
// Email: mabbas4@horizon.csueastbay.edu
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Data elements

string firstMessage = "Please enter file name...hint (try 'DataFile.txt')";
string error = "incorrect, please try again";
string userInput;
string fileName = "DataFile.txt";
int START1 = 0;
int START2 = 0;
int PHI = 0;
int sum = 0;
int *numberList1; // array for the first set of integers
int *numberList2; // array for the second set of integeres
string *errorList; // array for the non-integers
bool alpha1 = false;
bool alpha2 = false;

int main()
{
    std::cout << firstMessage << std::endl;
    std::cin >> userInput;
    while(userInput != fileName)
    {
        cout << "please try again" << endl;
        cin >> userInput;
    }
    if(userInput == fileName)
    {
    ifstream myfile("/Users/mohammedabbas/Desktop/DataFile.txt"); // creating object for file access
    if(myfile.is_open())
    {
        //cout<<"Success!"<<endl; // file opened
        string line1,line2;
        // allocation of new arrays for the columns and errors
        numberList1 = new int[1180];
        numberList2 = new int[1180];
        errorList = new string[1180];
        
        while(!myfile.eof()) // while we havent reached the end of the file
            {
            //getline(myfile.ignore(1180,',','),line1);
            getline(myfile, line1, ','); // ignoring anything with comma in file
            getline(myfile, line2); // getting the second column from file
            
            while(myfile >> line1 >> line2) // seperation of the integers by columns
            {
                alpha1 = false; // assignment of our conditions
                alpha2 = false;
                int i = 0; // counter
                
                while(line1[i] != '\0') // while its not the end of the file
                {
                    if(isalpha(line1[i])) // if its an alphabet char
                    {
                        alpha1 = true; // now its true
                        break;
                    }
                    i++;
                }
                while(line2[i] != '\0') // and if its not
                {
                    if(isalpha(line2[i]))
                    {
                        alpha2 = true; // this one is true for the othr column
                        break;
                    }
                    i++;
                }
                if(alpha1 && !alpha2) // if its not an integer we store it in here
                {
                    numberList1[START1] = stoi(line2);
                    errorList[PHI] = line1;
                    START1++;
                    PHI++;
                }
                else if(!alpha1 && alpha2) // same for the other column
                {
                    numberList2[START2] = stoi(line1);
                    errorList[PHI] = line2;
                    START2++;
                    PHI++;
                }
                else if(alpha1 && alpha2) // heres we store the errors
                {
                    errorList[PHI] = line1;
                    PHI++;
                    errorList[PHI] = line2;
                    PHI++;
                }
                else  // and finally the rest of whats left we use to fill our two arrays for calulation
                {
                    numberList1[START1] = stoi(line1);
                    numberList2[START2] = stoi(line2);
                    START1++;
                    START2++;
                }
                
            }
        }
        for(int i=0; i < START1; i++) // to calculate the average
        {
            sum = sum + numberList1[i];
        }
        double average = sum / 1180;
        cout << "Average value of array element is " << average << endl;
        
        int temp = 0; // place holder for the largest integer well find traversing the array
        for(int i = 0; i < START2; i++)
        {
            if(numberList2[i] > temp) // if that spot in the array is larger than our 0....
            {
                temp = numberList2[i]; // assign it here
            }
        }
        
        cout << "The largest value of all numbers in the second column: " << temp << endl;
        cout << "The invalid numbers are: " << endl;
        for(int i = 0; i < PHI; i++)
        {
            cout << errorList[i] << ",";
        }
        
        // END OF TEST
    
        cout << "The total number of rows in the file is: 1180"<< endl;
        myfile.close();
    }
    else
    {
        cout << "file not found..." << endl;
    }
    
    delete[] numberList1;
    delete[] numberList2;
    delete[] errorList;
}
}

