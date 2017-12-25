#pragma once
#include <time.h>
#include <chrono>

using namespace std::chrono;

class Timer {

public:
	Timer() {
		time_to_consume = 0;
	}

	void SetTime(double seconds) {
		time_to_consume = seconds;
	}

	void AddTime(double seconds) {
		time_to_consume += seconds;
	}

	void Start() {
		last_chrono_time = steady_clock::now();
	}

	void Pause() {
		paused = true;
	}

	void Resume() {
		last_chrono_time = steady_clock::now();
		paused = false;
	}

	bool IsExpired() const {
		return time_to_consume <= 0;
	}

	double GetRemainingTime() const {
		return time_to_consume;
	}

	double GetTotalTimeElapsed() {
		return totalTimeElapsed;
	}

	void ResetTotalTime() {
		totalTimeElapsed = 0.0;
	}

	void Update() {
		if (!paused && time_to_consume > 0) {
			duration<double> time_span = duration_cast<duration<double>>(steady_clock::now() - last_chrono_time);
			// timespan.count returns the number of seconds
			totalTimeElapsed += time_span.count();
			time_to_consume -= time_span.count();
			last_chrono_time = steady_clock::now();
			if (time_to_consume < 0) {
				time_to_consume = 0;
			}
		}
	}

private:
	steady_clock::time_point last_chrono_time;
	double time_to_consume;
	bool paused = false;
	double totalTimeElapsed = 0.0;
};