#pragma once

#include <mutex>

class Fork
{
public:
    explicit Fork(const unsigned int id) noexcept :
        m_id(id) {}

    Fork(const Fork&) = delete;
    Fork& operator=(const Fork&) = delete;
    Fork(Fork&&) = delete;
    Fork& operator=(Fork&&) = delete;

    // Satisfies the 'Lockable' concept
    void               lock() noexcept { m_mutex.lock(); }
    void               unlock() noexcept { m_mutex.unlock(); }
    [[nodiscard]] bool try_lock() noexcept { return m_mutex.try_lock(); }

    [[nodiscard]] unsigned int getId() const noexcept { return m_id; }

private:
    std::mutex         m_mutex;
    const unsigned int m_id;
};
