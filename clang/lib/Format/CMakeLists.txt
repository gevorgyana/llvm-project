set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangFormat
  AffectedRangeManager.cpp
  BreakableToken.cpp
  ContinuationIndenter.cpp
  Format.cpp
  FormatToken.cpp
  FormatTokenLexer.cpp
  MacroExpander.cpp
  NamespaceEndCommentsFixer.cpp
  SortJavaScriptImports.cpp
  TokenAnalyzer.cpp
  TokenAnnotator.cpp
  UnwrappedLineFormatter.cpp
  UnwrappedLineParser.cpp
  UsingDeclarationsSorter.cpp
  WhitespaceManager.cpp
  shim.cpp
  lexer.cpp
  Confusables.cpp
  Lexer.cpp
  )

target_include_directories(clangFormat PUBLIC /home/artyom/proj/formatter/swift/build/Ninja-DebugAssert/llvm-linux-x86_64/include /home/artyom/proj/formatter/swift/llvm-project/clang/include /home/artyom/proj/formatter/swift/swift/include /home/artyom/proj/formatter/swift/llvm-project/llvm/include)
