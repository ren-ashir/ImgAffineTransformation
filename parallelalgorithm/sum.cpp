#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <istream>
#include <ostream>
#include <iterator>
#include <functional>
#include <chrono>

using namespace std;

template<typename It,typename T>
struct sum_block
{
    void operator () (It first,It last,T& result)
    {
        result = std::accumulate(first,last,result);
    }
};
template<typename It,typename T>
T parallel_sum (It first,It last,T init)
{
    using cuint = unsigned int const;
    cuint len = std::distance(first,last);
    if (!len)
        return init;
    cuint min_per_thread = 25,
            max_threads = (len + min_per_thread - 1) / min_per_thread, // получить максимальное число потоков
            hardware_threads = std::thread::hardware_concurrency(),
            num_threads = std::min (hardware_threads == 0 ? 2 : hardware_threads,max_threads), // не запускать потоков больше, чем есть на машине
            block_size = len / num_threads;
    vector<T> results(num_threads);
    vector<thread> threads(num_threads - 1); // так как один поток уже есть
    It block_start = first;
    for (int i = 0; i < num_threads - 1; ++i)
    {
        It block_end = block_start;
        advance (block_end,block_size); // сдвинуть итератор на количестов элм. в блоке
        threads[i] = thread (sum_block<It,T>(),block_start,block_end,ref(results[i]));
        block_start = block_end;
    }
    sum_block<It,T>()(block_start,last,results[num_threads - 1]); // этот один поток
    for_each(threads.begin(),threads.end(),mem_fn(&thread::join)); // дождаться завершения всех потоков (присоединить все к текущему)
    //mem_fn возвращает функтор (с функциональностью метода), который может быть вызван как обычная функция
    return std::accumulate(results.begin(),results.end(),init);
}

int main ()
{
    vector<double> p(1000000000,11);

    auto t0 = chrono::high_resolution_clock::now();
    double res = parallel_sum (p.begin(),p.end(),0.0);
    auto t1 = chrono::high_resolution_clock::now();
    cout << res << '\n';
    cout << chrono::duration_cast<chrono::milliseconds>(t1-t0).count() << " msec\n";


    t0 = chrono::high_resolution_clock::now();
    res = accumulate (p.begin(),p.end(),0.0);
    t1 = chrono::high_resolution_clock::now();
    cout << res << '\n';
    cout << chrono::duration_cast<chrono::milliseconds>(t1-t0).count() << " msec\n";

}


