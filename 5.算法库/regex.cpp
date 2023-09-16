#include <iostream>
#include <regex>
#include <format>

int main()
{
    std::string str{"2023-09-16"};
    std::regex reg{R"(^(\d{4})-(\d{1,2})-(\d{1,2}))"};

    // 匹配regex_match(string, RegEx)
    std::cout << (regex_match(str, reg) ? "格式正确\n" : "格式错误\n");

    // 查找sregex_token_interator默认为end迭代器
    for (std::sregex_iterator iter{cbegin(str), cend(str), reg}, end{}; iter != end; ++iter){
        std::cout << format("{}年{}月{}日\n", (*iter)[1].str(), (*iter)[2].str(), (*iter)[3].str());
    }

    // 替换regex_replace
    std::string replacement{"年:$1\n月:$2\n日:$3\n"};
    std::cout << regex_replace(str, reg, replacement) << std::endl;
}
