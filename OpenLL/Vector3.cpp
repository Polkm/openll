// Most of this implementation documentation is for people working on the class
// if you are looking for how to use this class, look in the header for the
// appropriate documentation.

#include "Vector3.h"

// Standard c++ libraries
#include <ostream>
#include <istream>
#include <string>

const Vector3 Vector3::ZERO = Vector3();
const Vector3 Vector3::ONE = Vector3(1.0f);
const Vector3 Vector3::ONEX = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NONEX = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::ONEY = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::NONEY = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::ONEZ = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NONEZ = Vector3(0.0f, 0.0f, -1.0f);

// I am going to try and use initialization lists instead of the set function
// it could reduce the overhead of the constructors. The downside is that they don't
// use the Set function and won't update if I add something to the Set function
// further down the line.

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {
}
Vector3::Vector3(const float& all) : x(all), y(all), z(all)  {
}
Vector3::Vector3(const float& inX, const float& inY, const float& inZ) : x(inX), y(inY), z(inZ) {
}
Vector3::Vector3(const float array3[3]) : x(array3[0]), y(array3[1]), z(array3[2]) {
}
Vector3::Vector3(float* const array3) : x(array3[0]), y(array3[1]), z(array3[2]) {
}
// TODO: figure out why this doesn't work right
//Vector3::Vector3(const Vector3& source) : x(source.x), y(source.y), z(source.z) {
//	//Set(source);
//}

Vector3::~Vector3() {
}

Vector3& Vector3::operator=(const Vector3& parameter) {
	return Set(parameter);
}
Vector3& Vector3::operator=(const float& parameter) {
	return Set(parameter);
}

Vector3& Vector3::operator+=(const Vector3& parameter) {
	return Set(x + parameter.x, y + parameter.y, z + parameter.z);
}
Vector3& Vector3::operator+=(const float& parameter) {
	return Set(x + parameter, y + parameter, z + parameter);
}

Vector3& Vector3::operator-=(const Vector3& parameter) {
	return Set(x - parameter.x, y - parameter.y, z - parameter.z);
}
Vector3& Vector3::operator-=(const float& parameter) {
	return Set(x - parameter, y - parameter, z - parameter);
}

Vector3& Vector3::operator*=(const Vector3& parameter) {
	return Set(x * parameter.x, y * parameter.y, z * parameter.z);
}
Vector3& Vector3::operator*=(const float& parameter) {
	return Set(x * parameter, y * parameter, z * parameter);
}

Vector3& Vector3::operator/=(const Vector3& parameter) {
	return Set(x / parameter.x, y / parameter.y, z / parameter.z);
}
// I wanted to throw an exception if it equals zero. It seams weird though :/
Vector3& Vector3::operator/=(const float& parameter) {
	return parameter != 0.0f ? Set(x / parameter, y / parameter, z / parameter) : Set();
}

Vector3 Vector3::operator+(const Vector3& parameter) const {
	return Vector3(*this) += parameter;
}
Vector3 Vector3::operator+(const float& parameter) const {
	return Vector3(*this) += parameter;
}

Vector3 Vector3::operator-(const Vector3& parameter) const {
	return Vector3(*this) -= parameter;
}
Vector3 Vector3::operator-(const float& parameter) const {
	return Vector3(*this) -= parameter;
}

Vector3 Vector3::operator*(const Vector3& parameter) const {
	return Vector3(*this) *= parameter;
}
Vector3 Vector3::operator*(const float& parameter) const {
	return Vector3(*this) *= parameter;
}
// Can't get this to work :/ keep getting linker errors
//const Vector3 operator*(const float& lhSide, const Vector3& rhSide) {
	//return Vector3(rhSide.x * lhSide, rhSide.y * lhSide, rhSide.z * lhSide);
//}

Vector3 Vector3::operator/(const Vector3& parameter) const {
	return Vector3(*this) /= parameter;
}
Vector3 Vector3::operator/(const float& parameter) const {
	return Vector3(*this) /= parameter;
}

