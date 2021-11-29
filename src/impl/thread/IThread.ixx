export module lira.thread.IThread;
import std.threading;
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