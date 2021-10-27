#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
void readStdin(std::istream & istream);
void print(std::vector<std::string>);

int main(int argc, char ** argv) {
  if (argc == 1) {
    readStdin(std::cin);
  }
  else {
    readFiles(argc, argv);
  }
  return EXIT_SUCCESS;
}

void readFiles(int argc, char ** argv) {
  for (int i = 0; i < argc; i++) {
    std::ifstream readFile;
    readFile.open(argv[i], std::ios::in);
    if (!readFile.is_open()) {
      std::cerr << "file open fails" << std::endl;
      exit(EXIT_FAILURE);
    }
    readStdin(readFile);
    readFile.close();
  }
}

void readStdin(std::istream & file) {
  std::string readS;
  std::vector<std::string> ans;
  while (getline(file, readS)) {
    ans.push_back(readS);
    if (!std::cin.good()) {
      std::cerr << "Error reading line" << std::endl;
    }
  }
  //sort the line
  std::sort(ans.begin(), ans.end());
}

void print(std::vector<std::string> ans) {
  for (size_t i = 0; i < ans.size(); i++) {
    std::cout << ans[i];
  }
}
