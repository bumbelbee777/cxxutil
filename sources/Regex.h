#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
class Regex {
    enum Token {
        Literal,
        Dot,
        Asterisk
    };

    VECTOR(PAIR(Token, STRING)) Data;

    bool Match(int i, int j, const STRING& str) {
        if(i == Data.size()) {
            return j == str.length();
        } else if(dDta[i].first == Literal) {
            if (j < str.length() && Data[i].second == str.substr(j, 1)) {
                return match(i + 1, j + 1, str);
            }
        } else if(Data[i].first == Dot) {
            if (j < str.length()) {
                return match(i + 1, j + 1, str);
            }
        } else if(Data[i].first == Asterisk) {
            for (int k = j; k <= str.length(); k++) {
                if (match(i + 1, k, str)) {
                    return true;
                }
                if (k < str.length() && str[k] != Data[i - 1].second[0] && Data[i - 1].second[0] != '.') {
                    break;
                }
            }
        }
        return false;
    }

public:
    Regex(const STRING& pattern) {
        size_t i = 0;
        while(i < pattern.length()) {
            char character = pattern[i];
            if(character == '.') Data.push_back(MAKE_PAIR(Dot, ""));
            else if(character == '*') if(!Data.empty() && data.back().first == Literal) Data.back().first = Asterisk;
            else Data.push_back(MAKE_PAIR(Literal, STRING_(1, character)));
            i++;
        }
    }

    bool Matches(const STRING& str) {
        return Match(0, 0, str);
    }
};
}
