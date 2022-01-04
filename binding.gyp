{
    'targets': [
        {
            'target_name': 'nanobjectspreadtest',

            'sources': [
                "src/nanobjectspreadtest.cpp",
                "src/SampleObject.cpp",
            ],

            "include_dirs" : [
                "<!(node -e \"require('nan')\")"
            ],

            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions' ],
            'conditions': [
                ["OS=='win'", {
                "defines": [
                    "_HAS_EXCEPTIONS=1"
                ],
                "msvs_settings": {
                    "VCCLCompilerTool": {
                    "ExceptionHandling": 1
                    },
                },
                }],
                ["OS=='mac'", {
                    'cflags+': ['-fvisibility=hidden'],

                    'xcode_settings': {
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                        'CLANG_CXX_LIBRARY': 'libc++',
                        'MACOSX_DEPLOYMENT_TARGET': '10.7',
                        'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
                    },
                }],
            ]
        }
    ]
}
