#include <iostream>
#include <cstdlib>

const float X = 1.0;
const int ARRAY_SIZE = 10;
const float DEFAULT_REWARD = 5;
const int NUM_STEPS = 100;

using namespace std;

int find_max(float passed_array[ARRAY_SIZE]) {
	int max_val = passed_array[0];
	int loc = 0;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if(passed_array[i] > max_val) {
			max_val = passed_array[i];
			loc = i;
		}
	}
	return loc;
}

float random_task_value() {
	float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/X));	return r;
	return r;	
}

float step_function(float tre[ARRAY_SIZE], float tra[ARRAY_SIZE], int step) {
	float reward = 0;

	// locate array value for greedy selection
	int loc = find_max(&tre[ARRAY_SIZE]);
	
	// add to reward_total
	reward = tra[loc]; 

	cout << "Adjusting " << tre[loc] << " at " << loc;

	// adjust expected rewards
	// THIS DOESN'T WORK!!
	tre[loc] = tre[loc] + (1/step)*(DEFAULT_REWARD-tre[loc]);

	cout << " to " << tre[loc] << endl;

	return reward;
}

int main() {
	// create array_size random task values between 0 and 1
	float task_rewards_actual[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++) {
		task_rewards_actual[i] = random_task_value();
	}

	// create expected values array of DEFAULT_REWARD value
	float task_rewards_expected[ARRAY_SIZE]; 
	for (int i = 0; i < ARRAY_SIZE; i++) {
		task_rewards_expected[i] = DEFAULT_REWARD;
	}

	float reward_total = 0;

	// take step_num steps
	for (int i = 0; i < NUM_STEPS; i++) {
		reward_total += step_function(task_rewards_expected, task_rewards_actual, i);
	}

	return 0;
}