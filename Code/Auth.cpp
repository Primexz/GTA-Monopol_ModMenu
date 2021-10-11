//#pragma once
//#include "HTTPRequest.hpp"
//#include "sha512.hh"
//#include <string>
//#include <xstring>
//#include <tchar.h>
//#include "Encryptor.h"
//using std::string;
//
//
//
//
//
//
//
//
//
//
//
//
//
//unsigned char* GetBytes(unsigned long long obj) {
//    unsigned char ret[8];
//
//
//    for (int i = 0; i < 8; i++)
//        ret[i] = obj >> (i * 8);
//
//    return ret;
//}
//
//bool VerifyChecksum(unsigned int reference, std::string str) {
//    unsigned long long res = std::stoull(str);
//
//    unsigned char randomByte[4];
//    unsigned char intBytes[4];
//
//    if (str == "0")
//    {
//        return false;
//    }
//
//    for (int i = 0; i < 4; i++) {
//        unsigned char int1 = res >> (i * 8);
//        unsigned char int2 = res >> ((i + 4) * 8);
//
//        if (i % 2 == 0) {
//            randomByte[i] = int1;
//            intBytes[i] = int2;
//        }
//        else {
//            intBytes[i] = int1;
//            randomByte[i] = int2;
//        }
//    }
//
//    unsigned char* bytes = GetBytes(reference);
//
//    for (int i = 0; i < 4; i++) {
//        if (bytes[randomByte[i] - 1] != intBytes[i])
//            return false;
//    }
//
//    return true;
//}
//
//unsigned int GetRandomUInt() {
//    srand((unsigned)time(0));
//    return (rand() % 82347987 * (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987) + (rand() % 82347987));
//}
//
//bool IsNumber(const std::string& s)
//{
//    std::locale loc;
//    std::string::const_iterator it = s.begin();
//    while (it != s.end() && std::isdigit(*it, loc)) ++it;
//    return !s.empty() && it == s.end();
//}
//
//
//
//
//bool have_user_perms(std::string username, std::string password)
//{
//    char hwid[4096];
//    //total physical memory
//    MEMORYSTATUSEX statex;
//    statex.dwLength = sizeof(statex);
//    GlobalMemoryStatusEx(&statex);
//    sprintf_s(hwid, "%I64i", statex.ullTotalPhys / 1024);
//
//    // volume information
//    TCHAR volumename[MAX_PATH + 1] = { 0 };
//    TCHAR filesystemname[MAX_PATH + 1] = { 0 };
//    DWORD serialnumber = 0, maxcomponentlen = 0, filesystemflags = 0;
//    GetVolumeInformation(_T("C:\\"), volumename, ARRAYSIZE(volumename), &serialnumber, &maxcomponentlen, &filesystemflags, filesystemname, ARRAYSIZE(filesystemname));
//    sprintf_s(hwid, "%s%li%ws%li", hwid, serialnumber, filesystemname, maxcomponentlen);
//
//    // computer name
//    TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
//    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
//    GetComputerName(computerName, &size);
//    sprintf_s(hwid, "%s%ws", hwid, computerName);
//
//
//
//
//    int referencidouhsfgiuhpzrizudfgfgdhpoiodzuhfgpfgfgdzuhoiuhoizuhddfgoize = GetRandomUInt();
//
//
//    std::string reeeeeee = std::to_string(referencidouhsfgiuhpzrizudfgfgdhpoiodzuhfgpfgfgdzuhoiuhoizuhddfgoize);
//
//
//    auto url = skCrypt("darkcheats.company/Auth/DarkCheatsAuth/MenuAuth/auth.php");
//    http::Request request(url.decrypt());
//
//
//    std::map<std::string, std::string> parameters = { {"username", username.c_str()}, {"password", password.c_str()}, {"hwid", (sw::sha512::calculate(hwid).c_str())}, {"reference", reeeeeee.c_str()} };
//
//
//    const http::Response response = request.send("POST", parameters, {
//    "Content-Type: application/x-www-form-urlencoded"
//        });
//
//
//    std::string cString(response.body.begin(), response.body.end());
//
//
//
//
//
//
//
//    if (IsNumber(cString))
//    {
//        if (VerifyChecksum(referencidouhsfgiuhpzrizudfgfgdhpoiodzuhfgpfgfgdzuhoiuhoizuhddfgoize, cString.c_str())) {
//
//            return true;
//        }
//        else {
//
//
//
//        }
//    }
//    else
//    {
//
//    }
//    return false;
//
//
//
//
//}
//
//
//
//
//
