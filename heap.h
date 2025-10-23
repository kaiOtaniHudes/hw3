#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(size_t m_=2, PComparator c_ = PComparator()): data(),c(c_), m(m_){}

  /**
  * @brief Destroy the Heap object
  * 
  */
  //~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const{
    return data.empty();
  }

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const{
    return size_t(data.size());
  }

private:
  /// Add whatever helper functions and data members you need below

  void hpfy(size_t index);
  std::vector<T> data;
  PComparator c;
  size_t m;

};

// Add implementation of member functions here


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::underflow_error("stack underflow");
  }
  return this->data[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::underflow_error("stack underflow");
  }
  std::swap(this->data[0],this->data.back());
  this->data.pop_back();
  if(!this->empty()){this->hpfy(0);}
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::hpfy(size_t i){
  while(true){
    size_t lChild= this->m*i+1;
    if (lChild >= this->data.size()) break;
    size_t best = lChild;
    size_t end = std::min(lChild+this->m,this->data.size());

    for(size_t j = best+1; j<end; j++){
      if(this->c(this->data[j],this->data[best])) best = j;
    }
    if(c(this->data[i],this->data[best]))break;
    std::swap(this->data[i], this->data[best]);
    i = best;
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  this->data.push_back(item);
  size_t i= this->data.size()-1;
  while(i>0){
    size_t par = (i-1)/this->m;
    if(c(this->data[par],this->data[i])) break;
    std::swap(this->data[par],this->data[i]);
    i = par;
  }
}


#endif

