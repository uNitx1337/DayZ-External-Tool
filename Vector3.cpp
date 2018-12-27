/*
	by unitx 12.22.2018
*/

#include "Engine.h"
#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector3& Vector3::operator+=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

Vector3& Vector3::operator*=(float number)
{
	x *= number;
	y *= number;
	z *= number;

	return *this;
}

Vector3& Vector3::operator/=(float number)
{
	x /= number;
	y /= number;
	z /= number;

	return *this;
}