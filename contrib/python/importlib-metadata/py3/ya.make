# Generated by devtools/yamaker (pypi).

PY3_LIBRARY()

VERSION(8.4.0)

LICENSE(Apache-2.0)

NO_LINT()

PY_SRCS(
    TOP_LEVEL
    importlib_metadata/__init__.py
    importlib_metadata/_adapters.py
    importlib_metadata/_collections.py
    importlib_metadata/_compat.py
    importlib_metadata/_functools.py
    importlib_metadata/_itertools.py
    importlib_metadata/_meta.py
    importlib_metadata/_text.py
    importlib_metadata/compat/__init__.py
    importlib_metadata/compat/py311.py
    importlib_metadata/compat/py39.py
    importlib_metadata/diagnose.py
)

RESOURCE_FILES(
    PREFIX contrib/python/importlib-metadata/py3/
    .dist-info/METADATA
    .dist-info/top_level.txt
    importlib_metadata/py.typed
)

END()
