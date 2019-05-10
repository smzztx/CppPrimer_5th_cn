# cpplearn
ubuntu 14.04  
gcc version 4.8.4  
gcc -c thanks.c thanks_2.c  
gcc -o thanks thanks.o thanks_2.o  

g++ -c helloworld.cpp  
g++ -o hello helloworld.o  
//add C++11  
g++ -o sleep_time sleep_time.cpp -std=c++0x  
g++ -o helloworld helloworld.cpp -std=c++11  

// #define NDEBUG	//this is not work for assert(), we should use $ g++ -o ex47 ex47.cpp -D NDEBUG -std=c++11

gcc 4.8
regex(gcc4.9) hexfloat(gcc5)