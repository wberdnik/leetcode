//https://leetcode.com/problems/substring-with-concatenation-of-all-words/
struct Tracer {
    int startInx; //in s
    int curWordIndex; //0..lnPattern
    
    Tracer() : startInx(0), curWordIndex(0) {};
    Tracer(int s, int c) : startInx(s), curWordIndex(c) {};
};

struct WordTracers {
    int inxWord; //const
    std::vector<Tracer> trace;
    std::vector<int> successStartInx;
    
    WordTracers(int w) : inxWord(w) {};

};

struct CharDescriptor {
    char firstChar; //const
    std::vector <WordTracers> tracers;

    CharDescriptor(char c, int w) : firstChar(c) {
        tracers.push_back(WordTracers(w));
    };
};

struct WordDescriptor{
    int realInxWord;
    int count;
    string word;
       
    WordDescriptor(int inx, int c, string& w): realInxWord(inx), count(c), word(w) {};
};

struct Chain {
    int inxStart;
    int pointer;
    std::vector<WordDescriptor> words;
    
    Chain(int s, std::vector<WordDescriptor> zipWords) : inxStart(s), pointer(s) {
        std::copy(zipWords.begin(), zipWords.end(), std::back_inserter(words));
    };
    
    int probe(){
        int x = 0;
        for(auto word : words){
            x += word.count;
        }
        return x;
    } 
};

const int ERROR = -1;


class Solution {

public:
    
    std::vector<int> findSubstring(string s, vector<string>& words) { 
        
        int countWords = words.size();
        //asserts
        if (!countWords) {
            return std::vector <int>();
        }

        lnPattern = words.at(0).length();
        if (!lnPattern || countWords * lnPattern > s.length()) {
             return std::vector <int>();
        }

        zippingWords(words, countWords);       
        
        //test:
        if(zipWords.size() < 3){
            vector<string> variation;
            string first, second;
                
            switch(zipWords.size()){
               case 1: 
                  second = first = zipWords[0].word;
                  for(int i = 1; i< countWords; i++){
                      first = first + second;
                  }
                  variation.push_back(first);
                   break;
               case 2:
                   first = zipWords[0].word;                
                   second = zipWords[1].word;
                   variation.push_back(first+second);
                   variation.push_back(second+first);
                   break;                                   
            }
             
            
            if(countWords == 2 || zipWords.size() == 1){
               std::vector <int> res;
               for(auto probe : variation){
                    auto j = s.find(probe, 0);                  
                    while(j != std::string::npos){
                       if (find(res.begin(), res.end(), j) == res.end()) {
                           res.push_back(j);
                       }
                       j = s.find(probe, j+1); //aa ab
                    }                    
               }
               return res;
            }
               
                
            bool f = false;
            for(auto probe : variation){
                if(s.find(probe, 0) != std::string::npos){
                    f = true;
                    break;
                }
            }
            if(!f){
                 return std::vector <int>();
            }    
                
        }     
       
        compileRules(); 
        parseSource2Rules (s);    
   
        for (auto rule : rules) {
            for (auto wDs : rule.tracers) {
                for (auto startInx : wDs.successStartInx) {
                    if (allWords.find(startInx) == allWords.end()) {
                        allWords.insert(std::pair<int,vector<int>>(startInx, vector<int>()));
                    }
                    allWords[startInx].push_back(wDs.inxWord);
                }
            }
        }
        rules.clear();  
        
        int upLen = s.length() - lnPattern * countWords;
        return semantic(upLen);
    }
    
private:
    std::vector<CharDescriptor> rules;
    std::vector<WordDescriptor> zipWords;
    map <int, vector<int>> allWords;
    int lnPattern;
    
