#include "BWT.h"

#include "SuffixSort.h"

void BWT::encode(String<mchar> &data, DataInfo &data_info) {
    String <int> sorted_suffixes;
    std::vector <int> vdata(data.size());
    for (int i = 0; i < data.size(); i++) {
        vdata[i] = data[i];
    }
    // symbol that is less than others
    vdata.push_back(0);
    data.add(0);
    SuffixSort().sort(vdata, sorted_suffixes);

    //index of the suffix that is
    //equal to the whole string
    int first_suffix_number = -1;
    int n = data.size();
    for (int i = 0; i < n; i++) {
        data[i] = vdata[(sorted_suffixes[i] + n - 1) % n];
        if (sorted_suffixes[i] == 0) {
            first_suffix_number = i;
        }
    }

    data_info.write(first_suffix_number);
}

void BWT::decode(String<mchar> &data, DataInfo &data_info) {
    //cnt_less[i] -- number of symbols in data that are less than
    //the mchar(i)
    std::vector <int> cnt_less(257, 0);

    //cnt_eq_prev[i] -- number of j = 0...(i - 1) that data[j] < data[i]
    String <int> cnt_eq_prev(data.size());

    //the size = data.size() - 1 because we don't need additional symbol 0
    String <mchar> res_data((int)data.size() - 1);

    int data_size = data.size();

    //index of the suffix that is
    //equal to the whole string
    int first_suffix_number;
    data_info.read(first_suffix_number);

    //at first we store in cnt_less[i] number of mchar(i) in data
    for (int i = 0; i < data_size; i++) {
        if (i == first_suffix_number) {
            cnt_eq_prev[i] = 0;
            continue;
        }
        cnt_eq_prev[i] = cnt_less[data[i] + 1];
        cnt_less[data[i] + 1]++;
    }

    //then calculate cnt_less that was described before
    int cnt_prev = 1;
    cnt_less[0] = 0;
    for (int i = 1; i < 257; i++) {
        int tmp = cnt_less[i];
        cnt_less[i] = cnt_less[i - 1] + cnt_prev;
        cnt_prev = tmp;
    }

    int cur_index = first_suffix_number;
    int prev_symbol = 0;
    for (int i = 1; i < data_size; i++) {
        int newIndex = cnt_eq_prev[cur_index] + cnt_less[prev_symbol];
        res_data[data_size - i - 1] = data[newIndex];
        prev_symbol = res_data[data_size - i - 1] + 1;
        cur_index = newIndex;
    }

    std::swap(data, res_data);
}