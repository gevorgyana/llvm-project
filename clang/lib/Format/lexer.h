#include "Lexer.h"
#include "swift/Basic/LangOptions.h"
#include "clang/Lex/Token.h"
#include "shim.h"

#include <fstream>
#include <string>
#include <iostream>

bool get_me_some_swift_lexeme(const char* source, clang::tok::TokenKind& Result);

int intercept_main();
