#include <mutex>
#include <queue>

export module lira.thread.IThreadRequestProcessor;
import lira.thread.IThread;

export namespace lira::thread
{
	template<typename Request>
	class IThreadRequestProcessor : public IThread
	{
		std::mutex m;
		std::queue<Request> m_request_queue;
		bool keepRunning = true;
	private:
		Request Pop()
		{
			(void)std::unique_lock(m);
			auto el = m_request_queue.front();
			m_request_queue.pop();
			return el;
		}
	protected:
		void run() override
		{
			while (keepRunning)
			{
				if (!m_request_queue.empty())
				{
					auto req = Pop();
					ProcessRequest(req);
				}
			}
		}
		virtual void ProcessRequest(const Request& r) = 0;
	public:
		virtual ~IThreadRequestProcessor() = default;
		void stop()
		{
			keepRunning = false;
		}

		void Push(const Request& r)
		{
			(void)std::unique_lock(m);
			m_request_queue.push(r);
		}
	};
}