#pragma once

#include <vector>
#include <atomic>

namespace FPTL {
	namespace Runtime {

		// Очередь для хранения заданий. Неблокирующая версия.
		template <typename T>
		class LockFreeWorkStealingQueue
		{
		public:
			LockFreeWorkStealingQueue() : mHeadPos(0), mTailPos(0), mSize(32), mQueue(mSize)
			{}

			void push(const T & aElem)
			{
				int tailPos = mTailPos.load(std::memory_order_acquire);

				if (tailPos < mSize)
				{
					mQueue[tailPos] = aElem;
					mTailPos.store(tailPos + 1, std::memory_order_release);
				}
				else
				{
					// Увеличиваем размер очереди.

					int headPos = -1;

					// Нужно не дать крадущим потокам делать свою работу.
					// Для этого подменяем позицию чтения крадущего потока.
					while (true)
					{
						// Запоминаем позицию для "кражи".
						headPos = mHeadPos.load(std::memory_order_acquire);

						// Ждем, пока крадущий поток закончит свои действия.
						if (mHeadPos.compare_exchange_strong(headPos, tailPos))
							break;
					}

					int numJobs = tailPos - headPos;

					if (headPos > 0)
					{
						for (size_t i = 0; i < numJobs; i++)
						{
							mQueue[i] = mQueue[i + headPos];
						}

						mTailPos.store(numJobs, std::memory_order_relaxed);
					}

					// Увеличиваем размер очереди.
					mSize *= 2;
					mQueue.resize(mSize);

					// Добавляем элемент.
					mQueue[numJobs] = aElem;
					mTailPos.store(numJobs + 1, std::memory_order_relaxed);

					// Разрешаем "красть" задания дальше.
					mHeadPos.store(0, std::memory_order_release);
				}
			}

			bool pop(T & aElem)
			{
				int tailPos = mTailPos.load(std::memory_order_acquire) - 1;

				mTailPos.store(tailPos, std::memory_order_release);

				int headPos = mHeadPos.load(std::memory_order_acquire);

				if (tailPos < headPos)
				{
					mTailPos.store(headPos, std::memory_order_release);
					return false;
				}
				else
				{
					if (tailPos > headPos)
					{
						aElem = mQueue[tailPos];						
						return true;
					}
					else
					{
						if (mHeadPos.compare_exchange_strong(headPos, headPos + 1, std::memory_order_acq_rel))
						{
							aElem = mQueue[headPos];
							mTailPos.store(headPos + 1, std::memory_order::memory_order_release);
							return true;
						}
						else
						{
							mTailPos.store(headPos, std::memory_order::memory_order_release);
							return false; 
						}
					}
				}
			}

			bool steal(T & aElem)
			{
				int headPos = mHeadPos.load(std::memory_order_acquire);
				int tailPos = mTailPos.load(std::memory_order_acquire);

				if (headPos < tailPos)
				{
					if (mHeadPos.compare_exchange_strong(headPos, headPos + 1, std::memory_order_acq_rel))
					{
						aElem = mQueue[headPos];
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}

		private:

			std::atomic_int mHeadPos;
			std::atomic_int mTailPos;

			int mSize;
			std::vector<T> mQueue;
		};

	}
}