// CreateSquadOptions.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <windows.h>
#include <iostream>
#include <processthreadsapi.h>
#include <stdio.h>
#include "cJSON.h"
#pragma comment(lib,"cjson.lib") 
#pragma warning(disable:4996)
using namespace std;
int main()
{
    POINT MousePoint = { 0,0 };
    FILE* JSONFile = fopen("options.json", "w+");
    if (JSONFile == NULL) {
        cout << "ERROR OPEN!" << endl;
        ExitProcess(1);
    }
    cJSON* optionJSON = cJSON_CreateObject();
    cJSON* option = cJSON_CreateObject();
    cJSON_AddItemToObject(optionJSON, "options", option);

    cout << "请进入游戏，将鼠标放在游戏加载页面的右下角小人的背包身体中央然后按下ALT键！" << endl;
    while (1) {
        if (GetAsyncKeyState(VK_MENU) & 0x8000)break;
    }
    if (GetCursorPos(&MousePoint) == NULL)cout << "Error Code:" << GetLastError();
    cout << "Coordinate:" << "(" << MousePoint.x << "," << MousePoint.y << ")" << endl;
    cJSON_AddItemToObject(option, "x", cJSON_CreateNumber(MousePoint.x));
    cJSON_AddItemToObject(option, "y", cJSON_CreateNumber(MousePoint.y));
    cJSON_AddItemToObject(option, "mode", cJSON_CreateString("auto"));
    char* outputString = cJSON_Print(optionJSON);
    const byte fwnmemb = 1;
    if (fwrite(outputString, strlen(outputString), fwnmemb, JSONFile) != fwnmemb) {
        cout << "ERROR WIRTE!" << endl;
        cJSON_Delete(optionJSON);
        fclose(JSONFile);
        ExitProcess(1);
    }
    fclose(JSONFile);
    cJSON_Delete(optionJSON);
    cout << "succeed";

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
