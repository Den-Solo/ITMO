#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <filesystem>
#include <string>
#include <regex>
#include <fstream>
#include <windows.h>
#include <future>
#include <exception>
#include <memory>
#include <sstream>
#include <locale>

std::wstring utf8_to_wchar(const std::string& s) {
	std::wstring ws;
	ws.resize(s.length());
	::MultiByteToWideChar(CP_UTF8, 0, s.data(), s.length(), ws.data(), ws.length());
	return ws;
}
std::wstring cp1251_to_wchar(const std::string& s) {
	std::wstring ws;
	ws.resize(s.length());
	::MultiByteToWideChar(1251, 0, s.data(), s.length(), ws.data(), ws.length());
	return ws;
}

class Filter {

private:
	HANDLE hFile{ NULL };
	std::wstring pswd;
	std::wstring pattern;
	std::wregex reg;

private:

	bool open_tbl() {
		hFile = CreateFile(TEXT(".tbl"), GENERIC_READ,
			0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY, NULL);//exclusive open
		if (hFile == INVALID_HANDLE_VALUE) {
			return false; //already opened or doesn't exist
		}
		return true;
	}

	void read_tbl() {
		std::string sBuf;
		std::wstring wsBuf;
		DWORD dwBufSzLow, dwBufSzHigh, dwSzOfRead;

		//read file
		dwBufSzLow = GetFileSize(hFile, &dwBufSzHigh);
		sBuf.resize(dwBufSzLow + 1);
		ReadFile(hFile, sBuf.data(), dwBufSzLow, &dwSzOfRead, NULL);

		//defeat encoding problems
		wsBuf = utf8_to_wchar(sBuf);
		std::wistringstream wiss(wsBuf);
		wiss >> pswd;
		{//build regex
			pattern.reserve(dwBufSzLow);
			std::wstring tmp;
			while (wiss >> tmp) {
				if (tmp.size() && tmp[0] != '#') {
					if (pattern.size())
						pattern += '|';
					pattern += tmp;
				}
			}
			//reg = std::wregex(pattern);
		}

	}

public:
	Filter() {
		if (!open_tbl()) {
			throw std::runtime_error("file locked or doesn't exist");
		}
		read_tbl();
	}
	~Filter() {
		if (hFile && hFile!= INVALID_HANDLE_VALUE) {
			CloseHandle(hFile);
		}
	}
	void Run() const {
		//MessageBox(NULL, L"Started", L"Window", NULL);
		//...
	}
	bool CheckPassword(const std::string& s) const {
		std::wstring ws = cp1251_to_wchar(s);
		//hash
		return ws == pswd;
	}
};

void prepare_console() {
	setlocale(LC_CTYPE, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 15;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void init_exit(const Filter const* f) {
	std::string user_input;
	while (true) {
		std::cout << "Input Password to stop" << std::endl;
		std::cin >> user_input;
		if (f->CheckPassword(user_input)) {
			std::cout << "Correct" << std::endl;
			break;
		}
		std::cout << "Wrong Password\n" << std::endl;
	}
}

int main(int argc, TCHAR* argv[]) {
	prepare_console();

	std::unique_ptr<Filter> filter;
	try {
		filter = std::make_unique<Filter>();
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	//filtering files
	std::future<void> f;
	f = std::async(&Filter::Run, filter.get());

	init_exit(filter.get());
	return 0;
}