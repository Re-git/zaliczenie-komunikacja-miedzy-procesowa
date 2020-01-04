#include <iostream> // input / output
#include <thread>   // thread api
#include <vector>   // std::vector
#include <atomic>   // std::atomic

//c++14 standard:
//Specializations and instantiations of the atomic template shall have a deleted copy constructor, a deleted
//copy assignment operator, and a constexpr value constructor.
//shortly => primities, POD

class Wallet {
public:
	void addMoney(int val) {
		for(int i = 0 ; i < val; i++)
			_money++;
	}

	void removeMoney(int val) { 
		_money -= val; 
	}

	int checkMoney() { std::cout << _money << std::endl; }

private:
	std::atomic<int> _money{};
};

void checkThreads() 
{
	Wallet myWallet;
	std::vector<std::thread> thVec;
	thVec.reserve(5);
	
	for(int i = 0 ; i < 5 ; i++) {
		thVec.emplace_back(std::thread(&Wallet::addMoney, &myWallet, 10000));
	}

	for(std::thread& th : thVec) {
		th.join();
	}
	
	myWallet.checkMoney();
}

int main(int argc, char* argv[])
{
	for(int i = 0 ; i < 10 ; i++)	
		checkThreads();
	
	return 0;
}
