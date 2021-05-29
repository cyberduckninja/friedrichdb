import pytest  # type: ignore

from .utils import freeze, FrozenDict


def test_freeze():
    frozen = freeze([0, 1, 2, {'a': [1, 2, 3]}, {1, 2}])
    assert isinstance(frozen, tuple)
    assert isinstance(frozen[3], FrozenDict)
    assert isinstance(frozen[3]['a'], tuple)
    assert isinstance(frozen[4], frozenset)

    with pytest.raises(TypeError):
        frozen[0] = 10

    with pytest.raises(TypeError):
        frozen[3]['a'] = 10

    with pytest.raises(TypeError):
        frozen[3].pop('a')

    with pytest.raises(TypeError):
        frozen[3].update({'a': 9})
