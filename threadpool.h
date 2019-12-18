#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <queue>
#include <list>
#include <vector>

class ThreadPool {
	
	public :
		ThreadPool();
		ThreadPool(int nbrThreads);
		~ThreadPool();
		void addJob(std::function <void (void)>);
		void wait();
		void stop();
		
	private :
		void entry(int i);
		
		std::mutex queueLock;  
		std::condition_variable condition; // Notificateur de thread
		std::list<std::function<void (void)>> pool;
		std::vector <std::thread> threads;
		bool shutdown;
		
	
		
		
};
