#include <iostream>
#include <stdlib.h>
#include <map>

using namespace std;

struct NumBit
{
public:
/*	a	b	c	d	e	f	g
	0	1	2	3	4	5	6
*/
	bool bit[7] = { false };
	int getTureCount();
	NumBit operator++(int);
};

int NumBit::getTureCount()
{
	int trueCount = 0;
	for (int i = 0; i < 7; i++)
	{
		trueCount += bit[i];
	}
	return trueCount;
}

struct Linker
{
public:
	map<int, int*>_linker;
	Linker()
	{
		_linker.insert(pair<int, int*>(0, new int[] { 1, 5 }));
		_linker.insert(pair<int, int*>(1, new int[] { 0, 2, 6 }));
		_linker.insert(pair<int, int*>(2, new int[] { 1, 3, 6 }));
		_linker.insert(pair<int, int*>(3, new int[] { 2, 4 }));
		_linker.insert(pair<int, int*>(4, new int[] { 3, 5, 6 }));
		_linker.insert(pair<int, int*>(5, new int[] { 0, 4, 6 }));
		_linker.insert(pair<int, int*>(6, new int[] { 1, 2, 4, 5 }));
	}
};

NumBit NumBit::operator++(int)
{
	for (int i = 0; i < 7; i++)
	{
		if (!this->bit[i])
		{
			this->bit[i] = !this->bit[i];
			return *this;
		}
		else
		{
			this->bit[i] = !this->bit[i];
		}
	}
	return *this;
}

ostream& operator << (ostream& outStream, NumBit& numbit)
{
	//	¡ö¡õ	matrix[y][x]	matrix[9][5]	

	int Y = 9, X = 5;

	bool** matrix;
	matrix = new bool* [Y];
	for (int iy = 0; iy < Y; iy++) 
	{
		matrix[iy] = new bool[X] {false};
	}

#pragma region matrix

	//a
	matrix[0][1] = numbit.bit[0];
	matrix[0][2] = numbit.bit[0];
	matrix[0][3] = numbit.bit[0];

	//b
	matrix[1][4] = numbit.bit[1];
	matrix[2][4] = numbit.bit[1];
	matrix[3][4] = numbit.bit[1];

	//c
	matrix[5][4] = numbit.bit[2];
	matrix[6][4] = numbit.bit[2];
	matrix[7][4] = numbit.bit[2];

	//d
	matrix[8][1] = numbit.bit[3];
	matrix[8][2] = numbit.bit[3];
	matrix[8][3] = numbit.bit[3];

	//e
	matrix[5][0] = numbit.bit[4];
	matrix[6][0] = numbit.bit[4];
	matrix[7][0] = numbit.bit[4];

	//f
	matrix[1][0] = numbit.bit[5];
	matrix[2][0] = numbit.bit[5];
	matrix[3][0] = numbit.bit[5];

	//g
	matrix[4][1] = numbit.bit[6];
	matrix[4][2] = numbit.bit[6];
	matrix[4][3] = numbit.bit[6];

#pragma endregion	

	for (int iy = 0; iy < Y; iy++)
	{
		for (int ix = 0; ix < X; ix++)
		{
			switch (matrix[iy][ix])
			{
			case true:
				outStream << "¡ö";
				break;
			case false:
				outStream << "¡õ";
				break;
			}
		}
		outStream << endl;
	}

	// ÊÍ·Å
	for (int iy = 0; iy < Y; iy++)
	{
		delete[] matrix[iy];
	}
	delete[] matrix;

	return outStream;
}

void searcher(NumBit& numbit, Linker& linker, int loc)
{
	numbit.bit[loc] = false;
	for (int i = 0;
		i < _msize(linker._linker[loc]) / sizeof(linker._linker[loc][0]);
		i++)
	{
		if (numbit.bit[linker._linker[loc][i]])
		{
			searcher(numbit, linker, linker._linker[loc][i]);
		}
	}
	return;
}

bool numBitIsRight(NumBit& numbit, Linker& linker)
{
	NumBit numBitTemp = numbit;
	switch (numBitTemp.getTureCount())
	{
	case 0:
		return false;
		break;
	case 1:
		return true;
		break;
	default:
		for (int i = 0; i < 7; i++)
		{
			if (numBitTemp.bit[i])
			{
				searcher(numBitTemp, linker, i);
				break;
			}
		}
		return !numBitTemp.getTureCount();
		break;
	}
}

int main()
{
	NumBit numbit;
	Linker linker;
	int rightCount = 0;
	bool isRight;

	for (int i = 0; i < 128; i++, numbit++)
	{
		isRight = numBitIsRight(numbit, linker);
		cout << numbit << "\t" << (isRight ? "it's right" : "it's not right") << endl;
		cout << "======================" << endl;
		if (isRight) 
		{ 
			rightCount++; 
		}
	}

	cout << "result all right = " << rightCount << endl;
	cout << "======================" << endl;

	system("pause");
	return 0;
}