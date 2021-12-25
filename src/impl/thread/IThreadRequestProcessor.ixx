export module lira.thread.IThreadRequestProcessor;
import lira.thread.IThread;
import std.core;
import std.threading;
export namespace lira::thread
{
	struct IRequestBase
	{
		bool finished = false;
		void Notify()
		{
			finished = true;
		}
		void Wait()
		{
			// is spinlocking a better a better option with such short requests?
			while(finished != true);
		}
		virtual ~IRequestBase() {}
	};
	template<typename Request> requires std::derived_from<Request, IRequestBase>
	class IThreadRequestProcessor : public IThread
	{
		std::mutex m_mutex;
		std::queue<Request*> m_requestQueue;
		bool m_keepRunning = true;
	private:
		Request* Pop()
		{
			auto* el = m_requestQueue.front();
			m_requestQueue.pop();
			return el;
		}
	protected:
		void run() override
		{
			while (m_keepRunning)
			{
				std::lock_guard g(m_mutex);
				if (!m_requestQueue.empty())
				{
					auto* req = Pop();
					ProcessRequest(*req);
					req->Notify();
				}
			}
		}
		virtual void ProcessRequest(const Request& r) = 0;
	public:
		virtual ~IThreadRequestProcessor() 
		{
			m_keepRunning = false;
			std::lock_guard g(m_mutex);
		}
		void stop()
		{
			m_keepRunning = false;
		}

		void Push(Request* r)
		{
			m_requestQueue.push(r);
			r->Wait();
		}
	};
}