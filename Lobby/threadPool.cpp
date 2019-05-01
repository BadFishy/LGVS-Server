#include "threadPool.h"

threadPool::threadPool(int number) : stop(false)
{
	if (number <= 0 || number > MAX_THREADS)
		throw std::exception();
	for (int i = 1; i <= number; i++)
	{
		std::cout << "������" << i << "���߳� " << std::endl;
		work_threads.emplace_back(threadPool::worker, this);
	}
}

 threadPool::~threadPool()
{
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		stop = true;
	}
	condition.notify_all();
	for (auto &ww : work_threads)
		ww.join();
}

bool threadPool::append(Task task)
{
	/*������������ʱһ��Ҫ��������Ϊ���������̹߳���*/
	queue_mutex.lock();
	tasks_queue.push(task);
	queue_mutex.unlock();
	condition.notify_one(); //�̳߳���ӽ�ȥ��������ȻҪ֪ͨ�ȴ����߳�
	return true;
}
void *threadPool::worker(void *arg)
{
	threadPool *pool = (threadPool *)arg;
	pool->run();
	return pool;
}
void threadPool::run()
{
	while (!stop)
	{
		std::unique_lock<std::mutex> lk(this->queue_mutex);
		/*��unique_lock() ����������Զ�������*/
		this->condition.wait(lk, [this] { return !this->tasks_queue.empty(); });
		//���������в�Ϊ�գ���ͣ�����ȴ�����
		if (this->tasks_queue.empty())
		{
			continue;
		}
		else
		{
			Task task = tasks_queue.front();
			tasks_queue.pop();
			task();
		}
	}
}