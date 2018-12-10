#include "book_ex24.h"

Book& Book::operator=(const Book &rhs)
{
        this->no_ = rhs.no_;
        this->name_ = rhs.name_;
        this->author_ = rhs.author_;
        this->pubdate_ = rhs.pubdate_;

    return *this;
}

Book& Book::operator=(const Book &&rhs) noexcept
{
    if(this != &rhs)
    {
        this->no_ = rhs.no_;
        this->name_ = rhs.name_;
        this->author_ = rhs.author_;
        this->pubdate_ = rhs.pubdate_;
    }

    return *this;
}

std::istream& operator>>(std::istream &in, Book &book)
{
    in >> book.no_ >> book.name_ >> book.author_ >> book.pubdate_;
    return in;
}

std::ostream& operator<<(std::ostream &out, const Book &book)
{
    out << book.no_ << " " << book.name_ << " " << book.author_ << " " << book.pubdate_;
    return out;
}

bool operator==(const Book &lhs, const Book &rhs)
{
    return lhs.no_ == rhs.no_;
}

bool operator!=(const Book &lhs, const Book &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Book &lhs, const Book &rhs)
{
	return lhs.no_ < rhs.no_;
}

bool operator>(const Book &lhs, const Book &rhs)
{
	return rhs < lhs;
}

bool operator<=(const Book &lhs, const Book &rhs)
{
	return !(rhs < lhs);
}

bool operator>=(const Book &lhs, const Book &rhs)
{
	return !(lhs < rhs);
}