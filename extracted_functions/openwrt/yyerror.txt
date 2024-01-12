static void yyerror(const char *err);
static void zconfprint(const char *err, ...);
static void zconf_error(const char *err, ...);
static bool zconf_endtoken(const char *tokenname,
			   const char *expected_tokenname);

struct symbol *symbol_hash[SYMBOL_HASHSIZE];

struct menu *current_menu, *current_entry;



# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_HELPTEXT = 3,                 /* T_HELPTEXT  */
  YYSYMBOL_T_WORD = 4,                     /* T_WORD  */
  YYSYMBOL_T_WORD_QUOTE = 5,               /* T_WORD_QUOTE  */
  YYSYMBOL_T_BOOL = 6,                     /* T_BOOL  */
  YYSYMBOL_T_CHOICE = 7,                   /* T_CHOICE  */
  YYSYMBOL_T_CLOSE_PAREN = 8,              /* T_CLOSE_PAREN  */
  YYSYMBOL_T_COLON_EQUAL = 9,              /* T_COLON_EQUAL  */
  YYSYMBOL_T_COMMENT = 10,                 /* T_COMMENT  */
  YYSYMBOL_T_CONFIG = 11,                  /* T_CONFIG  */
  YYSYMBOL_T_DEFAULT = 12,                 /* T_DEFAULT  */
  YYSYMBOL_T_DEF_BOOL = 13,                /* T_DEF_BOOL  */
  YYSYMBOL_T_DEF_TRISTATE = 14,            /* T_DEF_TRISTATE  */
  YYSYMBOL_T_DEPENDS = 15,                 /* T_DEPENDS  */
  YYSYMBOL_T_ENDCHOICE = 16,               /* T_ENDCHOICE  */
  YYSYMBOL_T_ENDIF = 17,                   /* T_ENDIF  */
  YYSYMBOL_T_ENDMENU = 18,                 /* T_ENDMENU  */
  YYSYMBOL_T_HELP = 19,                    /* T_HELP  */
  YYSYMBOL_T_HEX = 20,                     /* T_HEX  */
  YYSYMBOL_T_IF = 21,                      /* T_IF  */
  YYSYMBOL_T_IMPLY = 22,                   /* T_IMPLY  */
  YYSYMBOL_T_INT = 23,                     /* T_INT  */
  YYSYMBOL_T_MAINMENU = 24,                /* T_MAINMENU  */
  YYSYMBOL_T_MENU = 25,                    /* T_MENU  */
  YYSYMBOL_T_MENUCONFIG = 26,              /* T_MENUCONFIG  */
  YYSYMBOL_T_MODULES = 27,                 /* T_MODULES  */
  YYSYMBOL_T_ON = 28,                      /* T_ON  */
  YYSYMBOL_T_OPEN_PAREN = 29,              /* T_OPEN_PAREN  */
  YYSYMBOL_T_OPTIONAL = 30,                /* T_OPTIONAL  */
  YYSYMBOL_T_PLUS_EQUAL = 31,              /* T_PLUS_EQUAL  */
  YYSYMBOL_T_PROMPT = 32,                  /* T_PROMPT  */
  YYSYMBOL_T_RANGE = 33,                   /* T_RANGE  */
  YYSYMBOL_T_RESET = 34,                   /* T_RESET  */
  YYSYMBOL_T_SELECT = 35,                  /* T_SELECT  */
  YYSYMBOL_T_SOURCE = 36,                  /* T_SOURCE  */
  YYSYMBOL_T_STRING = 37,                  /* T_STRING  */
  YYSYMBOL_T_TRISTATE = 38,                /* T_TRISTATE  */
  YYSYMBOL_T_VISIBLE = 39,                 /* T_VISIBLE  */
  YYSYMBOL_T_EOL = 40,                     /* T_EOL  */
  YYSYMBOL_T_ASSIGN_VAL = 41,              /* T_ASSIGN_VAL  */
  YYSYMBOL_T_OR = 42,                      /* T_OR  */
  YYSYMBOL_T_AND = 43,                     /* T_AND  */
  YYSYMBOL_T_EQUAL = 44,                   /* T_EQUAL  */
  YYSYMBOL_T_UNEQUAL = 45,                 /* T_UNEQUAL  */
  YYSYMBOL_T_LESS = 46,                    /* T_LESS  */
  YYSYMBOL_T_LESS_EQUAL = 47,              /* T_LESS_EQUAL  */
  YYSYMBOL_T_GREATER = 48,                 /* T_GREATER  */
  YYSYMBOL_T_GREATER_EQUAL = 49,           /* T_GREATER_EQUAL  */
  YYSYMBOL_T_NOT = 50,                     /* T_NOT  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_input = 52,                     /* input  */
  YYSYMBOL_mainmenu_stmt = 53,             /* mainmenu_stmt  */
  YYSYMBOL_stmt_list = 54,                 /* stmt_list  */
  YYSYMBOL_stmt_list_in_choice = 55,       /* stmt_list_in_choice  */
  YYSYMBOL_config_entry_start = 56,        /* config_entry_start  */
  YYSYMBOL_config_stmt = 57,               /* config_stmt  */
  YYSYMBOL_menuconfig_entry_start = 58,    /* menuconfig_entry_start  */
  YYSYMBOL_menuconfig_stmt = 59,           /* menuconfig_stmt  */
  YYSYMBOL_config_option_list = 60,        /* config_option_list  */
  YYSYMBOL_config_option = 61,             /* config_option  */
  YYSYMBOL_choice = 62,                    /* choice  */
  YYSYMBOL_choice_entry = 63,              /* choice_entry  */
  YYSYMBOL_choice_end = 64,                /* choice_end  */
  YYSYMBOL_choice_stmt = 65,               /* choice_stmt  */
  YYSYMBOL_choice_option_list = 66,        /* choice_option_list  */
  YYSYMBOL_choice_option = 67,             /* choice_option  */
  YYSYMBOL_type = 68,                      /* type  */
  YYSYMBOL_logic_type = 69,                /* logic_type  */
  YYSYMBOL_default = 70,                   /* default  */
  YYSYMBOL_if_entry = 71,                  /* if_entry  */
  YYSYMBOL_if_end = 72,                    /* if_end  */
  YYSYMBOL_if_stmt = 73,                   /* if_stmt  */
  YYSYMBOL_if_stmt_in_choice = 74,         /* if_stmt_in_choice  */
  YYSYMBOL_menu = 75,                      /* menu  */
  YYSYMBOL_menu_entry = 76,                /* menu_entry  */
  YYSYMBOL_menu_end = 77,                  /* menu_end  */
  YYSYMBOL_menu_stmt = 78,                 /* menu_stmt  */
  YYSYMBOL_menu_option_list = 79,          /* menu_option_list  */
  YYSYMBOL_source_stmt = 80,               /* source_stmt  */
  YYSYMBOL_comment = 81,                   /* comment  */
  YYSYMBOL_comment_stmt = 82,              /* comment_stmt  */
  YYSYMBOL_comment_option_list = 83,       /* comment_option_list  */
  YYSYMBOL_help_start = 84,                /* help_start  */
  YYSYMBOL_help = 85,                      /* help  */
  YYSYMBOL_depends = 86,                   /* depends  */
  YYSYMBOL_visible = 87,                   /* visible  */
  YYSYMBOL_prompt_stmt_opt = 88,           /* prompt_stmt_opt  */
  YYSYMBOL_end = 89,                       /* end  */
  YYSYMBOL_if_expr = 90,                   /* if_expr  */
  YYSYMBOL_expr = 91,                      /* expr  */
  YYSYMBOL_nonconst_symbol = 92,           /* nonconst_symbol  */
  YYSYMBOL_symbol = 93,                    /* symbol  */
  YYSYMBOL_word_opt = 94,                  /* word_opt  */
  YYSYMBOL_assignment_stmt = 95,           /* assignment_stmt  */
  YYSYMBOL_assign_op = 96,                 /* assign_op  */
  YYSYMBOL_assign_val = 97                 /* assign_val  */
};
