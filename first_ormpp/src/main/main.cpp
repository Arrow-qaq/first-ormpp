#include "dbng.hpp"
#include "mysql.hpp"
#include <string>

#include "connection_pool.hpp"

using namespace ormpp;

struct person
{
    int id;
    std::string name;
    int age;
};

REFLECTION(person, id, age, name)

struct test
{
    int id = 0;
    int a_;
    std::string b_;
};

REFLECTION(test, id, a_, b_)

void thread_1()
{
    std::thread::id id = std::this_thread::get_id();
    std::cout << "child thread id : " << id << std::endl;

    //auto vec = OrmPPProxy::Getinstance()->query<test>();
}

void thread_2()
{
    std::thread::id id = std::this_thread::get_id();
    std::cout << "child thread id : " << id << std::endl;

    person p = {8, "test8", 8};
    //OrmPPProxy::Getinstance()->insert(p);
}

struct GGGGGG
{
    int id = 0;
    int a_;
    std::string b_;
};

template <typename B, typename D, typename = void>
struct is_base_of : std::false_type
{
};

template <typename B, typename D>
struct is_base_of<B, D, std::void_t<decltype(dynamic_cast<B*>(&std::declval<D>()))>> : std::true_type
{
};


class AA
{
public:
    virtual ~AA() = default;

    virtual void func()
    {
        std::cout << "A" << std::endl;
    }

private:
    AA(const AA& aa);
    AA& operator =(const AA& aa);
};

class BB : public AA
{
public:
    void func() override
    {
        std::cout << "B" << std::endl;
    }
};

class CC
{
};

template <typename... Args>
std::string test1(Args&&... args)
{
    std::string sql;
    //((sql += std::forward<Args>(args), sql += " "), ...);
    ((sql += args, sql += " "), ...);
    return sql;
}


int main()
{
    // auto str = test1("a", "b", "c");
    //
    // auto a = is_base_of<BB, CC>();
    // auto b = is_base_of<AA, BB>();
    // auto c = is_base_of<BB, AA>();

    std::thread::id id = std::this_thread::get_id();
    std::cout << "main thread id : " << id << std::endl;

    person p = {1, "test8", 8};

    connection_pool<dbng<mysql>>::instance().init(4, "127.0.0.1", "root", "123456", "testdb", 0, 0);

    {
        auto db = connection_pool<dbng<mysql>>::instance().get();
        conn_guard guard(db);
        auto vec = db->query<person>();
    }

    int ggggggg = 0;

    // std::thread threa_test_1(thread_1);
    // std::thread threa_test_2(thread_2);
    // std::thread threa_test_3(thread_1);
    // std::thread threa_test_4(thread_2);
    // std::thread threa_test_5(thread_1);
    // threa_test_1.join();
    // threa_test_2.join();
    // threa_test_3.join();
    // threa_test_4.join();
    // threa_test_5.join();

    // person p = {1, "test1", 2};
    // person p1 = {2, "test2", 3};
    // person p2 = {3, "test3", 4};
    // std::vector<person> v{p1, p2};
    //
    //
    // dbng<mysql> _mysql;
    // _mysql.connect("127.0.0.1", "root", "123456", "testdb");
    // // mysql.create_datatable<person>();
    //
    // ormpp_key key1{"id"};
    // ormpp_not_null not_null{{"id", "age"}};
    //
    // _mysql.create_datatable<person>(key1, not_null);
    //
    // _mysql.insert(p);
    // _mysql.insert(v);
    //
    // _mysql.update(p);
    // _mysql.update(v);
    //
    // p.name = "mysql insert test";
    // _mysql.update(p, "id=1");
    //
    // auto result = _mysql.query<person>("id=1"); // vector<person>
    // for (auto& person : result)
    // {
    //     std::cout << person.id << " " << person.name << " " << person.age
    //         << std::endl;
    // }
    //
    // _mysql.delete_records<person>("id=1");
    //
    // // transaction
    // _mysql.begin();
    // for (int i = 0; i < 10; ++i)
    // {
    //     person s = {i, "tom", 19};
    //     if (!_mysql.insert(s))
    //     {
    //         _mysql.rollback();
    //         return -1;
    //     }
    // }
    // _mysql.commit();
    auto c = getchar();
    return 0;
}
