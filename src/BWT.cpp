#include "BWT.h"

#include "SuffixSort.h"

void BWT::encode(String<Symbol> &data, DataInfo &data_info) {
    String <int> sorted_suffixes;

    //In sort and in further in the code we consider,
    // that new Symbol(255) is greater than others
    data.add(Symbol(255));
    SuffixSort().sort(data, sorted_suffixes);

    int first_suffix_number = -1;
    String <Symbol> new_data(data.size());
    int n = data.size();
    for (int i = 0; i < n; i++) {
        new_data[i] = data[(sorted_suffixes[i] + n - 1) % n];
        if (sorted_suffixes[i] == 0) {
            first_suffix_number = i;
        }
    }

    std::swap(data, new_data);
    data_info.write(first_suffix_number);
}

void BWT::decode(String<Symbol> &data, DataInfo &data_info) {
    std::vector <int> cnt_less(257, 0);
    String <int> cnt_eq_prev(data.size());
    String <Symbol> res_data((int)data.size() - 1);

    int data_size = data.size();
    int first_suffix_number;
    data_info.read(first_suffix_number);
    for (int i = 0; i < data_size; i++) {
        if (i == first_suffix_number) {
            cnt_eq_prev[i] = 0;
            continue;
        }
        cnt_eq_prev[i] = cnt_less[data[i].get()];
        cnt_less[data[i].get()]++;
    }
    int cnt_prev = cnt_less[0];
    cnt_less[0] = 0;
    for (int i = 1; i < 256; i++) {
        int tmp = cnt_less[i];
        cnt_less[i] = cnt_less[i - 1] + cnt_prev;
        cnt_prev = tmp;
    }
    cnt_less[256] = data_size - 1;

    int cur_index = first_suffix_number;
    int prev_symbol = 256;
    for (int i = 1; i < data_size; i++) {
        int newIndex = cnt_eq_prev[cur_index] + cnt_less[prev_symbol];
        res_data[data_size - i - 1] = data[newIndex];
        prev_symbol = res_data[data_size - i - 1].get();
        cur_index = newIndex;
    }

    std::swap(data, res_data);
}