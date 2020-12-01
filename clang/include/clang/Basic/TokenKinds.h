//===--- TokenKinds.h - Enum values for C Token Kinds -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Defines the clang::TokenKind enum and support functions.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_BASIC_TOKENKINDS_H
#define LLVM_CLANG_BASIC_TOKENKINDS_H

#include "llvm/Support/Compiler.h"

namespace clang {

namespace tok {

/// Provides a simple uniform namespace for tokens from all C languages.
/*
enum TokenKind : unsigned short {

#define TOK(X) X,
#include "clang/Basic/TokenKinds.def"
NUM_TOKENS
};
                               */

enum TokenKind : unsigned short {
#define TOK(X) X,
// part of the tokens is already in clang
#include "clang/Basic/TokenKinds.def"
  // NUM_TOKENS
  // #undef TOK
  // And those that are specific to Swift have to be translated
  // verbatium
  // What is marked with CTO is for compile time only
  // which means that these tokens will be remapped thanks to
  // the RuntimeSwitch below

  kw_repeat,
  kw_in,
  kw_fallthrough,
  kw_where,
  kw_as,
  kw_Any,
  kw_is,
  kw_nil,
  kw_rethrows,
  kw_super,
  kw_self,
  kw_Self,
  kw_throws,
  kw___FILE__,
  kw___LINE__,
  kw___COLUMN__,
  kw___DSO_HANDLE__,
  kw__,
  // CTO
  l_angle,
  // CTO
  r_angle,
  period_prefix,
  at_sign,
  pound,
  amp_prefix,
  backtick,
  backslash,
  exclaim_postfix,
  question_postfix,
  question_infix,
  string_quote,
  single_quote,
  multiline_string_quote,
  pound_keyPath,
  pound_line,
  pound_selector,
  pound_file,
  pound_fileID,
  pound_filePath,
  pound_column,
  pound_function,
  pound_dsohandle,
  pound_assert,
  pound_sourceLocation,
  pound_warning,
  pound_error,
  pound_if,
  pound_elseif,
  pound_endif,
  pound_available,
  pound_fileLiteral,
  pound_imageLiteral,
  pound_colorLiteral,
  integer_literal,
  floating_literal,
  oper_binary_unspaced,
  oper_binary_spaced,
  oper_postfix,
  oper_prefix,
  dollarident,
  contextual_keyword,
  raw_string_delimiter,
  string_segment,
  string_interpolation_anchor,
  kw_yield,
  kw_undef,
  kw_sil,
  kw_sil_stage,
  kw_sil_property,
  kw_sil_vtable,
  kw_sil_global,
  kw_sil_witness_table,
  kw_sil_default_witness_table,
  kw_sil_differentiability_witness,
  kw_sil_coverage_map,
  kw_sil_scope,
  sil_dollar,
  sil_exclamation,
  code_complete,
  sil_local_name,
  pound_else,
  kw_guard,
  kw_defer,
  kw_internal,
  kw_fileprivate,
  kw_var,
  kw_typealias,
  kw_subscript,
  kw_protocol,
  kw_precedencegroup,
  kw_let,
  kw_inout,
  kw_init,
  kw_func,
  kw_extension,
  kw_deinit,
  kw_associatedtype,
  NUM_TOKENS
};

/// Provides a namespace for preprocessor keywords which start with a
/// '#' at the beginning of the line.
enum PPKeywordKind {
#define PPKEYWORD(X) pp_##X,
#include "clang/Basic/TokenKinds.def"
  NUM_PP_KEYWORDS
};

/// Provides a namespace for Objective-C keywords which start with
/// an '@'.
enum ObjCKeywordKind {
#define OBJC_AT_KEYWORD(X) objc_##X,
#include "clang/Basic/TokenKinds.def"
  NUM_OBJC_KEYWORDS
};

/// Defines the possible values of an on-off-switch (C99 6.10.6p2).
enum OnOffSwitch { OOS_ON, OOS_OFF, OOS_DEFAULT };

/// Determines the name of a token as used within the front end.
///
/// The name of a token will be an internal name (such as "l_square")
/// and should not be used as part of diagnostic messages.
const char *getTokenName(TokenKind Kind) LLVM_READNONE;

/// Determines the spelling of simple punctuation tokens like
/// '!' or '%', and returns NULL for literal and annotation tokens.
///
/// This routine only retrieves the "simple" spelling of the token,
/// and will not produce any alternative spellings (e.g., a
/// digraph). For the actual spelling of a given Token, use
/// Preprocessor::getSpelling().
const char *getPunctuatorSpelling(TokenKind Kind) LLVM_READNONE;

/// Determines the spelling of simple keyword and contextual keyword
/// tokens like 'int' and 'dynamic_cast'. Returns NULL for other token kinds.
const char *getKeywordSpelling(TokenKind Kind) LLVM_READNONE;

/// Return true if this is a raw identifier or an identifier kind.
inline bool isAnyIdentifier(TokenKind K) {
  return (K == tok::identifier) || (K == tok::raw_identifier);
}

/// Return true if this is a C or C++ string-literal (or
/// C++11 user-defined-string-literal) token.
inline bool isStringLiteral(TokenKind K) {
  return K == tok::string_literal || K == tok::wide_string_literal ||
         K == tok::utf8_string_literal || K == tok::utf16_string_literal ||
         K == tok::utf32_string_literal;
}

/// Return true if this is a "literal" kind, like a numeric
/// constant, string, etc.
inline bool isLiteral(TokenKind K) {
  return K == tok::numeric_constant || K == tok::char_constant ||
         K == tok::wide_char_constant || K == tok::utf8_char_constant ||
         K == tok::utf16_char_constant || K == tok::utf32_char_constant ||
         isStringLiteral(K) || K == tok::header_name;
}

/// Return true if this is any of tok::annot_* kinds.
bool isAnnotation(TokenKind K);

/// Return true if this is an annotation token representing a pragma.
bool isPragmaAnnotation(TokenKind K);

} // end namespace tok
} // end namespace clang

#endif
