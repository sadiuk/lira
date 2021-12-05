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
		std::mutex m;
		std::queue<Request*> m_request_queue;
		bool keepRunning = true;
	private:
		Request* Pop()
		{
			auto* el = m_request_queue.front();
			m_request_queue.pop();
			return el;
		}
	protected:
		void run() override
		{
			while (keepRunning)
			{
				std::lock_guard g(m);
				if (!m_request_queue.empty())
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
			keepRunning = false;
			std::lock_guard g(m);
		}
		void stop()
		{
			keepRunning = false;
		}

		void Push(Request* r)
		{
			m_request_queue.push(r);
			r->Wait();
		}
	};
}