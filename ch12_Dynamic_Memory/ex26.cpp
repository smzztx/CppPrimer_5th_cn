#include <iostream>
#include <string>
#include <memory>

int main()
{
    std::allocator<std::string> alloc;
    auto const p = alloc.allocate(5);
    auto q = p;
    alloc.construct(q++);
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++, "hi");
    
    while(q != p)
    {
        std::cout << *(--q) << std::endl;
        alloc.destroy(q);
    }
    alloc.deallocate(p, 5);

    return 0;
}