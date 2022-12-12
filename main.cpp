#include "smpl.h"

int main() {
	E e;
	std::string inp;
	while (1 == 1) {
	std::cout << "smpl > ";
	std::getline(std::cin, inp);
	e = run(inp);
	std::cout << inp << "\n";
	std::cout << e.out();
	}
	return 0;
}

