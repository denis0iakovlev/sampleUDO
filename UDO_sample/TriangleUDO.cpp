#include "TriangleUDO.h"
using namespace std;
using namespace NXOpen;
using namespace NXOpen::Features;

TriangleUDO::TriangleUDO()
{
	UF_initialize();//������������� ������� C �������
	this->theSession = Session::GetSession();
	this->theUI = UI::GetUI(); 
}

int TriangleUDO::iniUDO()
{
	return 0;
}
