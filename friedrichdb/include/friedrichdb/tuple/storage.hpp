#ifndef STORAGE_HPP
#define STORAGE_HPP
namespace friedrichdb {
    namespace tuple {
        namespace implement {

            class storage_t {
            public:
                storage_t();

                storage_t(const storage_t &);

                storage_t &operator=(const storage_t &);

                ~storage_t();

                char *data();

                const char *data() const;

                std::size_t size() const;

                void push(const void *data, std::size_t size);

                void resize(std::size_t size);

            private:
                ///TODO raw ptr -> std::shared_ptr<std::vector<char>>.
                struct Impl;
                Impl *impl_;

                void reset(Impl *p);
            };

        }
    }
}
#endif
