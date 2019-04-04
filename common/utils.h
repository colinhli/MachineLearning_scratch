#include<fstream>
#include <string>
#include <vector>
#include <iterator>
#include <regex>
using namespace std;
/*
   用delim指定的正则表达式将字符串in分割，返回分割后的字符串数组
   delim 分割字符串的正则表达式
 */
static std::vector<std::string> s_split(const std::string &in, const std::string &delim) {
    std::regex re{ delim };
    // 调用 std::vector::vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type())
    // 构造函数,完成字符串分割
    return std::vector<std::string> {
        std::sregex_token_iterator(in.begin(), in.end(), re, -1),
        std::sregex_token_iterator()
    };
}

static std::vector<std::vector<string>> load_data_string(const std::string &fname, const std::string &delim) {
    std::vector<std::vector<string>> data;
    ifstream inf;
    inf.open(fname.c_str());
    std::string line;
    while (getline(inf, line)) {
        auto result = s_split(line, delim);
        data.emplace_back(result);
    }
    return data;
}

static std::vector<std::vector<double>> load_data_double(const std::string &fname, const std::string &delim) {
    std::vector<std::vector<double>> data;
    ifstream inf;
    inf.open(fname.c_str());
    std::string line;
    while (getline(inf, line)) {
        std::vector<double> d_items;
        auto items = s_split(line, delim);
        for (auto item : items) {
            d_items.push_back(stod(item));
        }
        data.emplace_back(d_items);
    }
    return data;
}