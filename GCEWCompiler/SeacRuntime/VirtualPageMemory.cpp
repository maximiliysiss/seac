#include "VirtualPageMemory.h"
#include "bitset.h"

namespace seac::runtime {

	using namespace helper;

	Storage* seac::runtime::Storage::create_storage(uint id, uint prop, void* data, uint size)
	{
		Storage* st = nullptr;
		void* dataCpy = malloc(size);
		memcpy(dataCpy, data, size);

		if (prop & 1) {

		}
		else if (prop & (1 << 1)) {
			st = new StringStorage(id, dataCpy);
		}
		else {
			st = new Storage(id, dataCpy, size);
		}

		if (st)
			st->prop = prop;

		return st;
	}

	Storage* seac::runtime::Storage::create_storage(uint id, uint prop, uint size)
	{
		Storage* st = nullptr;

		if (prop & 1) {

		}
		else if (prop & (1 << 1)) {
			st = new StringStorage(id, nullptr);
		}
		else {
			st = new Storage(id, calloc(1, size), size);
		}

		if (st)
			st->prop = prop;

		return st;
	}

	Storage::Storage(ull id, void* data, uint size)
		:data(data), id(id), size(size) {
	}

	void Storage::setValue(void* newData, uint size) {
		if (data)
			delete data;
		data = newData;
		this->size = size;
	}

	void* Storage::getCpy() {
		void* cpy = malloc(size);
		memcpy(cpy, data, size);
		return cpy;
	}

	Storage::~Storage() {
		delete data;
	}

	StringStorage::StringStorage(ull id, void* data)
		:Storage(id, data, 0) {
		if (data)
			size = strlen((char*)data) + 1;
	}

	Storage& StringStorage::operator-(Storage&& s2){
		throw helpers::runtime("invalid operation for string");
	}

	Storage& StringStorage::operator-(Storage& s2){
		throw helpers::runtime("invalid operation for string");
	}

	Storage& StringStorage::operator*(Storage&& s2){
		throw helpers::runtime("invalid operation for string");
	}

	Storage& StringStorage::operator*(Storage& s2){
		throw helpers::runtime("invalid operation for string");
	}

	Storage& StringStorage::operator/(Storage&& s2){
		throw helpers::runtime("invalid operation for string");
	}

	Storage& StringStorage::operator/(Storage& s2){
		throw helpers::runtime("invalid operation for string");
	}

	Storage& Storage::operator+(Storage&& s2) {
		return (*this) + s2;
	}

	Storage& Storage::operator+(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset f(getCpy(), size);
		bitset s(s2.getCpy(), s2.size);

		auto res = f + s;
		Storage* newStorage = new Storage(-1, res.cpy(), resSize);
		return *newStorage;
	}

	Storage& Storage::operator-(Storage&& s2) {
		return (*this) - s2;
	}

	Storage& Storage::operator-(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = x - y;

		Storage* newStorage = new Storage(-1, res.cpy(), resSize);
		return *newStorage;
	}

	Storage& Storage::operator*(Storage&& s2) {
		return (*this) * s2;
	}

	Storage& Storage::operator*(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = x * y;

		Storage* newStorage = new Storage(-1, res.cpy(), resSize);
		return *newStorage;
	}

	Storage& Storage::operator/(Storage&& s2) {
		return (*this) / s2;
	}

	Storage& Storage::operator/(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = x / y;

		Storage* newStorage = new Storage(-1, res.cpy(), resSize);
		return *newStorage;
	}

	Storage& Storage::operator<(Storage&& s2) {
		return (*this) < s2;
	}

	Storage& Storage::operator<(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = bitset::create_bitset(x < y);

		Storage* newStorage = new Storage(-1, res.cpy(), res.get_size());
		return *newStorage;
	}

	Storage& Storage::operator>(Storage&& s2) {
		return (*this) > s2;
	}

	Storage& Storage::operator>(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = bitset::create_bitset(x > y);

		Storage* newStorage = new Storage(-1, res.cpy(), res.get_size());
		return *newStorage;
	}

	Storage& Storage::operator==(Storage&& s2) {
		return (*this) == s2;
	}

	Storage& Storage::operator==(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = bitset::create_bitset(x == y);

		Storage* newStorage = new Storage(-1, res.cpy(), res.get_size());
		return *newStorage;
	}

}