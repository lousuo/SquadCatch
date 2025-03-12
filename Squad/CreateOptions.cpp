// CreateSquadOptions.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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

    cout << "�������Ϸ������������Ϸ����ҳ������½�С�˵ı�����������Ȼ����ALT����" << endl;
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

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
