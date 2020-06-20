//MergeSort �������� ����� (Solovyov Denis), N3251
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <cstddef>
#include <chrono>

//#define TIME_LOGGER 1
//#define ERROR_LOGGER 1

using namespace std;

using namespace std::chrono;
class LogDuration {
public:
	explicit LogDuration(const string& msg = "")
		: message(msg + ": ")
		, start(steady_clock::now())
		, prev(start)
	{
	}
	void Check(const string& m) {
		auto finish = steady_clock::now();
		auto dur = finish - prev;
		cerr << m << ": "
			<< duration_cast<milliseconds>(dur).count()
			<< " ms\n";
		prev = finish;
	}
	~LogDuration() {
		auto finish = steady_clock::now();
		auto dur = finish - start;
		cerr << message
			<< duration_cast<milliseconds>(dur).count()
			<< " ms\n";
	}
private:
	string message;
	steady_clock::time_point start;
	steady_clock::time_point prev;
};


inline unsigned LineToUintBegin(char* line, size_t& count) {
	unsigned result = 0;
	int i = 0;
	while (line[i] != '\r' && line[i] != '\0') {
		if (line[i] >= '0' && line[i] <= '9') {
			result *= 10;
			result += line[i] - '0';
		}
		else
			throw runtime_error("unknown symbol in num of lines\n");
		++i;
	}
	if (i == 0)
		throw runtime_error("string starts from ' '\n");
	if (result == 0 && line[i] == '\r' && line[i + 2] != '\0') {
			throw runtime_error("File is Longer than expected");
	count += i;
	return result;
}


inline unsigned LineToUint(char* line, size_t& count) {
	unsigned result = 0;
	int i = 0;
	for (; line[i] != ' '; ++i) {
		if (line[i] >= '0' && line[i] <= '9') {
			result *= 10;
			result += line[i] - '0';
		}
		else
			throw runtime_error("unknown symbol in number\n");
	}
	if (i == 0)
		throw runtime_error("string starts from ' '\n");
	count += i;
	return result;
}

struct Node {
	unsigned key;
	int length;     //length of line 
	size_t idx;     //index in memory mapped file
};


inline void InsertionSort(Node* arr, size_t size) {
	if (size <= 1)
		return;
	for (int i = 1; i < size; ++i) {
		Node tmp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j].key > tmp.key) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = tmp;
	}
}


inline void Merge(Node* data1, size_t size1, Node* data2, size_t size2, Node* buf) {
	size_t idx1 = 0;
	size_t idx2 = 0;


	while (idx1 < size1 && idx2 < size2) {
		if (data1[idx1].key <= data2[idx2].key) {
			*buf = data1[idx1];
			++buf;
			++idx1;
		}
		else {
			*buf = data2[idx2];
			++buf;
			++idx2;
		}
	}
	if (idx1 != size1) {
		while (idx1 < size1) {
			*buf = data1[idx1];
			++buf;
			++idx1;
		}
	}
	else if (idx2 != size2) {
		while (idx2 < size2) {
			*buf = data2[idx2];
			++buf;
			++idx2;
		}
	}
}

inline Node* MergeSort(Node* data, unsigned size) {
	if (size <= 1)
		return data;
	if (size == 2) {
		if (data[0].key > data[1].key)
			swap(data[0], data[1]);
		return data;
	}
	Node* buf = new Node[size];

	Node* src = data;
	Node* dst = buf;

	const int block_size_ = 25;
	{
		unsigned len;
		size >= block_size_ ? len = block_size_ : len = size;
		int offset = 0;
		while (len != 0) {
			InsertionSort(src + offset, len);
			offset += len;
			if (offset + len >= size) {
				len = size - offset;
			}
		}
	}

	unsigned len = block_size_;
	while (len < size) {
		//����������: src ������ �� ���� �����������
		unsigned i = 0;
		while (i < size - len) {
			unsigned len2 = len;
			if (i + len + len2 > size) {
				len2 = size - (i + len);
			}
			Merge(src + i, len, src + i + len, len2, dst + i);
			i += len + len2;
		}
		if (i < size)
			memcpy(dst + i, src + i, sizeof(Node) * (size - i));
		len *= 2;
		swap(src, dst);
	}
	delete[] dst;
	return src;
}


