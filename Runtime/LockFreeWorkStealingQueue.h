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
			LockFreeWorkStealingQueue();

			// Добавление задачи в конец очереди
			void push(const T & aElem);
			// Удаление задачи из начала очереди
			bool pop(T & aElem);
			// Кража задачи из конца очереди
			bool steal(T & aElem);

		private:
			std::atomic_size_t mHeadPos;
			std::atomic_size_t mTailPos;
			size_t mSize;

			std::vector<T> mQueue;
		};

		template<typename T>
		LockFreeWorkStealingQueue<T>::LockFreeWorkStealingQueue() : 
			mHeadPos(0), mTailPos(0), mSize(32), mQueue(mSize)
		{
		}

		template<typename T>
		void LockFreeWorkStealingQueue<T>::push(const T & aElem)
		{
			size_t tailPos = mTailPos.load(std::memory_order_acquire);

			if (tailPos < mSize)
			{
				mQueue[tailPos] = aElem;
				mTailPos.store(tailPos + 1, std::memory_order_release);
			}
			else
			{
				// Увеличиваем размер очереди.
				size_t headPos;

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

				size_t numJobs = tailPos - headPos;

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

		template<typename T>
		bool LockFreeWorkStealingQueue<T>::pop(T & aElem)
		{
			size_t tailPos = mTailPos.load(std::memory_order_acquire);
			if (tailPos == 0) return false;
			tailPos -= 1;
			mTailPos.store(tailPos, std::memory_order_release);
			std::atomic_thread_fence(std::memory_order_seq_cst);
			size_t headPos = mHeadPos.load(std::memory_order_acquire);

			if (tailPos < headPos)
			{
				mTailPos.store(headPos, std::memory_order_relaxed);
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
					if (mHeadPos.compare_exchange_strong(headPos, headPos + 1))
					{
						aElem = mQueue[headPos];
						mTailPos.store(headPos + 1, std::memory_order::memory_order_relaxed);
						return true;
					}
					else
					{
						mTailPos.store(headPos, std::memory_order::memory_order_relaxed);
						return false;
					}
				}
			}
		}

		template<typename T>
		bool LockFreeWorkStealingQueue<T>::steal(T & aElem)
		{
			size_t headPos = mHeadPos.load(std::memory_order_acquire);
			const size_t tailPos = mTailPos.load(std::memory_order_acquire);

			if (headPos < tailPos)
			{
				if (mHeadPos.compare_exchange_strong(headPos, headPos + 1))
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
	}
}