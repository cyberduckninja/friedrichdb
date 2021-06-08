"""
Utility functions.
"""

from collections import OrderedDict, abc
from typing import List, Iterator, TypeVar, Generic, Union, Optional

K = TypeVar('K')
V = TypeVar('V')
D = TypeVar('D')

__all__ = ( 'freeze')


class FrozenDict(dict):
    """
    An immutable dictoinary.

    This is used to generate stable hashes for queries that contain dicts.
    Usually, Python dicts are not hashable because they are mutable. This
    class removes the mutability and implements the ``__hash__`` method.
    """

    def __hash__(self):
        # Calculate the has by hashing a tuple of all dict items
        return hash(tuple(sorted(self.items())))

    def _immutable(self, *args, **kws):
        raise TypeError('object is immutable')

    # Disable write access to the dict
    __setitem__ = _immutable
    __delitem__ = _immutable
    clear = _immutable
    setdefault = _immutable
    popitem = _immutable

    def update(self, e=None, **f):
        raise TypeError('object is immutable')

    def pop(self, k, d=None):
        raise TypeError('object is immutable')


def freeze(obj):
    """
    Freeze an object by making it immutable and thus hashable.
    """
    if isinstance(obj, dict):
        # Transform dicts into ``FrozenDict``s
        return FrozenDict((k, freeze(v)) for k, v in obj.items())
    elif isinstance(obj, list):
        # Transform lists into tuples
        return tuple(freeze(el) for el in obj)
    elif isinstance(obj, set):
        # Transform sets into ``frozenset``s
        return frozenset(obj)
    else:
        # Don't handle all other objects
        return obj
