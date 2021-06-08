import re
from typing import Mapping, Tuple, Callable, Any, Union, List

from .utils import freeze

__all__ = ('Query', 'where')


def is_sequence(obj):
    return hasattr(obj, '__iter__')


class QueryInstance:
    def __init__(self, test: Callable[[Mapping], bool], hashval: Tuple):
        self._test = test
        self._hash = hashval

    def __call__(self, value: Mapping) -> bool:
        return self._test(value)

    def __hash__(self):
        # We calculate the query hash by using the ``hashval`` object which
        # describes this query uniquely so we can calculate a stable hash value
        # by simply hashing it
        return hash(self._hash)

    def __repr__(self):
        return 'QueryImpl{}'.format(self._hash)

    def __eq__(self, other: object):
        if isinstance(other, QueryInstance):
            return self._hash == other._hash

        return False

    # --- Query modifiers -----------------------------------------------------

    def __and__(self, other: 'QueryInstance') -> 'QueryInstance':
        # We use a frozenset for the hash as the AND operation is commutative
        # (a & b == b & a) and the frozenset does not consider the order of
        # elements
        return QueryInstance(lambda value: self(value) and other(value),
                             ('and', frozenset([self._hash, other._hash])))

    def __or__(self, other: 'QueryInstance') -> 'QueryInstance':
        # We use a frozenset for the hash as the OR operation is commutative
        # (a | b == b | a) and the frozenset does not consider the order of
        # elements
        return QueryInstance(lambda value: self(value) or other(value),
                             ('or', frozenset([self._hash, other._hash])))

    def __invert__(self) -> 'QueryInstance':
        return QueryInstance(lambda value: not self(value),
                             ('not', self._hash))


class Query(QueryInstance):
    def __init__(self) -> None:
        # The current path of fields to access when evaluating the object
        self._path = ()  # type: Tuple[str, ...]

        # Prevent empty queries to be evaluated
        def notest(_):
            raise RuntimeError('Empty query was evaluated')

        super().__init__(
            test=notest,
            hashval=(None,)
        )

    def __repr__(self):
        return '{}()'.format(type(self).__name__)

    def __hash__(self):
        return super().__hash__()

    def __getattr__(self, item: str):
        # Generate a new query object with the new query path
        # We use type(self) to get the class of the current query in case
        # someone uses a subclass of ``Query``
        query = type(self)()

        # Now we add the accessed item to the query path ...
        query._path = self._path + (item,)

        # ... and update the query hash
        query._hash = ('path', query._path)

        return query

    def __getitem__(self, item: str):
        return self.__getattr__(item)

    def _generate_test(
            self,
            test: Callable[[Any], bool],
            hashval: Tuple,
            allow_empty_path: bool = False
    ) -> QueryInstance:
        if not self._path and not allow_empty_path:
            raise ValueError('Query has no path')

        def runner(value):
            try:
                # Resolve the path
                for part in self._path:
                    value = value[part]
            except (KeyError, TypeError):
                return False
            else:
                # Perform the specified test
                return test(value)

        return QueryInstance(
            lambda value: runner(value),
            hashval
        )

    def __eq__(self, rhs: Any):
        return self._generate_test(
            lambda value: value == rhs,
            ('==', self._path, freeze(rhs))
        )

    def __ne__(self, rhs: Any):
        return self._generate_test(
            lambda value: value != rhs,
            ('!=', self._path, freeze(rhs))
        )

    def __lt__(self, rhs: Any) -> QueryInstance:
        return self._generate_test(
            lambda value: value < rhs,
            ('<', self._path, rhs)
        )

    def __le__(self, rhs: Any) -> QueryInstance:
        return self._generate_test(
            lambda value: value <= rhs,
            ('<=', self._path, rhs)
        )

    def __gt__(self, rhs: Any) -> QueryInstance:
        return self._generate_test(
            lambda value: value > rhs,
            ('>', self._path, rhs)
        )

    def __ge__(self, rhs: Any) -> QueryInstance:
        return self._generate_test(
            lambda value: value >= rhs,
            ('>=', self._path, rhs)
        )

    def exists(self) -> QueryInstance:
        return self._generate_test(
            lambda _: True,
            ('exists', self._path)
        )

    def matches(self, regex: str, flags: int = 0) -> QueryInstance:
        def test(value):
            if not isinstance(value, str):
                return False

            return re.match(regex, value, flags) is not None

        return self._generate_test(test, ('matches', self._path, regex))

    def search(self, regex: str, flags: int = 0) -> QueryInstance:
        def test(value):
            if not isinstance(value, str):
                return False

            return re.search(regex, value, flags) is not None

        return self._generate_test(test, ('search', self._path, regex))

    def test(self, func: Callable[[Mapping], bool], *args) -> QueryInstance:
        return self._generate_test(
            lambda value: func(value, *args),
            ('test', self._path, func, args)
        )

    def any(self, cond: Union[QueryInstance, List[Any]]) -> QueryInstance:
        if callable(cond):
            def test(value):
                return is_sequence(value) and any(cond(e) for e in value)

        else:
            def test(value):
                return is_sequence(value) and any(e in cond for e in value)

        return self._generate_test(
            lambda value: test(value),
            ('any', self._path, freeze(cond))
        )

    def all(self, cond: Union['QueryInstance', List[Any]]) -> QueryInstance:
        if callable(cond):
            def test(value):
                return is_sequence(value) and all(cond(e) for e in value)

        else:
            def test(value):
                return is_sequence(value) and all(e in value for e in cond)

        return self._generate_test(
            lambda value: test(value),
            ('all', self._path, freeze(cond))
        )

    def one_of(self, items: List[Any]) -> QueryInstance:
        return self._generate_test(
            lambda value: value in items,
            ('one_of', self._path, freeze(items))
        )

    def fragment(self, document: Mapping) -> QueryInstance:
        def test(value):
            for key in document:
                if key not in value or value[key] != document[key]:
                    return False

            return True

        return self._generate_test(
            lambda value: test(value),
            ('fragment', freeze(document)),
            allow_empty_path=True
        )

    def noop(self) -> QueryInstance:
        return QueryInstance(
            lambda value: True,
            ()
        )


def where(key: str) -> Query:
    return Query()[key]
