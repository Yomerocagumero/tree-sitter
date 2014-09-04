{
  'targets': [
    {
      'target_name': 'compiler',

      'type': 'static_library',
      'include_dirs': [
        'include',
        'src',
      ],
      'sources': [
        'src/compiler/build_tables/build_lex_table.cc',
        'src/compiler/build_tables/build_parse_table.cc',
        'src/compiler/build_tables/build_tables.cc',
        'src/compiler/build_tables/first_set.cc',
        'src/compiler/build_tables/get_metadata.cc',
        'src/compiler/build_tables/item.cc',
        'src/compiler/build_tables/item_set_closure.cc',
        'src/compiler/build_tables/item_set_transitions.cc',
        'src/compiler/build_tables/lex_conflict_manager.cc',
        'src/compiler/build_tables/lex_item.cc',
        'src/compiler/build_tables/parse_conflict_manager.cc',
        'src/compiler/build_tables/parse_item.cc',
        'src/compiler/build_tables/rule_can_be_blank.cc',
        'src/compiler/build_tables/rule_transitions.cc',
        'src/compiler/compile.cc',
        'src/compiler/conflict.cc',
        'src/compiler/generate_code/c_code.cc',
        'src/compiler/grammar.cc',
        'src/compiler/lex_table.cc',
        'src/compiler/parse_table.cc',
        'src/compiler/prepare_grammar/expand_repeats.cc',
        'src/compiler/prepare_grammar/expand_tokens.cc',
        'src/compiler/prepare_grammar/extract_tokens.cc',
        'src/compiler/prepare_grammar/intern_symbols.cc',
        'src/compiler/prepare_grammar/parse_regex.cc',
        'src/compiler/prepare_grammar/prepare_grammar.cc',
        'src/compiler/prepare_grammar/token_description.cc',
        'src/compiler/prepared_grammar.cc',
        'src/compiler/rules/blank.cc',
        'src/compiler/rules/built_in_symbols.cc',
        'src/compiler/rules/character_range.cc',
        'src/compiler/rules/character_set.cc',
        'src/compiler/rules/choice.cc',
        'src/compiler/rules/metadata.cc',
        'src/compiler/rules/named_symbol.cc',
        'src/compiler/rules/pattern.cc',
        'src/compiler/rules/repeat.cc',
        'src/compiler/rules/rule.cc',
        'src/compiler/rules/rules.cc',
        'src/compiler/rules/seq.cc',
        'src/compiler/rules/string.cc',
        'src/compiler/rules/symbol.cc',
        'src/compiler/rules/visitor.cc',
        'src/compiler/util/string_helpers.cc',
      ],
      'cflags_cc': [
        '-std=c++0x',
      ],
      'cflags_cc!': [
        '-fno-rtti'
      ],
      'xcode_settings': {
        'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
        'GCC_ENABLE_CPP_RTTI': 'YES',
        'GCC_ENABLE_CPP_EXCEPTIONS': 'NO',
      },
      'direct_dependent_settings': {
        'include_dirs': [
          'include'
        ],
      },

      # Mac OS has an old version of libstdc++ that doesn't support c++11.
      # libc++ is only present on 10.7 and later.
      'conditions': [
        ['OS == "mac"', {
          'cflags_cc': [ '-stdlib=libc++' ],
          'xcode_settings': {
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
          },
          'direct_dependent_settings': {
            'cflags_cc': [ '-stdlib=libc++' ],
            'xcode_settings': {
              'CLANG_CXX_LIBRARY': 'libc++',
            },
          },
        }]
      ],
    },

    {
      'target_name': 'runtime',
      'type': 'static_library',
      'include_dirs': [
        'include',
        'src',
      ],
      'sources': [
        'src/runtime/document.c',
        'src/runtime/lexer.c',
        'src/runtime/node.c',
        'src/runtime/parser.c',
        'src/runtime/stack.c',
        'src/runtime/string_input.c',
        'src/runtime/tree.c',
      ],
      'cflags_c': [
        '-std=c99'
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          'include'
        ],
      },
    },
  ],

  'target_defaults': {
    'default_configuration': 'Release',
    'configurations': {
      'Debug': {
        'cflags': [ '-g', '-O0' ],
        'xcode_settings': {
          'GCC_OPTIMIZATION_LEVEL': '0',
        },
      },
      'Release': {
        'cflags': [ '-O2', '-fno-strict-aliasing' ],
        'cflags!': [ '-O3', '-fstrict-aliasing' ],
      },
    },

    'cflags': [
      '-Wall',
      '-Wextra',
      '-Wno-unused-parameter'
    ],

    'xcode_settings': {
      'ALWAYS_SEARCH_USER_PATHS': 'NO',
      'WARNING_CFLAGS': [
        '-Wall',
        '-Wextra',
        '-Wno-unused-parameter'
      ],
    },
  }
}