#include <iostream>
#include <vector>
#include <string>

std::vector<bool> decimalToBinary (int num) {
  std::vector<bool> binaryForm{};
  while(num>0) {
    binaryForm.push_back(num%2);
    num = num / 2;
  }
  return binaryForm;
}

std::vector<int> decimalToHex(int num) {
  std::vector<int> hexForm{};
  while(num>0) {
    hexForm.push_back(num%16);
    num = num / 16;
  }
  return hexForm;
}

void printBinaryNumber(std::vector<bool>& binaryForm) {
  for(std::size_t i {binaryForm.size()}; 0 != i; i--) {
    std::cout << static_cast<int>(binaryForm[i-1]);
  }
  return;
}

void printHexNumber(std::vector<int>& hexForm) {
  for(std::size_t i {hexForm.size()}; 0 != i; i--) {
    switch (hexForm[i-1]) 
    {
      case 10:
        std::cout << 'A';
        break;
      case 11:
        std::cout << 'B';
        break;
      case 12:
        std::cout << 'C';
        break;
      case 13:
        std::cout << 'D';
        break;
      case 14:
        std::cout << 'E';
        break;
      case 15:
        std::cout << 'F';
        break;
      default:
        std::cout << hexForm[i-1];
      break;
    }
  }
  return;
}

int main() {
  int num {6342};
  std::vector hexNumber{decimalToHex(num)};
  printHexNumber(hexNumber);
  return 0;
}
