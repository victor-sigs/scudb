#include <memory>
#include <stdexcept>
#include <vector>
#include "p0_starter.cpp"
#include <iostream>
using namespace std;

//测试各函数功能
void test()
{
	//测试Matrix的基本构造与修改
	cout << "-----Testing Matrix-----" << endl;
	RowMatrix<int> test(4, 4);
	vector<int> src(16, 3);

	cout << "FillFrom Test:" << endl;
	test.FillFrom(src);
	cout << "Row number: " << test.GetRowCount() << endl;
	cout << "Column number: " << test.GetColumnCount() << endl;
	cout << "Elem(3,3) = " << test.GetElement(3, 3) << endl;
	cout << "SetElement Test:" << endl;
	test.SetElement(3, 3, 7);
	cout << "Elem(3,3) = " << test.GetElement(3, 3) << endl;

	//测试Matrix的加、减、乘法后加法运算
	RowMatrix<int> A(2, 2);
	vector<int> srcA(4, 2);
	A.FillFrom(srcA);

	RowMatrix<int> B(2, 2);
	vector<int> srcB(4, 3);
	B.FillFrom(srcB);

	RowMatrixOperations<int> oprt;
	int ans;

	cout << "-----Matrix for testing-----" << endl;
	cout << "A:" << endl;
	for (int i = 0; i < A.GetRowCount(); i++) {
		for (int j = 0; j < A.GetColumnCount(); j++) {
			cout << A.GetElement(i, j) << " ";
		}
		cout << endl;
	}

	cout << "B:" << endl;
	for (int i = 0; i < B.GetRowCount(); i++) {
		for (int j = 0; j < B.GetColumnCount(); j++) {
			cout << B.GetElement(i, j) << " ";
		}
		cout << endl;
	}

	cout << "-----Testing Operations(Add)-----" << endl;
	std::unique_ptr<RowMatrix<int>> AaddB = oprt.Add(&A, &B);
	cout << "Add result:" << endl;
	
	for (int i = 0; i < AaddB->GetRowCount(); i++)
	{
		for (int j = 0; j < AaddB->GetColumnCount(); j++)
		{
			ans = AaddB->GetElement(i, j);
			cout << ans << " ";
		}
		cout << endl;
	}

	cout << "-----Testing Operations(Multiply)-----" << endl;
	std::unique_ptr<RowMatrix<int>> AmulB = oprt.Multiply(&A, &B);
	cout << "Multiply result:" << endl;

	for (int i = 0; i < AmulB->GetRowCount(); i++)
	{
		for (int j = 0; j < AmulB->GetColumnCount(); j++)
		{
			ans = AmulB->GetElement(i, j);
			cout << ans << " ";
		}
		cout << endl;
	}

	cout << "-----Testing Operations(GEMM)-----" << endl;
	std::unique_ptr<RowMatrix<int>> AgemmB = oprt.GEMM(&A, &B, &A);
	cout << "GEMM result:" << endl;

	for (int i = 0; i < AgemmB->GetRowCount(); i++)
	{
		for (int j = 0; j < AgemmB->GetColumnCount(); j++)
		{
			ans = AgemmB->GetElement(i, j);
			cout << ans << " ";
		}
		cout << endl;
	}
}

int main()
{
	test();

	return 0;
}