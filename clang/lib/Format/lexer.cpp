#include "lexer.h"

#include "Lexer.h"
#include "swift/Basic/LangOptions.h"
#include "clang/Lex/Token.h"
#include "shim.h"

#include <fstream>
#include <string>
#include <iostream>

bool get_me_some_swift_lexeme(const char* source, clang::tok::TokenKind& Result) {
  swift::LangOptions langOpts;
  std::string contents(source);
  std::cout << contents << std::endl;
  swift::LexerMode lexMode;
  swift::SourceManager SM;
  swift::Lexer L(
      langOpts,
      SM,
      contents,
      lexMode
  );
  swift::Token Tok;
  swift::ParsedTrivia LeadingTrivia, TrailingTrivia;
  L.lex(Tok, LeadingTrivia, TrailingTrivia);
  auto in_clang_terms = shim(Tok.getKind());
  Result = in_clang_terms;
  if (Tok.getKind() != swift::tok::eof) {
    return true;
  } else {
    return false;
  }
}

int intercept_main() {
  swift::LangOptions langOpts;
  std::ifstream ifs("test/main.swift");
  std::string contents(
      (std::istreambuf_iterator<char>(ifs)),
      (std::istreambuf_iterator<char>())
  );
  std::cout << contents << std::endl;
  swift::LexerMode lexMode;
  swift::SourceManager SM;

  // Use the capabilities of the SourceManager now
  // const char* source = "func foo() {}";
  // SM.addNewSourceBuffer(llvm::MemoryBuffer::getMemBuffer(source, "foobar"));

  swift::Lexer L(
      langOpts,
      SM,
      contents,
      lexMode
  );
  swift::Token Tok;
  swift::ParsedTrivia LeadingTrivia, TrailingTrivia;
  do {
    L.lex(Tok, LeadingTrivia, TrailingTrivia);
    auto in_clang_terms = shim(Tok.getKind());
  } while (Tok.getKind() != swift::tok::eof);
  return 0;
}
