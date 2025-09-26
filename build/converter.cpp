#include "converter.h"

bool isStringDigit(std::string str) {
  for(auto& ch : str) {
    if(!std::isdigit(ch))
      return false;
  }
  return true;
}

//converts single number to a boolean vector
std::vector<bool> decimalToBinary (int num) {
  std::vector<bool> binaryForm{};
  while(num>0) {
    binaryForm.push_back(num%2);
    num = num / 2;
  }
  return binaryForm;
}

//converts boolean vector to a string
std::string binaryVectorToString(std::vector<bool> binForm) {
  std::string binString {};
  for(std::size_t i {binForm.size()}; 0 != i; i--) {
    switch (binForm[i-1])
    {
      case 1:
        binString.push_back('1');
        break;
      case 0:
        binString.push_back('0');
    }
  }
  return binString;
}

//takes a number and returns binary form as a string
std::string decimalToBinString(int num) {
  return binaryVectorToString(decimalToBinary(num));
}

std::vector<int> decimalToHex(int num) {
  std::vector<int> hexForm{};
  while(num>0) {
    hexForm.push_back(num%16);
    num = num / 16;
  }
  return hexForm;
}

//outputs boolean vector into terminal
void printBinaryNumber(std::vector<bool>& binaryForm) {
  for(std::size_t i {binaryForm.size()}; 0 != i; i--) {
    std::cout << static_cast<int>(binaryForm[i-1]);
  }
  return;
}

//takes in an int vector and prints out as hex
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

//takes int vector representing a hex number and returns a string
std::string hexVectorToString(std::vector<int> hexForm) {
  std::string hexString {};
  for(std::size_t i {hexForm.size()}; 0 != i; i--) {
    switch (hexForm[i-1]) 
    {
      case 10:
        hexString.push_back('A');
        break;
      case 11:
        hexString.push_back('B');
        break;
      case 12:
        hexString.push_back('C');
        break;
      case 13:
        hexString.push_back('D');
        break;
      case 14:
        hexString.push_back('E');
        break;
      case 15:
        hexString.push_back('F');
        break;
      default:
        char temp (hexForm[i-1]+48);
        hexString.push_back(temp);
        break;
    }
  }
  return hexString;
}

//takes in a number and returns it as hex string
std::string decimalToHexString(int num) {
  return hexVectorToString(decimalToHex(num));
}

//takes string representing an IP and converts into int vector
std::vector<int> extractIpFromString(std::string IPAddr) {
  //early return if string is empty
  if(IPAddr.empty())
    return std::vector<int> {-1};
  std::string octatHolder {};
  int octatNumber {0};
  std::vector<int> IPAddrIntVector {};
  for(std::size_t i {0}; i < IPAddr.size(); i++)
  {
    if(IPAddr.at(i) == '.') {
      std::cout << "dot found" << '\n';
      IPAddrIntVector.push_back(stoi(octatHolder));
      octatHolder.clear();
      octatNumber++;
    }
    else {
      if(!std::isdigit(IPAddr[i]))
        return std::vector<int> {-1};
      std::cout << "pushing back " << IPAddr.at(i) << '\n';
      octatHolder.push_back(IPAddr.at(i));
    }
  }
  std::cout << "exiting extractor" << '\n';
  IPAddrIntVector.push_back(stoi(octatHolder));
  return IPAddrIntVector;
}

//takes int vector and converts into a binary form string
std::string convertedIpToBin(std::vector<int> IpAddr) {
  if(IpAddr[0] == -1)
    return "invalid IP address";
  std::string convertedIp {};
  for(size_t i {0}; i < IpAddr.size(); i++) {
    if(IpAddr[i] != 0) {
    convertedIp += binaryVectorToString(decimalToBinary(IpAddr[i]));
    }
    else {
      convertedIp.push_back('0');
    }
    if(i < IpAddr.size()-1)
      convertedIp.push_back('.');
  }
  return convertedIp;
}

//convert a prefix to a subnet mask string
std::string prefixToSubnetString (std::string prefixStr) {
  if(
    prefixStr.empty() ||
    !isStringDigit(prefixStr)
  )
    return "invalid prefix";
  int prefix { std::stoi(prefixStr) };
  //end of prefunction checks
  int minimumLength {4};
  std::string subnetMask {};
  while(prefix > 8) {
    subnetMask += "255.";
    prefix -= 8;
    minimumLength--;
  }
  subnetMask += std::to_string(static_cast<int>(256-std::pow(2, 8-prefix)));
  minimumLength--;
  while(minimumLength > 0) {
    subnetMask += ".0";
    minimumLength--;
  }
  return subnetMask;
}
