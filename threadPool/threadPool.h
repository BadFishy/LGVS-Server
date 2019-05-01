
#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <stdexcept>
#include <condition_variable>
#include <memory> //unique_ptr
#include <functional>

const int MAX_THREADS = 1000; //����߳���Ŀ

typedef std::function<void(void)> Task;

class threadPool
{
public:
	/*Ĭ�Ͽ�һ���߳�*/
	threadPool(int number = 6) ;
	~threadPool();
	/*��������У�task_queue�����������<T *>*/
	bool append(Task task);

private:
	/*�����߳���Ҫ���еĺ���,���ϵĴ����������ȡ����ִ��*/
	static void *worker(void *arg);
	void run();

private:
	std::vector<std::thread> work_threads; /*�����߳�*/
	std::queue<Task> tasks_queue;		   /*�������*/

	std::mutex queue_mutex;
	std::condition_variable condition; /*������unique_lock���ʹ��*/
	bool stop;
};
