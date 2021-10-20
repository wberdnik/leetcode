//https://leetcode.com/problems/regular-expression-matching/

struct Rule {
	char c;
	bool asterisk;
};

struct Range {
	unsigned int start;
	unsigned int len;
};


class Solution {
public:
	bool isMatch(std::string s, std::string p) {

		Range s_rn, P_rn;
		s_rn.start = 0;
		s_rn.len = s.size();
		P_rn.start = 0;
		P_rn.len = 0;
		

		P.resize(p.size());


		for (int i = 0, n = p.size(); i < n; i++) {
			if (p[i] == '*') {
				throw "Wrong constraints";
			}

			P[P_rn.len].c = p[i];
			P[P_rn.len].asterisk = false;

			if (i + 1 < n && p[i + 1] == '*') {
				P[P_rn.len].asterisk = true;
				i++; // skip '*'
			}
			P_rn.len++;
		}


		//fast
		while (P_rn.start < P_rn.len && s_rn.start < s_rn.len) {
			Rule rule = P[P_rn.start];
			if (rule.asterisk) {
				break;
			}


			if (s[s_rn.start] == rule.c || rule.c == '.') {
				s_rn.start++;
				P_rn.start++;
				continue;
			}
			return false;
		}

		//fast
		while (P_rn.start < P_rn.len && s_rn.start < s_rn.len) {
			Rule rule = P[P_rn.len - 1];
			if (rule.asterisk) {
				break;
			}

			if (s[s_rn.len - 1] == rule.c || rule.c == '.') {
				s_rn.len--;
				P_rn.len--;
				continue;
			}
			return false;
		}
		unsigned int count_asterisk = 0;

		for (int i = P_rn.start; i < P_rn.len; i++) {
			if (P[i].asterisk) {
				count_asterisk++;
			}
		}

		if (s_rn.len - s_rn.start <= 0 && count_asterisk == P_rn.len - P_rn.start) { // empty source and only asterisk in the pattern
			return true;
		}

		source = s;
		return isMatchHard( s_rn, P_rn);
	}

private:

	std::vector <Rule> P;
	std::string source;

	bool isMatchHard( Range s_rn, Range P_rn) {
		unsigned int P_ln = P_rn.len - P_rn.start, s_ln = s_rn.len - s_rn.start;

		if (P_ln <= 0 && s_ln > 0) {
			return false; // the sourse is longer than the pattern 
		}

		if (P_ln <= 0 && s_ln <= 0) {
			return true;
		}

		Range s_rn_l = s_rn, P_rn_l = P_rn;
		s_rn_l.start++;
		P_rn_l.start++;


		bool firstCharTest = s_ln && (source[s_rn.start] == P[P_rn.start].c || P[P_rn.start].c == '.');
		
		if (P[P_rn.start].asterisk) {
			

			return (firstCharTest && isMatchHard(s_rn_l, P_rn))   //next symbol if first char equal
				||
				// next rule 
				isMatchHard(s_rn, P_rn_l);
		}

		if (firstCharTest) {					
			return isMatchHard(s_rn_l, P_rn_l);
		}

		return false;
	}
};
