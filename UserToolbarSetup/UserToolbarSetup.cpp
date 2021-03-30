#include "UserToolbarSetup.h"
#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif
#include <cstdio>
#include <algorithm>
#include <filesystem>
#include <string>

#ifndef _MSC_VER
#include <cstring>
#endif

#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif 

#ifndef _countof
#define _countof(m) (sizeof(m) / sizeof / m[0]))
#endif

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {

    char cpath[_MAX_PATH] = {0};
    char startstring[] = "***START***\nLM_SPACER\n***END***\n***START***\n\"";
    char endstring[] = "\" -lm-handle \"%9\" \"%1\"\n0, Runs Pixi on the rom, reloads it after.\n***END**";
    constexpr int tot_len = 45 + _MAX_PATH + 74 + 1; // strlen(startstring) + MAX_PATH + strlen(endstring) + \0
    char totalstring[tot_len] = {0};
    printf("Drag and drop Lunar Magic's executable here:\n");
    gets_s(cpath, (unsigned)_countof(cpath));
    if (cpath[0] == '"' && cpath[strlen(cpath) - 1] == '"') {
        cpath[strlen(cpath) - 1] = '\0';
        memmove(cpath, cpath + 1, strlen(cpath) + 1);
    }
    fs::path lmpath(cpath);
    if (lmpath.is_relative() || lmpath.extension() == "") {
        Error("Path wasn't correct. Path was:", lmpath);
    }

    std::string strPath = lmpath.parent_path().generic_string() + "/usertoolbar.txt";

    FILE *out = nullptr;
    auto err = fopen_s(&out, strPath.c_str(), "w");

    if (err != 0 || out == nullptr) {
        Error("Couldn\'t open file ", strPath.c_str());
    }

    std::vector<fs::directory_entry> dires{};
    for (const auto &de : fs::directory_iterator(fs::current_path())) {
        if (de.is_regular_file() && de.exists()) {
            dires.emplace_back(de);
        }
    }

    auto res = std::find_if(dires.begin(), dires.end(), [](const fs::directory_entry &de) {
        const auto &p = de.path();
        return p.filename() == "pixi.exe";
    });

    if (res == dires.end()) {
        Error("Couldn't find pixi's executable in the current folder");
    }

    fs::path pixiPath = *res;

    std::string strpixiPath = fs::absolute(pixiPath).generic_string();

    char cstrpixiPath[_MAX_PATH];
    err = strcpy_s(cstrpixiPath, _MAX_PATH, strpixiPath.c_str());

    if (err != 0) {
        Error("Error while copying path");
    }

    int ret = sprintf_s(totalstring, "%s%s%s", startstring, cstrpixiPath, endstring);

    totalstring[tot_len - 1] = '\0';

#pragma warning(disable : 6387)

    fprintf(out, "%s", totalstring);

    fclose(out);

    puts("usertoolbar.txt created successfully in your Lunar Magic folder!");
    ret = getchar();
    return 0;
}
