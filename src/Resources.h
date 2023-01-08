#pragma once

#include <string>

using std::string;

class Resources {
    //TODO: No idea why I can't declare a static string&...
    //TODO: No idea why this static string causes tons of linker errors when I don't RE-define it in Resources.cpp...
    private:
        static string resourcesFolderPath;

    public:
        static void initialize(const string& exeFilePath);
        inline static string getResourcesFolderPath() { return resourcesFolderPath; }

        //TODO: UNIT TEST!
        static const string getRelativeResourcesPath(const string& filePath);
        static const string getAbsoluteResourcesPath(const string& filePath);
    private:
        Resources();
};
