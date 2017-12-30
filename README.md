# GreedyLengthOpt
Greedy based approach to the Cutting Stock problem

```C++
std::vector<size_t> arr;
arr.push_back(1000);
arr.push_back(200);
arr.push_back(2990);
arr.push_back(2990);
arr.push_back(400);
arr.push_back(2000);
arr.push_back(700);

size_t stock_len = 6000;
size_t saw       = 10;
CLengthOptResults *pResults = CLengthGreedyOpt::OptimizeGreedy(arr, stock_len, saw);
for (auto *pLenArray : *pResults) {
    for (size_t nLen : *pLenArray) {
       nLen;
    }
}
delete pResults;
```

GreedyLengthOpt uses CMake as a general build tool.   

Supported compilers and platforms:   
Microsoft Visual Studio 2015 32/64  C/C++/C# <br />
Microsoft Visual Studio 2017 32/64  C/C++/C# <br />
CodeBlocks TDM-GCC-32/64 <br />

For C and C# languages do use C function Wrapper_OptimizeGreedy.
