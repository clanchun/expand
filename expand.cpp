//
//  expand.cpp
//  clanchun
//
//  Created by clanchun on 6/29/16.
//  Copyright © 2016 clanchun. All rights reserved.
//

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <stack>
#include <set>

using namespace std;

typedef deque<string> Prefix;
typedef set<string> Suffix;
map<Prefix, Suffix> statetab;

typedef map<string, set<Prefix> > Starter;
Starter starter;

typedef pair<string, Suffix> Node;
stack<Node> tree;

void build(Prefix&, istream&);
void add(Prefix&, string&);
void buildStarter(Prefix&, string&);

void generate(int, string&);
Suffix chooseSuffix(Prefix&, char);
int print(vector<string>&, Suffix&);

void build(Prefix& prefix, istream& in)
{
    string str;
    
    while (in >> str) {
        add(prefix, str);
    }
}

void add(Prefix& prefix, string& s)
{
    if (prefix.size() == 2) {
        statetab[prefix].insert(s);
        buildStarter(prefix, s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}

void buildStarter(Prefix& prefix, string& s)
{
    char a = prefix[0][0];
    char b = prefix[1][0];
    if (a >= 'A' && a <= 'Z')
        a += 32;
    if (b >= 'A' && b <= 'Z')
        b += 32;
    
    string str = string(1, a) + string(1, b);
    starter[str].insert(prefix);
}

void generate(int nwords, string& abbr)
{
    Prefix prefix;
    int nphrase = 0;
    string startStr = abbr.substr(0, 2);
    
    Starter::iterator iter = starter.find(startStr);
    if (iter != starter.end()) {
        set<Prefix> prefixes = iter->second;
        
        for (set<Prefix>::iterator iter = prefixes.begin(); iter != prefixes.end(); iter++)
        {
            prefix = *iter;
            Suffix suffix = chooseSuffix(prefix, abbr[2]);
            tree.push(make_pair(prefix[1], suffix));
            
            vector<string> phrase;
            phrase.push_back(prefix[0]);
            phrase.push_back(prefix[1]);
            
            int cnt = 1;
            
            while (!tree.empty())
            {
                if (cnt == nwords) {
                    Node node = tree.top();
                    if (node.second.empty()) {
                        tree.pop();
                        phrase.pop_back();
                        cnt--;
                    } else {
                        nphrase += print(phrase, node.second);
                        tree.pop();
                        phrase.pop_back();
                        cnt--;
                        continue;
                    }
                } else {
                    Node node = tree.top();
                    string lastWord = node.first;
                    Suffix suffix = node.second;
                    if (suffix.empty()) {
                        tree.pop();
                        phrase.pop_back();
                        cnt--;
                    } else {
                        string nextWord = *suffix.begin();
                        suffix.erase(suffix.begin());
                        Prefix prefix;
                        prefix.push_back(lastWord);
                        prefix.push_back(nextWord);
                        Suffix nextSuffix = chooseSuffix(prefix, abbr[cnt + 2]);
                        tree.pop();
                        tree.push(make_pair(lastWord, suffix));
                        tree.push(make_pair(nextWord, nextSuffix));
                        phrase.push_back(nextWord);
                        cnt++;
                    }
                }
            }
        }
    }
    
    if (nphrase > 0)
        cout << nphrase << " phrase(s) generated." << endl;
    else
        cout << "0 phrase generated, try another input text." << endl;
}

Suffix chooseSuffix(Prefix& prefix, char c)
{
    Suffix suffix = statetab[prefix];
    Suffix subSuffix;
    for (Suffix::iterator iter = suffix.begin(); iter != suffix.end(); iter++) {
        if ((*iter)[0] == c || (*iter)[0] - c == 32 || (*iter)[0] - c == -32) {
            subSuffix.insert(*iter);
        }
    }
    
    return subSuffix;
}

int print(vector<string>& phrase, Suffix& suffix)
{
    string str;
    int cnt = 0;
    
    for (vector<string>::iterator iter = phrase.begin(); iter != phrase.end(); iter++)
        str += *iter + " ";
    
    for (Suffix::iterator iter = suffix.begin(); iter != suffix.end(); iter++) {
        cout << str << *iter << " " << endl;
        cnt++;
    }
    
    return cnt;
}

int main(int argc, const char * argv[])
{
    if (argc < 2) {
        cout << "please input an abbr." << endl;
        exit(1);
    }
    
    string abbr = argv[1];
    int nwords = int(abbr.size());
    if (nwords < 3) {
        cout << "please input an abbr, at least 3 chars." << endl;
        exit(2);
    }
    
    Prefix prefix;
    
    build(prefix, cin);
 
    generate(nwords - 2, abbr);

    return 0;
}
