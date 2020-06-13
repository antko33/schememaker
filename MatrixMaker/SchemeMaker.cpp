#include "stdafx.h"
#include "ScadProject.h"
#include "IniReader.h"

void Expand(std::vector<UINT>*, int);
void BordersInit(std::vector<UINT>*, int, int, int);

std::string GetFileNameWithoutExtension(const std::string&);
std::string GetExtension(const std::string&);
std::string Combine(std::string, std::string);

const std::string Delimeter = ",";
const std::string SettingsFileName = "settings.ini";
const std::string SectionName = "scheme";

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	INIReader ini(SettingsFileName);

	std::string title = ini.GetString(SectionName, "title", "");
	LPCSTR ProjectTitle = title.c_str();

	std::string workDir = ini.GetString(SectionName, "workdir", "");

	int SizeArr[2] = { 0, 0 };
	std::string sizeStr = ini.GetString(SectionName, "size", "");
	int qpos = 0;
	int qi = 0;
	std::string qtoken;
	while ((qpos = sizeStr.find(Delimeter)) != std::string::npos)
	{
		qtoken = sizeStr.substr(0, qpos);
		SizeArr[0] = atoi(qtoken.c_str());
		sizeStr.erase(0, qpos + Delimeter.length());
		qi++;
	}
	const char* qwerty = sizeStr.c_str();
	SizeArr[1] = atoi(qwerty);

	int BorderMax[4];
	std::string borderMaxStr = ini.GetString(SectionName, "border_max", "");
	size_t pos = 0;
	int i = 0;
	std::string token;
	while ((pos = borderMaxStr.find(Delimeter)) != std::string::npos)
	{
		token = borderMaxStr.substr(0, pos);
		BorderMax[i] = atoi(token.c_str());
		borderMaxStr.erase(0, pos + Delimeter.length());
		i++;
	}
	BorderMax[i] = atoi(borderMaxStr.c_str());

	int size, step;
	if (BorderMax[1] - BorderMax[0] == SizeArr[0])
	{
		size = SizeArr[0];
		step = (BorderMax[2] - BorderMax[0]) / SizeArr[1];
	}
	else if (BorderMax[1] - BorderMax[0] == SizeArr[1])
	{
		size = SizeArr[1];
		step = (BorderMax[2] - BorderMax[0]) / SizeArr[0];
	}
	else if (BorderMax[2] - BorderMax[0] == SizeArr[0])
	{
		size = SizeArr[0];
		step = (BorderMax[1] - BorderMax[0]) / SizeArr[1];
	}
	else if (BorderMax[2] - BorderMax[0] == SizeArr[1])
	{
		size = SizeArr[1];
		step = (BorderMax[1] - BorderMax[0]) / SizeArr[0];
	}

	std::vector<UINT> border;
	std::string fileName;
	BordersInit(&border, size, step, BorderMax[0]);
	int length = 0;

	do
	{
		std::ostringstream oss;
		oss << length;
		std::string origName = GetFileNameWithoutExtension(ProjectTitle);
		fileName = origName.append("_").append(oss.str()).append(".").append(GetExtension(ProjectTitle));
		std::cout << fileName.c_str() << " started..." << std::endl;

		ScadProject project(ProjectTitle);

		if (length != 0)
		{
			UINT* elemsArr = &border[0];
			project.SetZeroBed(border.size(), elemsArr);
			Expand(&border, step);
		}
		length += 2;

		std::string newPath = Combine(workDir, fileName);
		project.SaveAndClose(LPCSTR(newPath.c_str()));

		std::cout << fileName.c_str() << " done" << std::endl;
	} while (std::find(border.begin(), border.end(), BorderMax[0]) == border.end());

	std::cout << "Пожалуйста, проверьте, верна ли геометрия карстового провала в файле " << fileName.c_str() << std::endl;
	system("pause");

	return 0;
}