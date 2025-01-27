{
    "targets": [
        {
            "target_name": "krp-sharedmemory-lib",
            "sources": [
                "lib/memory/memory.h",
                "lib/memory/memory.cpp",
                "lib/sharedmemory.h",
                "lib/lib.h",
                "lib/lib.cpp",
            ],
            "dependencies": ["<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except_all"],
        }
    ]
}