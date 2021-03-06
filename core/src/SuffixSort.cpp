#include "SuffixSort.h"


void SuffixSort::sort(std::vector <int> &data, String <int> &sorted_suffixes) {
    for (int i = 0; i < (int)data.size() - 1; i++) {
        data[i]++;
    }
    std::vector <int> vsorted_suffixes;
    sortSuffixes(data, vsorted_suffixes);
    sorted_suffixes.resize(vsorted_suffixes.size());
    for (int i = 0; i < sorted_suffixes.size(); i++) {
        sorted_suffixes[i] = vsorted_suffixes[i];
    }
    for (int i = 0; i < (int)data.size() - 1; i++) {
        data[i]--;
    }
}

void SuffixSort::sortSuffixes(std::vector <int> &data, std::vector <int> &sorted_suffixes){
    if (data.size() == 1) {
        sorted_suffixes.push_back(0);
        return;
    }
    int n = data.size();

    //i is a LMS(leftmost S) if type[i] = S, type[i - 1] = L
    std::vector <int> lms_suffixes;
    std::vector <bool> is_lms(data.size(), false);

    int max_symb_number = 0;
    for (int i = 0; i < n; i++) {
        max_symb_number = std::max(data[i], max_symb_number);
    }
    max_symb_number++;

    std::vector <int> block_begin(max_symb_number + 1, 0);

    block_begin[0] = 1;
    bool cur_type, last_type = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (data[i] < data[i + 1]) {
            cur_type = 0;
        }
        if (data[i] > data[i + 1]) {
            cur_type = 1;
        }
        if (data[i] == data[i + 1]) {
            cur_type = last_type;
        }

        if (cur_type == 1 && last_type == 0) {
                lms_suffixes.push_back(i + 1);
                is_lms[i + 1] = true;
        }
        block_begin[data[i]]++;
        last_type = cur_type;
    }
    std::reverse(lms_suffixes.begin(), lms_suffixes.end());

    //position at which the block of corresponding symbol starts
    int cur_pos = 0;
    for (int i = 0; i < max_symb_number; i++) {
        int tmp = block_begin[i];
        block_begin[i] = cur_pos;
        cur_pos += tmp;
    }
    block_begin[max_symb_number] = cur_pos;

    inducedSort(data, block_begin, lms_suffixes,
        sorted_suffixes, max_symb_number);
    std::vector <int> sorted_lms;
    std::vector <int> eq_class(data.size());
    int cur_class = 0;
    int last_lms_index = -1;
    for (int i = 0; i < sorted_suffixes.size(); i++) {
        if (!is_lms[sorted_suffixes[i]]) {
            continue;
        }
        if (last_lms_index == -1) {
            eq_class[sorted_suffixes[i]] = cur_class;
            last_lms_index = sorted_suffixes[i];
            continue;
        }
        int i1 = sorted_suffixes[i];
        int i2 = last_lms_index;
        bool is_eq = true;
        if (data[i1] != data[i2]) {
            is_eq = false;
        }
        else {
            for (int j = 1; j < data.size(); j++) {
                if (data[i1 + j] != data[i2 + j]) {
                    is_eq = false;
                    break;
                }
                if (is_lms[i1 + j] || is_lms[i2 + j]) {
                    if (!is_lms[i1 + j] || !is_lms[i2 + j]) {
                        is_eq = false;
                    }
                    break;
                }
            }
        }

        if (!is_eq) {
            cur_class++;
        }
        eq_class[sorted_suffixes[i]] = cur_class;
        last_lms_index = sorted_suffixes[i];
    }
    std::vector <int> lms_data(lms_suffixes.size());
    for (int i = 0; i < lms_suffixes.size(); i++) {
        lms_data[i] = eq_class[lms_suffixes[i]];
    }
    sorted_suffixes.clear();
    sortSuffixes(lms_data, sorted_suffixes);
    std::vector <int> sorted_lms_suffixes(lms_suffixes.size());
    for (int i = 0; i < sorted_suffixes.size(); i++) {
        sorted_lms_suffixes[i] = lms_suffixes[sorted_suffixes[i]];
    }

    sorted_suffixes.clear();
    inducedSort(data, block_begin, sorted_lms_suffixes,
        sorted_suffixes, max_symb_number);
}


void SuffixSort::inducedSort(std::vector <int> &data,
                             std::vector <int> &block_begin,
                             std::vector<int> &lms_suffixes,
                             std::vector<int> &sorted_suffixes,
                             int max_symb_number) {
    sorted_suffixes.assign(data.size(), -1);
    //how many symbols have been added to the S block of corresponding symbol
    std::vector <int> cur_shift(max_symb_number, 0);

    for (int i = (int)lms_suffixes.size() - 1; i >= 0; i--) {
        int symb = data[lms_suffixes[i]];
        sorted_suffixes[block_begin[symb + 1] - cur_shift[symb] - 1] = lms_suffixes[i];
        cur_shift[symb]++;
    }

    //find positions for L-suffixes
    cur_shift.assign(max_symb_number, 0);
    for (int i = 0; i < sorted_suffixes.size(); i++) {
        if (sorted_suffixes[i] != -1 && sorted_suffixes[i] != 0 &&
            data[sorted_suffixes[i] - 1] >= data[sorted_suffixes[i]]) {
            int suffix = sorted_suffixes[i] - 1;
            int symb = data[suffix];
            sorted_suffixes[block_begin[symb] + cur_shift[symb]] = suffix;
            cur_shift[symb]++;
        }
    }

    //find positions for S-suffixes
    cur_shift.assign(max_symb_number, 0);
    for (int i = (int)sorted_suffixes.size() - 1; i >= 0; i--) {
        if (sorted_suffixes[i] <= 0) {
            continue;
        }
        int j = sorted_suffixes[i] - 1;
        int k = sorted_suffixes[i];
        int symb = data[j];
        int pos = block_begin[symb + 1] - 1 - cur_shift[symb];
        //check if `sorted_suffixes[i] - 1` is S-type
        if (data[j] < data[k] || data[j] == data[k] && pos < i) {
            sorted_suffixes[pos] = j;
            cur_shift[symb]++;
        }
    }
}