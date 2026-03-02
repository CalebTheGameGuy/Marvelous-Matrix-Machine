#include "Matricies.h"
#include <iostream>
#include "Vector3d.h"

Matrix::Matrix()
{
	//Sets matrix size to the max 10x10
	m = M;
	n = N;

	//Fills the matrix with zeros
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = 0;
		}
	}
}

Matrix::Matrix(int _m, int _n)
{
	//Sets matrix size to inputted variables
	m = _m;
	n = _n;

	//Fills the matrix with zeros
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = 0;
		}
	}
}

//Allows the user to input data into the matrix
void Matrix::read()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cin >> A[i][j];
		}
	}
}

//Prints out the data in the matrix
void Matrix::print()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << A[i][j] << " ";
		}
		std::cout << "\n";
	}
}

//Multiplies the matrix by another matrix
Matrix Matrix::multiply(Matrix other)
{
	//Tests if the multiplication is possible
    if (other.m != n)
    {
        std::cout << "Can't multiply because of size differences!\n";
        return *this;
    }

	//Creates the empty resulting matrix
    Matrix dynamicResult(m, other.n);

	//Fills the resulting matrix with the correct data
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < other.n; j++)
        {
			//Multiplies the value of the first matrix by the correct value of the second matrix
			//It then adds it correctly to the correct spot in the resulting matrix
			double resultValue = 0;
            for (int k = 0; k < other.m; k++)
            {
				resultValue += (A[i][k] * other.A[k][j]);
            }
			dynamicResult.A[i][j] = resultValue;
        }
    }

    return dynamicResult;
}

//Transposes the matrix by flipping the rows and columns
Matrix Matrix::transpose()
{
	//Creates the resulting matrix
	Matrix transposeMatrix(n,m);

	//Goes through and flips the rows and columns
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			transposeMatrix.A[j][i] = A[i][j];
		}
	}

	return transposeMatrix;
}

//Finds the determinate of a 3x3 matrix via the Sarrus' rule
double Matrix::determinant()
{
	//Checks if a determinate is possible.
	if (m != 3 || n != 3)
	{
		std::cout << "This method can't find determinate of non 3x3 matrix!\n";
		return 0.0;
	}

	//Uses the Sarrus' Rule
	float downArrows = (A[0][0] * A[1][1] * A[2][2]) + (A[0][1] * A[1][2] * A[2][0]) + (A[0][2] * A[1][0] * A[2][1]);
	float upArrows = (A[2][0] * A[1][1] * A[0][2]) + (A[2][1] * A[1][2] * A[0][0]) + (A[2][2] * A[1][0] * A[0][1]);

	return downArrows - upArrows;
}

//Inverses a 3x3 matrix using the equation: A^-1 = (1/det(A))*adj(A)
Matrix Matrix::inverse()
{
	//Checks if it is a 3x3 matrix
	if (m != 3 || n !=3)
	{
		std::cout << "This operation can only be completed with a 3x3 matrix!\n";
		return *this;
	}

	//Finds the determinate
	float determinate = determinant();

	//Uses the determinate to make sure that the matrix has an inverse
	if (determinate == 0)
	{
		std::cout << "The determinate is equal to 0!\nThis matrix cannot be inversed!\nReturning the same matrix!\n";
		return *this;
	}

	//Defines variables
	Matrix cofactorMatrix(m,n); //Empty cofactor matrix
	Matrix matrixTwoByTwo(2,2); //Temp 2x2 matrix to get the cofactors
	float matrixTwoByTwoData[4]; //Data in the 2x2 matrix
	float matrixTwoByTwoDeterminate; //Determinate of the 2x2 matrix

	//Creates the cofactor matrix
	for (int row = 0; row < m; row++) //Goes through each spot in the 3x3 matrix to test it
	{
		for (int column = 0; column < n; column++)
		{
			//Gather the 2x2 Matrix Data
			int counter = 0;
			for (int rowTest = 0; rowTest < m; rowTest++) //goes through each spot in the 3x3 matrix to create a 2x2 matrix for the tested spot
			{
				for (int columnTest = 0; columnTest < n; columnTest++)
				{
					//Determines if it is in the same row or column as the tested matrix spot
					//If it is, skips it, if not, it adds it to a temp 2x2 matrix data holder
					if (row == rowTest || column == columnTest) continue;
					matrixTwoByTwoData[counter] = A[rowTest][columnTest];
					counter++;
				}
			}


			//Fill the 2x2 Matrix with the data from the data holder
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					matrixTwoByTwo.A[i][j] = matrixTwoByTwoData[i * 2 + j];
				}
			}

			//Find the determinate of the 2x2 Matrix
			matrixTwoByTwoDeterminate = matrixTwoByTwo.determinateTwoByTwo();


			//Make it negative if row + column is odd
			if ((row + column) % 2 == 1)
			{
				matrixTwoByTwoDeterminate *= -1;
			}

			//Add the resulting cofactor to the cofactor matrix
			cofactorMatrix.A[row][column] = matrixTwoByTwoDeterminate;
		}
	}

	//Return the inverse using the cofactor matrix and several methods
	return cofactorMatrix.transpose().multiply(1/determinate);
}

Vector3D Matrix::multiply(Vector3D v)
{
	//Checks if method works.
	if (n != 3)
	{
		std::cout << "Failed! This function can only return 3D Vectors, so the matrix must be 3x3!\n";
		return v;
	}
	if (n != 3)
	{
		std::cout << "Can't multiply because of size differences! Additionally, "
			   "this function can only return 3D Vectors, so the matrix must be 3x3! \n";
		return v;
	}

	//Variables
	Vector3D returnVector;
	float sumDataHolder[3] = {0,0,0};

	//Fills the sumDataHolder with relavent data
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			switch (j)
			{
			case 0:
				sumDataHolder[i] += A[i][j] * v.x;
				break;
			case 1:
				sumDataHolder[i] += A[i][j] * v.y;
				break;
			case 2:
				sumDataHolder[i] += A[i][j] * v.z;
				break;
			}
		}
	}

	//Fills the vector with sumDataHolder
	returnVector.x = sumDataHolder[0];
	returnVector.y = sumDataHolder[1];
	returnVector.z = sumDataHolder[2];

	return returnVector;
}

//Gives the determinate of a 2x2 matrix
double Matrix::determinateTwoByTwo()
{
	//Checks if the matrix is a 2x2
	if ((m != 2) || (n != 2))
	{
		std::cout << "This method can't find determinate of non 2x2 matrix!\n";
		return 0.0;
	}

	//Gives determinate
	return (A[0][0] * A[1][1] - A[0][1] * A[1][0]);
}

//Multiplies a matrix by a constant
Matrix Matrix::multiply(float x)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] *= x;
		}
	}

	return *this;
}