Vector3& Vector3::operator++() {
	return Set(x + 1.0f, y + 1.0f, z + 1.0f);
}
Vector3& Vector3::operator--() {
	return Set(x - 1.0f, y - 1.0f, z - 1.0f);
}

Vector3 Vector3::operator++(int) {
	Vector3 oldVector = Vector3(*this); // Save a copy
	Set(x + 1.0f, y + 1.0f, z + 1.0f); // Increment
	return oldVector; // Return old values
}
Vector3 Vector3::operator--(int) {
	Vector3 oldVector = Vector3(*this); // Save a copy
	Set(x - 1.0f, y - 1.0f, z - 1.0f); // Deincrement
	return oldVector; // Return old values
}

const Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}
const Vector3 Vector3::operator+() const {
	return (*this);
}

bool Vector3::operator==(const Vector3& parameter) const {
	return (x == parameter.x && y == parameter.y && z == parameter.z);
}
bool Vector3::operator==(const float& parameter) const {
	return Length() == parameter;
}

bool Vector3::operator!=(const Vector3& parameter) const {
	return !(*this == parameter);
}
bool Vector3::operator!=(const float& parameter) const {
	return !(*this == parameter);
}

bool Vector3::operator>(const Vector3& parameter) const {
	return Length() > parameter.Length();
}
bool Vector3::operator>(const float& parameter) const {
	return Length() > parameter;
}
bool Vector3::operator>=(const Vector3& parameter) const {
	return Length() >= parameter.Length();
}
bool Vector3::operator>=(const float& parameter) const {
	return Length() >= parameter;
}

bool Vector3::operator<(const Vector3& parameter) const {
	return !(*this >= parameter);
}
bool Vector3::operator<(const float& parameter) const {
	return !(*this >= parameter);
}
bool Vector3::operator<=(const Vector3& parameter) const {
	return !(*this > parameter);
}
bool Vector3::operator<=(const float& parameter) const {
	return !(*this > parameter);
}

// Should this use a switch, because the compiler might be able to
// make it go faster? For now this works well.
float& Vector3::operator[](const size_t index) {
	return index == 0 ? x : index == 1 ? y : z;
}
const float& Vector3::operator[](const size_t index) const {
	return index == 0 ? x : index == 1 ? y : z;
}


Vector3& Vector3::Set(const float& all) {
	return Set(all, all, all);
}
Vector3& Vector3::Set(const float& inX, const float& inY, const float& inZ) {
	x = inX; y = inY; z = inZ;
	return *this;
}
Vector3& Vector3::Set(const float* array3) {
	return Set(array3[0], array3[1], array3[2]);
}
Vector3& Vector3::Set(const Vector3& parameter) {
	return this != &parameter ? Set(parameter.x, parameter.y, parameter.z) : *this;
}

void Vector3::Swap(Vector3& secondVector) {
	std::swap(x, secondVector.x);
	std::swap(y, secondVector.y);
	std::swap(z, secondVector.z);
}

Vector3& Vector3::SnapToGrid(const Vector3& gridSize) {
	return *this;//Set(UtilMath::Snap(x, gridSize.x), UtilMath::Snap(y, gridSize.y), UtilMath::Snap(z, gridSize.z));
}
Vector3& Vector3::SnapToGrid(const float& gridSize) {
	return *this;//Set(UtilMath::Snap(x, gridSize), UtilMath::Snap(y, gridSize), UtilMath::Snap(z, gridSize));
}

Vector3& Vector3::Normalize() {
	return (*this) /= Length();
}
Vector3 Vector3::Normal() const {
	return Vector3(*this).Normalize();
}

Vector3& Vector3::SetToCrossProduct(const Vector3& secondVector) {
	return Set((y * secondVector.z) - (z * secondVector.y), (z * secondVector.x) - (x * secondVector.z), (x * secondVector.y) - (y * secondVector.x));
}
Vector3 Vector3::CrossProduct(const Vector3& secondVector) const {
	return Vector3(*this).SetToCrossProduct(secondVector);
}

