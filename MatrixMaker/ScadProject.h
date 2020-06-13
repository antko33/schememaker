#pragma once
class ScadProject
{
public:
	/// <param name="fileName">
	/// Project file name
	/// </param>
	ScadProject(LPCSTR fileName);

	/// <summary>
	/// Sets the bed coeffs of the specified elements to 0
	/// </summary>
	/// <param name="qntElem">
	/// Quantity of elements to modify
	/// </param>
	/// <param name="listElem">
	/// List of modified elements
	/// </param>
	UINT SetZeroBed(UINT qntElem, const UINT* listElem);

	/// <summary>
	/// Saves the project to specified file and releases API
	/// </summary>
	/// <param name="qntElem">
	/// Name of result file
	/// </param>
	APICode SaveAndClose(LPCSTR fileName);

private:
	static const byte TYPE = 'I';

	ScadAPI handle;
};

