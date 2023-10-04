#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
int main() {
  const int kLogPower = 2;
  const int kDecimal = 15;
  int number;
  std::cin >> number;
  std::vector<double> sounds;
  sounds.resize(number + 1);
  double sound0;
  sounds[0] = 0;
  std::cin >> sound0;
  sound0 = log2(sound0);
  sounds[1] = sound0;
  double prefsum = sound0;
  for (int cnt = 2; cnt < number + 1; cnt++) {
    double sound;
    std::cin >> sound;
    sound = log2(sound);
    prefsum += sound;
    sounds[cnt] = prefsum;
  }
  int segment;
  std::cin >> segment;
  for (int element = 0; element < segment; element++) {
    int left;
    int right;
    std::cin >> left >> right;
    double ans;
    ans = sounds[right + 1] - sounds[left];
    ans = pow(kLogPower, ans / (right - left + 1));
    std::cout << std::setprecision(kDecimal) << ans << std::endl;
  }
}
