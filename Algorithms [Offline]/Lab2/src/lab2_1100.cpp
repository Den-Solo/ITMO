#include <iostream>

using namespace std;

struct TeamData {
	unsigned id;
	unsigned points;
};

inline void Merge(TeamData* data1, size_t size1, TeamData* data2, size_t size2, TeamData* buf) {
    size_t idx1 = 0;
    size_t idx2 = 0;


    while (idx1 < size1 && idx2 < size2) {
        if (data1[idx1].points >= data2[idx2].points) {
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

inline TeamData* MergeSort(TeamData* data, unsigned size) {
    if (size <= 1) {
        return data;
    }
    if (size == 2) {
        if (data[0].points < data[1].points) {
            swap(data[0], data[1]);
        }
        return data;
    }
    TeamData* buf = new TeamData[size];

    TeamData* src = data;
    TeamData* dst = buf;

    
    unsigned len = 1;
    while (len < size) {
        unsigned i = 0;
        while (i < size - len) {
            unsigned len2 = len;
            if (i + len + len2 > size) {
                len2 = size - (i + len);
            }
            Merge(src + i, len, src + i + len, len2, dst + i);
            i += len + len2;
        }
        if (i < size) {
            memcpy(dst + i, src + i, sizeof(TeamData) * (size - i));
        }
        len *= 2;
        swap(src, dst);
    }
    delete[] dst;
    return src;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	unsigned num_of_teams;
	cin >> num_of_teams;

	TeamData* teams = new TeamData[num_of_teams];

	for (unsigned i = 0; i < num_of_teams; ++i) {
		cin >> teams[i].id >> teams[i].points;
	}
	
    teams = MergeSort(teams, num_of_teams);
    for (unsigned i = 0; i < num_of_teams; ++i) {
        cout << teams[i].id <<' ' << teams[i].points << '\n';
    }
    delete[] teams;
}