#include "stdafx.h"

std::string GetFilename(const std::string& path)
{
	int lastPos = path.find_last_of('\\');
	std::string filename = path.substr(lastPos + 1);
	return filename;
}

std::string GetFileNameWithoutExtension(const std::string& path)
{
	std::string filename = GetFilename(path);
	int lastPos = filename.find_last_of('.');
	filename = filename.substr(0, lastPos);
	return filename;
}

std::string GetExtension(const std::string& path)
{
	std::string filename = GetFilename(path);
	int lastPos = filename.find_last_of('.');
	std::string ext = filename.substr(lastPos + 1);
	return ext;
}

std::string Combine(std::string dir, std::string name)
{
	return dir.append("\\").append(name);
}