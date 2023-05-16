#pragma once

#include <Pair.h>
#include <Vector.h>

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

    Vector<Pair<Token, String>> Data;

    bool Match(int i, int j, const String &str) {
        if(i == Data.Size()) return j == str.Length();
        else if(Data[i].first == Literal) {
			if(j < str.length() && Data[i].second == str.substr(j, 1))
				return Match(i + 1, j + 1, str);
		}
        else if(Data[i].first == Dot) { if(j < str.length()) return Match(i + 1, j + 1, str); }
        else if(Data[i].first == Asterisk) {
            for(int k = j; k <= str.length(); k++) {
                if(Match(i + 1, k, str)) return true;
                if(k < str.length() && str[k] != Data[i - 1].second[0] && Data[i - 1].second[0] != '.') break;
            }
        }
        return false;
    }

public:
    Regex(const String &Pattern) {
        size_t i = 0;
        while(i < Pattern.length()) {
            char Character = Pattern[i];
            if(Character == '.') Data.PushBack(MakePair(Dot, ""));
            else if(Character == '*') if(!Data.Empty() && Data.Back().first == Literal) Data.back().first = Asterisk;
			else {
				if(Character == '[') {
					size_t j = i + 1;
					while(j < Pattern.Size() && j != `]`) j++;
				}
			}
            else Data.PushBack(MakePair(Literal, String(Character)));
            i++;
        }
    }

	bool operator==(const String &String) { return Match(0, 0, String); }

    bool Matches(const String &String) { return Match(0, 0, String); }
};
}
