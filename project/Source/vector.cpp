#include "vector.h"
#include <math.h>

// ¡¡¡Vector2¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡

Vector2::Vector2() : Vector2(0.0f, 0.0f)
{
}

Vector2::Vector2(float _xy) : Vector2(_xy, _xy)
{
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::Vector2(const VECTOR& v) : Vector2(v.x, v.y)
{
}

Vector2::Vector2(const VECTOR2& v) : Vector2(v.x, v.y)
{
}

const Vector2 Vector2::operator+(const Vector2& value) const
{
	Vector2 vec;

	vec.x = x + value.x;
	vec.y = y + value.y;

	return vec;
}

const Vector2 Vector2::operator-(const Vector2& value) const
{
	Vector2 vec;

	vec.x = x - value.x;
	vec.y = y - value.y;

	return vec;
}

const Vector2 Vector2::operator*(const Vector2& value) const
{
	Vector2 vec;

	vec.x = x * value.x;
	vec.y = y * value.y;

	return vec;
}

const Vector2 Vector2::operator/(const Vector2& value) const
{
	Vector2 vec;

	vec.x = x / value.x;
	vec.y = y / value.y;

	return vec;
}

const Vector2 Vector2::operator*(float value) const
{
	Vector2 vec;

	vec.x = x * value;
	vec.y = y * value;

	return vec;
}

const Vector2 Vector2::operator/(float value) const
{
	Vector2 vec;

	vec.x = x / value;
	vec.y = y / value;

	return vec;
}

void Vector2::operator+=(const Vector2& value)
{
	x = x + value.x;
	y = y + value.y;
}

void Vector2::operator-=(const Vector2& value)
{
	x = x - value.x;
	y = y - value.y;
}

void Vector2::operator*=(const Vector2& value)
{
	x = x * value.x;
	y = y * value.y;
}

void Vector2::operator/=(const Vector2& value)
{
	x = x / value.x;
	y = y / value.y;
}

void Vector2::operator*=(float value)
{
	x = x * value;
	y = y * value;
}

void Vector2::operator/=(float value)
{
	x = x / value;
	y = y / value;
}

bool Vector2::operator==(const Vector2& value) const
{
	return x == value.x && y == value.y;
}

bool Vector2::operator!=(const Vector2& value) const
{
	return !(*this == value);
}

float Vector2::Get(int i) const
{
	float value = 0.0f;

	switch (i)
	{
	case 0:
		value = x;
		break;
	case 1:
		value = y;
		break;
	}

	return value;
}

void Vector2::Set(int i, float value)
{
	switch (i)
	{
	case 0:
		x = value;
		break;
	case 1:
		y = value;
		break;
	}
}

std::string Vector2::ToString() const
{
	std::string ret;
	ret += std::to_string(x) + ",";
	ret += std::to_string(y);
	return ret;
}

float Vector2::Size() const
{
	return sqrtf(SquareSize());
}

float Vector2::SquareSize() const
{
	return x * x + y * y;
}

const Vector2 Vector2::Norm() const
{
	float size = Size();
	if (size == 0) return V2::ZERO;
	else return *this / size;
}

Vector2::operator const VECTOR() const
{
	return VGet(x, y, 0);
}

Vector2::operator const VECTOR2() const
{
	return VECTOR2(x, y);
}

Vector2::operator bool() const
{
	return this->Size() != 0;
}

const Vector2 Vector2::operator-() const
{
	Vector2 vec = *this;
	vec *= -1.0f;

	return vec;
}

float V2::Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

float V2::Cross(const Vector2& a, const Vector2& b)
{
	return a.x * b.y - b.x * a.y;
}

// ¡¡¡Vector3¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡

Vector3::Vector3() : Vector3(0.0f, 0.0f, 0.0f)
{
}

Vector3::Vector3(float _xyz) : Vector3(_xyz, _xyz, _xyz)
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::Vector3(const VECTOR& v) : Vector3(v.x, v.y, v.z)
{
}

const Vector3 Vector3::operator-() const
{
	Vector3 vec = *this;
	vec *= -1.0f;

	return vec;
}

const Vector3 Vector3::operator+(const Vector3& value) const
{
	Vector3 vec;

	vec.x = x + value.x;
	vec.y = y + value.y;
	vec.z = z + value.z;

	return vec;
}

const Vector3 Vector3::operator-(const Vector3& value) const
{
	Vector3 vec;

	vec.x = x - value.x;
	vec.y = y - value.y;
	vec.z = z - value.z;

	return vec;
}

const Vector3 Vector3::operator*(const Vector3& value) const
{
	Vector3 vec;

	vec.x = x * value.x;
	vec.y = y * value.y;
	vec.z = z * value.z;

	return vec;
}

const Vector3 Vector3::operator/(const Vector3& value) const
{
	Vector3 vec;

	vec.x = x / value.x;
	vec.y = y / value.y;
	vec.z = z / value.z;

	return vec;
}

const Vector3 Vector3::operator*(float value) const
{
	Vector3 vec;

	vec.x = x * value;
	vec.y = y * value;
	vec.z = z * value;

	return vec;
}

const Vector3 Vector3::operator/(float value) const
{
	Vector3 vec;

	vec.x = x / value;
	vec.y = y / value;
	vec.z = z / value;

	return vec;
}

void Vector3::operator+=(const Vector3& value)
{
	x = x + value.x;
	y = y + value.y;
	z = z + value.z;
}

void Vector3::operator-=(const Vector3& value)
{
	x = x - value.x;
	y = y - value.y;
	z = z - value.z;
}

void Vector3::operator*=(const Vector3& value)
{
	x = x * value.x;
	y = y * value.y;
	z = z * value.z;
}

void Vector3::operator/=(const Vector3& value)
{
	x = x / value.x;
	y = y / value.y;
	z = z / value.z;
}

void Vector3::operator*=(float value)
{
	x = x * value;
	y = y * value;
	z = z * value;
}

void Vector3::operator/=(float value)
{
	x = x / value;
	y = y / value;
	z = z / value;
}

bool Vector3::operator==(const Vector3& value) const
{
	return x == value.x && y == value.y && z == value.z;
}

bool Vector3::operator!=(const Vector3& value) const
{
	return !(*this == value);
}

float Vector3::Get(int i) const
{
	float value = 0.0f;

	switch (i)
	{
	case 0:
		value = x;
		break;
	case 1:
		value = y;
		break;
	case 2:
		value = z;
		break;
	}

	return value;
}

void Vector3::Set(int i, float value)
{
	switch (i)
	{
	case 0:
		x = value;
		break;
	case 1:
		y = value;
		break;
	case 2:
		z = value;
		break;
	}
}

std::string Vector3::ToString() const
{
	std::string ret;
	ret += std::to_string(x) + ",";
	ret += std::to_string(y) + ",";
	ret += std::to_string(z);
	return ret;
}

float Vector3::Size() const
{
	return VSize(*this);
}

float Vector3::SquareSize() const
{
	return VSquareSize(*this);
}

const Vector3 Vector3::Norm() const
{
	float size = Size();
	if (size == 0) return V3::ZERO;
	else return *this / size;
}

const Vector3 Vector3::Transform(const MATRIX& mat) const
{
	return VTransform(*this, mat);
}

Vector3::operator const VECTOR() const
{
	return VGet(x, y, z);
}

Vector3::operator bool() const
{
	return this->Size() != 0;
}

float V3::Dot(const Vector3& a, const Vector3& b)
{
	return VDot(a, b);
}

Vector3 V3::Cross(const Vector3& a, const Vector3& b)
{
	return VCross(a, b);
}
