import os
import copy
import json
import pytest
import pymongo
from friedrich_db import DataBase, Client

# setup the db
db_name = os.path.abspath('./test_db')
try:
    for f in os.listdir(os.path.join('.', db_name)):
        print('removing file ', f)
        os.remove(os.path.join(db_name, f))
except OSError:
    pass

try:
    if len(os.listdir(db_name)) == 0:
        os.rmdir(db_name)
except OSError:
    pass

tiny_client = Client()
tiny_database = tiny_client.create("tinyDatabase")
tiny_collection = tiny_database.create("tinyCollection")

@pytest.fixture()
def collection(request):
    # setup the db, clear if necessary
    # todo: the 'drop()' function from pymongo should work in future revisions
    tiny_collection.delete_many({})  # should delete all records in the collection

    # insert 100 integers, strings, floats, booleans, arrays, and objects
    for num in range(100):
        new_obj = {}
        new_obj['count'] = num
        new_obj['countStr'] = str(num)
        new_obj['countFloat'] = float(num) + 0.1
        new_obj['countBool'] = True if num & 1 else False
        new_obj['countArray'] = [num + i for i in range(5)]
        new_obj['countDict'] = {
            'odd': bool(num & 1),
            'even': not(num & 1),
            'three': not(num % 3),
            'five': not(num % 5),
        }
        new_obj['nestedArray'] = [[num + i] for i in range(5)]
        new_obj['dictArray'] = [{'number': num + i} for i in range(5)]
        new_obj['mixedDict'] = copy.deepcopy(new_obj)
        # todo: add object to the db

        tiny_collection.insert_one(new_obj)

    def fin():
        tiny_client.close()
        mongo_client.close()

    request.addfinalizer(finalizer=fin)

    return {
        'tiny': tiny_collection
    }


def test_initialize_db():
    """
    Ensure that the db can be created, use two clients in order to increase coverage

    :return:
    """
    tiny_client = tm.TinyMongoClient(db_name)
    another_client = tm.TinyMongoClient(db_name)
    assert True


def test_access_database_by_subscription():
    assert isinstance(tiny_client['tinyDatabase'], tm.TinyMongoDatabase)


def test_access_collection_by_subscription():
    assert isinstance(tiny_database['tinyCollection'], tm.TinyMongoCollection)


def test_list_collections():
    """
    Testing db.collection_names()
    Should list out all collections/tables in database
    """
    tables = tiny_database.collection_names()
    assert '_default' in tables
    assert 'tinyCollection' in tables


def test_initialize_collection(collection):
    """
    Ensure that the initial db is of the correct size

    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({})

    count = 0
    for doc in c:
        count += 1

    assert count == 100
    assert c.count() == 100
    assert collection['tiny'].count() == 100
    assert collection['mongo'].find({}).count() == 100
    assert collection['mongo'].count() == 100


def test_drop_collection(collection):
    c = collection['tiny']

    # assert True for successful drop
    assert c.drop() is True

    # assert False because collection does not exist anymore
    assert c.drop() is False


def test_find_with_filter_named_parameter(collection):
    c = collection['tiny'].find(filter={})
    assert c.count() == 100
    assert collection['mongo'].find(filter={}).count() == 100


def test_greater_than(collection):
    """
    Testing the greater than operator

    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({'count': {'$gte': 50}})

    assert c.count() == 50
    assert collection['mongo'].find({'count': {'$gte': 50}}).count() == 50


def test_find_in_subdocument(collection):
    """
    Testing finding documents in a nested subdocument, with a direct value query
    :param collection: pytest fixture that returns the collection
    :return:

    """
    c = collection['tiny'].find({'mixedDict.count': 0})

    assert c.count() == 1
    assert collection['mongo'].find({'mixedDict.count': 0}).count() == 1


def test_find_in_subdocument_with_operator(collection):
    """
    Testing finding documents in a nested subdocument
    :param collection: pytest fixture that returns the collection
    :return:

    """
    c = collection['tiny'].find({'mixedDict.count': {'$gte': 50}})

    assert c.count() == 50
    assert collection['mongo'].find({'mixedDict.count': {'$gte': 50}}).count() == 50


