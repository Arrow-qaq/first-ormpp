#pragma once

#include "dbng.hpp"
#include "mysql.hpp"

using namespace ormpp;

struct _mysqlSS
{
    dbng<mysql>* pSql;
    std::atomic<bool> isFree = false;

    _mysqlSS(dbng<mysql>* sql, bool isFree)
    {
        this->pSql = sql;
        this->isFree = isFree;
    }
};

class autoStatusLock
{
public:
    autoStatusLock(std::atomic<bool>* status);
    ~autoStatusLock();

private:
    std::atomic<bool>* m_status;
};

inline autoStatusLock::autoStatusLock(std::atomic<bool>* status): m_status(status)
{
    *m_status = false;
}

inline autoStatusLock::~autoStatusLock()
{
    *m_status = true;
}

class OrmPPProxy
{
public:
    static OrmPPProxy* Getinstance(uint8_t _maxNum = 4)
    {
        static OrmPPProxy _instance(_maxNum);
        return &_instance;
    }

    template <typename T, typename... Args>
    std::vector<T> query(Args&&... args)
    {
        auto pMysqlSS = getFreeMysql();
        autoStatusLock lock(&pMysqlSS->isFree);
        std::vector<T> res = pMysqlSS->pSql->query<T>(std::forward<Args>(args)...);
        return res;
    }

    template <typename T, typename... Args>
    int insert(const T& t, Args&&... args)
    {
        auto pMysqlSS = getFreeMysql();
        autoStatusLock lock(&pMysqlSS->isFree);
        auto res = pMysqlSS->pSql->insert(t, std::forward<Args>(args)...);
        return res;
    }

    template <typename T, typename... Args>
    int update(const T& t, Args&&... args)
    {
        auto pMysqlSS = getFreeMysql();
        autoStatusLock lock(&pMysqlSS->isFree);
        auto res = pMysqlSS->pSql->update(t, std::forward<Args>(args)...);
        return res;
    }

    template <typename T, typename... Args>
    int update(const std::vector<T>& t, Args&&... args)
    {
        auto pMysqlSS = getFreeMysql();
        autoStatusLock lock(&pMysqlSS->isFree);
        auto res = pMysqlSS->pSql->update(t, std::forward<Args>(args)...);
        return res;
    }

    template <typename T, typename... Args>
    bool delete_records(Args&&... where_conditon)
    {
        auto pMysqlSS = getFreeMysql();
        autoStatusLock lock(&pMysqlSS->isFree);
        auto res = pMysqlSS->pSql->delete_records<T>(std::forward<Args>(where_conditon)...);
        return res;
    }

    // transaction
    bool begin()
    {
        auto pMysqlSS = getFreeMysql();
        autoStatusLock lock(&pMysqlSS->isFree);
        return pMysqlSS->pSql->begin();
    }

    bool commit()
    {
        auto pMysqlSS = getFreeMysql();
        autoStatusLock lock(&pMysqlSS->isFree);
        return pMysqlSS->pSql->commit();
    }

    bool rollback()
    {
        auto pMysqlSS = getFreeMysql();
        autoStatusLock lock(&pMysqlSS->isFree);
        return pMysqlSS->pSql->rollback();
    }

private:
    std::list<_mysqlSS*> m_listMysql;

    std::mutex m_mutex;

    _mysqlSS* getFreeMysql()
    {
        std::lock_guard<std::mutex> locke(m_mutex);
        while (true)
        {
            for (auto pMysqlSS : m_listMysql)
            {
                if (pMysqlSS->isFree)
                {
                    pMysqlSS->isFree = false;
                    return pMysqlSS;
                }
            }
        }
    }

    OrmPPProxy(uint8_t _maxNum)
    {
        for (int i = 0; i < _maxNum; i++)
        {
            dbng<mysql>* pMysql = new dbng<mysql>();
            pMysql->connect("127.0.0.1", "root", "123456", "testdb");
            _mysqlSS* pMysqlSS = new _mysqlSS(pMysql, true);

            m_listMysql.push_back(pMysqlSS);
        }
    }

    ~OrmPPProxy()
    {
    }
};
