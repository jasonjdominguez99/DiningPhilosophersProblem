#pragma once

#include <mutex>

class Fork
{
public:
    explicit Fork(const unsigned int id) :
        m_id(id) {}

    Fork(const Fork&) = delete;
    Fork& operator=(const Fork&) = delete;
    Fork(Fork&&) = delete;
    Fork& operator=(Fork&&) = delete;

    // Satisfies the 'Lockable' concept
    void lock() { m_mutex.lock(); }
    void unlock() { m_mutex.unlock(); }
    bool try_lock() { return m_mutex.try_lock(); }

    unsigned int getId() const { return m_id; }

private:
    std::mutex         m_mutex;
    const unsigned int m_id;
};
