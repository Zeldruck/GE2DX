#include <Engine/Matrix3.hpp>

Matrix3::Matrix3(int _row, int _column)
{
	nbRows = _row;
	nbColumns = _column;

	mat = new float* [_row];

	for (int i = 0; i < _row; i++)
	{
		mat[i] = new float[_column];
	}
}

Matrix3::~Matrix3()
{
	for (int i = 0; i < nbRows; i++)
		delete[] mat[i];

	delete[] mat;
}

float Matrix3::GetValue(int x, int y) const
{
	return mat[x][y];
}

void Matrix3::SetValue(int x, int y, float value)
{
	mat[x][y] = value;
}

void Matrix3::MultiplyRow(int _row, int _scalaire)
{
	if (_scalaire == 0 || _row < 0 || _row >= nbRows)
		return;

	for (int i = 0; i < nbColumns; i++)
	{
		mat[_row][i] *= _scalaire;
	}
}

void Matrix3::MultiplyColumn(int _column, int _scalaire)
{
	if (_scalaire == 0 || _column < 0 || _column >= nbColumns)
		return;

	for (int i = 0; i < nbRows; i++)
	{
		mat[i][_column] *= _scalaire;
	}
}

Matrix3 Matrix3::Identity(int _size)
{
	Matrix3 nMat(_size, _size);

	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (j == i)
				nMat.SetValue(i, j, 1.f);
			else
				nMat.SetValue(i, j, 0.f);
		}
	}

	return nMat;
}

Matrix3 Matrix3::RemoveRow(const Matrix3& _matrix, int _rowIndex)
{
	if (_rowIndex < 0 || _rowIndex >= _matrix.nbRows)
		return;

	Matrix3 nMat(_matrix.nbRows - 1, _matrix.nbColumns);

	int ad = 0;

	for (int i = 0; i < _matrix.nbRows; i++)
	{
		if (i == _rowIndex)
		{
			ad = 1;
			continue;
		}

		for (int j = 0; j < _matrix.nbColumns; j++)
		{
			nMat.SetValue(i - ad, j, _matrix.GetValue(i, j));
		}
	}

	return nMat;
}

Matrix3 Matrix3::RemoveColumn(const Matrix3& _matrix, int _columnIndex)
{
	if (_columnIndex < 0 || _columnIndex >= _matrix.nbRows)
		return;

	Matrix3 nMat(_matrix.nbRows, _matrix.nbColumns - 1);

	int ad = 0;

	for (int i = 0; i < _matrix.nbRows; i++)
	{
		for (int j = 0; j < _matrix.nbColumns; j++)
		{
			if (j == _columnIndex)
			{
				ad = 1;
				continue;
			}

			nMat.SetValue(i, j - ad, _matrix.GetValue(i, j));
		}

		ad = 0;
	}

	return nMat;
}

float Matrix3::Determinant(const Matrix3& _matrix)
{
	float result = 0.f;

	if (_matrix.nbColumns == 2)
	{
		result = _matrix.GetValue(0, 0) * _matrix.GetValue(1, 1) - _matrix.GetValue(1, 0) * _matrix.GetValue(0, 1);
		return result;
	}

	for (int i = 1; i < _matrix.nbColumns; i++)
	{
		Matrix3 nMat = _matrix.RemoveRow(_matrix, 0);

		float det = Determinant(nMat.RemoveColumn(nMat, i - 1));

		if (i % 2 == 0)
		{
			result -= det;
		}
		else
		{
			result += det;
		}
	}

	return result;
}
