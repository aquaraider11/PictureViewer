#include "stdafx.h"
namespace fs = std::experimental::filesystem;

bool isImage(std::string file)
{
	std::string imgType[]{ ".jpg", ".png" };
	std::transform(file.begin(), file.end(), file.begin(), ::tolower);

	for (std::string type : imgType)
		if (file.rfind(type) != std::string::npos)
			return true;

	return false;
}

std::vector<std::string> getDirectoryContents(std::string path)
{
	std::vector<std::string> list;

	for (auto & p : fs::directory_iterator(path))
	{
		std::cout << p << std::endl;
		std::string s = p.path().string();
		if (isImage(s))
			list.push_back(s);
	}

	return list;
}

std::string getDirectory(std::string file)
{
	std::size_t found = file.find_last_of("/\\");
	return file.substr(0, found);
}
