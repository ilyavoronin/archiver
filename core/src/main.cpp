#include "ConsoleUI.h"

std::string file_path = "../files/test.txt";

int main() {
    ConsoleUI ui;
    ui.run("zip", file_path);
    ui.run("unzip", file_path + ".arc");
    return 0;
}