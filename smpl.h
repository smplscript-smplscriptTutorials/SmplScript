#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string digits = "0123456789";

class Error {
public:
	std::string en = "Illegal Character";
	std::string dts;
	Error() {
		en = "NO ERROR";
		dts = "NO ERROR";
	}
	Error(std::string error_name, std::string dets) {
		en = error_name;
		dts = dets;
	}
	std::string toString() {
		std::string temp = en;
		temp.append(": ");
		temp.append(dts);
		return temp;
	}
};

class IllegalCharError {
public:
	std::string en = "Illegal Character";
	std::string dts;
	IllegalCharError() {
		en = "NO ERROR";
		dts = "NO ERROR";
	}
	IllegalCharError(std::string dets) {
		dts = dets;
	}
	std::string toString() {
		std::string temp = en;
		temp.append(": ");
		temp.append(dts);
		temp.append("\n");
		return temp;
	}
};

std::string tt_int = "int";
std::string tt_float = "float";
std::string tt_string = "string";
std::string tt_plus = "plus";
std::string tt_minus = "minus";
std::string tt_mult = "mult";
std::string tt_div = "div";
std::string tt_lparen = "lparen";
std::string tt_rparen = "rparen";
std::string tt_exp = "exp";
std::string tt_keyword = "keyword";
// std::vector<std::string> keywords{};

class conversion {
public:
	std::string success = "failed";
	int integer;
	long double floatingPoint;
	std::string str;
	conversion() {
		std::cout << "";
	}
	void conversions(int a, std::string b = "") {
		if (b.compare(""))
			success = b;
		integer = a;
	}
	void conversions(long double a, std::string b = "") {
		if (b.compare(""))
			success = b;
		floatingPoint = a;
	}
	void conversions(std::string a, std::string b = "success") {
		str = a;
		success = b;
	}
};

conversion convert(std::string x) {

	std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int dec_count = 0;
	try {
		std::string current;
		for (int i = 0; i < x.length(); i++) {
			current = x.substr(i, 1);
			if (!current.compare(".")) {
				if (dec_count == 1) {
					conversion failed;
					failed.conversions(i + 1);
					throw failed;
				}
				dec_count++;
			}
			for (int j = 0; j < alphabet.length(); j++) {
				if (!current.compare(alphabet.substr(j, 1))) {
					conversion failed;
					failed.conversions(i + 1);
					throw failed;
				}
				else {
					continue;
				}
			}
		}
		//std::cout << "successful";
		if (dec_count == 0) {
			int b = std::stoi(x);
			conversion success;
			success.conversions(b, "success");
			return success;
		}
		std::cout << x << '\n';
		long double b = std::stold(x);
		std::cout << std::stold(x);
		conversion success;
		success.conversions(b, "success");
		return success;

	}
	catch (conversion fail) {
		return fail;
	}
}


conversion convert(int x) {
	std::stringstream ss;
	std::string y;
	ss << x;
	ss >> y;
	conversion c;
	c.conversions(y);
	return c;
}

conversion convert(long double x) {
	std::stringstream ss;
	std::string y;
	ss << x;
	ss >> y;
	conversion c;
	c.conversions(y);
	return c;
}

class Value {
public:
	int integerVal = 0;
	long double floatingPoint = 0.0;
	std::string stringVal = "";


	Value() {}

	void set(int val) {
		integerVal = val;
	}

	void set(std::string val) {
		stringVal = val;
	}

	void set(long double val) {
		floatingPoint = val;
	}

	bool is_empty() {
		if ((integerVal == 0 && floatingPoint == 0.0) || !stringVal.empty()) {
			return true;
		}
		return false;
	}
};



class Token {
private:
	conversion converted;
public:
	std::string type_;
	Value value;
	Token(std::string _type) {
		type_ = _type;
	}
	Token(std::string _type, std::string _value) {
		type_ = _type;
		if (!type_.compare(tt_int)) {
			converted = convert(_value);
			value.set(converted.integer);
		}
		else if (!type_.compare(tt_float)) {
			converted = convert(_value);
			value.set(converted.floatingPoint);
		}
		else {
			value.set(converted.str);
		}
	}
	std::string out() {
		if (value.is_empty()) {
			return type_;
		}
		std::string temp = type_;
		temp.append(": ");
		if (value.floatingPoint != 0) {
			conversion c = convert(value.floatingPoint);
			temp.append(c.str);
			return temp;
		}
		else if (value.integerVal != 0) {
			conversion c = convert(value.integerVal);
			temp.append(c.str);
			return temp;
		}
		temp.append(value.stringVal);
		std::cout << temp;
		return temp;
	}
};

bool inDigits(char x) {
	for (int i = 0; i < digits.size(); i++) {
		if (digits.at(i) == x || x == '.') {
			return true;
		}
	}
	return false;
}

std::string toString(char x) {
	std::string s(1, x);

	return s;
}

class E {
public:
	std::vector<Token> tokens;
	IllegalCharError ice;

	E() {
		ice = IllegalCharError();
	}

	bool isError() {
		if (!ice.en.compare(ice.dts)) {
			return false;
		}
		return true;
	}
	std::string out() {
		if (!E::isError()) {
			std::string temp;
			temp.append("[");
			for (int i = 0; i < tokens.size(); i++) {
				temp.append(tokens.at(i).out());
				if (i<tokens.size()-1)
					temp.append(", ");
			}
			temp.append("]\n");
			return temp;
		}
		else
			return ice.toString();
	}


};

class Lexer {
private:
	std::string txt;
public:
	int pos = -1;
	char current = '\0';
	Lexer(std::string text) {
		txt = text;
		Lexer::advance();
	}

	void advance() {
		pos++;
		if (pos < txt.size())
			current = txt.at(pos);
		else
			current = '\0';
	}
	Token make_number() {
		std::string numstr = "";
		int dot_count = 0;

		while (inDigits(current) && current != '\0') {
			if (current == '.') {
				if (dot_count == 1) {
					break;
				}
				dot_count++;
				numstr.append(".");
			}
			else {
				numstr.append(toString(current));
			}
			Lexer::advance();
		}
		if (dot_count == 0) {
			return Token(tt_int, numstr);
		}
		return Token(tt_float, numstr);
	}
	E make_tokens() {
		E e = E();
		std::vector<Token> tokens;
		while (current != '\0') {
			if (current == ' ' || current == '\t') {
				Lexer::advance();
			}
			else if (inDigits(current)) {
				tokens.push_back(Lexer::make_number());
			}
			else if (current == '+') {
				tokens.push_back(Token(tt_plus));
				Lexer::advance();
			}
			else if (current == '-') {
				tokens.push_back(Token(tt_minus));
				Lexer::advance();
			}
			else if (current == '*') {
				tokens.push_back(Token(tt_mult));
				Lexer::advance();
			}
			else if (current == '/') {
				tokens.push_back(Token(tt_div));
				Lexer::advance();
			}
			else if (current == '(') {
				tokens.push_back(Token(tt_rparen));
				Lexer::advance();
			}
			else if (current == ')') {
				tokens.push_back(Token(tt_lparen));
				Lexer::advance();
			}
			else {
				char c = current;
				Lexer::advance();
				e.ice = IllegalCharError(toString(c));
				return e;
			}
		}
		e.tokens = tokens;
		return e;
	}

};

E run(std::string txt) {
	Lexer lexer = Lexer(txt);
	E lexerRes = lexer.make_tokens();

	return lexerRes;
}