#pragma once

#include <mutex>
#include <condition_variable>

template <typename T>
class vlock {
	std::mutex m;
	std::condition_variable cv;
	T val;
public:
	void set_callback(T val) {
		this->val = val;
		cv.notify_one();
	}

	T wait() {
		std::unique_lock lk(m);
		cv.wait(lk);

		return val;
	}
};
