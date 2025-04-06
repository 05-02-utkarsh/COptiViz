


#ifndef TOKENS_H
#define TOKENS_H

// Literal tokens
#define TOK_INT_LITERAL       256
#define TOK_FLOAT_LITERAL     257
#define TOK_IDENTIFIER        258

// Keywords
#define TOK_AUTO              259
#define TOK_BREAK             260
#define TOK_CASE              261
#define TOK_CHAR              262
#define TOK_CONST             263
#define TOK_CONTINUE          264
#define TOK_DEFAULT           265
#define TOK_DO                266
#define TOK_DOUBLE            267
#define TOK_ELSE              268
#define TOK_ENUM              269
#define TOK_EXTERN            270
#define TOK_FLOAT             271
#define TOK_FOR               272
#define TOK_GOTO              273
#define TOK_IF                274
#define TOK_INT               275
#define TOK_LONG              276
#define TOK_REGISTER          277
#define TOK_RETURN            278
#define TOK_SHORT             279
#define TOK_SIGNED            280
#define TOK_SIZEOF            281
#define TOK_STATIC            282
#define TOK_STRUCT            283
#define TOK_SWITCH            284
#define TOK_TYPEDEF           285
#define TOK_UNION             286
#define TOK_UNSIGNED          287
#define TOK_VOID              288
#define TOK_VOLATILE          289
#define TOK_WHILE             290

// Operators
#define TOK_ASSIGN            291  // =
#define TOK_EQ                292  // ==
#define TOK_NEQ               293  // !=
#define TOK_LT                294  // <
#define TOK_GT                295  // >
#define TOK_LE                296  // <=
#define TOK_GE                297  // >=
#define TOK_PLUS              298  // +
#define TOK_MINUS             299  // -
#define TOK_MULT              300  // *
#define TOK_DIV               301  // /
#define TOK_MOD               302  // %
#define TOK_INC               303  // ++
#define TOK_DEC               304  // --
#define TOK_AND               305  // &&
#define TOK_OR                306  // ||
#define TOK_NOT               307  // !
#define TOK_BITAND            308  // &
#define TOK_BITOR             309  // |
#define TOK_BITXOR            310  // ^
#define TOK_BITNOT            311  // ~
#define TOK_SHL               312  // <<
#define TOK_SHR               313  // >>

// Compound assignment
#define TOK_PLUSEQ            314
#define TOK_MINUSEQ           315
#define TOK_MULTEQ            316
#define TOK_DIVEQ             317
#define TOK_MODEQ             318

// Symbols and punctuation
#define TOK_LPAREN            319 // (
#define TOK_RPAREN            320 // )
#define TOK_LBRACE            321 // {
#define TOK_RBRACE            322 // }
#define TOK_LBRACKET          323 // [
#define TOK_RBRACKET          324 // ]
#define TOK_SEMICOLON         325 // ;
#define TOK_COMMA             326 // ,
#define TOK_DOT               327 // .
#define TOK_ARROW             328 // ->
#define TOK_COLON             329 // :
#define TOK_QUESTION          330 // ?

// Others
#define TOK_ERROR             331

//Micellanous
#define TOK_DQUOTE            300
#define TOK_SQUOTE            301
#define TOK_BACKSLASH         302


#endif // TOKENS_H


