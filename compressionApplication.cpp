#include "header.h"

// s must have EOS symbol '$'
string comp(string s) {
	// s += '$'; 
  s = burrowsWheelerTransform(s);
	string RLE_str;
	int n = s.size(), first = 0, last = 0;
	while (first < n) {
		last = first + 1;
		while (last < n && s[last] == s[first]) {
			++last;
		}
		int temp = last - first;
		if (temp != 1) {
			RLE_str.insert(RLE_str.size(), to_string(temp));
		}
		RLE_str.push_back(s[first]);
		first = last;
	}
	//RLE_str la chuoi da nen theo phuong phap RLE
	return RLE_str;
}

string decomp(string s) {
	//Nhan vao chuoi nen roi giai nen
	string ORG_str;
	for (int i = 0; i < s.size(); ++i) {
		if (!isdigit(s[i])) {
			if (i == 0 || !isdigit(s[i - 1]))
				ORG_str.push_back(s[i]);
			else {
				int j = i - 1;
				string digit;
				while (j >= 0 && isdigit(s[j])) {
					digit.push_back(s[j]);
					--j;
				}
				reverse(digit.begin(), digit.end());
				stringstream ss(digit);
				int k;
				ss >> k;
				for (int j = 0; j < k; ++j) {
					ORG_str.push_back(s[i]);
				}
			}
		}
	}
	//ORG_str la chuoi da giai nen
	return inverseBurrowsWheelerTransform(ORG_str);
}