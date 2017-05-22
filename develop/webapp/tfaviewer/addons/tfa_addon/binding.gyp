{
  "targets": [
    {
      "target_name": "tfa_addon",
      "include_dirs": [
        ".",
        "<!(node -e \"require('nan')\")"
      ],
      "sources": [
        "tfa_addon.cc",
        "zutil.cc",
        "zindex.cc"
      ],
      "libraries": [
        "-lz"
      ],
      "cflags": [
        "-std=c++1y",
        "-static-libstdc++"
      ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'OTHER_CPLUSPLUSFLAGS' : ['-stdlib=libc++'],
          },
        }],
        ['OS=="linux"', {
            'libraries': [
                "/usr/lib64/libstdc++.so.6"
            ],
        }],
      ],
    }
  ]
}


# ******************************************************************************
# Previous configurations
# ******************************************************************************
#{
#  "make_global_settings": [
#    ['CXX','/usr/bin/clang++'],
#    ['LINK','/usr/bin/clang++'],
#  ],
#  "targets": [
#    {
#      "target_name": "tfa_addon",
#      "include_dirs": [
#        ".",
#        "<!(node -e \"require('nan')\")"
#      ],
#      "sources": [
#        "tfa_addon.cc",
#        "zutil.cc",
#        "zindex.cc"
#      ],
#      "libraries": [
#        "-lz"
#      ],
#      "cflags": [
#        "-std=c++1y",
#        "-static-libstdc++"
#      ],
#      "ldflags": [
#      ],
#      'conditions': [
#        ['OS=="mac"', {
#          "cflags": [
#                '-g',
#                '-O2',
#                '-mmacosx-version-min=10.8',
#                '-stdlib=libstdc++',
#                '-lstdc++'
#          ],
#          "cxxflags": [
#                '-g',
#                '-O2',
#                '-mmacosx-version-min=10.8',
#                '-stdlib=libstdc++',
#                '-lstdc++'
#          ],
#          "ldflags": [
#                '-mmacosx-version-min=10.8',
#                '-stdlib=libstdc++'
#          ],
#          "libraries": [
#                '-lstdc++'
#          ],
#        }],
#        ['OS=="linux"', {
#            'libraries': [
#                "/usr/lib64/libstdc++.so.6"
#            ],
#            "cflags": [
#            ],
#          }
#        ],
#      ],
#    }
#  ]
#}

