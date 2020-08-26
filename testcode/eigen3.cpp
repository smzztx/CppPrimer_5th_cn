#include <iostream>
#include <unistd.h>
#include <eigen3/Eigen/Eigenvalues>
#include <stdint.h>

typedef union    //ACC
{
 unsigned char b[4];
 float f;
}PID;

int main()
{
	float f = 0.1;
	// std::cout << int(f) << std::endl;
	PID P;
	P.f = 0.1;
	std::cout << std::hex << (int)P.b[0] << std::endl;
	std::cout << std::hex << (int)P.b[1] << std::endl;
	std::cout << std::hex << (int)P.b[2] << std::endl;
	std::cout << std::hex << (int)P.b[3] << std::endl;
	// P.b[0] = uint8_t(f & 0x000000ff);
	// P.b[1] = uint8_t((f & 0x000000ff)>>8);
	// P.b[2] = uint8_t((f & 0x000000ff)>>16);
	// P.b[3] = uint8_t((f & 0x000000ff)>>24);
	// std::cout << P.f << std::endl;

Eigen::MatrixXd m = Eigen::MatrixXd::Random(3,3);
  m = (m + Eigen::MatrixXd::Constant(3,3,1.2)) * 50;
  m << 1, 2, 3, 4, 5, 6, 7, 8, 9;
  std::cout << "m =" << std::endl << m << std::endl;
  Eigen::VectorXd v(3);
  v << 1, 2, 3;
  std::cout << "m * v =" << std::endl << m * v << std::endl;

	Eigen::Vector2d L_i = Eigen::Vector2d::Zero();
	std::cout << L_i << std::endl;
	L_i << 1,2;
	std::cout << L_i << std::endl;
	std::cout << L_i.transpose() << std::endl;
	std::cout << L_i * L_i.transpose() << std::endl;
	
	std::cout << "start" << std::endl;
	for (int i = 0; i < 101; ++i)
	{
		std::cout.width(3);
		std::cout << i << "%";
		std::cout << "\b\b\b\b";
		usleep(100000);
		// std::cout << i << std::endl;
		std::cout << std::flush;
	}
	std::cout << std::endl;
	std::cout << "end" << std::endl;
	
	return 0;
}