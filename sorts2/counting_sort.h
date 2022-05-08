#ifndef SORTS_COUNTING_SORT_H_
#define SORTS_COUNTING_SORT_H_

#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>

template <typename IterT,
        typename T = typename std::iterator_traits<IterT>::value_type>
void counting_sort(IterT first, IterT last)
{
    const auto len = std::distance(first, last);
    if(len < 2)
        return ;
    const T max = *std::max_element(first, last);
    if(max == 0)
        return ;
    
    std::vector<size_t> counter(max + 1);
    for(IterT i = first; i != last; ++i)
    {
        ++counter[*i];
    }

    // 统计数组变形，前面的元素等于后面的元素个数之和
    for(size_t i = 1; i != max + 1; ++i)
    {
        const size_t j = max - i;
        counter[j] += counter[j+1];

    }
    // 从统计数组找到相对位置，输出到结果数组
    std::vector<T> temp(len);
    for(IterT i = first; i != last; i++)
    {
        temp[len - counter[*i]] = *i;
        --counter[*i];
    }
    std::copy(temp.begin(), temp.end(), first);
}


#endif
