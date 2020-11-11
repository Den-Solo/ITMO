#include "Uninstaller.h"

#include <Windows.h>
#include <string>
#include <vector>

static std::vector<std::string> keys = { "-Silent", "/Silent", "-S", "/S" };

int main(int argc, char** argv) 
{
    Uninstaller uninst;
    if (argc == 1 || (argc > 1 && std::find(keys.begin(), keys.end(), argv[1]) == keys.end())) {
        if (IDCANCEL == MessageBox (NULL, L"Хотите удалить приложение?", L"Удаление", MB_OKCANCEL))
            return 0;
        if (uninst.Exec())
            MessageBox(NULL, L"Успешно удалено", L"Удаление", MB_OK);
        else
            MessageBox(NULL, L"В процессе удаления возникли ошибки\nили программа уже была удалена", L"Удаление", MB_OK);
    } else {
        uninst.Exec();
    }
}