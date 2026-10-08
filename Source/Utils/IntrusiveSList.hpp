#pragma once

struct NodeHook {
    NodeHook* next = nullptr;
};

template <typename T>
class IntrusiveSList {
public:
    class Iterator {
        NodeHook* current;
    public:
        Iterator(NodeHook* node) : current(node) {}
        T& operator*() const { return *static_cast<T*>(current); }
        T* operator->() const { return static_cast<T*>(current); }
        Iterator& operator++() { if (current) current = current->next; return *this; }
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        NodeHook* get_node() const { return current; }
    };

    IntrusiveSList() = default;

    void swap(IntrusiveSList& other) noexcept {
        std::swap(this->head, other.head);
        std::swap(this->tail, other.tail);
    }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    void splice(Iterator position, IntrusiveSList& other) noexcept {
        if (other.empty()) return;

        if (position == end()) {
            if (this->empty()) {
                this->head = other.head;
                this->tail = other.tail;
            } else {
                this->tail->next = other.head;
                this->tail = other.tail;
            }
        }
        else if (position == begin()) {
            other.tail->next = this->head;
            if (this->empty()) {
                this->tail = other.tail;
            }
            this->head = other.head;
        }

        other.head = nullptr;
        other.tail = nullptr;
    }

    void push_front(T& item) {
        auto* hook = static_cast<NodeHook*>(&item);
        hook->next = head;
        if (empty()) {
            tail = hook;
        }
        head = hook;
    }

    bool empty() const { return head == nullptr; }

    template <typename Disposer>
void clear_and_dispose(Disposer disposer) {
        NodeHook* current = head;

        head = nullptr;
        tail = nullptr;

        while (current) {
            NodeHook* next_node = current->next;
            current->next = nullptr;
            disposer(static_cast<T*>(current));
            current = next_node;
        }
    }

    template <typename Predicate, typename Disposer>
void remove_and_dispose_if(Predicate pred, Disposer disposer) {
        NodeHook* current = head;
        NodeHook* prev = nullptr;

        while (current) {
            NodeHook* next_node = current->next;
            T* obj_ptr = static_cast<T*>(current);

            if (pred(*obj_ptr)) {
                if (prev) {
                    prev->next = next_node;
                } else {
                    head = next_node;
                }

                if (current == tail) {
                    tail = prev;
                }

                current->next = nullptr;
                disposer(obj_ptr);
            } else {
                prev = current;
            }

            current = next_node;
        }
    }

private:
    NodeHook* head = nullptr;
    NodeHook* tail = nullptr;
};
