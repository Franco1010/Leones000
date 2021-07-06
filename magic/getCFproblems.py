# © 2021-04-10 00:30:48 Franco1010 All Rights Reserved
import requests
base = "https://codeforces.com";

def hyperlink(text, target):
    p = "=HIPERVINCULO(\"{}\"; \"{}\")".format(target, text);
    return p;

class Problem:
    def __init__(self, url = "", name = "", numSolved = 0):
        self.url = url;
        self.name = name;
        self.numSolved = numSolved;
    def sheetUrl(self):
        return hyperlink(self.name, self.url);
    def deb(self):
        print(self.name, self.numSolved, self.url);

def getProblems(url):
    problems = {};
    # last = ["", "", 0];
    last = Problem();
    res = requests.get(url);
    title = 0;
    for i in res.text.split('\n'):
        i = i.strip();
        if(title == 2 and ("Participants solved the problem" in i)):
            pos = len(i) - 1;
            while(pos>=0 and i[pos] != 'x'): pos -= 1;
            if(pos >= 0):
                i = i[pos + 1:];
                i = i[:len(i) - 4];
                last.numSolved = i;
                title = 0;
                if(not last.name in problems): problems[last.name] = last;
                last = Problem();
        elif(title == 1 and i.startswith("-->")):
            i = i[3:];
            i = i[:len(i) - 4];
            last.name = i;
            title = 2;
        elif(i.startswith("<a href=\"") and
            ("contest" in i) and
            not("virtual" in i) and
            not("standings" in i) and
            not("contests" in i) and
            not("problems" in i) and
            ("problem" in i)):
                while(i[len(i) - 1] != '\"'): i = i[:len(i) - 1];
                i = i[:len(i) - 1];
                while(i[0] != '/'): i = i[1:];
                i = base + i;
                last.url = i;
                title = 1;
    return problems;

def getProblemsFromContestList(urlList):
    problems = {};
    for url in urlList:
        p = getProblems(url);
        for i in p:
            if(i not in problems): problems[i] = p[i];
    return problems;

def getGroupProblems(urlGroup):
    response = requests.get(urlGroup);
    urlsContests = [];
    for i in response.text.split(' '):
        i = i.strip();
        if(i.startswith("href=\"/group") and
            ("contest" in i) and
            not("virtual" in i) and
            not("standings" in i) and
            not("contests" in i)):
                while(i[len(i) - 1] != '\"'): i = i[:len(i) - 1];
                i = i[:len(i) - 1];
                while(i[0] != '/'): i = i[1:];
                urlsContests.append(base + i);
    return getProblemsFromContestList(urlsContests);

ans = getGroupProblems("https://codeforces.com/group/j1UosVRZar/contests");
# for i in ans: ans[i].deb();
for i in ans: print(ans[i].sheetUrl());
# for i in ans: print(ans[i].numSolved);
