#include <mutex>
#include <functional>
#include <thread>
#include <stdexcept>
#include <cstddef>
#include <iostream>

template <typename T, typename Compare>
class priority_queue
{
public:
    explicit
    priority_queue(unsigned int capacity);
    priority_queue(priority_queue const & other); /*strong*/
    auto operator =(priority_queue const & other) /*strong*/ -> priority_queue &;
    ~priority_queue();

    auto empty() const -> bool;
    auto size() const  -> size_t;

    auto enqueue(T const & value)  -> bool;
    auto dequeue(T& value)  -> bool;
    
    void print();

private:
    
    unsigned int capacity_;
    unsigned int size_;
    T*           heap_; 
    Compare      compare;     


    mutable std::mutex mutexpriority_queue_;

private:
    auto throw_is_empty() const -> void;
    void filter_up(int index);
    void filter_down(int index);
};


template<typename T, typename Compare>
auto priority_queue<T,Compare>::throw_is_empty() const->void
{
    throw std::logic_error("Error!"); 
}

template <typename T, typename Compare>/*noexcept*/
priority_queue<T,Compare>::priority_queue(unsigned int capacity) : capacity_(capacity), size_(0)
{
    heap_ =(T*)malloc(sizeof(T)*capacity_);
}

template <typename T, typename Compare>
priority_queue<T,Compare>::priority_queue(priority_queue const & st) : mutexpriority_queue_() 
{
    std::lock_guard<std::mutex> lock1(mutexpriority_queue_);
    std::lock_guard<std::mutex> lock2(st.mutexpriority_queue_);

}

template <typename T, typename Compare>
priority_queue<T,Compare>::~priority_queue()
{
    free(heap_);
    heap_ = nullptr;
}

template <typename T, typename Compare>
auto priority_queue<T,Compare>::operator=(const priority_queue & st)-> priority_queue &
{
    std::lock(mutexpriority_queue_, st.mutexpriority_queue_);
    std::lock_guard<std::mutex> lock1(mutexpriority_queue_, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(st.mutexpriority_queue_, std::adopt_lock);


    return *this;
}

template <typename T, typename Compare>
void priority_queue<T,Compare>::print()
{
    for (int i = 0 ; i < size_; i++)
    {
        std::cout << heap_[i]<<"  ";
    }
    std::cout << "\n";
}

template <typename T, typename Compare>
size_t  priority_queue<T,Compare>::size() const
{
    std::lock_guard<std::mutex> lock(mutexpriority_queue_);

    return size_;
}

template <typename T, typename Compare>
void priority_queue<T,Compare>::filter_up(int index)
{
    T value = heap_[index];
    int current_index = index;
    while(current_index > 0)
    {
        int parent_index = (current_index - 1) / 2;
        if (!compare(heap_[parent_index], value))
        {
            T parent_value = heap_[parent_index];
            heap_[parent_index] = heap_[current_index];
            heap_[current_index] = parent_value;
        }
        else
        {
            break;
        }
        current_index = parent_index;
    }
}

template <typename T, typename Compare>
auto priority_queue<T,Compare>::enqueue(T const &value)-> bool
{
    std::lock_guard<std::mutex> lock(mutexpriority_queue_);
    if (size_ == capacity_)
    {
        T* heap_bak = heap_;
        heap_ = (T*)realloc(heap_, sizeof(T)*(size_ + 50));
        if(NULL == heap_)
        {
            heap_ = heap_bak;
            return false;
        }
    }
    heap_[size_] = value;
    filter_up(size_);
    size_++;
    return true;
}

template <typename T, typename Compare>
void priority_queue<T,Compare>::filter_down(int index)
{
    int parent_index = 0;
    heap_[parent_index] = heap_[index];
    int child_index = parent_index * 2 + 1;  // left child
    while(child_index + 1 < index)
    {
        /* select largest one of the two children to exchange with parent  */
        if (!compare(heap_[child_index], heap_[child_index + 1]))
        {
            child_index ++;
        }
      
        /* if parent's value less than child's value, exchange them */
        if(!compare(heap_[parent_index], heap_[child_index]))
        {
            T value = heap_[parent_index];
            heap_[parent_index] = heap_[child_index];
            heap_[child_index] = value;
        }
        else
        {
            break;
        }
        parent_index = child_index;
        child_index  = parent_index * 2 + 1;  // left child
    }
}

template <typename T, typename Compare>
auto priority_queue<T,Compare>::dequeue(T& value)-> bool
{
    std::lock_guard<std::mutex> lock(mutexpriority_queue_);
    if (0 == size_)
        return false;
    value = heap_[0];
    size_ --;
    filter_down(size_);
    return true;
}

template <typename T, typename Compare>/*noexcept*/
auto priority_queue<T,Compare>::empty()const->bool 
{
    std::lock_guard<std::mutex> lock(mutexpriority_queue_);
    return(size_ == 0);
}
