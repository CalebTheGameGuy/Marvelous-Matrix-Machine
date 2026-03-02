#pragma once
class Vector3D
{
public:
	//Main Methods
	Vector3D();
	Vector3D(float _x, float _y, float _z);
	void read();
	void print();

	//Variables
	float x;
	float y;
	float z;
};

