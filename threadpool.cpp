#include "threadpool.h"

using namespace std;

ThreadPool::ThreadPool() {
	
}

ThreadPool::ThreadPool(int nbrThreads) {
	//-Constructeur-//
	/* Crée un ThreadPool avec nbrThread qui est le nombre de thread "ordinateur",
	 * c'est à dire le nombre de coeurs du CPU
	*/
	
	shutdown = false; // FLAG
	threads.reserve(nbrThreads); // Libère 4 espaces mémoires (tread) dans le vecteur threads
	
	for (int i = 0; i < nbrThreads; i++) {
		threads.emplace_back(std::bind(&ThreadPool::entry, this, i));													
	}
}


ThreadPool::~ThreadPool() {
	//-Destructeur-//
	{
		unique_lock <std::mutex> loc(queueLock); // Empêche le passage à un autre thread
		shutdown = true;
	}
	condition.notify_all(); // Notifie tout les threads de regarder si shutdown=true
	
	for (auto& thread : threads) {
		thread.join(); // Attend tout les threads
	}
}

void ThreadPool::addJob(function <void(void)> func) {
	// Ajoute un job à la liste à faire
	{
		unique_lock <mutex> lock(queueLock);
		pool.push_back(func); // Ajout à la fin de la list<> pool de la fonction func
	}
	condition.notify_one();
}

void ThreadPool::entry(int i) {
	function <void (void)> job; // tâche à faire
	
	while(true) {
		{
			unique_lock<mutex> lock(queueLock);
			
			while (!shutdown && pool.empty()) {
				// thread attend un changement de condition
				condition.wait(lock);
			}
			
			if (shutdown && pool.empty()) {
				// Fin de fonction
				break;
			}
			
			// FIFO (First In First Out)
			// Réassigne une fonction à faire au thread
			job = pool.front();  // pseudocode : job = job<1>
			pool.pop_front(); // pseudocode : job<-1>.delete()
			
		}
		
		job(); // Exécute le gotoh
	}
}
