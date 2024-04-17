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

    1.  In order to do this, you have to know about the architecture! So
        I guess that means you'd need to write a bunch of different JITs?
        I didn't get this, but it's in the answer key.

    1.  Bytecode is more compact than machine code, so if you don't have
        a ton of memory (embedded device for example) maybe you don't want
        to be spending a ton of memory on machine code if you can just use
        bytecode. I didn't get this.

        It also seems like maybe the "overhead" of running a JIT on an
        embedded device might not be worth the speed increase? Maybe that
        doesn't make sense, though.

    1.  Some platforms don't allow it! Who knew. I didn't get this.

1.  Why might Lisp implementations include both a `C` transpiler and an
    interpreter?

    1.  I think it's a tradeoff. Compiling to `C` and then to machine code
        probably generates good final code (you can do optimizations etc),
        but that's two compilation steps and the optimizations probably take
        time. Running the Lisp in an interpreter would result in less
        optimized machine code, but the user doesn't have to wait for
        compilation to complete in order to run their program.

        Apparently this isn't it at all! The reason is that Lisp lets you
        define macros, which need to be executed at compile time. So you
        *could* separately compile the macro and then run it, but that's
        overhead that doesn't make sense. To be honest, maintaining an
        entire interpreter just to implement the macros of your language
        *also* seems like a lot of overhead, though...