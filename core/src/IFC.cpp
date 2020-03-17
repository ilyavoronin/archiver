#include "IFC.h"

#include <vector>

void IFC::encode(String <mchar> &inputString, DataInfo &data_info) {
    String <mchar> result;
    std::vector <int> weight(256, 0);
    std::vector <short int> symbolPosition;
    std::vector <short int> symbols;
    for (int i = 0; i < 256; i++) {
        symbolPosition.push_back(i);
        symbols.push_back(i);
    }
    int prevAverage = 0, average, difference, increment, prevIncrement = 16;
    result.resize((int)inputString.size());
    for (int i = 0; i < (int)inputString.size(); i++) {
        int symbol = inputString[i];
        int index;
        if (i != 0 && symbol == inputString[i - 1]) {
            index = 0;
        }
        else {
            if (i == 0 || symbolPosition[symbol] > symbolPosition[inputString[i - 1]]) {
                index = symbolPosition[symbol];
            }
            else {
                index = symbolPosition[symbol] + 1;
            }
        }
        //index = symbolPosition[symbol];
        result[i] = index;
        average = (prevAverage * (windowSize - 1) + index) / windowSize;
        difference = average - prevAverage;
        if (abs(difference) > const4) {
            if (difference > 0) {
                difference = const4;
            }
            else {
                difference = -const4;
            }
        }
        increment = prevIncrement - (prevIncrement * difference / const1);
        if (i > 0 && inputString[i] == inputString[i - 1]) {
            increment = increment + increment / 2;
        }
        weight[symbol] += increment;
        if (weight[symbol] > const3) {
            for (int i = 0; i < 256; i++) {
                weight[i] = (weight[i] + 1) / 2;
            }
            increment = (increment + 1) / 2;
        }
        int curIndex = symbolPosition[symbol];
        if (increment > 0) {
            while (curIndex > 0 && weight[symbol] >= weight[symbols[curIndex - 1]]) {
                std::swap(symbolPosition[symbol], symbolPosition[symbols[curIndex - 1]]);
                std::swap(symbols[curIndex], symbols[curIndex - 1]);
                curIndex--;
            }
        }
        else {
            while (curIndex < 255 && weight[symbol] < weight[symbols[curIndex + 1]]) {
                std::swap(symbolPosition[symbol], symbolPosition[symbols[curIndex + 1]]);
                std::swap(symbols[curIndex], symbols[curIndex + 1]);
                curIndex++;
            }
        }
        prevIncrement = increment;
        prevAverage = average;
    }
    std::swap(inputString, result);
}

void IFC::decode(String <mchar> &inputString, DataInfo &data_info) {
    String <mchar> result;
    std::vector <int> weight(256, 0);
    std::vector <short int> symbolPosition;
    std::vector <short int> symbols;
    for (int i = 0; i < 256; i++) {
        symbolPosition.push_back(i);
        symbols.push_back(i);
    }
    int prevAverage = 0, average, difference, increment, prevIncrement = 16;
    for (int i = 0; i < (int)inputString.size(); i++) {
        int index, symbol;
        index = inputString[i];
        if (index == 0 && i != 0) {
            symbol = result.back();
        }
        else {
            if (i != 0 && index <= symbolPosition[result.back()]) {
                symbol = symbols[index - 1];
            }
            else {
                symbol = symbols[index];
            }
        }
        result.add(symbol);
        average = (prevAverage * (windowSize - 1) + index) / windowSize;
        difference = average - prevAverage;
        if (abs(difference) > const4) {
            if (difference > 0) {
                difference = const4;
            }
            else {
                difference = -const4;
            }
        }
        increment = prevIncrement - (prevIncrement * difference / const1);
        if (i > 0 && result[i] == result[i - 1]) {
            increment = increment + increment / 2;
        }
        weight[symbol] += increment;
        if (weight[symbol] > const3) {
            for (int i = 0; i < 256; i++) {
                weight[i] = (weight[i] + 1) / 2;
            }
            increment = (increment + 1) / 2;
        }
        int curIndex = symbolPosition[symbol];
        if (increment > 0) {
            while (curIndex > 0 && weight[symbol] >= weight[symbols[curIndex - 1]]) {
                std::swap(symbolPosition[symbol], symbolPosition[symbols[curIndex - 1]]);
                std::swap(symbols[curIndex], symbols[curIndex - 1]);
                curIndex--;
            }
        }
        else {
            while (curIndex < 255 && weight[symbol] < weight[symbols[curIndex + 1]]) {
                std::swap(symbolPosition[symbol], symbolPosition[symbols[curIndex + 1]]);
                std::swap(symbols[curIndex], symbols[curIndex + 1]);
                curIndex++;
            }
        }
        prevIncrement = increment;
        prevAverage = average;
    }
    std::swap(inputString, result);
}