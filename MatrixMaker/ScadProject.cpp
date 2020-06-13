#include "stdafx.h"
#include "ScadProject.h"

ScadProject::ScadProject(LPCSTR fileName)
{
	this->handle = NULL;
	APICode result;
	result = ApiCreate(&handle);
	if (result == APICode_OK)
	{
		ApiReadProject(handle, fileName);
	}
	else
	{
		throw result;
	}
}

UINT ScadProject::SetZeroBed(UINT qntElem, const UINT * listElem)
{
	double size[1] = { 0 };
	return ApiSetBed(handle, ApiGroupPlate, TYPE, 1, size, qntElem, listElem);
}

APICode ScadProject::SaveAndClose(LPCSTR fileName)
{
	APICode result;
	result = ApiWriteProject(handle, fileName);
	if (result == APICode_OK)
	{
		ApiRelease(&handle);
	}
	else
	{
		throw result;
	}
}