Vector3& Vector3::SetToReflect(const Vector3& normal) {
	return Set((*this) - (normal * 2.0f * DotProduct(normal)));
}
Vector3 Vector3::Reflect(const Vector3& normal) const {
	return Vector3(*this).SetToReflect(normal);
}

Vector3& Vector3::Negate() {
	return Set(-x, -y, -z);
}
Vector3 Vector3::Negative() const {
	return -(*this);
}

Vector3& Vector3::SetToLerp(const Vector3& parameter, const float& delta) {
	return Set(x + ((parameter.x - x) * delta), y + ((parameter.y - y) * delta), z + ((parameter.z - z) * delta));
}
Vector3 Vector3::Lerp(const Vector3& parameter, const float& delta) const {
	return Vector3(*this).SetToLerp(parameter, delta);
}

Vector3& Vector3::SetToPerpendicular2D() {
	return z > 0.0f ? Set(-z, y, x) : Set(z, y, -x);
}
Vector3 Vector3::Perpendicular2D() const {
	return Vector3(*this).SetToPerpendicular2D();
}

Vector3& Vector3::SetToAngleAxis() {
	if (*this == ONEY)
		return Set(ONEY);
	if (*this == NONEY)
		return Set(NONEZ);
	return SetToCrossProduct(ONEY).Normalize();
}
Vector3& Vector3::SetToPerpendicular() {
	return SetToAngleAxis();
}
Vector3 Vector3::AngleAxis() const {
	return Vector3(*this).SetToAngleAxis();
}
Vector3 Vector3::Perpendicular() const {
	return AngleAxis();
}

Vector3& Vector3::SetToAbsolute() {
	return Set(fabs(x), fabs(y), fabs(z));
}
Vector3 Vector3::Absolute() const {
	return Vector3(*this).SetToAbsolute();
}

// Basicly just find the average of the components
Vector3 Vector3::MidPoint(const Vector3& secondPoint) const {
	return Vector3((secondPoint + (*this)) / 2.0f);
}

Vector3& Vector3::SetFloor(const Vector3& minVec) {
	return Set(x < minVec.x ? minVec.x : x, y < minVec.y ? minVec.y : y, z < minVec.z ? minVec.z : z);
}
Vector3& Vector3::SetCeil(const Vector3& maxVec) {
	return Set(x > maxVec.x ? maxVec.x : x, y > maxVec.y ? maxVec.y : y, z > maxVec.z ? maxVec.z : z);
}

Vector3& Vector3::SetToLambdaExp(const std::function<float (const float&)>& lambda) {
	return Set(lambda(x), lambda(y), lambda(z));
}
Vector3 Vector3::LambdaExp(const std::function<float (const float&)>& lambda) const {
	return Vector3(*this).SetToLambdaExp(lambda);
}

float Vector3::DotProduct(const Vector3& secondVector) const {
	return (x * secondVector.x) + (y * secondVector.y) + (z * secondVector.z);
}

float Vector3::AbsDotProduct(const Vector3& secondVector) const {
	return fabs(x * secondVector.x) + fabs(y * secondVector.y) + fabs(z * secondVector.z);
}

float Vector3::GetAngle() const {
	return -acos(Vector3(*this).Normalize().DotProduct(Vector3::ONEY));
}

float Vector3::LengthSquared() const {
	return (x * x) + (y * y) + (z * z);
}
float Vector3::Length() const {
	return sqrt(LengthSquared());
}

float Vector3::Distance(const Vector3& secondVector) const {
	return ((*this) - secondVector).Length();
}

float Vector3::AngleToTarget(const Vector3& aimVector, const Vector3& targetPos) {
	return acos(Vector3(aimVector).Normalize().DotProduct((targetPos - (*this)).Normalize()));
}

float* Vector3::GetArray() {
	float arr[3];
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
	return arr;
}