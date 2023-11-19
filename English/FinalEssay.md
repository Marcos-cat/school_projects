---
name: Marcos Grzesiak
title: The Superpowers of Uiua
topic: Uiua and Stack-Based Array Languages
---

Typically, programming includes English letters, and everyday words. (If somewhat specialized.) But, some look more like this: `⍜⍘√(÷⊃⧻/+)-÷⊃⧻/+.`. What are these symbols, hieroglyphics!? In fact, this is a programming language called Uiua. Programmers have had the comfort of the C-based languages for a long time. C is the language upon which many commonplace languages are built. It has a familiar curly-brace syntax and uses regular English characters; characters that can be typed on a keyboard. But other languages exist unbeknownst to many that break the norms that many don't even realize can be broken. Uiua is one such language. The combination of paradigms in Uiua enables a problem-solving mindset. 

Languages that use glyphs allow for more concise programs. Take the example of a simple sum function. In a language like Python you might solve the problem via importing a library like `numpy`, and using its built-in sum function. The code to do that might look something like this:
    
```python
import numpy as np 

np.sum([1, 2, 3])
```

The above solution is about as simple as it can get for Python, and for other languages as well. But take a look at the solution Uiua provides:

```uiua
/+ [1 2 3]
```

Excluding the list of numbers for which we are trying to find the sum (i.e. `[1 2 3]`), this solution is just two characters, excluding whitespace. When you contrast this with the twenty-three that Python uses, one begins to realize the appeal of this language. This isn't a cherry-picked example either, Uiua consistently provides shorter solutions to the same problem. Uiua can accomplish this because rather than using words like `sum` to name its functions, it uses Unicode symbols that carry the same meaning. In the Uiua example, the two stars of the show are `/` and `+`. The plus sign (`+`) is fairly self-explanatory, it takes two numbers (often called scalars) and adds them together to produce a single number. For example, one and two would produce three. Having this property, we refer to the plus sign (`+`) as a binary operation or function because it takes two inputs. The `/` or slash on the other hand is not a function at all, but instead modifies the function in front of it to give it novel behavior. The slash (`/`) in Uiua is referred to as Reduce because it takes an array (a list of numbers) and applies its functions 'in-between' all the values, *reducing* all the values into one single value. That is to say, Reduce transforms the expression `/+ [1 2 3]` into something like `1 + 2 + 3`. That is why the above example computes the sum of the array. As has been made quite apparent, Uiua packs much more meaning into the set of glyphs that it uses. This approach had the result of making the Uiua example much more concise than the Python solution. The use of glyphs allows programs to be elegant and simplistic, rather than overly verbose and complex. 

When writing programs in Uiua, Point-free programming produces algorithms that are more similar to how people think. First, a clarification of what Point-free really means. Point-free code is defined as code that does not specify what inputs it will take. Plain and simple. The essence of Point-free programming is thinking about general transformations rather than specific ones. An easy example is the Pythagorean theorem in Uiua. The code looks like this:

```uiua
√+∩(×.) 3 4
```

This would output the number five, as the hypotenuse of a triangle with legs of size three and four is five. The three and four are fed into the function and a five comes out. Without diving into the specifics the `√+∩(×.)` is a function that describes the transformation that the input values must undergo. A good analogy is that rather than 'slotting in' the values of three and four, they are fed through a pipeline. When the vast majority of your time is spent thinking about algorithms and how they affect the inputs, the method of Point-free programming allows the algorithms to be separated from their inputs, which removes an extra complication from the mental process of deciphering what a bit of code does. Allowing programmers to more easily reason about code, Point-free is a valuable and beneficial technique.

Uiua's extensive system of Rank-polymorphism removes mental overhead from the programmer. So, what IS Rank-polymorphism? Although it sounds big and complex, the word can be split in two. Rank is just a fancy way of describing how many dimensions an array has. For example a number is Rank 0, a vector (or list) is Rank 1, and a matrix is Rank 2. Polymorphism is the principle that a function changes slightly depending on its input. Put the two together and the meaning becomes "a function that changes its behavior depending on the Rank of the inputs." An example of a function with this behavior is the addition function from earlier. In the following example, the output will be five, as expected.

```uiua
+ 3 2
```

But the next example provides a surprise.

```uiua
+ 1 [1 2 3]
```

Even though addition wasn't supplied with a number but rather a list of numbers, its behavior changes. Instead, it goes through each of the numbers in the list and adds one to them as it was supplied with a one as its first input. The output of the above code would be `[2 3 4]` because each of the elements was increased by one. This is what Rank-polymorphism allows for. As shown in the example above, the fact that the addition function has Rank-polymorphism enables writing much simpler programs. There was no need to specify that the one should be added to each of the numbers in the list, it was done automatically as an integral behavior of the addition function. Having to specify the behavior that you need is an unnecessary extra step that Uiua doesn't force you to take. As a whole, the ease of use provided by Rank-polymorphism removes mental overhead from the programmer.

In many different scenarios, the features that Uiua provides are beneficial for programmers. Uiua is able to condense programs down for maximum efficiency by employing a wide variety of glyphs. It also enforces Point-free programming and stops you from writing functions that are too tangled and complex, forcing all code to be a simple pipeline, a mere transformation. Finally, Uiua's extensive system of Rank-polymorphism takes care of tons of redundant code that would not add any extra information. In short, Uiua is an incredible language that can be used as a vastly superior alternative to many common languages, such as Python.