def test_find_in_subdocument_3_levels(collection):
    """
    Testing finding documents in a nested subdocument with
    :param collection: pytest fixture that returns the collection
    :return:

    """
    c = collection['tiny'].find({'mixedDict.countDict.even': True})

    assert c.count() == 50
    assert collection['mongo'].find({'mixedDict.countDict.even': True}).count() == 50


def test_sort_wrong_input_type(collection):
    """
    Testing the sort method in the positive direction

    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find()  # find all
    with pytest.raises(ValueError):
        c.sort(['count'], 1)


def test_sort_positive(collection):
    """
    Testing the sort method in the positive direction

    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find()  # find all
    c.sort('count', 1)
    assert c[0]['count'] == 0
    assert c[1]['count'] == 1


def test_sort_negative(collection):
    """
    Testing the sort method in the positive direction

    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find()  # find all
    c.sort('count', -1)
    assert c[0]['count'] == 99
    assert c[1]['count'] == 98


def test_sort_behavior(collection):
    """
    Testing sort behavior by sorting any kind of data type together
    and compare the result with MongoDB
    """
    dirname = os.path.dirname(__file__)
    source = os.path.join(dirname, "dataset_sample", "mixed_type.json")
    dataset = []
    with open(source) as data_file:
        for line in data_file:
            dataset.append(json.loads(line))

    for i, d in enumerate(dataset):
        d["_id"] = i + 1

    collection['mongo'].delete_many({})
    collection['mongo'].insert_many(dataset)
    collection['tiny'].delete_many({})
    collection['tiny'].insert_many(dataset)

    sort_by = [('item', 1), ('amount', -1)]

    mongo_find = collection['mongo'].find().sort(sort_by)
    tiny_find = collection['tiny'].find().sort(sort_by)

    assert mongo_find.count() == tiny_find.count()

    no_difference = True
    for i, m_data in enumerate(mongo_find):
        if not m_data == tiny_find[i]:
            no_difference = False

    assert no_difference


def test_has_next(collection):
    """
    Testing hasNext

    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find().sort('count', 1)

    assert c.hasNext() is True
    assert c.next()['count'] == 0


def test_not_has_next(collection):
    """
    Testing hasNext when it should be false

    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({'count': {'$gte': 98}}).sort('count', 1)

    assert c.hasNext() is True
    assert c.next()['count'] == 98
    assert c.hasNext() is True
    assert c.next()['count'] == 99
    assert c.hasNext() is False


def test_empty_find(collection):
    """
    Tests 'find' method when empty
    :param collection:
    :return:
    """
    c = collection['tiny'].find()
    assert c.count() == 100


def test_find_one(collection):
    """
    Testing the retrieval of an item using the 'find_one' method

    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find_one({'count': 3})

    assert c['countStr'] == '3'


def test_find_one_with_filter_named_parameter(collection):
    c = collection['tiny'].find_one(filter={'count': 3})
    assert c['countStr'] == '3'


def test_gte_lt(collection):
    """
    Testing the >= and < queries
    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({'count': {'$gte': 50, '$lt': 51}})
    assert c.count() == 1
    assert c[0]['countStr'] == '50'


def test_gt_lte(collection):
    """
    Testing the < and >= queries
    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({'count': {'$gt': 50, '$lte': 51}})
    assert c.count() == 1
    assert c[0]['countStr'] == '51'


def test_ne(collection):
    """
    Testing the < and >= queries
    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({'count': {'$ne': 50}})
    assert c.count() == 99

    for item in c:
        assert item['countStr'] != '50'


def test_regex(collection):
    """
    Testing the regex query
    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({'countStr': {'$regex': r'[5]{1,2}'}}).sort('count', 1)
    assert c.count() == 11

    c.sort('count', 1)
    assert c[0]['count'] == 5
    assert c[1]['count'] == 50
    assert c[2]['count'] == 51
    assert c[10]['count'] == 59

    c = collection['tiny'].find({'countStr': {'$regex': r'[^5][5]{1}'}}).sort('count', 1)
    assert c.count() == 8

    c.sort('count', 1)
    assert c[0]['count'] == 15
    assert c[1]['count'] == 25
    assert c[4]['count'] == 65
    assert c[7]['count'] == 95


