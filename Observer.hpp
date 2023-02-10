#pragma once

class NoCopyAble
{
protected:
    NoCopyAble() = default;
    ~NoCopyAble() = default;
    NoCopyAble(const NoCopyAble&) = default;
    NoCopyAble& operator=(const NoCopyAble&) = default;
};

#include <map>

template <typename Func>
class Events : NoCopyAble
{
public:
    Events()
    {
    }

    ~Events()
    {
    }

    int Connect(Func&& func)
    {
        return Assgin(func);
    }

    int Connect(const Func& func)
    {
        return Assgin(func);
    }

    void disConnenct(int id)
    {
        m_connectins.erase(id);
    }

    template<typename... Args>
    void notify(Args... args)
    {
        for (auto& it:m_connectins)
        {
            it.second(std::forward<Args>(args)...);
        }
    }

private:
    template <typename F>
    int Assgin(F&& f)
    {
        int id = m_observserId++;
        m_connectins.emplace(id, std::forward<F>(f));
        return id;
    }

    int m_observserId = 0;
    std::map<int, Func> m_connectins;
};
