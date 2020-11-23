// Violent X macros usage, inspired by the Swift and Clang teams.
// This is metaprogramming anyway ;)

// As they are using StringRef in their code, and I don't want to break ODR,
// I should just make sure the compiler knows what that is. This is a workaround, though.
#include "llvm/ADT/StringRef.h"
using namespace llvm;

// this defines the Swift token enum
#include "swift/Syntax/TokenKinds.h"
// This has already been modified to account for new tokens that come
// from Swift
#include "clang/Basic/TokenKinds.h"

#include "llvm/ADT/StringSwitch.h"
#include <iostream>

// Visit all Swift tokens and convert them into a string value
#define TOKEN(id)				\
  #id,
static char const* SWIFT_TOKEN_STRING_REPR[] = {
#include "swift/Syntax/TokenKinds.def"
#undef TOKEN
};

__attribute__((noinline))clang::tok::TokenKind shim(swift::tok SwiftTok) {
  // First of all, we should convert the numeric value that we have to
  // a string. For that, we have defined the swift token in string form
  auto SwiftTokStr =  SWIFT_TOKEN_STRING_REPR[static_cast<unsigned short>(SwiftTok)];

  // From the compiler's point of view, it is all good, because we do have all of
  // the necessary tokens types in clang as we have extended them above
  // But we won't need everything, but some of the characters have to be remapped.
  // Which is why we use a Runtime switch with a checker built into it.
  auto RuntimeSwitch =
    llvm::StringSwitch<clang::tok::TokenKind>(StringRef(SwiftTokStr));

#define TOKEN(id)						\
  if (strcmp(#id, "l_angle") != 0 && strcmp(#id, "r_angle") != 0) {		\
    RuntimeSwitch.Case(#id, clang::tok::TokenKind::id);		\
  }
#include "swift/Syntax/TokenKinds.def"
  RuntimeSwitch.Case("l_angle", clang::tok::TokenKind::pound);
  RuntimeSwitch.Case("r_angle", clang::tok::TokenKind::pound);
  return RuntimeSwitch.Default(clang::tok::TokenKind::pound);
}

/*
int main() {
  return 0;
}

*/
