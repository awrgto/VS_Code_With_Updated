#include <queue>

void nAmB(const std::string& g, const std::string& a, int& n, int& m) {
    n = (g[0] == a[0]) + 
        (g[1] == a[1]) + 
        (g[2] == a[2]) + 
        (g[3] == a[3]);
    m = (g[0] == a[1]) + (g[0] == a[2]) + (g[0] == a[3]) + 
        (g[1] == a[0]) + (g[1] == a[2]) + (g[1] == a[3]) + 
        (g[2] == a[0]) + (g[2] == a[1]) + (g[2] == a[3]) + 
        (g[3] == a[0]) + (g[3] == a[1]) + (g[3] == a[2]);
}

int GuessNumberAI::algorithm(const std::string& guess_str) {
    struct Compare {
        bool operator()(const std::string& lhs, const std::string& rhs) {
            return lhs.compare(rhs) >= 0;
        }
    };
    typedef std::priority_queue<std::string, std::vector<std::string>, Compare > PQ_TYPE;
    PQ_TYPE my_pq;
    std::vector<PQ_TYPE> vec_pq_1(10, my_pq);
    std::vector<PQ_TYPE> vec_pq_2(10, my_pq);
    std::vector<PQ_TYPE>* ptr_main_pq = &vec_pq_1;
    std::vector<PQ_TYPE>* ptr_sub_pq  = &vec_pq_2;
    std::vector<PQ_TYPE>* ptr_tmp_pq  = 0;
    for(int i = 123; i < 10000; ++i) {
        char g[5];
        g[0] = (i / 1000) + '0';
        g[1] = ((i % 1000) / 100) + '0';
        g[2] = ((i % 100) / 10) + '0';
        g[3] = (i % 10) + '0';
        g[4] = '\0';
        if(g[0] == g[1] || g[0] == g[2] || g[0] == g[3] || 
           g[1] == g[2] || g[1] == g[3] || 
           g[2] == g[3]) {
                continue;
        }
        std::string str(g);
        int x = str[0] - '0';
        ptr_main_pq->at(x).push(str);
    }
    int t = 1;
    while(true) {
        int max_sz = -1;
        int max_x = -1;
        for(int x = 0; x < 10; ++x) {
            int sz = ptr_main_pq->at(x).size();
            if(sz > 0 && max_sz < sz) {
                max_x = x;
                max_sz = sz;
            }
        }
        std::string str = ptr_main_pq->at(max_x).top();
        ptr_main_pq->at(max_x).pop();
        int n = -1;
        int m = -1;
        nAmB(str, guess_str, n, m);
        if(n == 4 && m == 0) {
            break;
        } else {
            int sum = n + m;
            for(int y = 0; y < 10; ++y) {
                while(!ptr_main_pq->at(y).empty()) {
                    std::string next_str = ptr_main_pq->at(y).top();
                    ptr_main_pq->at(y).pop();
                    int tmp_n = -1;
                    int tmp_m = -1;
                    nAmB(next_str, str, tmp_n, tmp_m);
                    if(tmp_n == n && tmp_m == m) {
                        ptr_sub_pq->at(y).push(next_str);
                    }
                }
            }
            ptr_tmp_pq = ptr_main_pq;
            ptr_main_pq = ptr_sub_pq;
            ptr_sub_pq = ptr_tmp_pq;
        }
        ++t;
    }
    return t;
}