int main(int argc, char* args[]) {

#ifdef TIME_LOGGER
	LogDuration logger("MergeSort");
#endif

	if (argc != 3) {
#ifdef ERROR_LOGGER
		cerr << "Wrong number of args\n";
#endif
		return 1;
	}

	HANDLE hFileInput = CreateFileA(
		args[1],
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
		NULL
	);

	if (hFileInput == INVALID_HANDLE_VALUE) {
#ifdef ERROR_LOGGER
		cerr << "CreateFileA(input) INVALID_HANDLE_VALUE: Input file not found\n";
#endif
		return 2;//fail file
	}


	HANDLE hFileOutput = CreateFileA(
		args[2],
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL
	);

	if (hFileOutput == INVALID_HANDLE_VALUE) {
#ifdef ERROR_LOGGER
		cerr << "CreateFileA(output) INVALID_HANDLE_VALUE: Output file cannot be created\n";
#endif
		CloseHandle(hFileInput);
		return 2;//fail file
	}

	LARGE_INTEGER file_size;

	if (GetFileSizeEx(hFileInput, &file_size) && file_size.QuadPart != 0) {

		HANDLE hMapInput = CreateFileMappingA(
			hFileInput,
			NULL,
			PAGE_READONLY,
			0,
			0,
			"MyInputFileDenis"
		);


		if (hMapInput != NULL) {

			LPVOID mapViewInput = MapViewOfFile(hMapInput, FILE_MAP_READ, 0, 0, 0);

			if (mapViewInput != NULL) {

				char* input_ptr = (char*)mapViewInput;
				size_t idx = 0;
				unsigned n;
				Node* data = nullptr;

				bool endedWith0 = true;
				//Reading---------------------------------------
				try {
					//num of lines
					n = LineToUintBegin(input_ptr, idx);

					if (n == 0) {
						if (file_size.QuadPart == 1)
							WriteFile(hFileOutput, input_ptr, 1, NULL, NULL);
						else
							WriteFile(hFileOutput, input_ptr, 3, NULL, NULL);
						UnmapViewOfFile(mapViewInput);
						CloseHandle(hMapInput);
						CloseHandle(hFileOutput);
						CloseHandle(hFileInput);
						return 0;
					}


					idx += 2; //eat "\r\n"
					data = new Node[n];

					for (unsigned i = 0; i < n - 1; ++i) {
						data[i].idx = idx;
						data[i].key = LineToUint(input_ptr + idx, idx);
						while (input_ptr[idx] != '\n') {
							if (input_ptr[idx] == '\0') {
								throw runtime_error("File Shorter than Expected\n");
							}
							++idx;
						}
						++idx;//eat "\r\n"
						data[i].length = static_cast<int>(idx - data[i].idx);
					}

					unsigned n2 = n - 1;
					data[n2].idx = idx;
					data[n2].key = LineToUint(input_ptr + idx, idx);
					while (input_ptr[idx] != '\0') {
						if (input_ptr[idx] == '\n') {
							if (input_ptr[idx + 1] == '\0') {
								endedWith0 = false;
								++idx;
								break;
							}
							else {
								throw runtime_error("File Longer than Expected or contains \"\\r\\n\" at the end\n");
							}
						}
						++idx;
					}
					if (endedWith0)
						data[n2].length = -1; //ends with '\0'
					else
						data[n2].length = static_cast<int>(idx - data[n2].idx);
				}
				catch (runtime_error & e) {
					delete[] data;
					UnmapViewOfFile(mapViewInput);
					CloseHandle(hMapInput);
					CloseHandle(hFileOutput);
					CloseHandle(hFileInput);
#ifdef ERROR_LOGGER
					cerr << e.what();
#endif
					return 3;
				}
				//--Reading---------------------------------------
#ifdef TIME_LOGGER
				logger.Check("Reading");
#endif

				//Sorting------------------------------------

				data = MergeSort(data, n);
#ifdef TIME_LOGGER
				logger.Check("Sorting");
#endif
				//--Sorting------------------------------------


				//Writing------------------------------------

				HANDLE hMapOutput = CreateFileMappingA(
					hFileOutput,
					NULL,
					PAGE_READWRITE,
					file_size.HighPart,
					file_size.LowPart,
					"MyOutputFileDenis"
				);


				if (hMapOutput != NULL) {

					LPVOID mapViewOutput = MapViewOfFile(hMapOutput, FILE_MAP_WRITE, 0, 0, 0);

					size_t oidx = 0;

					if (mapViewOutput != NULL) {

						char* out_ptr = (char*)mapViewOutput;

						//num of lines
						while (input_ptr[oidx] != '\n') {
							out_ptr[oidx] = input_ptr[oidx];
							++oidx;
						}
						out_ptr[oidx] = input_ptr[oidx]; // '/n'
						++oidx;


						//lines from 0 to n - 2
						unsigned n2 = n - 1;
						unsigned cur_length;
						for (unsigned i = 0; i < n2; ++i) {
							if (data[i].length != -1) {
								cur_length = data[i].length;
								for (unsigned j = 0; j < cur_length; ++j) {
									out_ptr[oidx] = input_ptr[data[i].idx + j];
									++oidx;
								}
							}
							else {
								unsigned j = 0;
								while (input_ptr[data[i].idx + j] != '\0') {
									out_ptr[oidx] = input_ptr[data[i].idx + j];
									++oidx;
									++j;
								}
								out_ptr[oidx] = '\r';
								++oidx;
								out_ptr[oidx] = '\n';
								++oidx;
							}

						}

						if (endedWith0) {
							if (data[n2].length != -1) {
								cur_length = data[n2].length - 2;
								for (unsigned j = 0; j < cur_length; ++j) {
									out_ptr[oidx] = input_ptr[data[n2].idx + j];
									++oidx;
								}
							}
							else {
								unsigned j = 0;
								while (input_ptr[data[n2].idx + j] != '\0') {
									out_ptr[oidx] = input_ptr[data[n2].idx + j];
									++oidx;
									++j;
								}
							}
						}
						else {
							cur_length = data[n2].length;
							for (unsigned j = 0; j < cur_length; ++j) {
								out_ptr[oidx] = input_ptr[data[n2].idx + j];
								++oidx;
							}
						}

						UnmapViewOfFile(mapViewOutput);
					}
					else {
#ifdef ERROR_LOGGER
						cerr << "MapViewOfFile(output) error\n";
#endif
						return 2;
					}
				}
				else {
#ifdef ERROR_LOGGER
					cerr << "CreateFileMapping(output) Error\n";
#endif
					return 2;
				}
				//--Writing------------------------------------
#ifdef TIME_LOGGER
				logger.Check("Writing");
#endif

				delete[] data;

				UnmapViewOfFile(mapViewInput);
				CloseHandle(hMapOutput);
				CloseHandle(hMapInput);
				CloseHandle(hFileOutput);
				CloseHandle(hFileInput);
			}
			else {
#ifdef ERROR_LOGGER
				cerr << "MapViewOfFile(input) error\n";
#endif
				CloseHandle(hMapInput);
				CloseHandle(hFileOutput);
				CloseHandle(hFileInput);
				return 2;
			}
		}
		else {
			CloseHandle(hFileOutput);
			CloseHandle(hFileInput);
#ifdef ERROR_LOGGER
			cerr << "CreateFileMapping(input) Error\n";
#endif
			return 2;
		}

	}
	else {
		CloseHandle(hFileOutput);
		CloseHandle(hFileInput);
#ifdef ERROR_LOGGER
		cerr << "GetFileSizeEx(input) error or size is 0\n";
#endif
		return 3;
	}

	return 0;
}