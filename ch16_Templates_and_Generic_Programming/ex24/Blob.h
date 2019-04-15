#ifndef BLOB_H_
#define BLOB_H_

#include <vector>
#include <memory>

template <typename T>
class Blob
{
public:
	// template <typename It>
	// Blob(It begin, It end) : data(std::make_shared<std::vector<T>>(begin, end)) { }
	template <typename It>
	Blob(It begin, It end);
private:
	std::shared_ptr<std::vector<T>> data;
};

template <typename T>
template <typename It>
Blob<T>::Blob(It begin, It end) : data(std::make_shared<std::vector<T>>(begin, end)) { }

#endif