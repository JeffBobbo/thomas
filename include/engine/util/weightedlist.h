#ifndef WEIGHTEDLIST_H_INCLUDE
#define WEIGHTEDLIST_H_INCLUDE

#include <utility>
#include <list>

#include "random.h"

namespace engine
{
namespace util
{
template <typename T>
class weightedlist_t
{
public:
  weightedlist_t() : total(0.0) {}
  ~weightedlist_t() {}

  inline bool empty() const { return entries.empty(); }
  inline size_t size() const { return entries.size(); }
  inline double weight() const { return total; }

  const T& choose() const
  {
    auto it = entries.begin();
    double roll = random(0.0, weight()) - it->first;
    while (roll >= 0.0 && it != std::end(entries))
    {
      ++it
      roll -= it->first;
    }
    return it->second;
  }

  void insert(const double weight, const T& t)
  {
    if (weight <= 0.0)
      throw std::string("weight less than 0.0");
    entries.push_back(std::make_pair(weight, t));
    total += weight;
  }

  inline typename std::vector<std::pair<double, T> >::iterator begin() const { return std::begin(entries); }
  inline typename std::vector<std::pair<double, T> >::iterator end() const { return std::end(entries); }
  inline typename std::vector<std::pair<double, T> >::iterator erase(typename std::vector<std::pair<double, T> >::iterator it) const
  {
    return entries.erase(it);
  }

private:
  std::list<std::pair<double, T> > entries;
  double total;
};
}
}

#endif