def test_in(collection):
    """
    Testing the $in query with list of values as parameter
    :param collection: pytest fixture that returns the collection
    :return:
    """
    # int value testing
    c = collection['tiny'].find({'count': {'$in': [22,44,66,88]}}).sort('count', 1)
    assert c.count() == 4
    assert c[0]['count'] == 22
    assert c[1]['count'] == 44
    assert c[2]['count'] == 66
    assert c[3]['count'] == 88

    # str value testing
    c = collection['tiny'].find({'countStr': {'$in': ['11','33','55','77','99']}}).sort('count', 1)
    assert c.count() == 5
    assert c[0]['count'] == 11
    assert c[1]['count'] == 33
    assert c[2]['count'] == 55
    assert c[3]['count'] == 77
    assert c[4]['count'] == 99

    # find in list testing
    c = collection['tiny'].find({'countArray': {'$in': [22, 50]}}).sort('count', 1)
    assert c.count() == 10
    for doc in c:
        if doc['count'] <= 22:
            assert 22 in doc['countArray']
        elif doc['count'] <= 50:
            assert 50 in doc['countArray']


def test_update_one_set(collection):
    """
    Testing the update_one method of the collection

    :param collection: pytest fixture that returns the collection
    :return:
    """
    cu = collection['tiny'].update_one({'count': 3}, {'$set': {'countStr': 'three'}})
    # cu.raw_result contains the updated ids
    assert len(cu.raw_result) is 1  # only one is updated

    c = collection['tiny'].find_one({'count': 3})
    assert c['countStr'] == 'three'


def test_delete_one(collection):
    """
    Testing the 'delete_one' method

    :param collection: pytest fixture that returns the collection
    :return:
    """
    collection['tiny'].delete_one({'count': 3})

    c = collection['tiny'].find({})

    assert c.count() == 99


def test_delete_all(collection):
    """
    Testing the 'delete_many' method to remove all

    :param collection: pytest fixture that returns the collection
    :return:
    """
    collection['tiny'].delete_many({})

    c = collection['tiny'].find({})

    assert c.count() == 0


def test_delete_many(collection):
    """
    Testing the 'delete_many' method to remove some items

    :param collection: pytest fixture that returns the collection
    :return:
    """
    collection['tiny'].delete_many({'count': {'$gte': 50}})

    c = collection['tiny'].find({})

    assert c.count() == 50


def test_insert_one(collection):
    """
    Testing the 'insert_one' method
    :param collection: pytest fixture that returns the collection
    :return:
    """
    collection['tiny'].insert_one({'my_object_name': 'my object value', 'count': 1000})

    c = collection['tiny'].find({})

    assert c.count() == 101
    assert collection['tiny'].find({'my_object_name': 'my object value'})['count'] == 1000


def test_insert_many(collection):
    """
    Testing the 'insert_many' method
    :param collection: pytest fixture that returns the collection
    :return:
    """
    items = []
    for i in range(10):
        value = 1000 + i
        items.append({'count': value, 'countStr': str(value)})

    collection['tiny'].insert_many(items)

    c = collection['tiny'].find({})

    assert c.count() == 110


def test_insert_many_wrong_input(collection):
    """
    Testing the 'insert_many' method with a non-list input
    :param collection: pytest fixture that returns the collection
    :return:
    """
    item = {'my_key': 'my value'}
    with pytest.raises(ValueError):
        collection['tiny'].insert_many(item)


def test_insert_one_with_list_input(collection):
    """
    Testing the 'insert_one' method with a list input
    :param collection: pytest fixture that returns the collection
    :return:
    """
    with pytest.raises(ValueError):
        collection['tiny'].insert_one([{'my_object_name': 'my object value', 'count': 1000}])


def test_and(collection):
    """
    Testing the '$and' query
    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({"$and": [{"count": {"$gt": 10}}, {"count": {"$lte": 50}}]})
    assert c.count() == 40


def test_or(collection):
    """
    Testing the '$or' query
    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({"$or": [{"count": {"$lt": 10}}, {"count": {"$gte": 90}}]})
    assert c.count() == 20


def test_not(collection):
    """
    Testing the '$not' query
    :param collection: pytest fixture that returns the collection
    :return:
    """
    c = collection['tiny'].find({"count": {"$not": { "$gte": 90, "$lt": 10}}})
    assert c.count() == 80
