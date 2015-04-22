#ifndef __MANHATTAN_VECTOR3_H__
#define __MANHATTAN_VECTOR3_H__

// No idea how to forward declare these
#include <functional>

class Vector3 {
public:
	// Defaults the vector to (0.0, 0.0, 0.0)
	Vector3();
	// Will set all the components to the value of the one parameter
	explicit Vector3(const float& all);
	// Sets each component to their respective parameter. Z has a default
	// parameter of 0.0 so that the vector can mimic a 2D vector. 
	Vector3(const float& x, const float& y, const float& z = 0.0f);
	// Sets the vector to the corisponiding values in the array
	explicit Vector3(const float array3[3]);
	explicit Vector3(float* const array3);
	// Currently not working, the compiler keeps wanting to make its own.
	//Vector3(const Vector3& source);
	~Vector3();

	// Unairy arithmetic operators
	Vector3& operator=(const Vector3& parameter);
	Vector3& operator=(const float& parameter);
	Vector3& operator+=(const Vector3& parameter);
	Vector3& operator+=(const float& parameter);
	Vector3& operator-=(const Vector3& parameter);
	Vector3& operator-=(const float& parameter);
	Vector3& operator*=(const Vector3& parameter);
	Vector3& operator*=(const float& parameter);
	Vector3& operator/=(const Vector3& parameter);
	Vector3& operator/=(const float& parameter);

	// Binary arithmetic operators
	Vector3 operator+(const Vector3& parameter) const;
	Vector3 operator+(const float& parameter) const;
	Vector3 operator-(const Vector3& parameter) const;
	Vector3 operator-(const float& parameter) const;
	Vector3 operator*(const Vector3& parameter) const;
	Vector3 operator*(const float& parameter) const;
	//friend const Vector3 operator*(const float& lhSide, const Vector3& rhSide);
	Vector3 operator/(const Vector3& parameter) const;
	Vector3 operator/(const float& parameter) const;

	// Incrementing operators
	Vector3& operator++(); // Prefix
	Vector3& operator--(); // Prefix
	Vector3 operator++(int); // Postfix
	Vector3 operator--(int); // Postfix

	// Negative and positive operators
	const Vector3 operator-() const;
	// Pointless but need to make sure the compiler doesn't do something stupid.
	const Vector3 operator+() const;

	// Comparison operators
	bool operator==(const Vector3& parameter) const;
	bool operator==(const float& parameter) const;
	bool operator!=(const Vector3& parameter) const;
	bool operator!=(const float& parameter) const;
	bool operator>(const Vector3& parameter) const;
	bool operator>(const float& parameter) const;
	bool operator>=(const Vector3& parameter) const;
	bool operator>=(const float& parameter) const;
	bool operator<(const Vector3& parameter) const;
	bool operator<(const float& parameter) const;
	bool operator<=(const Vector3& parameter) const;
	bool operator<=(const float& parameter) const;

	// Indexing operator
	float& operator[](const size_t index);
	const float& operator[](const size_t index) const;

	// Sets the components of the vector
	Vector3& Set(const float& all = 0.0f);
	Vector3& Set(const float& x, const float& y, const float& z = 0.0f);
	Vector3& Set(const float* array3);
	Vector3& Set(const Vector3& parameter);

	// Swaps the coridnates of self with secondVector.
	void Swap(Vector3& secondVector);

	// Rounds the components so that they are on the grid.
	Vector3& SnapToGrid(const Vector3& gridSize);
	Vector3& SnapToGrid(const float& gridSize = 1.0f);

	// Makes the length of the vector equal to one.
	Vector3& Normalize();
	Vector3 Normal() const;

	// Sets self to cross product of self and secondVector.
	Vector3& SetToCrossProduct(const Vector3& secondVector);
	Vector3 CrossProduct(const Vector3& secondVector) const;

	// Sets self to the reflection of self and normal.
	Vector3& SetToReflect(const Vector3& normal);
	Vector3 Reflect(const Vector3& normal) const;

	// Multiplies each component to negative one.
	Vector3& Negate();
	Vector3 Negative() const;

	// Sets the vector to the linear interpolation of the parameter.
	// Delta is the factor normally [0.0, 1.0] one being complete translation.
	Vector3& SetToLerp(const Vector3& parameter, const float& delta = 0.5f);
	Vector3 Lerp(const Vector3& parameter, const float& delta = 0.5f) const;

	// Swaps x and z and negates z (ignores y, hence the 2D).
	Vector3& SetToPerpendicular2D();
	Vector3 Perpendicular2D() const;

	// Angle axis is the normal vector who represents the axis about.
	// wich you can rotate in order to get to the normal of self (Perpendicular).
	Vector3& SetToAngleAxis();
	Vector3& SetToPerpendicular();
	Vector3 AngleAxis() const;
	Vector3 Perpendicular() const;

	// Sets each component to the absolute value of that component.
	Vector3& SetToAbsolute();
	Vector3 Absolute() const;

	// Finds the mid point between self and secondPoint.
	Vector3 MidPoint(const Vector3& secondPoint) const;

	// Clamps components to be greater than the minVector components.
	Vector3& SetFloor(const Vector3& minVector);
	// Clamps components to be less than the maxVector components.
	Vector3& SetCeil(const Vector3& maxVector);

	// Allows you to run a Lambda expression on each component, this can be used
	// to make complex expressions easy.
	// Example useage:
	//   "SetToLambdaExp([](const float& x) { return x * x; });" Returns x ^ 2 for each componenet
	//   "SetToLambdaExp([](const float& x) { return cos(x); });" Returns cos(x) for each componenet
	//   "SetToLambdaExp([](const float& x) { return sin(x) * foo(x) + x * someConstant; });" Example of complicated statement
	Vector3& SetToLambdaExp(const std::function<float (const float&)>& lambda);
	Vector3 LambdaExp(const std::function<float (const float&)>& lambda) const;

	// Returns the dot product of self and secondVector.
	float DotProduct(const Vector3& secondVector) const;
	// Absolute dot product.
	float AbsDotProduct(const Vector3& secondVector) const;

	// Returns the angle that the vector represents on the angle axis.
	float GetAngle() const;

	// Returns the length of the vector squared (length ^ 2).
	float LengthSquared() const;
	// Returns the length of the vector.
	float Length() const;

	// Returns the distance between self and secondVector.
	float Distance(const Vector3& secondVector) const;

	// Returns the andle between self and targetPos in comparison to the aimVector.
	float AngleToTarget(const Vector3& aimVector, const Vector3& targetPos);

	// Fills an array with each component {x, y, z}.
	float* GetArray();

	// Commonly used constants
	static const Vector3 ZERO;
	static const Vector3 ONE;
	static const Vector3 ONEX;
	static const Vector3 NONEX;
	static const Vector3 ONEY;
	static const Vector3 NONEY;
	static const Vector3 ONEZ;
	static const Vector3 NONEZ;

	// The all important components
	float x, y, z;

};

#endif