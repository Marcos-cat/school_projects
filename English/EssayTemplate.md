---
name: Marcos Grzesiak
title: # TODO
topic: Uiua and Stack-Based Array Languages
---

# Introduction Paragraph

## Hook

Typically, programming includes English letters, and everyday words. (If somewhat specialized.) But, some look more like this: `⍜⍘√(÷⊃⧻/+)-÷⊃⧻/+.`. What are these symbols, hieroglyphics!? In fact, this is a programming language called Uiua.

## Background Information

Programmers have had the comfort of the C-based languages for a long time. C is the language upon which many commonplace languages are built. It has a familiar curly-brace syntax and uses regular English characters for its function and variable names. But other languages exist unbeknownst to many that break the norms that many don't even realize can be broken. Uiua is one such language.

## Thesis Statement

The combination of paradigms in Uiua enables a problem-solving mindset. 

---

# Body Paragraph 1

## Topic Sentence

Languages that use glyphs allow for more concise programs. 

## Context/Evidence

Take the example of a simple sum function. In a language like python you might solve the problem via importing a library like `numpy`, and using its built-in sum function. The code to do that might look something like this:
    
```python
import numpy as np 

np.sum([1, 2, 3])
```

The above solution is about as simple as it can get for python, and for other languages as well. But take a look at the solution Uiua provides:

```uiua
/+ [1 2 3]
```

Excluding the list of numbers for which we are trying to find the sum (i.e. `[1 2 3]`), this solution is just two characters, excluding whitespace. When you contrast this with the twenty-three that Python uses, one begins to realize the appeal of this language. This isn't a cherry-picked example either, Uiua consistently provides shorter solutions to the same problem.

## Analysis

Uiua can accomplish this because rather that using words like `sum` to name its functions, it uses Unicode symbols that carry the same meaning. In the Uiua example, the two stars of the show are `/` and `+`. The plus sign (`+`) is fairly self-explanatory, it takes to numbers (often called scalars) and adds them together to produce a single number. For example one and two would produce three. Having this property, we refer to the plus sign (`+`) as a binary operation or function because it takes two inputs. The `/` or slash on the other hand is not a function at all, but instead modifies the function in front of it to give it novel behavior. The slash (`/`) in Uiua is referred to as Reduce because it takes an array (a list of numbers) and applies its functions 'in between' all the values. That is to say, Reduce takes the binary function addition and transforms this expression: `/+ [1 2 3]`, into something like: `1 + 2 + 3`. That is why the above example computes the sum of the array.

## Conclusion Sentence

As has been made quite apparent, Uiua packs much more meaning into the set of glyphs that it uses. This approach had the result of making the Uiua example much more concise than the Python solution. The use of glyphs allows programs to be elegant and simplistic, rather than overly verbose and complex. 

---

# Body Paragraph 2

## Topic Sentence

Point free programming produces algorithms that are more similar to how people think.

## Context/Evidence



## Analysis

## Conclusion Sentence

---

# Body Paragraph 3

## Topic Sentence

Rank-polymorphism removes mental overhead from the programmer.

## Context/Evidence

## Analysis

## Conclusion Sentence

---

# Conclusion Paragraph

## Restate Thesis

## Recap All Main Points

## Clincher/"Mic Drop"

[thesis]: ./BabyTheses.md
