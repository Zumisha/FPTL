#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

#include <boost/optional.hpp>

namespace FPTL
{
	namespace Runtime
	{
		template <typename T> class BlockingQueue
		{
		public:
			BlockingQueue() : mQuit(false)
			{
			}

			void push(const T & elem)
			{
				std::unique_lock<std::mutex> lock(mMutex);
				mQueue.push(elem);
				mCond.notify_one();
			}

			void push(T && elem)
			{
				std::unique_lock<std::mutex> lock(mMutex);
				mQueue.push(std::move(elem));
				mCond.notify_one();
			}

			boost::optional<T> pop()
			{
				std::unique_lock<std::mutex> lock(mMutex);
				mCond.wait(lock, [this]() { return !mQueue.empty() || mQuit; });

				if (!mQueue.empty())
				{
					boost::optional<T> ret(std::move(mQueue.front()));
					mQueue.pop();
					return ret;
				}

				return boost::optional<T>();
			}

			void quit()
			{
				std::unique_lock<std::mutex> lock(mMutex);
				mQuit = true;
				mCond.notify_one();
			}

		private:
			std::queue<T> mQueue;
			std::mutex mMutex;
			std::condition_variable mCond;
			bool mQuit;
		};
	}
}
