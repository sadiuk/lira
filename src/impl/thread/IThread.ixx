#include <thread>
export module lira.thread.IThread;

export namespace lira::thread
{
	class IThread
	{
		std::thread m_thread;
	public:
		IThread() : m_thread(&IThread::run, this)
		{
		}

		virtual ~IThread()
		{
			m_thread.join();
		}
		virtual void run() = 0;
	};
}