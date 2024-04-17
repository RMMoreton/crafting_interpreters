# Chapter 2 Challenges

1.  Pick an open source language and poke around. Does it use Yacc/Lex?

    1.  [cPython](https://github.com/python/cpython) has a directory
        `/Parser/lexer` and `/Parser/tokenizer` which have some complex
        looking `C` in them. I assume, from the names, that that's their
        tokenizer (i.e. no, they aren't using Yacc/Lex).

1.  Why might an interpreter *not* use JIT compilation?

    1.  That seems complicated, which I've got to assume would be a pretty
        good reason not to. The book describes it as, "best left to the
        experts".

1.  Why might Lisp implementations include both a `C` transpiler and an
    interpreter?

    1.  I think it's a tradeoff. Compiling to `C` and then to machine code
        probably generates good final code (you can do optimizations etc),
        but that's two compilation steps and the optimizations probably take
        time. Running the Lisp in an interpreter would result in less
        optimized machine code, but the user doesn't have to wait for
        compilation to complete in order to run their program.