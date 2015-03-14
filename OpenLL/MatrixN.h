#ifndef __STRUCTURES_MATRIX_H__
#define __STRUCTURES_MATRIX_H__

class Vector3;

class MatrixN {
public:
	MatrixN(const unsigned char newRows = 4, const unsigned char newColumns = 4);
	MatrixN(const MatrixN& m2);
	~MatrixN();

	// Unairy arithmetic operators
	MatrixN& operator=(const MatrixN& m2);
	MatrixN& operator+=(const MatrixN& m2);
	MatrixN& operator-=(const MatrixN& m2);

	// Indexing operator
	float& operator[](const size_t index);
	const float operator[](const size_t index) const;

	// Seting functions
	MatrixN& Clear();
	MatrixN& Set(const float all = 0.0f);
	MatrixN& Set(const float* ary);
	MatrixN& Set(const MatrixN& m2);

	MatrixN& SetRow(const unsigned char row, const Vector3& newRow);
	Vector3 GetRow(const size_t row) const;

	// Getting functions
	const float* Get() const;
	unsigned char GetRows() const;
	unsigned char GetColumns() const;
	unsigned char GetSize() const;

	MatrixN& Identity(const float squareVals = 1.0f);

	// Translates the matrix by a vector3
	MatrixN& Translate(const Vector3& vec);

	// Rotate on a vector3
	MatrixN& Rotate(const float angle, const Vector3& axis);

	// Scale by a vector3 or a scalar
	MatrixN& Scale(const Vector3& scale);
	MatrixN& Scale(const float scale);

	MatrixN& Perspective(const float fovy, const float aspect, const float near, const float far);
	MatrixN& LookAt(const Vector3& eye, const Vector3& focus, const Vector3& up);


private:
	float* m;
	unsigned char rows, columns;
	unsigned char size, byteSize;
};

#endif