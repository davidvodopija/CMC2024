class Util {
 public:
  template <typename T>
  static T clamp(T value, T lb, T ub) {
    if (value > ub) return ub;
    if (value < lb) return lb;
    return value;
  }
};