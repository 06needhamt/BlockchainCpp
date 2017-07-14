#pragma once

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
#include <string> // std::string
#include <ctime> // time_t localtime() struct tm* asctime()
#include <chrono> // std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::nanoseconds
#include <stdexcept> // throw throw std::runtime_error()
#include <map> // std::map
#include "transactiondata.hpp"
#include "transactioninput.hpp"
#include "transactionoutput.hpp"

namespace BlockchainCpp {
	
	template <class T>
	
	class Transaction {
		public:
			
			std::vector<unsigned char> toBytes() {
				return std::vector<unsigned char>();
			}

			std::string toString() {
				return "";
			}
			bool verify() {

			}

			std::string getHash() const {
				return hash;
			}

			void setHash(std::string hash) {
				this->hash = hash
			}

			std::map<std::string, TransactionInput*> getInputs() const {
				return inputs;
			}

			void setInputs(std::map<std::string, TransactionInput*> inputs) {
				this->inputs = inputs
			}

			std::map<std::string, TransactionOutput*> getOutputs() const {
				return outputs;
			}

			void setOutputs(std::map<std::string, TransactionOutput*> outputs) {
				this->outputs = outputs
			}

			double getValue() const {
				return value;
			}

			void setValue(double value) {
				this->value = value;
			}

			time_t getTimeCreated() const {
				return timeCreated;
			}

			void setTimeCreated(time_t time_created) {
				timeCreated = time_created;
			}

			time_t getTimeLocked() const {
				return timeLocked;
			}

			void setTimeLocked(time_t time_locked) {
				timeLocked = time_locked;
			}

			time_t getTimeConfirmed() const {
				return timeConfirmed;
			}

			void setTimeConfirmed(time_t time_confirmed) {
				timeConfirmed = time_confirmed;
			}

			T* getData() const {
				return data;
			}

			void setData(T* data) {
				this->data = data;
			}


			friend bool operator==(const Transaction& lhs, const Transaction& rhs) {
				return lhs.hash == rhs.hash
					&& lhs.inputs == rhs.inputs
					&& lhs.outputs == rhs.outputs
					&& lhs.value == rhs.value
					&& lhs.timeCreated == rhs.timeCreated
					&& lhs.timeLocked == rhs.timeLocked
					&& lhs.timeConfirmed == rhs.timeConfirmed
					&& lhs.data == rhs.data;
			}

			friend bool operator!=(const Transaction& lhs, const Transaction& rhs) {
				return !(lhs == rhs);
			}

		protected:

		private:

		std::string computeHash() {

		}

		std::string hash;
		std::map<std::string, TransactionInput*> inputs;
		std::map<std::string, TransactionOutput*> outputs;
		double value;
		time_t timeCreated;
		time_t timeLocked;
		time_t timeConfirmed;
		T* data;
	};
}