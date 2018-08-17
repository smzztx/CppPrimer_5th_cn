#ifndef SCREEN_EX23_H_
#define SCREEN_EX23_H_

#include <string>
#include <vector>

class Screen;

class Window_mgr
{
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens;
};

class Screen 
{
friend void Window_mgr::clear(ScreenIndex);
public:
    using pos = std::string::size_type;

    Screen() = default;
    Screen(pos ht, pos wd):height(ht), width(wd){ }
    Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

    char get() const { return contents[cursor]; }
    char get(pos r, pos c) const { return contents[r*width+c]; }
    Screen &move(pos r, pos c);
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream &os) {do_display(os); return *this;}
    const Screen &display(std::ostream &os) const {do_display(os); return *this;}

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    void do_display(std::ostream &os) const {os << contents;}
};



inline Screen &Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

inline Screen &Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

inline Screen &Screen::set(pos r, pos col, char c)
{
	contents[r*width + col] = c;
	return *this;
}

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

#endif