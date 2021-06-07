#include <stdio.h>
#include <string>

bool isMatch(char c1, char c2){
	if(c1 == '(' && c2 == ')') return true;
	if(c1 == '[' && c2 == ']') return true;
	if(c1 == '{' && c2 == '}') return true;
	return false;
}

bool isValid(std::string s) {
    int top = -1;
    for (int i = 0; i < s.size(); ++i) {
        if (top == -1 || !isMatch(s[top], s[i]))
        {
            ++top;
            s[top] = s[i];
        }
        else --top;
    }

    return top == -1;
}

int main(int argc, const char **argv) {

    std::string tmp("(){}[]");
    printf("%d\n", (int)isValid(tmp));

    return 0;
}
