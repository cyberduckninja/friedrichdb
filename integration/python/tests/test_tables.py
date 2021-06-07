import pytest  # type: ignore
import re

from tinydb import where


def test_tables_list(db):
    db.table('table1').insert({'a': 1})
    db.table('table2').insert({'a': 1})

    assert db.tables() == {'_default', 'table1', 'table2'}


def test_one_table(db):
    table1 = db.table('table1')

    table1.insert_multiple({'int': 1, 'char': c} for c in 'abc')

    assert table1.get(where('int') == 1)['char'] == 'a'
    assert table1.get(where('char') == 'b')['char'] == 'b'


def test_multiple_tables(db):
    table1 = db.table('table1')
    table2 = db.table('table2')
    table3 = db.table('table3')

    table1.insert({'int': 1, 'char': 'a'})
    table2.insert({'int': 1, 'char': 'b'})
    table3.insert({'int': 1, 'char': 'c'})

    assert table1.count(where('char') == 'a') == 1
    assert table2.count(where('char') == 'b') == 1
    assert table3.count(where('char') == 'c') == 1

    db.drop_tables()

    assert len(table1) == 0
    assert len(table2) == 0
    assert len(table3) == 0


def test_table_is_iterable(db):
    table = db.table('table1')

    table.insert_multiple({'int': i} for i in range(3))

    assert [r for r in table] == table.all()


def test_table_name(db):
    name = 'table3'
    table = db.table(name)
    assert name == table.name

    with pytest.raises(AttributeError):
        table.name = 'foo'


def test_table_repr(db):
    name = 'table4'
    table = db.table(name)

    assert re.match(
        r"<Table name=\'table4\', total=0, "
        r"storage=<tinydb\.storages\.MemoryStorage object at [a-zA-Z0-9]+>>",
        repr(table))
