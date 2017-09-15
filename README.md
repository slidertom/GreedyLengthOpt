# GreedyLengthOpt
Greedy based approach to the Cutting Stock problem

Usage sample:
std::vector<size_t> arr;
arr.push_back(1000);
arr.push_back(200);
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
