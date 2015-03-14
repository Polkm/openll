#include "MatrixN.h"

#include "Vector3.h"

#include <string>

MatrixN::MatrixN(const unsigned char newRows, const unsigned char newColumns) :
	rows(newRows), columns(newColumns), size(newRows * newColumns), byteSize(sizeof(float) * size) {
	m = new float[size];
	Identity();
}
MatrixN::MatrixN(const MatrixN& m2) :
	rows(m2.GetRows()), columns(m2.GetColumns()), size(m2.GetRows() * m2.GetColumns()), byteSize(sizeof(float) * size) {
	m = new float[size];
	Set(m2);
}
MatrixN::~MatrixN() {
	if (m != nullptr) {
		delete [] m;
		m = nullptr;
	}
}

MatrixN& MatrixN::operator=(const MatrixN& m2) {
	return Set(m2);
}

MatrixN& MatrixN::operator+=(const MatrixN& m2) {
	if (m2.GetRows() == rows && m2.GetColumns() == columns)
		for (unsigned char i = 0; i < size; ++i)
			m[i] += m2[i];
	return *this;
}

MatrixN& MatrixN::operator-=(const MatrixN& m2) {
	if (m2.GetRows() == rows && m2.GetColumns() == columns)
		for (unsigned char i = 0; i < size; ++i)
			m[i] -= m2[i];
	return *this;
}

float& MatrixN::operator[](const size_t index) {
	if (index >= size)
		return m[size - 1];
	else
		return m[index];
}
const float MatrixN::operator[](const size_t index) const {
	if (index >= size)
		return m[size - 1];
	else
		return m[index];
}

MatrixN& MatrixN::Clear() {
	return Set();
}
MatrixN& MatrixN::Set(const float all) {
	for (unsigned char i = 0; i < size; ++i)
		m[i] = all;
	return *this;
}
MatrixN& MatrixN::Set(const float* ary) {
	memcpy(m, ary, sizeof(float) * size);
	return *this;
}
MatrixN& MatrixN::Set(const MatrixN& m2) {
	if (&m2 != this && m2.GetRows() == rows && m2.GetColumns() == columns)
		memcpy(m, m2.Get(), sizeof(float) * size);
	return *this;
}

MatrixN& MatrixN::SetRow(const unsigned char row, const Vector3& newRow) {
	m[row] = newRow.x;
	m[row + 4] = newRow.y;
	m[row + 8] = newRow.z;
	return *this;
}
Vector3 MatrixN::GetRow(const size_t row) const {
	return Vector3(m[row], m[row + 4], m[row + 8]); 
}

const float* MatrixN::Get() const {
	return m;
}
unsigned char MatrixN::GetRows() const {
	return rows;
}
unsigned char MatrixN::GetColumns() const {
	return columns;
}
unsigned char MatrixN::GetSize() const {
	return size;
}

MatrixN& MatrixN::Identity(const float squareVals) {
	memset(m, 0, sizeof(float) * size);
	unsigned char diagonalElements = ((size - 1) / (columns + 1)) + 1;
	for (unsigned char i = 0; i < diagonalElements; ++i)
		m[i * (columns + 1)] = squareVals;
	return *this;
}

MatrixN& MatrixN::Translate(const Vector3& vec) {
	// Must be a 4x4 for this to even remotely make sense.
	if (rows != 4 || columns != 4) return *this;

	Vector3 m0 = GetRow(0);
	Vector3 m1 = GetRow(1);
	Vector3 m2 = GetRow(2);
	Vector3 m3 = GetRow(3);

	SetRow(3, m0 * vec.x + m1 * vec.y + m2 * vec.z + m3);

	return *this;
}

MatrixN& MatrixN::Rotate(const float angle, const Vector3& vec) {
	// Must be a 4x4 for this to even remotely make sense.
	if (rows != 4 || columns != 4) return *this;

	float a = angle * (3.1415926f / 180.0f);
	float c = cos(a);
	float s = sin(a);
	Vector3 axis = Vector3(vec).Normalize();
	Vector3 temp = axis * (1.0f - c);
	MatrixN rot(rows, columns);

	rot[0] = c + temp[0] * axis[0];
	rot[4] = 0 + temp[0] * axis[1] + s * axis[2];
	rot[8] = 0 + temp[0] * axis[2] - s * axis[1];

	rot[1] = 0 + temp[1] * axis[0] - s * axis[2];
	rot[5] = c + temp[1] * axis[1];
	rot[9] = 0 + temp[1] * axis[2] + s * axis[0];

	rot[2] = 0 + temp[2] * axis[0] + s * axis[1];
	rot[6] = 0 + temp[2] * axis[1] - s * axis[0];
	rot[10] = c + temp[2] * axis[2];

	Vector3 m0 = GetRow(0);
	Vector3 m1 = GetRow(1);
	Vector3 m2 = GetRow(2);

	SetRow(0, m0 * rot[0] + m1 * rot[4] + m2 * rot[8]);
	SetRow(1, m0 * rot[1] + m1 * rot[5] + m2 * rot[9]);
	SetRow(2, m0 * rot[2] + m1 * rot[6] + m2 * rot[10]);

	return *this;
}

MatrixN& MatrixN::Scale(const Vector3& scale) {
	// Must be a 4x4 for this to even remotely make sense.
	if (rows != 4 || columns != 4) return *this;

	m[0] *= scale.x;
	m[5] *= scale.y;
	m[10] *= scale.z;

	return *this;
}

MatrixN& MatrixN::Scale(const float scale) {
	// Must be square for this to even remotely make sense.
	if (rows != columns) return *this;

	// Scale the diangonal
	for (unsigned char i = 0; i < columns - 1; ++i)
		m[i + (columns + 1)] *= scale;

	return *this;
}

MatrixN& MatrixN::Perspective(const float fovy, const float aspect, const float near, const float far) {
	// Must be a 4x4 for this to even remotely make sense.
	if (rows != 4 || columns != 4) return *this;

	float range = tan((fovy / 2.0f) * (3.1415926f / 180.0f)) * near;
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;

	Identity();
	m[0] = near / right;
	m[5] = near / top;
	m[10] = -(far + near) / (far - near);
	m[11] = -1.0f;
	m[14] = -(2.0f * far * near) / (far - near);
	m[15] = 0.0f;

	return *this;
}

MatrixN& MatrixN::LookAt(const Vector3& eye, const Vector3& focus, const Vector3& up) {
	Vector3 f = (focus - eye).Normalize();
	Vector3 s = Vector3(f).SetToCrossProduct(Vector3(up).Normalize()).Normalize();
	Vector3 u = Vector3(s).SetToCrossProduct(f);

	Identity();
	m[0] = s.x;
	m[4] = s.y;
	m[8] = s.z;

	m[1] = u.x;
	m[5] = u.y;
	m[9] = u.z;

	m[2] = -f.x;
	m[6] = -f.y;
	m[10] = -f.z;

	m[12] = -s.DotProduct(eye);
	m[13] = -u.DotProduct(eye);
	m[14] = f.DotProduct(eye);

	return *this;
}