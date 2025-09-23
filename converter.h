#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
#include <vector>
#include <string>

std::vector<bool> decimalToBinary (int num);
std::string binaryVectorToString(std::vector<bool> binForm);
std::string decimalToBinString(int num);
std::vector<int> decimalToHex(int num);
void printBinaryNumber(std::vector<bool>& binaryForm);
void printHexNumber(std::vector<int>& hexForm);
std::string hexVectorToString(std::vector<int> hexForm);
std::string decimalToHexString(int num);
std::vector<int> extractIpFromString(std::string IpAddr);
std::string convertedIpToBin(std::vector<int> IpAddr);

#endif
