#pragma once

#include <mutex>

class Fork
{
public:
    explicit Fork(const unsigned int id) :
        m_id(id) {}

    // Satisfies the 'Lockable' concept
    void lock() { m_mutex.lock(); }
    void unlock() { m_mutex.unlock(); }
    bool try_lock() { return m_mutex.try_lock(); }

    unsigned int getId() const { return m_id; }

private:
    std::mutex         m_mutex;
    const unsigned int m_id;
};
