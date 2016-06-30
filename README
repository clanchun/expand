# Expand
---
The reverse of abbreviation.

## Origin
---

Some friends asked me what _clanchun_ means, I usually told them that it means _the bright Spring_, cause I got _灿烂春_ when I first time typed _clanchun_ using a Chinese pinyin input method :) But, can it be the abbreviation of any phrase? Just like _imho_ could be _in my humble opinion_.

## Algorithm
---
The key algorithm is __Markov Chain__. Given a training text, build all possible Markov States
where the state is a two-word prefix and a suffix which is a set of words that follows this
prefix in the training text. Then, if start with any state and randomly choose one word from
the suffix, a reasonably meaningful text will be generated. But, except choosing a random word,
here, the next word is choosed according to the next character in the given abbreviation. Hopefully, some phrases could be generated.

## Usage
---
    clang++(g++) expand.cpp -o expand
	
    cat input.txt | ./expand any_abbr

## Result
---
After trying several novels downloaded from [Project Gutenberg](http://gutenberg.org/) and even putting them all together, not one phrase of _clanchun_ was generated. Cause the generation mostly stopped at _clanch_, I splited _clanchun_ into _clanc_ and _hun_, finally, I got a phrase: 

    came like a noble child, his unfinished novel.

Unfortunately, this phrase still doesn't make too much sense. so I insist that _clanchun_ means: 

    the bright Spring.
