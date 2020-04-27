/*
	Name: Struct and System I/O
	Author: Hector Mariscal, Michelle Kirkwood, Adam Peltenburg - Group 7
	Date: 12-04-18 13:55
	Description: This application uses a struct to create a new data type which I called PayRecord which
	requires a first name, last name, total hours worked and their weekly wage. I then created a variable
	based on this data type which will hold all of the mentioned attributes for each employee. I then read
	the data from a text file using the fstream library and the I/O streams. Assigned the data in the text file
	into the corresponding attributes in the newEmployee variable based on the struct I created. I then calculate
	the weekly earnings and total earnings, and perform some string manipulation to get the desired output into a new
	text file that is created called pay.txt.
*/
#include <iostream>
#include <iomanip>
#include <fstream>	// needed for ifstream class
#include <string>   //for the string manipulation to get the first character of the first name

using namespace std;

struct PayRecord //new struct that will take a day, month and year making this a data type of dates
{
	string firstName;   //will hold the employees first name
	string lastName;    //will hold the employees last name
	double hoursWorked; //will hold the amount of hours the employee has worked
	double wagePerHour; //will hold how much the employee makes an hour
};

int main()
{

    string fileName = "hours.txt";	// hold the file name to open
    string targetFileName = "pay.txt";
	ifstream inFile;       // an ifstream object to connect to the file
	string myName = "Hector Mariscal";  //my name
	int returnValue = 0;    //holds the value that is returned based on the program working or not
	double weeklyPay = 0.0; //holds the amount of money the employee makes in a week
	double totalPay = 0.0;  //holds the amount of money every employee made together
	ofstream outFile;

	PayRecord newEmployee; //variable based on the struct

    inFile.open(fileName.c_str());

 	if(inFile.fail()) // If the input file could not be opened
 	{
 		// Inform the user
		cout << "\nThe file was NOT successfully opened. "
			 << "Check that the file exists" << endl;

		// set the return value of main() to 1
		returnValue = 1;  // '1' indicating the program did not
 	 				      // execute successfully
 	}
 	else
 	{
        outFile.open(targetFileName.c_str());
        if(outFile.fail()) // If the output file could not be opened
	 	{
	 		// Inform the user
			cout << "\nThe output file was NOT successfully opened. " << endl;

			// close the input file
			inFile.close();
			// set the return value of main() to 1
			returnValue = 1;  // '1' indicating the program did not
	 	 				      // execute successfully
	 	}
	 	else
        {
            cout << "The Program Worked! Look For The pay.txt File";

            char firstInitial;  //holds the first initial of the first name
            inFile.seekg(0L, ios_base::beg);    //used to put the cursor at the begining
            // set the console output formatting
            cout  << setiosflags(ios::fixed)
                  << setiosflags(ios::showpoint)
                  << setprecision(2);

        outFile << myName << endl   //outputs the intro text into the new file
        <<"PAY FOR THIS WEEK" << endl
		 << "==============================" << endl;
            inFile >> newEmployee.firstName >> newEmployee.lastName >> newEmployee.hoursWorked >> newEmployee.wagePerHour;
            while(!inFile.eof())    //loops through the text to obtain the data and assign each to their corresponding attribute in the newEmployee variable
            {
//                 cout << "DEBUGGING" << endl;
//                cout << left << setw(5) << newEmployee.firstName
//                     << left << setw(7) << newEmployee.lastName
//                     << right << setw(8) << newEmployee.hoursWorked
//                     << right << setw(8) << newEmployee.wagePerHour <<endl;



                firstInitial = newEmployee.firstName.at(0); //gets the first character of the first name string to obtain the first initial
                weeklyPay = newEmployee.hoursWorked*newEmployee.wagePerHour;    //calculates the weekly pay
                totalPay += weeklyPay;  //calculates the total pay by adding upall of the weekl pays


                //outputs the new formatted data into the newly created pay.txt
                outFile << right << setw(2) << firstInitial << setw(1) << ". "
                        << left << setw(8) << newEmployee.lastName
                        << right <<setw(4) << "$" << right <<setw(8) << fixed << setprecision(2)<< weeklyPay << endl;
                inFile >> newEmployee.firstName >> newEmployee.lastName >> newEmployee.hoursWorked >> newEmployee.wagePerHour;


            }

            inFile.close(); // close the file.

            outFile << "==============================" << endl
            << right << setw(12) << "Total:"    //
            << right <<setw(4) << "$" << right <<setw(8) << fixed << setprecision(2) << totalPay << endl;   //output the total pay in the new txt file
            outFile.close(); //closes the new txt file

        }

        cout << endl << endl;
        return returnValue;
}
}
