#include <iostream>

#define MAX_C 12
#define MAX_S 10

using namespace std;

int num_tests;
int num_courses;
int num_must_take;
int num_semester;
int max_course_in_semester;

int priors[MAX_C];
int courses[MAX_S];

int get_candidate(int taken) {
  int candidate = 0;
  for (int i = 0; i < num_courses; ++i) {
    int course_in_bit = (1 << i);
    // If taken, pass
    if ((taken & course_in_bit) > 0) continue;

    // If there is a course that has no prior
    if (priors[i] == 0 || (priors[i] & ~taken) == 0) {
      candidate |= course_in_bit;
    }
  }
  return candidate;
}

int try_to_take(int candidate, int semester) {
  return candidate & courses[semester];
}

int get_count(int taken) {
  int count = 0;
  while (taken > 0) {
    ++count;
    taken &= (taken - 1);
  }
  return count;
}

int get_min_semester(int taken, int start_semester) {
  if (get_count(taken) >= num_must_take) return 0;
  int min_semester = MAX_S + 1;
  for (int semester = start_semester; semester < num_semester; ++semester) {
    int candidate = get_candidate(taken);
    int can_take = try_to_take(candidate, semester);
    if (can_take) {
      int next_taken = taken | can_take;
      int curr_min_semester = get_min_semester(next_taken, semester + 1) + 1;
      if (curr_min_semester < min_semester) {
        min_semester = curr_min_semester;
      }
    }
  }
  return min_semester;
}

void solution() {
  if (num_must_take == 0) {
    cout << 0 << endl;
    return;
  }
  int taken = 0;
  int answer = get_min_semester(0, 0);
  if (answer > MAX_S) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << answer << endl;
  }
}

int main() {
  cin.sync_with_stdio(false);

  cin >> num_tests;
  while (--num_tests >= 0) {
    cin >> num_courses;
    cin >> num_must_take;
    cin >> num_semester;
    cin >> max_course_in_semester;

    for (int i = 0; i < num_courses; ++i) {
      int count; cin >> count;
      priors[i] = 0;
      for (int j = 0; j < count; ++j) {
        int course; cin >> course;
        priors[i] |= (1 << course);
      }
    }

    for (int i = 0; i < num_semester; ++i) {
      int count; cin >> count;
      courses[i] = 0;
      for (int j = 0; j < count; ++j) {
        int course; cin >> course;
        courses[i] |= (1 << course);
      }
    }

    solution();
  }

  return 0;
}