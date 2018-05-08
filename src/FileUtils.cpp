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

/*
 *
 */
void removeFile(const std::string& fileName){
	/*get fileName from fileDir */
	rmTree(TMPDIR);
	return;

	std::string name = "";
	for (int i = fileName.length() - 1; i >= 0; --i)
		if (fileName[i] != '/')
			name = fileName[i] + name;
		else
			break;

	std::string filePath = std::string(TMPDIR) + "/" + name;
	if (exists(filePath))
		remove(filePath.c_str());

	filePath =  std::string(TMPDIR) + "/w_l_" + name;
	if (exists(filePath))
		remove(filePath.c_str());

	filePath =  std::string(TMPDIR) + "/converted_" + name;
	if (exists(filePath))
		remove(filePath.c_str());
}

/*
 *
 */
void rmTree(const char path[]){
    size_t path_len;
    char *full_path;
    DIR *dir;
    struct stat stat_path, stat_entry;
    struct dirent *entry;

    // stat for the path
    stat(path, &stat_path);

    // if path does not exists or is not dir - exit with status -1
    if (S_ISDIR(stat_path.st_mode) == 0) {
        fprintf(stderr, "%s: %s\n", "Is not directory", path);
        exit(-1);
    }

    // if not possible to read the directory for this user
    if ((dir = opendir(path)) == NULL) {
        fprintf(stderr, "%s: %s\n", "Can`t open directory", path);
        exit(-1);
    }

    // the length of the path
    path_len = strlen(path);

    // iteration through entries in the directory
    while ((entry = readdir(dir)) != NULL) {

        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        // determinate a full path of an entry
        full_path = (char *)calloc(path_len + strlen(entry->d_name) + 1, sizeof(char));
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, entry->d_name);

        // stat for the entry
        stat(full_path, &stat_entry);

        // recursively remove a nested directory
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            rmTree(full_path);
            continue;
        }

        // remove a file object
        unlink(full_path);
    }

    // remove the devastated directory and close the object of it
    rmdir(path);
    closedir(dir);
}

void removeLog(){
	if (exists(LOGFILE))
		remove(LOGFILE);
	if (exists(LOGAXIOMFILE))
		remove(LOGAXIOMFILE);
}



