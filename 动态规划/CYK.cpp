#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <stdexcept>
#include <utility>
#include <set>

class CFL_CYK_Decider
{
    private:
        std::map<std::string, std::vector<char>> rev_rules;
        char start_symbol;
        std::string input_string;
        std::vector<std::vector<std::set<char>>> table;
        std::pair<bool, bool> calculated = {false, false};

        bool Derivation()
        {
            if(calculated.first) return calculated.second;

            table.resize(input_string.length());
            for(auto &row : table) 
            {
                row.resize(input_string.length());
                for(auto &col : row) 
                {
                    col.clear();
                }
            }
            // ! \brief Initialization
            bool ret = false;
            for(int i = 1; i <= input_string.length(); i++) 
            {
                for(auto terminable_symbol : rev_rules[input_string.substr(i - 1, 1)]) 
                {
                    table[i - 1][i - 1].insert(terminable_symbol);
                }
            }

            // ! \brief Derivation
            for(int len = 2; len <= input_string.length(); len++) 
            {
                for(int j = 1; j <= input_string.length() - len + 1; j++) 
                {
                    int start = j - 1, end = j + len - 2;
                    for(int mid = start; mid < end; mid++) 
                    {
                        for(auto st2mid_symbol : table[start][mid])
                        {
                            for(auto mid2ed_symbol : table[mid+1][end])
                            {
                                for(auto symbol : rev_rules[std::string(1, st2mid_symbol) + std::string(1, mid2ed_symbol)])
                                {
                                    table[start][end].insert(symbol);
                                }
                            }
                        }
                    }
                }
            }

            // ! \brief Check
            for(auto symbol : table[0][input_string.length() - 1]) 
            {
                if(symbol == start_symbol) 
                {
                    ret = true;
                    break;
                }
            }

            calculated.first = true;
            calculated.second = ret;
            return ret;
        }
    public:
        CFL_CYK_Decider(std::map<char, std::vector<std::string>> rules, char start_symbol, std::string input_string)
            : start_symbol(start_symbol), input_string(input_string)
            {
                rev_rules.clear();
                for(auto symbol : rules) 
                {
                    for(auto rule : symbol.second) 
                    {
                        rev_rules[rule].push_back(symbol.first);
                    }
                }
                std::cout << "Initialize Success!" << std::endl;

                bool Gen = Derivation();
                //if(!Gen) throw std::runtime_error("CYK: Derivation failed!");
            }
        void CheckTable() 
        {
            if(!calculated.first) throw std::runtime_error("CYK: Table not calculated!");

            int length = input_string.length();
            std::cout << "Table Length: " << length << std::endl;
            for(int len = length; len >= 1; len--) 
            {
                for(int st = 1; st <= length - len + 1; st++) 
                {
                    std::cout << "{";

                    int start = st - 1, end = st + len - 2;
                    for(auto symbol : table[start][end]) 
                    {
                        std::cout << symbol;
                        if(symbol != *table[start][end].rbegin()) std::cout << ", ";
                    }

                    std::cout << "}";
                    if(st != length - len + 1) std::cout << ", ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        bool CheckString() 
        {
            if(!calculated.first) throw std::runtime_error("CYK: Table not calculated!");

            return calculated.second;
        }
};

int main(void)
{
    std::map<char, std::vector<std::string>> rules;
    int rules_num = 0;
    std::cin >> rules_num;
    for(int i = 0; i < rules_num; i++) {
        char symbol;
        std::string rule;
        std::cin >> symbol >> rule;
        rules[symbol].push_back(rule);
    }

    char start_symbol;
    std::cin >> start_symbol;

    std::string input_string;
    std::cin >> input_string;

    // ! \brief Test Input
    std::cout << "Rules: " << std::endl;
    for(auto symbol : rules) {
        std::cout << symbol.first << " -> ";
        for(auto rule : symbol.second) {
            std::cout << rule;
            if(rule != symbol.second.back()) std::cout << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << "Start Symbol: " << start_symbol << std::endl;
    std::cout << "Input String: " << input_string << std::endl;

    CFL_CYK_Decider decider(rules, start_symbol, input_string);
    
    std::cout << "CYK Result: ";
    
    if(decider.CheckString()) 
        std::cout << "Yes" << std::endl;
    else 
        std::cout << "No" << std::endl;

    decider.CheckTable();

    return 0;
}