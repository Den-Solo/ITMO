#include "Uninstaller.h"

#include <Windows.h>
#include <string>
#include <vector>

static std::vector<std::string> keys = { "-Silent", "/Silent", "-S", "/S" };

int main(int argc, char** argv) 
{
    Uninstaller uninst;
    if (argc == 1 || (argc > 1 && std::find(keys.begin(), keys.end(), argv[1]) == keys.end())) {
        if (IDCANCEL == MessageBox (NULL, L"������ ������� ����������?", L"��������", MB_OKCANCEL))
            return 0;
        if (uninst.Exec())
            MessageBox(NULL, L"������� �������", L"��������", MB_OK);
        else
            MessageBox(NULL, L"� �������� �������� �������� ������\n��� ��������� ��� ���� �������", L"��������", MB_OK);
    } else {
        uninst.Exec();
    }
}