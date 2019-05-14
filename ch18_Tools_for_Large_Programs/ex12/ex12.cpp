#include <iostream>
#include <string>
#include "TextQuery.h"
#include "Query.h"
#include "NotQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"

void runQueries(std::ifstream &infile)
{
    chapter10::TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        chapter10::print(std::cout, tq.query(s)) << std::endl;
        // tq.query(s);
    }
}

int main()
{
    std::ifstream file("../../ch12_Dynamic_Memory/storyDataFile");
    // runQueries(file);
    chapter10::TextQuery t(file);

    chapter15::Query q = chapter15::Query("fiery") & chapter15::Query("bird") | chapter15::Query("wind");
    std::cout << "------------" << std::endl;
    std::cout << q << std::endl;
    std::cout << "------------" << std::endl;
    chapter10::print(std::cout, q.eval(t)) << std::endl;

    return 0;
}