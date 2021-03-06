/*
MIT License

Copyright (c) 2017 ZetaChain_Native

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "platform.hpp" // Platform Specific Stuff NOTE: Must Always be the first include in a file
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "conversions.hpp"
#include "operators.hpp"
#include "hashing.hpp"
#include "framedata.hpp"

FrameData::FrameData(std::vector<unsigned char> rawdata) {
	this->rawData = rawdata;
}

FrameData::~FrameData() {

}

std::string FrameData::getHash() {
	return this->hash;
}

std::vector<unsigned char> FrameData::getRawData() {
	return this->rawData;
}

std::string FrameData::computeHash() {
	if (this->hash != "")
		throw std::runtime_error("Hash has already been set");
	std::vector<unsigned char> bytes = this->toBytes();
	return Hashing::hashVector(bytes);
}

std::vector<unsigned char> FrameData::toBytes() {
	std::vector<unsigned char> bytes = std::vector<unsigned char>(sizeof(FrameData));
	bytes += this->rawData;

	return bytes;
}