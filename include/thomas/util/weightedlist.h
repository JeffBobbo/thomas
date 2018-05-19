#ifndef WEIGHTEDLIST_H_INCLUDE
#define WEIGHTEDLIST_H_INCLUDE

#include <utility>
#include <list>

#include "random.h"

namespace thomas
{
namespace util
{
/**
 * weightedlist_t provides a way to select items randomly from a list with relative weights.
 */
template <typename T>
class weightedlist_t
{
public:
  weightedlist_t() : total(0.0) {}
  ~weightedlist_t() {}

  /**
   * @return Returns true if the list is empty
   */
  inline bool empty() const
  {
    return entries.empty();
  }

  /**
   * @return Returns the number of entries
   */
  inline size_t size() const
  {
    return entries.size();
  }

  /**
   * @return Returns the total weight of the list
   */
  inline double weight() const
  {
    return total;
  }

  /**
   * Randomly chooses an item from the list using the internal random number generator.
   * @return The chosen item
   */
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

  /**
   * Inserts an item into the list, with the given weight
   * @param weight The weight for this item
   * @param t      The item to insert
   */
  void insert(const double weight, const T& t)
  {
    if (weight <= 0.0)
      throw std::string("weight less than 0.0");
    entries.push_back(std::make_pair(weight, t));
    total += weight;
  }

  /**
   * Provides an iterator to the start of the list, a-la std::begin
   * @return Iterator to the start of the list
   */
  inline typename std::list<std::pair<double, T> >::iterator begin() const
  {
    return std::begin(entries);
  }

  /**
   * Provides an iterator to the end of the list, a-la std::end
   * @return Iterator to the end of the list
   */
  inline typename std::list<std::pair<double, T> >::iterator end() const
  {
    return std::end(entries);
  }

  /**
   * Erases an element, given by an iterator, from the list, a-la std::list::erase
   * @param  it The iterator to erase from the weighted list
   * @return    Iterator following the removed element, or end() if it was the last element.
   */
  inline typename std::list<std::pair<double, T> >::iterator erase(typename std::list<std::pair<double, T> >::iterator it) const
  {
    total -= it->first;
    return entries.erase(it);
  }

private:
  std::list<std::pair<double, T> > entries;
  double total;
};
}
}

#endif
