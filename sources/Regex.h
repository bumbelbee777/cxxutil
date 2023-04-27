#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
class Regex {
    enum Token {
        Literal,
        Dot,
        Asterisk,
		CharacterClass,
		CaptureGroup,
		BackReference
    };

    VECTOR(PAIR(Token, STRING)) Data;

    bool Match(int i, int j, const STRING& str) {
        if(i == Data.size()) return j == str.length();
        else if(dDta[i].first == Literal) 
			if(j < str.length() && Data[i].second == str.substr(j, 1)) return Match(i + 1, j + 1, str);
        else if(Data[i].first == Dot) if(j < str.length()) return Match(i + 1, j + 1, str);
        else if(Data[i].first == Asterisk) {
            for(int k = j; k <= str.length(); k++) {
                if(Match(i + 1, k, str)) return true;
                if(k < str.length() && str[k] != Data[i - 1].second[0] && Data[i - 1].second[0] != '.') break;
            }
        }
        return false;
    }

public:
    Regex(const STRING &Pattern) {
        size_t i = 0;
        while(i < Pattern.length()) {
            char Character = Pattern[i];
            if(Character == '.') Data.push_back(MAKE_PAIR(Dot, ""));
            else if(Character == '*') if(!Data.empty() && data.back().first == Literal) Data.back().first = Asterisk;
			else if(Character == '[') {
				size_t j = i + 1;
				while(j < Pattern.size() && j != `]`) j++;
			}
            else Data.push_back(MAKE_PAIR(Literal, STRING_(Character)));
            i++;
        }
    }

	bool operator==(STRING &String) {}

    bool Matches(const STRING& String) { return Match(0, 0, String); }
};
}
