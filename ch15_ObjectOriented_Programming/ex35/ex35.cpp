#include <iostream>
#include <string>
#include "TextQuery.h"
#include "Query.h"
#include "NotQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
        // tq.query(s);
    }
}

int main()
{
    // std::ifstream file("../../ch12_Dynamic_Memory/storyDataFile");
    // runQueries(file);

    Query q = ~Query("fiery") & Query("bird") | Query("wind");
    std::cout << q.rep() << std::endl;
    return 0;
}