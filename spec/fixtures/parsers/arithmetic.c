#include "tree_sitter/parser.h"

#define STATE_COUNT 32
#define SYMBOL_COUNT 20

enum {
    ts_sym_expression = ts_builtin_sym_start,
    ts_sym_sum,
    ts_sym_difference,
    ts_sym_product,
    ts_sym_quotient,
    ts_sym_exponent,
    ts_sym_group,
    ts_sym_number,
    ts_sym_variable,
    ts_sym_comment,
    ts_aux_sym_1,
    ts_aux_sym_2,
    ts_aux_sym_3,
    ts_aux_sym_4,
    ts_aux_sym_5,
    ts_aux_sym_6,
    ts_aux_sym_7,
};

static const char *ts_symbol_names[] = {
    [ts_builtin_sym_document] = "DOCUMENT",
    [ts_sym_expression] = "expression",
    [ts_sym_sum] = "sum",
    [ts_sym_difference] = "difference",
    [ts_sym_product] = "product",
    [ts_sym_quotient] = "quotient",
    [ts_sym_exponent] = "exponent",
    [ts_sym_group] = "group",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [ts_sym_number] = "number",
    [ts_sym_variable] = "variable",
    [ts_sym_comment] = "comment",
    [ts_aux_sym_1] = "'+'",
    [ts_aux_sym_2] = "'-'",
    [ts_aux_sym_3] = "'*'",
    [ts_aux_sym_4] = "'/'",
    [ts_aux_sym_5] = "'^'",
    [ts_aux_sym_6] = "'('",
    [ts_aux_sym_7] = "')'",
};

static const int ts_hidden_symbol_flags[SYMBOL_COUNT] = {
    [ts_aux_sym_1] = 1,
    [ts_aux_sym_2] = 1,
    [ts_aux_sym_3] = 1,
    [ts_aux_sym_4] = 1,
    [ts_aux_sym_5] = 1,
    [ts_aux_sym_6] = 1,
    [ts_aux_sym_7] = 1,
};

