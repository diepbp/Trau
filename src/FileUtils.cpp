/*
 * MakeDir.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: diepbp
 */
#include "FileUtils.h"

bool isDirExist(const std::string& path)
{
#if defined(_WIN32)
    struct _stat info;
    if (_stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & _S_IFDIR) != 0;
#else
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
#endif
}

bool makePath(const std::string& path)
{
#if defined(_WIN32)
    int ret = _mkdir(path.c_str());
#else
    mode_t mode = 0755;
    int ret = mkdir(path.c_str(), mode);
#endif
    if (ret == 0)
        return true;

    switch (errno)
    {
    case ENOENT:
        // parent didn't exist, try to create it
        {
        	std::size_t pos = path.find_last_of('/');
            if (pos == std::string::npos)
#if defined(_WIN32)
                pos = path.find_last_of('\\');
            if (pos == std::string::npos)
#endif
                return false;
            if (!makePath( path.substr(0, pos) ))
                return false;
        }
        // now, try to create again
#if defined(_WIN32)
        return 0 == _mkdir(path.c_str());
#else
        return 0 == mkdir(path.c_str(), mode);
#endif

    case EEXIST:
        // done!
        return isDirExist(path);

    default:
        return false;
    }
}

inline bool exists(const std::string& name){
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void removeFile(const std::string& fileName){
	/*get fileName from fileDir */
	std::string name = "";
	for (int i = fileName.length() - 1; i >= 0; --i)
		if (fileName[i] != '/')
			name = fileName[i] + name;
		else
			break;

	std::string filePath = "/tmp/fat_str_convert/" + name;
	if (exists(filePath))
		remove(filePath.c_str());

	filePath = "/tmp/fat_str_convert/w_l_" + name;
	if (exists(filePath))
		remove(filePath.c_str());

	filePath = "/tmp/fat_str_convert/converted_" + name;
	if (exists(filePath))
		remove(filePath.c_str());
}

void removeLog(){
	if (exists(LOGFILE))
		remove(LOGFILE);
	if (exists(LOGAXIOMFILE))
		remove(LOGAXIOMFILE);
}



