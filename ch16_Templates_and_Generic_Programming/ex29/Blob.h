#ifndef BLOB_H_
#define BLOB_H_

#include <vector>
#include <memory>
#include "shared_pointer.h"

template <typename T>
class Blob
{
public:
	// template <typename It>
	// Blob(It begin, It end) : data(std::make_shared<std::vector<T>>(begin, end)) { }
	template <typename It>
	Blob(It begin, It end);
private:
	cp5::shared_pointer<std::vector<T>> data;
};

template <typename T>
template <typename It>
Blob<T>::Blob(It begin, It end) : data(std::make_shared<std::vector<T>>(begin, end)) { }

#endif