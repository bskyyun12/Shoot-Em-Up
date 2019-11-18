#ifndef _MATHHELPER_H
#define _MATHHELPER_H
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f
#define RAD_TO_DEG 180.0f / PI

struct Vector2D
{
	float x;
	float y;

	float GetX()
	{
		return x;
	}

	float GetY()
	{
		return y;
	}

	void SetX(float _x)
	{
		x = _x;
	}

	void SetY(float _y)
	{
		y = _y;
	}

	Vector2D(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {}

	//--------------------------------------------------------------------------------------------
	// Calculates the square of the magnitude (preferably used instead of Magnitude if possible)   
	//--------------------------------------------------------------------------------------------
	float MagnitudeSqr() {
		return x * x + y * y;
	}

	//-------------------------------------------
	// Calculates the magnitude of the vector     
	//-------------------------------------------
	float Magnitude()
	{
		return (float)sqrt(MagnitudeSqr());
	}

	//----------------------------------------------------------------------------------------
	// Returns a directional Vector2D with the same direction as the Vector2D but of length 1    
	// (Does not change the x and y values of the original vector)                                       
	//----------------------------------------------------------------------------------------
	Vector2D Normalized()
	{
		float mag = Magnitude();

		return Vector2D(x / mag, y / mag);
	}

	Vector2D& operator +=(const Vector2D& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vector2D& operator -=(const Vector2D& vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	Vector2D operator -() const
	{
		return Vector2D(-x, -y);
	}
};

inline Vector2D operator +(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

inline Vector2D operator -(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x - v2.x, v1.y - v2.y);
}

inline Vector2D operator *(const Vector2D& vec, const float& value)
{
	return Vector2D(vec.x * value, vec.y * value);
}

inline Vector2D operator *(const float& value, const Vector2D& vec)
{
	return Vector2D(value * vec.x, value * vec.y);
}

inline bool operator ==(const Vector2D& v1, const Vector2D& v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

//----------------------------------------------------------------
//Rotates the given vector by the given angle around the origin   
//(Does not change the original vector)                             
//----------------------------------------------------------------
inline Vector2D RotateVector(Vector2D& vec, float angle)
{
	float radAngle = (float)(angle * DEG_TO_RAD);

	return Vector2D((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

inline Vector2D Lerp(Vector2D& start_vec, Vector2D& end_vec, float time)
{
	if (time <= 0.0f)
		return start_vec;
	if (time >= 1.0f)
		return end_vec;

	Vector2D direction = (end_vec - start_vec).Normalized();
	float mag = (end_vec - start_vec).Magnitude();

	return start_vec + direction * mag * time;
}

const Vector2D VECTOR2D_ZERO = { 0.0f, 0.0f };
const Vector2D VECTOR2D_ONE = { 1.0f, 1.0f };
const Vector2D VECTOR2D_UP = { 0.0f, -1.0f };
const Vector2D VECTOR2D_DOWN = { 0.0f, 1.0f };
const Vector2D VECTOR2D_RIGHT = { 1.0f, 0.0f };
const Vector2D VECTOR2D_LEFT = { -1.0f, 0.0f };

struct BezierCurve
{
	Vector2D p0;
	Vector2D p1;
	Vector2D p2;
	Vector2D p3;

	Vector2D CalculateCurvePoint(float t)
	{
		float tt = t * t;
		float ttt = tt * t;
		float u = 1.0f - t;
		float uu = u * u;
		float uuu = uu * u;

		Vector2D point = (uuu * p0) + (3 * uu * t * p1) + (3 * u * tt * p2) + (ttt * p3);
		point.x = (float)round(point.x);
		point.y = (float)round(point.y);

		return point;
	} 

};

#endif // !_MATHHELPER_H

