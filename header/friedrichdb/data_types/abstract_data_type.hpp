#ifndef FRIEDRICHDB_ABSTRACT_DATA_TYPE_HP
#define FRIEDRICHDB_ABSTRACT_DATA_TYPE_HP
class abstract_data_type {
    abstract_data_type(const abstract_data_type&)= delete;
    abstract_data_type&operator=(const abstract_data_type&)= delete;

public:
    virtual void serialize_binary() const = 0;
    virtual void deserialize_binary() const = 0;
    virtual void serialize_json() const = 0;
    virtual void deserialize_json() const = 0;
};
#endif //FRIEDRICHDB_ABSTRACT_DATA_TYPE_HP
