#include "BWT.h"

#include "SuffixSort.h"

void BWT::encode(String<Symbol> &data, DataInfo &data_info) {
    String <int> sorted_suffixes;

    //In sort and in further in the code we consider,
    // that new Symbol(255) is greater than others
    data.add(Symbol(255));
    SuffixSort().sort(data, sorted_suffixes);

    //index of the suffix that is
    //equal to the whole string
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
    //cnt_less[i] -- number of symbols in data that are less than
    //the Symbol(i)
    std::vector <int> cnt_less(257, 0);

    //cnt_eq_prev[i] -- number of j = 0...(i - 1) that data[j] < data[i]
    String <int> cnt_eq_prev(data.size());

    //the size = data.size() - 1 because we don't need additional Symbol(255)
    String <Symbol> res_data((int)data.size() - 1);

    int data_size = data.size();

    //index of the suffix that is
    //equal to the whole string
    int first_suffix_number;
    data_info.read(first_suffix_number);

    //at first we store in cnt_less[i] number of Symbol(i) in data
    for (int i = 0; i < data_size; i++) {
        if (i == first_suffix_number) {
            cnt_eq_prev[i] = 0;
            continue;
        }
        cnt_eq_prev[i] = cnt_less[data[i].get()];
        cnt_less[data[i].get()]++;
    }

    //then calculate cnt_less that was describes before
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