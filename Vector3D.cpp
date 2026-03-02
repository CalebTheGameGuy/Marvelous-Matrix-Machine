#include <iostream>

#include "Vector3d.h"

//Makes a vector with 0s for all data
Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

//Makes a vector with specific data
Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

//Allows user to input data
void Vector3D::read()
{
	std::cin >> x;
	std::cin >> y;
	std::cin >> z;
}

//Prints the vector data
void Vector3D::print()
{
	std::cout << "[ " << x << ", " << y << ", " << z << " ]\n";
}
