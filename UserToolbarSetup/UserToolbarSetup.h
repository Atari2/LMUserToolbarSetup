
#include <iostream>

template <typename T, auto P> class AddPre {
  private:
    const T &ref;

  public:
    AddPre(const T &r) : ref(r) {}
    friend std::ostream &operator<<(std::ostream &os, AddPre<T, P> s) { return os << P << s.ref; }
};

template <typename First, typename... Args> void Error(First firstarg, Args... args) {
    std::cout << firstarg;
    (std::cout << ... << AddPre<Args, ' '>(args)) << '\n';
    int a = getchar();
    exit(0);
}