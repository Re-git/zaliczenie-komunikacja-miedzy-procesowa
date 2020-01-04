#include <iostream> // input / output
#include <thread>   // thread api
#include <vector>   // std::vector
#include <mutex>    // std::mutex

class Wallet {
public:
	void addMoney(int val) {
		_myMutex.lock();
			for(int i = 0 ; i < val; i++)
				_money++;
		_myMutex.unlock();
	}

	void removeMoney(int val) { 
		_myMutex.lock();
			_money -= val; 
		_myMutex.unlock();
	}

	int checkMoney() { std::cout << _money << std::endl; }

private:
	int _money{};
	std::mutex _myMutex;
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
