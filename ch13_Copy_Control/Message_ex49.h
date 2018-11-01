#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <set>
#include <utility>

class Folder;

class Message
{
	friend class Folder;
	friend void swap(Message&, Message&);
public:
	explicit Message(const std::string &str = "") : contents(str) { };
	Message(const Message&);
	Message(Message&& m) : contents(std::move(m.contents))
	{
		move_Folders(&m);
	}
	Message& operator=(const Message&);
	Message& operator=(Message&&);
	~Message();
	void save(Folder&);
	void remove(Folder&);
	void move_Folders(Message*);
private:
	std::string contents;
	std::set<Folder*> folders;
	void add_to_Folders(const Message&);
	void remove_from_Folders();
	void addFldr(Folder *f) { folders.insert(f); }
	void remFldr(Folder *f) { folders.erase(f); }
};

class Folder
{
	friend void swap(Folder&, Folder&);
	friend class Message;
public:
	Folder() = default;
	Folder(const Folder &);
	Folder& operator=(const Folder&);
	~Folder();
private:
	std::set<Message*> msgs;
	void add_to_Message(const Folder&);
	void remove_from_Message();
	void addMsg(Message *m) { msgs.insert(m); }
	void remMsg(Message *m) { msgs.erase(m); }
};

void Message::move_Folders(Message *m)
{
	folders = std::move(m->folders);
	for(auto f : folders)
	{
		f->remMsg(m);
		f->addMsg(this);
	}
	m->folders.clear();
}

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
	for(auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message & m) : contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Folders()
{
	for(auto f : folders)
		f->remMsg(this);
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

Message& Message::operator=(Message &&rhs)
{
	if(this != &rhs)
	{
		remove_from_Folders();
		contents = std::move(rhs.contents);
		move_Folders(&rhs);
	}
	return *this;
}
// void swap(Message &lhs, Message &rhs)
// {
// 	using std::swap;
// 	for(auto f : lhs.folders)
// 		f->remMsg(&lhs);
// 	for(auto f : rhs.folders)
// 		f->remMsg(&rhs);
// 	swap(lhs.folders, rhs.folders);
// 	swap(lhs.contents, rhs.contents);
// 	for(auto f : lhs.folders)
// 		f->addMsg(&lhs);
// 	for(auto f : rhs.folders)
// 		f->addMsg(&rhs);
// }

void Folder::add_to_Message(const Folder &f)
{
	for(auto m : f.msgs)
		m->addFldr(this);
}

Folder::Folder(const Folder &f) : msgs(f.msgs)
{
	add_to_Message(f);
}

void Folder::remove_from_Message()
{
	for(auto m : msgs)
		m->remFldr(this);
}

Folder::~Folder()
{
	remove_from_Message();
}

Folder &Folder::operator=(const Folder &rhs)
{
	remove_from_Message();
	msgs = rhs.msgs;
	add_to_Message(rhs);
	return *this;
}

#endif