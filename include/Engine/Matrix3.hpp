#pragma once
#include <memory>
#include <Engine/Export.hpp>

class GE2DX_ENGINE_API Matrix3
{
public:
	Matrix3(int _row, int _column);
	~Matrix3();

	float GetValue(int x, int y) const;
	void SetValue(int x, int y, float value);

	void MultiplyRow(int _row, int _scalaire);
	void MultiplyColumn(int _column, int _scalaire);

	static Matrix3 Identity(int _size);
	static Matrix3 RemoveRow(const Matrix3& _matrix, int _rowIndex);
	static Matrix3 RemoveColumn(const Matrix3& _matrix, int _columnIndex);
	static float Determinant(const Matrix3& _matrix);


private:
	float** mat;

	int nbRows, nbColumns;
};