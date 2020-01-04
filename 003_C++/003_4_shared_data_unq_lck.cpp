#include <iostream> // input / output
#include <thread>   // thread api
#include <vector>   // std::vector
#include <mutex>    // std::mutex

class Wallet {
public:
	void addMoney(int val) {
		std::unique_lock<std::mutex> lk{_myMutex};
			for(int i = 0 ; i < val; i++)
				_money++;
		//lk.unlock(); //mozna zrobic
	}

	void removeMoney(int val) { 
		std::unique_lock<std::mutex> lk{_myMutex};
			_money -= val; 
		//lk.unlock(); //mozna zrobic
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
