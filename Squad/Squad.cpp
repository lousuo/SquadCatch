//C++程序实现
//读取屏幕像素
#include <windows.h>
#include <iostream>
#include <processthreadsapi.h>
#include <stdio.h>
#include "cJSON.h"
#pragma comment(lib,"cjson.lib") 
#pragma warning(disable:4996)
//#pragma warning(disable:4996)

using namespace std;
void up(int vk)
{
    keybd_event(vk, 0, NULL, 0);
}
void down(int vk)
{
    keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
}
/*
void initSquadConsole(int times) { //The value of times should be between 1 and 2.
    //唤出控制台
    if (times == 1) {
        up(VK_OEM_3);
        down(VK_OEM_3);
    }else if (times == 2) {
        up(VK_OEM_3);
        down(VK_OEM_3);
        up(VK_OEM_3);
        down(VK_OEM_3);
    }else return;
}
*/
void inputSquadConsole(int times) {
    up(VK_OEM_3);
    down(VK_OEM_3);
    for (int i = 0; i <= times; i++) {
        up(VK_CONTROL);
        up(0x56);
        down(0x56);
        down(VK_CONTROL);
        up(VK_RETURN);
        down(VK_RETURN);
    }
}

BOOL ChangePriorityClass(int pClass) {
    HANDLE pHandle = GetCurrentProcess();
    return SetPriorityClass(pHandle, pClass);
    
}
//DWORD WINAPI Squad(LPVOID lp){

//}


int main(){
    HDC dng = GetDC(NULL);
    //提高进程优先级
    ChangePriorityClass(HIGH_PRIORITY_CLASS);

    cout << "抢队器--当你切换到游戏页面后按下Alt--可以重复使用" << endl << "请复制抢点代码，抢点代码例：CreateSquad ZCCRWS 1" << endl;
    //cout << "请进入游戏，将鼠标放在游戏加载页面的右下角小人的背包身体中央然后按下ALT键！" << endl;
    //while (1) {
    //    if (GetAsyncKeyState(VK_MENU) & 0x8000)break;
    //}
    //if (GetCursorPos(&MousePoint) == NULL)cout << "INIT Error Code:" << GetLastError();
    //cout << "Coordinate:" << "(" << MousePoint.x << "," << MousePoint.y << ")" << endl;
    //while (1) {
    //    if (GetAsyncKeyState(VK_MENU) & 0x1)break;
    //}
    char* readBuf = NULL;
    size_t fileSize;
    FILE* JSONFile = fopen("options.json", "r+");
    if (JSONFile == NULL) {
        cout << "ERROR OPEN!" << endl;
        ExitProcess(1);
    }
    if (fseek(JSONFile, 0, SEEK_END) != NULL) {
        cout << "ERROR SEEK!" << endl;
        fclose(JSONFile);
        ExitProcess(1);
    }
    fileSize = ftell(JSONFile);
    if (fileSize == -1L) {
        cout << "ERROR GET SIZE!" << endl;
        fclose(JSONFile);
        ExitProcess(1);
    }
    if (fileSize == 0) {
        cout << "OPTIONS.JSON IS EMPTY" << endl;
        fclose(JSONFile);
        ExitProcess(1);
    }
    fseek(JSONFile, 0, SEEK_SET);

    readBuf = (char*)calloc(fileSize, 1);
    if (readBuf == NULL) {
        cout << "ERROR CALLOC!" << endl;
        fclose(JSONFile);
        ExitProcess(1);
    }
    cout << readBuf;
    fread(readBuf, sizeof(char), fileSize, JSONFile);
    cJSON* optionJSON = cJSON_Parse(readBuf);//将JSON字符串转换成JSON结构体
    if (optionJSON == NULL) {						//判断转换是否成功
        printf("ERROR cJSON!\r\n");
        fclose(JSONFile);
        free(readBuf);
        ExitProcess(1);
    }
    cJSON* options = cJSON_GetObjectItem(optionJSON, "options");
    cJSON* xJSON = cJSON_GetObjectItem(options, "x");
    cJSON* yJSON = cJSON_GetObjectItem(options, "y");
    cJSON* modeJSON = cJSON_GetObjectItem(options, "mode");
    char* xChar = cJSON_Print(xJSON);
    char* yChar = cJSON_Print(yJSON);
    char* modeChar = cJSON_Print(modeJSON);

    short wigth = atoi(xChar);
    short length = atoi(yChar);

    std::cout << "x:" << wigth << " " << "y:" << length << endl;
    //只需要释放主JSON,不需要释放分出来的对象
    fclose(JSONFile);
    cJSON_Delete(optionJSON);
    free(readBuf);
    HANDLE th = NULL;
    Back:
    while (1) {
        if (GetAsyncKeyState(VK_MENU) & 0x8000)break;
    }
    //COLORREF firstColor = GetPixel(dng, wight, length);
    COLORREF newColor = GetPixel(dng, wigth, length);
    while (1) {
        newColor = GetPixel(dng, wigth, length);
        //cout << newColor << endl;//DEBUG
        if (newColor != RGB(255, 255, 255))break;
    }
    inputSquadConsole(1);
    cout << "succeed!" << endl;
    while (1) {
        if (GetAsyncKeyState(VK_MENU) & 0x1)break;
    }
    goto Back;
    ReleaseDC(NULL, dng);
    return 0;
}
