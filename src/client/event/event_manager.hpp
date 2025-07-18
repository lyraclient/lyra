#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>
#include <mutex>

namespace selaura {
    struct event_manager {
        using subscription_token = std::uint64_t;

        template <typename T>
        using listener_t = std::function<void(T&)>;

        template<typename T>
        struct listener_container {
            struct listener_entry {
                subscription_token token;
                std::function<void(T&)> callback;
                void* instance = nullptr;
                union {
                    void (*static_fn)(T&) = nullptr;
                    void* member_fn;
                };
            };
            std::vector<listener_entry> listeners;
            subscription_token nextToken = 1;
            std::mutex mutex;
        };

        template <typename T>
        void dispatch(T& event) {
            auto& container = get_listener_container<T>();
            std::vector<typename listener_container<T>::listener_entry> listenersCopy;
            {
                std::lock_guard lock(container.mutex);
                listenersCopy = container.listeners;
            }
            for (const auto& entry : listenersCopy) {
                entry.callback(event);
            }
        }

        template <typename T>
        void dispatch() {
            T event{};
            dispatch(event);
        }

        template <typename T>
        subscription_token subscribe(std::function<void(T&)> listener) {
            auto& container = get_listener_container<T>();
            std::lock_guard lock(container.mutex);
            subscription_token token = container.nextToken++;
            typename listener_container<T>::listener_entry entry;
            entry.token = token;
            entry.callback = listener;
            entry.instance = nullptr;
            entry.static_fn = listener;

            container.listeners.push_back(std::move(entry));

            return token;
        }

        template <typename T, typename Func>
        subscription_token subscribe(Func listener) {
            return subscribe<T>(listener_t<T>{listener});
        }

        template <typename T, typename C>
        subscription_token subscribe(void (C::* listener)(T&), C* instance) {
            auto& container = get_listener_container<T>();
            std::lock_guard lock(container.mutex);
            subscription_token token = container.nextToken++;
            typename listener_container<T>::listener_entry entry;
            entry.token = token;
            entry.callback = [instance, listener](T& event) { (instance->*listener)(event); };
            entry.instance = static_cast<void*>(instance);
            entry.member_fn = *reinterpret_cast<void**>(&listener);

            container.listeners.push_back(std::move(entry));

            return token;
        }

        template <typename T>
        void unsubscribe(const std::function<void(T&)>& listener) {
            auto& container = get_listener_container<T>();
            std::lock_guard lock(container.mutex);
            auto& entries = container.listeners;

            for (auto it = entries.begin(); it != entries.end(); ++it) {
                if (it->instance != nullptr)
                    continue;
                if (it->callback.target_type() != listener.target_type())
                    continue;
                if (auto ptr1 = it->callback.template target<void(*)(T&)>()) {
                    if (auto ptr2 = listener.template target<void(*)(T&)>()) {
                        if (*ptr1 == *ptr2) {
                            entries.erase(it);
                            return;
                        }
                    }
                }
                if (it->callback.template target<void>() == listener.template target<void>()) {
                    entries.erase(it);
                    return;
                }
            }
        }

        template <typename T, typename Func>
        void unsubscribe(Func listener) {
            unsubscribe<T>(listener_t<T>{listener});
        }

        template <typename T, typename C>
        void unsubscribe(void (C::* listener)(T&), C* instance) {
            auto& container = get_listener_container<T>();
            std::lock_guard lock(container.mutex);
            auto& entries = container.listeners;

            void* targetInstance = static_cast<void*>(instance);
            void* targetMemberFunc = *reinterpret_cast<void**>(&listener);

            for (auto it = entries.begin(); it != entries.end(); ++it) {
                if (it->instance == targetInstance && it->member_fn == targetMemberFunc) {
                    entries.erase(it);
                    return;
                }
            }
        }

        template <typename T>
        subscription_token subscribe(void (*listener)(T&)) {
            auto& container = get_listener_container<T>();
            std::lock_guard lock(container.mutex);
            subscription_token token = container.nextToken++;
            container.listeners.push_back({
                token,
                listener,
                nullptr,
                listener
            });
            return token;
        }

        template <typename T>
        void unsubscribe(void (*listener)(T&)) {
            auto& container = get_listener_container<T>();
            std::lock_guard lock(container.mutex);
            auto& entries = container.listeners;

            for (auto it = entries.begin(); it != entries.end(); ++it) {
                if (it->static_fn == listener && it->instance == nullptr) {
                    entries.erase(it);
                    return;
                }
            }
        }

    private:
        template<typename T>
        listener_container<T>& get_listener_container() {
            static listener_container<T> container;
            return container;
        }
    };
}