    /** control of 'discovery'
    **/
    std::vector<int> semantic(int upLen){
        std::vector <int> res;
        vector<Chain> currentChains, newChains;        
        int min_inx = -1;

        for (auto position : allWords) {
            if (position.first > upLen || position.first < min_inx) {
                continue;
            }
            for (auto inxWord : position.second) {
                auto chain = Chain(position.first, zipWords);
                chain.words[inxWord].count --;
                    
                if (chain.inxStart <= min_inx) {
                    break;
                }
                    
               discovery(chain, res, newChains, min_inx, upLen);                      
            }
        }
        
        while(newChains.size()){
            for(auto i : newChains)
                currentChains.push_back(i);
            newChains.clear();
            for(auto chain: currentChains ){
                discovery(chain, res, newChains, min_inx, upLen);
            }
            
        }

        return res;
    }
    
    
    /** trying to consruct chain of words
    **/
    void discovery(
        Chain& chain, 
        std::vector<int>& res, 
        vector<Chain>& newChains,          
        int& min_inx,
        int upLen
    ){
        
        if (chain.inxStart > upLen || chain.inxStart < min_inx) {
              return;
        }
        
        int remain = chain.probe();
         while (true) { 
             if (!remain) {// success                        
                 if (find(res.begin(), res.end(), chain.inxStart) == res.end()) {
                     min_inx = chain.inxStart;
                     res.push_back(chain.inxStart);
                  }                 
                  return;// while
              }

              auto nextChain = allWords.find(chain.pointer + lnPattern);
              if (nextChain == allWords.end()) { // broken chain of words
                   return;
              }

              bool it_first = true;
              int lastNWord;
              for (auto nWord : nextChain->second) {
                  if (chain.words[nWord].count > 0) {
                     if (it_first) {
                         it_first = false;
                         lastNWord = nWord;
                         chain.words[nWord].count--;
                         chain.pointer = nextChain->first; // move to next word
                         remain--;
                         continue;
                      }                    
                      
                      if(!remain){
                          break;
                      }
                      
                      
                     Chain dop = chain;
                     dop.words[nWord].count--;
                     dop.words[lastNWord].count++;
                     newChains.push_back(dop);
                  }
                }
                if(it_first){ // nothing to add
                  return;
                }
         }//while
    }
    
    /* preparing zipWords
    */
    void zippingWords(vector<string>& words, int countWords) {
        //prepare zipWords
        for(int i = 0; i < countWords; i++){
            string& word = words[i];
            bool f = false;
            for(auto z = zipWords.begin(); z!= zipWords.end(); z++){
                if(z->word == word){
                    z->count++;
                    f = true;
                    break;
                }
            }
            if(!f){
                zipWords.push_back(WordDescriptor(i,1,word));
            }
        }    
   };

    /* preparing structures for parse sourse by words
    */
    void compileRules() {      
        for (int i = 0; i < zipWords.size(); i++) {
            char c = zipWords[i].word[0];
            
            bool f = false;
            for (auto rule = rules.begin(); rule != rules.end(); ++rule) {

                if (rule->firstChar == c) {
                    f = true;
                    rule->tracers.push_back(WordTracers(i));
                    break;
                }
            }
            if (!f) {
                rules.push_back(CharDescriptor(c, i));
            }
        }
    }
    
    /* parsing sourse by 'words'
    */
    void parseSource2Rules (string& s){
        const char* in_s = s.c_str();       

        for (int i = 0, n = s.length(); i <= n; i++) {// +1 extra to close all tracert
            char c = i == n ? ' ' : in_s[i];             
          

            for (auto rule = rules.begin(); rule != rules.end(); rule++) {

                // moving  
                for (auto wDs = rule->tracers.begin(); wDs != rule->tracers.end(); wDs++) {
                    
                    const char* corrent_word = zipWords[wDs->inxWord].word.c_str();
                    
                    int watch = 0;

                    for (auto tracer = wDs->trace.begin(); tracer != wDs->trace.end(); tracer++) {
                        if (tracer->curWordIndex == ERROR) {
                            watch ++;
                            continue;
                        }

                        tracer->curWordIndex++;

                        if (tracer->curWordIndex >= lnPattern) {
                            wDs->successStartInx.push_back(tracer->startInx);
                            
                            watch ++;
                            tracer->curWordIndex = ERROR; // erase
                            continue;

                        }
                        if (c != corrent_word[tracer->curWordIndex]) {
                            watch ++;
                            tracer->curWordIndex = ERROR; // erase
                        }
                    }
                    if(watch && wDs->trace.size() == watch){
                         wDs->trace.clear();
                    }

                }

                if (rule->firstChar == c && i <= n - lnPattern) {
                    // new  trace
                    auto t = Tracer(i, 0);
                    for (auto wDs = rule->tracers.begin(); wDs != rule->tracers.end(); wDs++) {
                        wDs->trace.push_back(t);
                    }
                }
            }
        } 
 
    }
};
