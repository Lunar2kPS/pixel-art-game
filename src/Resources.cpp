#include "Resources.h"

string Resources::resourcesFolderPath;

//NOTE: Huge thanks to https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
static void replaceAll(string& source, const string& from, const string& to) {
    string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    size_t lastPos = 0;
    size_t findPos;

    while((findPos = source.find(from, lastPos)) != std::string::npos) {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString.append(source, lastPos, source.length() - lastPos);
    source.swap(newString);
}

void Resources::initialize(const string& exeFilePath) {
    //TODO: Currently have no idea how to properly deal with strings here efficiently... so...
    string copy = exeFilePath;
    replaceAll(copy, "\\", "/");
    const string& forwardFilePath = copy;

    size_t indexOfLastFolderSeparator = forwardFilePath.find_last_of("/");

    resourcesFolderPath = forwardFilePath.substr(0, indexOfLastFolderSeparator) + "/resources";
    printf("Resources folder path = %s\n", resourcesFolderPath.c_str());
}

const string Resources::getRelativeResourcesPath(const string& filePath) {
    if (filePath.find("resources/") == 0)
        return filePath.substr(10);
    if (filePath.find(resourcesFolderPath) != string::npos)
        return filePath.substr(resourcesFolderPath.length());
    return filePath;
}

const string Resources::getAbsoluteResourcesPath(const string& filePath) {
    if (filePath.find("resources/") == 0)
        return resourcesFolderPath.substr(0, resourcesFolderPath.length() - 10) + "/" + filePath;
    if (filePath.find(resourcesFolderPath) == string::npos)
        return resourcesFolderPath + "/" + filePath;
    return filePath;
}