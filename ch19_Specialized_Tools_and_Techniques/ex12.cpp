#include <string>
#include <iostream>

class Screen {
    public:
        using pos = std::string::size_type;

        static const std::string Screen::*data() { return &Screen::contents; }
        Screen() = default;
        Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

        char get() const { return contents[cursor]; }
        char get(pos r, pos c) const { return contents[r*width+c]; }

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};

int main()
{
    // const std::string Screen::*pdata;
    // pdata = &Screen::contents;
    // auto pdata = &Screen::contents;  //contents is private

    const std::string Screen::*pdata = Screen::data();
    Screen myScreen(2, 2, 'c');
    auto s = myScreen.*pdata;
    std::cout << s << std::endl;

    return 0;
}