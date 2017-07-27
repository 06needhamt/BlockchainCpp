/*
MIT License

Copyright (c) 2017 Blockchain-VCS

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
#include <map> // std::map
#include <string> // std::string
#include <ctime> // time_t localtime() struct tm* asctime()
#include <chrono> // std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::nanoseconds
#include <stdexcept> // throw throw std::runtime_error()
#include "thirdparty/json.hpp"
#include "operators.hpp"
#include "conversions.hpp" // toBytes()
#include "transaction.hpp"
#include "shortblockdata.hpp"
#include "hashing.hpp"

namespace BlockchainCpp {
	ShortBlockData::ShortBlockData(short data){
		this->rawData = data;
	}

	ShortBlockData::~ShortBlockData(){

	}

	std::string ShortBlockData::computeHash(){
		return Hashing::hashVector(this->toBytes());
	}

	std::vector<unsigned char> ShortBlockData::toBytes(){
		std::vector<unsigned char> bytes = std::vector<unsigned char>(sizeof(ShortBlockData));

 		std::vector<std::string> values = Conversions::mapToValuesString(this->transactions, this->transactions.size());
		
		for(int i = 0; i < values.size() - 1; i++)
			bytes += Conversions::toBytes(values[i]);

		bytes += Conversions::toBytes(&this->size);
		bytes += Conversions::toBytes(&this->transactionCount);
		bytes += Conversions::toBytes(&this->bits);
		bytes += Conversions::toBytes(&this->timeCreated);
		bytes += Conversions::toBytes(&this->timeRecieved);
		bytes += Conversions::toBytes(&this->timeLocked);
		bytes += Conversions::toBytes(&this->rawData);
		return bytes;
	}

	std::string ShortBlockData::toString(){
		nlohmann::json j;
		nlohmann::json transactions = nlohmann::json::array();
		std::vector<std::string> keys = Conversions::mapToKeys(this->transactions, this->transactions.size());
		std::vector<std::string> values = Conversions::mapToValuesString(this->transactions, this->transactions.size());

		j["type", "TransactionInput"];
		j["hash", this->hash];
		j["size", this->size];
		for(int x = 0, y = 0; x < this->transactions.size() - 1; x++, y++) {
			j.push_back("Transaction: " + keys[x] + ", " + values[y]);
		}
		j["transactionCount", this->transactionCount];
		j["bits", this->bits];
		j["timeCreated", this->timeCreated];
		j["timeRecieved", this->timeRecieved];
		j["timeLocked", this->timeLocked];
		return j;
	}

	bool ShortBlockData::verify(){
		return this->hash == computeHash();
	}

	bool ShortBlockData::lock() {
		//TODO
		return false;
	}


	std::string ShortBlockData::getHash(){
		return this->hash;
	}

	std::map<std::string, Transaction<TransactionData*>*> ShortBlockData::getTransactions(){
		return static_cast<std::map<std::string, Transaction<TransactionData*>*>>(this->transactions);
	}

	unsigned long ShortBlockData::getSize(){
		return this->size;
	}

	unsigned long ShortBlockData::getTransactionCount(){
		return this->transactionCount;
	}

	unsigned long ShortBlockData::getBits(){
		return this->bits;
	}

	time_t ShortBlockData::getTimeCreated(){
		return this->timeCreated;
	}

	time_t ShortBlockData::getTimeRecieved(){
		return this->timeRecieved;
	}

	time_t ShortBlockData::getTimeLocked(){
		return this->timeLocked;
	}

	short ShortBlockData::getRawData(){
		return this->rawData;
	}

	void ShortBlockData::setHash() {
		if(this->hash != "")
			throw std::runtime_error("Hash has already been set");
		this->hash = computeHash();
	}

	void ShortBlockData::setTransactions(std::map<std::string, Transaction<TransactionData*>*> transactions){
		if(this->transactions.size() != 0)
			throw std::runtime_error("Transactions have already been set");
		this->transactions = transactions;
	}

	void ShortBlockData::setSize(unsigned long size){
		if(this->size != -1)
			throw std::runtime_error("Size has already been set");
		this->size = size;
	}

	void ShortBlockData::setTransactionCount(unsigned long count){
		if(this->transactionCount != -1)
			throw std::runtime_error("Transaction Count has already been set");
		this->transactionCount = count;
	}

	void ShortBlockData::setBits(unsigned long bits){
		if(this->bits != -1)
			throw std::runtime_error("Bits has already been set");
		this->bits = bits;
	}

	void ShortBlockData::setTimeCreated(time_t timeCreated){
		if(this->timeCreated != 0) {
			struct tm* timeinfo;
			timeinfo = localtime(&this->timeCreated);
			time_t _time = this->timeCreated;
			throw std::runtime_error("Block Data was already created at");
		}
		this->timeCreated = timeCreated;
	}

	void ShortBlockData::setTimeRecieved(time_t timeRecieved){
		if(this->timeRecieved != 0) {
			struct tm* timeinfo;
			timeinfo = localtime(&this->timeRecieved);
			time_t _time = this->timeRecieved;
			throw std::runtime_error("Block Data was already recieved");
		}
		this->timeRecieved = timeRecieved;
	}

	void ShortBlockData::setTimeLocked(time_t timeLocked){
		if(this->timeLocked != 0) {
			struct tm* timeinfo;
			timeinfo = localtime(&this->timeLocked);
			time_t _time = this->timeLocked;
			throw std::runtime_error("Block Data was already locked");
		}
		this->timeLocked = timeLocked;
	}

}