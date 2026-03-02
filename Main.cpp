#include <iostream>
#include "Matricies.h"

Matrix CreateANewMatrix();
Matrix MatrixChoices(Matrix _mainMatrix);

bool runProgram = true;

int main()
{
	std::cout << "Hello! Welcome to the Marvelous Matrix Machine!\nFirst, you need to make your main matrix!\n";
	Matrix mainMatrix = CreateANewMatrix();
	std::cout << "Nice! You made the matrix:\n";
	mainMatrix.print();

	//Main loop that allows user to continue running the program
	while (runProgram)
	{
		//Allows the matrix to do several functions to the matrix
		std::cout << "\n";
		mainMatrix = MatrixChoices(mainMatrix);
	}

	return 0;
}

//Creates a new matrix by asking user to input data
Matrix CreateANewMatrix()
{
	int rows;
	int columns;

	std::cout << "How many rows would you like the matrix to have? (max 10)\n";
	std::cin >> rows;
	std::cout << "How many columns would you like the matrix to have? (max 10)\n";
	std::cin >> columns;

	std::cout << "Great! You chose a " << rows << " by " << columns << " matrix!\n";
	std::cout << "Now let's fill it up with data!\nPlease input the information (left to right & top to down):\n";

	Matrix createdMatrix(rows, columns);
	createdMatrix.read();
	std::cout << "\n";

	return createdMatrix;
}

//Gives the user many options of what they want to do with their matrix
Matrix MatrixChoices(Matrix _mainMatrix)
{	
	std::cout << "Type what you want to do with your matrix.\n\n"
		"1: Update your main matrix.\n"
		"2: Multiply your main matrix with another matrix.\n"
		"3: Multiply your matrix by a 3D vector (only works with 3x3 matrix).\n"
		"4: Multiply your matrix by a constant.\n"
		"5: Transpose your main matrix.\n"
		"6: Inverse your main matrix (only works with 3x3 matrix). \n"
		"7: Calculate the determinate of your 3x3 matrix.\n"
		"8: Calculate the determinate of your 2x2 matrix.\n"
		"9: Print current main matrix.\n"
		"10: Exit program.\n\n";

	std::string numberChoice;
	std::cin >> numberChoice;
	std::cout << "\n";

	//Checks what the user inputted and does the corresponding calculations and results
	if (numberChoice == "1")
	{
		std::cout << "Great you choice to update your main matrix!\n";
		Matrix returnMatrix = CreateANewMatrix();
		std::cout << "Nice you made the matrix:\n";
		returnMatrix.print();
		std::cout << "\n";

		return returnMatrix;
	}
	if (numberChoice == "2")
	{
		std::cout << "Great! You choice to multiply your matrix with another matrix!\n";
		std::cout << "First, create the second matrix you want to multiply your main matrix with.\n";
		std::cout << "How many columns do you want your second matrix to have (max 10):\n";

		int columns = 0;
		std::cin >> columns;
		std::cout << "\n";

		Matrix multiplyMatrix(_mainMatrix.n,columns);

		std::cout << "Great, you made a " << multiplyMatrix.m << " by " << multiplyMatrix.n << " matrix!\n"
		"Now let's fill it with data!\n";

		multiplyMatrix.read();

		std::cout << "Here is your second matrix:\n";
		multiplyMatrix.print();
		std::cout << "\nHere is the multiplied matrix:\n";

		Matrix returnMatrix = _mainMatrix.multiply(multiplyMatrix);
		returnMatrix.print();

		return returnMatrix;
	}
	if (numberChoice == "3")
	{
		if (_mainMatrix.m !=3 || _mainMatrix.n !=3)
		{
			std::cout << "Failed! This only works with a 3x3 matrix!\n";
			std::cout << "Your matrix remains the same!\n";
			return _mainMatrix;
		}
		std::cout << "Great! You choice to multiply your matrix with a 3D Vector!\n";
		std::cout << "First, create the vector you want to multiply your main matrix with.\n";
		std::cout << "Input the three values of the vector:\n";

		Vector3D multiplyVector;
		multiplyVector.read();

		std::cout << "\nNice! You made the vector:\n";
		multiplyVector.print();

		std::cout << "The multiplied vector result is: ";

		Vector3D finalVector = _mainMatrix.multiply(multiplyVector);
		finalVector.print();

		std::cout << "\n";

		Matrix returnMatrix(3,1);
		returnMatrix.A[0][0] = finalVector.x;
		returnMatrix.A[1][0] = finalVector.y;
		returnMatrix.A[2][0] = finalVector.z;

		std::cout << "Your main vector will now be the matrix equivalent of this vector result!\n";

		return returnMatrix;
	}
	if (numberChoice == "4")
	{
		std::cout << "Great! You chose to multiply your matrix by a constant!\n";
		std::cout << "Please input the constant you want to multiply your matrix by:\n";

		float constant;
		std::cin >> constant;

		Matrix returnMatrix = _mainMatrix.multiply(constant);

		std::cout << "Here is your resulting matrix:\n";
		returnMatrix.print();

		return returnMatrix;
	}
	if (numberChoice == "5")
	{
		std::cout << "Here is your transposed matrix:\n";

		Matrix returnMatrix = _mainMatrix.transpose();
		returnMatrix.print();

		return returnMatrix;
	}
	if (numberChoice == "6")
	{
		std::cout << "Here is your inverted matrix:\n";

		Matrix returnMatrix = _mainMatrix.inverse();
		returnMatrix.print();

		return returnMatrix;
	}
	if (numberChoice == "7")
	{
		if (_mainMatrix.m != 3 || _mainMatrix.n != 3)
		{
			std::cout << "Failed! This only works with a 3x3 matrix!\n";
			return _mainMatrix;
		}

		std::cout << "Here is your determinate:\n";

		std::cout << _mainMatrix.determinant() << "\n";

		return _mainMatrix;
	}
	if (numberChoice == "8")
	{
		if (_mainMatrix.m != 2 || _mainMatrix.n != 2)
		{
			std::cout << "Failed! This only works with a 2x2 matrix!\n";
			return _mainMatrix;
		}

		std::cout << "Here is your determinate:\n";

		std::cout << _mainMatrix.determinateTwoByTwo() << "\n";

		return _mainMatrix;
	}
	if (numberChoice == "9")
	{
		std::cout << "Here is the current main matrix:\n";
		_mainMatrix.print();

		return _mainMatrix;
	}
	if (numberChoice == "10")
	{
		std::cout << "Thank you for coming to the Marvelous Matrix Machine!\n";
		runProgram = false;
	}
	else
	{
		std::cout << "That is an invalid input! Please try again!\n";
		return _mainMatrix;
	}
}