static TSTree *ts_lex(TSLexer *lexer, TSStateId lex_state) {
    START_LEXER();
    switch (lex_state) {
        case 1:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 2:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(2);
            ACCEPT_TOKEN(ts_sym_comment);
        case 3:
            ACCEPT_TOKEN(ts_aux_sym_6);
        case 4:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_sym_number);
        case 5:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(ts_sym_variable);
        case 6:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(7);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(6);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(9);
            if (lookahead == '-')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if (lookahead == '^')
                ADVANCE(12);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 8:
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 9:
            ACCEPT_TOKEN(ts_aux_sym_1);
        case 10:
            ACCEPT_TOKEN(ts_aux_sym_2);
        case 11:
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 12:
            ACCEPT_TOKEN(ts_aux_sym_5);
        case 13:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(13);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(9);
            if (lookahead == '-')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if (lookahead == '^')
                ADVANCE(12);
            LEX_ERROR();
        case 14:
            ACCEPT_TOKEN(ts_aux_sym_7);
        case 15:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(15);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(14);
            LEX_ERROR();
        case 16:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(7);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(16);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(9);
            if (lookahead == '-')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(12);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(7);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(16);
            if (lookahead == '#')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(8);
            if (lookahead == '+')
                ADVANCE(9);
            if (lookahead == '-')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(11);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == '^')
                ADVANCE(12);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 6,
    [2] = 6,
    [3] = 1,
    [4] = 13,
    [5] = 13,
    [6] = 15,
    [7] = 1,
    [8] = 13,
    [9] = 15,
    [10] = 13,
    [11] = 1,
    [12] = 1,
    [13] = 1,
    [14] = 1,
    [15] = 1,
    [16] = 13,
    [17] = 13,
    [18] = 13,
    [19] = 13,
    [20] = 13,
    [21] = 6,
    [22] = 1,
    [23] = 1,
    [24] = 1,
    [25] = 1,
    [26] = 1,
    [27] = 6,
    [28] = 6,
    [29] = 6,
    [30] = 6,
    [31] = 6,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [ts_sym_expression] = SHIFT(1),
        [ts_sym_sum] = SHIFT(2),
        [ts_sym_difference] = SHIFT(2),
        [ts_sym_product] = SHIFT(2),
        [ts_sym_quotient] = SHIFT(2),
        [ts_sym_exponent] = SHIFT(2),
        [ts_sym_group] = SHIFT(2),
        [ts_sym_number] = SHIFT(2),
        [ts_sym_variable] = SHIFT(2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(3),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(22),
        [ts_aux_sym_2] = SHIFT(23),
        [ts_aux_sym_3] = SHIFT(24),
        [ts_aux_sym_4] = SHIFT(25),
        [ts_aux_sym_5] = SHIFT(26),
    },
    [2] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_expression, 1),
    },
    [3] = {
        [ts_sym_expression] = SHIFT(4),
        [ts_sym_sum] = SHIFT(5),
        [ts_sym_difference] = SHIFT(5),
        [ts_sym_product] = SHIFT(5),
        [ts_sym_quotient] = SHIFT(5),
        [ts_sym_exponent] = SHIFT(5),
        [ts_sym_group] = SHIFT(5),
        [ts_builtin_sym_error] = SHIFT(6),
        [ts_sym_number] = SHIFT(5),
        [ts_sym_variable] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(7),
    },
    [4] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(11),
        [ts_aux_sym_2] = SHIFT(12),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_4] = SHIFT(14),
        [ts_aux_sym_5] = SHIFT(15),
        [ts_aux_sym_7] = SHIFT(21),
    },
    [5] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
    },
    [6] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(21),
    },
    [7] = {
        [ts_sym_expression] = SHIFT(8),
        [ts_sym_sum] = SHIFT(5),
        [ts_sym_difference] = SHIFT(5),
        [ts_sym_product] = SHIFT(5),
        [ts_sym_quotient] = SHIFT(5),
        [ts_sym_exponent] = SHIFT(5),
        [ts_sym_group] = SHIFT(5),
        [ts_builtin_sym_error] = SHIFT(9),
        [ts_sym_number] = SHIFT(5),
        [ts_sym_variable] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(7),
    },
    [8] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(11),
        [ts_aux_sym_2] = SHIFT(12),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_4] = SHIFT(14),
        [ts_aux_sym_5] = SHIFT(15),
        [ts_aux_sym_7] = SHIFT(10),
    },
    [9] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(10),
    },
    [10] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_group, 3),
    },
    [11] = {
        [ts_sym_expression] = SHIFT(20),
        [ts_sym_sum] = SHIFT(5),
        [ts_sym_difference] = SHIFT(5),
        [ts_sym_product] = SHIFT(5),
        [ts_sym_quotient] = SHIFT(5),
        [ts_sym_exponent] = SHIFT(5),
        [ts_sym_group] = SHIFT(5),
        [ts_sym_number] = SHIFT(5),
        [ts_sym_variable] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(7),
    },
    [12] = {
        [ts_sym_expression] = SHIFT(19),
        [ts_sym_sum] = SHIFT(5),
        [ts_sym_difference] = SHIFT(5),
        [ts_sym_product] = SHIFT(5),
        [ts_sym_quotient] = SHIFT(5),
        [ts_sym_exponent] = SHIFT(5),
        [ts_sym_group] = SHIFT(5),
        [ts_sym_number] = SHIFT(5),
        [ts_sym_variable] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(7),
    },
    [13] = {
        [ts_sym_expression] = SHIFT(18),
        [ts_sym_sum] = SHIFT(5),
        [ts_sym_difference] = SHIFT(5),
        [ts_sym_product] = SHIFT(5),
        [ts_sym_quotient] = SHIFT(5),
        [ts_sym_exponent] = SHIFT(5),
        [ts_sym_group] = SHIFT(5),
        [ts_sym_number] = SHIFT(5),
        [ts_sym_variable] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(7),
    },
    [14] = {
        [ts_sym_expression] = SHIFT(17),
        [ts_sym_sum] = SHIFT(5),
        [ts_sym_difference] = SHIFT(5),
        [ts_sym_product] = SHIFT(5),
        [ts_sym_quotient] = SHIFT(5),
        [ts_sym_exponent] = SHIFT(5),
        [ts_sym_group] = SHIFT(5),
        [ts_sym_number] = SHIFT(5),
        [ts_sym_variable] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(7),
    },
    [15] = {
        [ts_sym_expression] = SHIFT(16),
        [ts_sym_sum] = SHIFT(5),
        [ts_sym_difference] = SHIFT(5),
        [ts_sym_product] = SHIFT(5),
        [ts_sym_quotient] = SHIFT(5),
        [ts_sym_exponent] = SHIFT(5),
        [ts_sym_group] = SHIFT(5),
        [ts_sym_number] = SHIFT(5),
        [ts_sym_variable] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(7),
    },
    [16] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_5] = SHIFT(15),
        [ts_aux_sym_7] = REDUCE(ts_sym_exponent, 3),
    },
    [17] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_4] = SHIFT(14),
        [ts_aux_sym_5] = SHIFT(15),
        [ts_aux_sym_7] = REDUCE(ts_sym_quotient, 3),
    },
    [18] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_4] = SHIFT(14),
        [ts_aux_sym_5] = SHIFT(15),
        [ts_aux_sym_7] = REDUCE(ts_sym_product, 3),
    },
    [19] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(11),
        [ts_aux_sym_2] = SHIFT(12),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_4] = SHIFT(14),
        [ts_aux_sym_5] = SHIFT(15),
        [ts_aux_sym_7] = REDUCE(ts_sym_difference, 3),
    },
    [20] = {
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(11),
        [ts_aux_sym_2] = SHIFT(12),
        [ts_aux_sym_3] = SHIFT(13),
        [ts_aux_sym_4] = SHIFT(14),
        [ts_aux_sym_5] = SHIFT(15),
        [ts_aux_sym_7] = REDUCE(ts_sym_sum, 3),
    },
    [21] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_group, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_group, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_group, 3),
    },
    [22] = {
        [ts_sym_expression] = SHIFT(31),
        [ts_sym_sum] = SHIFT(2),
        [ts_sym_difference] = SHIFT(2),
        [ts_sym_product] = SHIFT(2),
        [ts_sym_quotient] = SHIFT(2),
        [ts_sym_exponent] = SHIFT(2),
        [ts_sym_group] = SHIFT(2),
        [ts_sym_number] = SHIFT(2),
        [ts_sym_variable] = SHIFT(2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(3),
    },
    [23] = {
        [ts_sym_expression] = SHIFT(30),
        [ts_sym_sum] = SHIFT(2),
        [ts_sym_difference] = SHIFT(2),
        [ts_sym_product] = SHIFT(2),
        [ts_sym_quotient] = SHIFT(2),
        [ts_sym_exponent] = SHIFT(2),
        [ts_sym_group] = SHIFT(2),
        [ts_sym_number] = SHIFT(2),
        [ts_sym_variable] = SHIFT(2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(3),
    },
    [24] = {
        [ts_sym_expression] = SHIFT(29),
        [ts_sym_sum] = SHIFT(2),
        [ts_sym_difference] = SHIFT(2),
        [ts_sym_product] = SHIFT(2),
        [ts_sym_quotient] = SHIFT(2),
        [ts_sym_exponent] = SHIFT(2),
        [ts_sym_group] = SHIFT(2),
        [ts_sym_number] = SHIFT(2),
        [ts_sym_variable] = SHIFT(2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(3),
    },
    [25] = {
        [ts_sym_expression] = SHIFT(28),
        [ts_sym_sum] = SHIFT(2),
        [ts_sym_difference] = SHIFT(2),
        [ts_sym_product] = SHIFT(2),
        [ts_sym_quotient] = SHIFT(2),
        [ts_sym_exponent] = SHIFT(2),
        [ts_sym_group] = SHIFT(2),
        [ts_sym_number] = SHIFT(2),
        [ts_sym_variable] = SHIFT(2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(3),
    },
    [26] = {
        [ts_sym_expression] = SHIFT(27),
        [ts_sym_sum] = SHIFT(2),
        [ts_sym_difference] = SHIFT(2),
        [ts_sym_product] = SHIFT(2),
        [ts_sym_quotient] = SHIFT(2),
        [ts_sym_exponent] = SHIFT(2),
        [ts_sym_group] = SHIFT(2),
        [ts_sym_number] = SHIFT(2),
        [ts_sym_variable] = SHIFT(2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(3),
    },
    [27] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_exponent, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_exponent, 3),
        [ts_aux_sym_5] = SHIFT(26),
    },
    [28] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_quotient, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_quotient, 3),
        [ts_aux_sym_3] = SHIFT(24),
        [ts_aux_sym_4] = SHIFT(25),
        [ts_aux_sym_5] = SHIFT(26),
    },
    [29] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_product, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_product, 3),
        [ts_aux_sym_3] = SHIFT(24),
        [ts_aux_sym_4] = SHIFT(25),
        [ts_aux_sym_5] = SHIFT(26),
    },
    [30] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_difference, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(22),
        [ts_aux_sym_2] = SHIFT(23),
        [ts_aux_sym_3] = SHIFT(24),
        [ts_aux_sym_4] = SHIFT(25),
        [ts_aux_sym_5] = SHIFT(26),
    },
    [31] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_sum, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(22),
        [ts_aux_sym_2] = SHIFT(23),
        [ts_aux_sym_3] = SHIFT(24),
        [ts_aux_sym_4] = SHIFT(25),
        [ts_aux_sym_5] = SHIFT(26),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_arithmetic);