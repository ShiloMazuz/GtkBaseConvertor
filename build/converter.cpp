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
        std::cout << "pushing back 1\n";
        break;
      case 0:
        binString.push_back('0');
        std::cout << "pushing back 0\n";
    }
  }
    while(binString.size() < 8) {
      binString = "0" + binString;
    }
  std::cout << "exiting binaryVectorToString function\n";
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
  for(std::size_t i {0}; i < IPAddrIntVector.size(); i++) {
  if(IPAddrIntVector[i] > 255 || IPAddrIntVector[i] < 0)
    return std::vector<int> {-1};
  }
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
      convertedIp += "00000000";
    }
    if(i < IpAddr.size()-1)
      convertedIp.push_back('.');
  }
  std::cout << convertedIp << '\n';
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

std::string prefixToHostsString(std::string prefixStr) {
  if(
    prefixStr.empty() ||
    !isStringDigit(prefixStr)
  )
    return "invalid prefix";
  int prefix { std::stoi(prefixStr) };
  int hostsAvilable {static_cast<int>(std::pow(2, 32-prefix))};
  if(hostsAvilable >= 2)
    hostsAvilable -= 2;
  std::string avilableHosts { std::to_string(hostsAvilable)};
  std::cout << avilableHosts << " hosts avilable\n";
  return avilableHosts;
}

std::string hostsToPrefixString (std::string hostsStr) {
if(
    hostsStr.empty() ||
    !isStringDigit(hostsStr)
  )
    return "invalid input";
  int hosts{std::stoi(hostsStr)};
  int requiredPrefix(static_cast<int>(32-std::log2(hosts+2)));
  return std::to_string(requiredPrefix);
}

std::string prefixToBinarySubnet(std::string prefixStr) {
  if( prefixStr.empty() || !isStringDigit(prefixStr) )
    return "invalid subnet mask";

  int prefix { std::stoi(prefixStr) };
  std::string subnetBinary {};

  for(std::size_t n {1}; n <= 32; n++) {
    if(n <= prefix)
      subnetBinary.push_back('1');

    else
      subnetBinary.push_back('0');

    if(static_cast<int>(n%8 == 0) && n != 32)
      subnetBinary.push_back('.');
  }
  return subnetBinary;
}

std::vector<std::string> extractBinaryIpString (std::string binIp) {
  std::vector<std::string> extractedIp (4);
  int octatCounter {0};
  for(std::size_t i {0}; i < binIp.size(); i++) {
    switch (binIp.at(i)) {
      case '0':
        std::cout << "[extractBinaryIpString] pushing back 0" << '\n';
        extractedIp[octatCounter].push_back('0');
        break;
      case '1':
        std::cout << "[extractBinaryIpString] pushing back 1" << '\n';
        extractedIp[octatCounter].push_back('1');
        break;
      case '.':
        std::cout << "[extractBinaryIpString] octatCounter++" << '\n';
        octatCounter++;
        break;
    }
  }
  std::cout << "binary IP address successfully extracted\n";
  return extractedIp;
}

std::string extractedBinIpToDecimal (std::vector<std::string> extractedBinIp) {
  std::string decimalIpAddr {};
  std::cout << "[extractedBinIpToDecimal] extractedBinIp.size() = " << extractedBinIp.size() << '\n';
  for(std::size_t n {0}; n < extractedBinIp.size(); n++) {
  int octatBuffer {};
  std::cout << "[extractedBinIpToDecimal] extractedBinIp[" << n << "].size() = " << extractedBinIp[n].size() << '\n';
    for(std::size_t i {0}; i < extractedBinIp[n].size(); i++) {
      if(extractedBinIp[n].at(i) == '1') {
        octatBuffer += static_cast<int>(std::pow(2, extractedBinIp[n].size()-(i+1)));
        std::cout << "octat buffer now equals " << octatBuffer << '\n';
      }
    }
    decimalIpAddr += std::to_string(octatBuffer);
    if(n+1 < extractedBinIp.size()) {
      std::cout << "n+1 = " << n+1 << '\n';
      std::cout << "[extractedBinIpToDecimal] pushing back ." << '\n';
      decimalIpAddr += '.';
    }
  }
  std::cout << "[extractedBinIpToDecimal] exiting function, decimalIpAddr = " << decimalIpAddr << '\n';
  return decimalIpAddr;
}

std::string binIpToDecimal (std::string binIp) {
  return extractedBinIpToDecimal(extractBinaryIpString(binIp));
}

std::string findNetworkAddress(std::string ipAddrStr, std::string prefixStr) {
  std::cout << "entering findNetworkAddress function\n";
  std::string binarySubnetMask { prefixToBinarySubnet(prefixStr) };
  std::cout << "converted prefix to binary subnet mask\n";
  std::string binaryIpAddr { convertedIpToBin(extractIpFromString(ipAddrStr))};
  std::cout << "converted ip address to binary\n";
  std::string binaryNetworkAddress {};

  std::cout << "using AND gate on IP and SubnetMask\n";
  std::cout << "binarySubnetMask.size() = " << binarySubnetMask.size() << '\n';
  std::cout << "binaryIpAddr.size() = " << binaryIpAddr.size() << '\n';
  for(std::size_t i {0}; i < binarySubnetMask.size(); i++) {
    std::cout << " i = " << i << '\n';
    if(binaryIpAddr.at(i) == binarySubnetMask.at(i)) {
      std::cout << "pushing back " << binaryIpAddr.at(i) << '\n';
      binaryNetworkAddress.push_back(binaryIpAddr.at(i));
    }
    else {
      std::cout << "pushing back 0" << '\n';
      binaryNetworkAddress.push_back('0');
    }
  }
  std::cout << "converting binaryNetworkAddress to decimal (" << binaryNetworkAddress << ")\n";
  return binIpToDecimal(binaryNetworkAddress);
}

//limits ipAndPrefixToLimits (std::string ipAddrStr, std::string prefixStr) {
//  std::vector<int> ipAddr {extractIpFromString ipAddrStr};
//  if(ipAddr[0] == -1);
//        return ("invalid IP address","invalid prefix");
//
//  if(prefixStr.empty() || !isStringDigit(prefixStr))
//        return ("invalid IP address","invalid prefix");
//  std::stoi(prefixStr);
//
//}
