#include<cstdio>
#include<iostream>
template<typename T> void Swap(T& elem1, T& elem2) {
    T other = elem1;
    elem1 = elem2;
    elem2 = other;
}

template <typename T> class Point {
 public:
    T val;
    Point *next;
    Point(T val) {
        this->val = val;
        next = NULL;
    }
};

template<typename T> class List {
 public:
    const size_t size() {
        return size_val;
    }

    List() {
        size_val = 0;
        left = NULL;
        right = NULL;
    }

    ~List() {
        Point<T> *cur = left, *cur1;
        while (cur != NULL) {
            cur1 = cur;
            cur = cur->next;
            delete(cur1);
        }
    }

    void Add(T& val) {
        if (right == NULL) {
            right = new Point<T>(val);
            left = right;
            size_val = 1;
        } else {
            right->next = new Point<T>(val);
            right = right->next;
            ++size_val;
        }
    }

    Point<T>* begin() const {
        return left;
    }

    Point<T>* end() const {
        return right;
    }

 private:
    Point<T> *left, *right;
    size_t size_val;
};

template <typename T> std::ostream& operator << (std::ostream& out, const List<T> &ans) {
        auto cur = ans.begin();
        while (cur != ans.end()) {
            out << cur->val << ' ';
            cur = cur->next;
        }

        out << ans.end()->val;
        return out;
}

template <typename T> void Sort(Point<T> *first, Point<T> *last) {
        if (first == last)
            return;

        if (first->next == last) {
            if (first->val > last->val) {
                Swap(first->val, last->val);
            }
            return;
        }

        size_t length_first = 1, length_second = 1;
        Point<T> *cur, *mid1, *mid2, *cur1, *cur2, *fail;
        for (cur = first; cur != last; ++length_first) {
            cur = cur->next;
        }

        for (cur = first; length_second != length_first / 2; ++length_second) {
            cur = cur->next;
        }

        mid1 = cur;
        mid2 = cur->next;
        Sort(first, mid1);
        Sort(mid2, last);


        cur = first;
        cur1 = first->next;
        cur2 = mid2;
        fail = mid1->next;
        while ((cur1 != fail) || (cur2 != last)) {
            if ((cur2 == last) || ((cur1 != fail) && (cur1->val <= cur2->val))) {
                cur->next = cur1;
                cur1 = cur1->next;
                cur = cur->next;
            } else {
                cur->next = cur2;
                cur2 = cur2->next;
                cur = cur->next;
            }
        }

        cur->next = last;
        cur = first;
        while ((cur->next != last) && (cur->next->val < cur->val)) {
            Swap(cur->next->val, cur->val);
            cur = cur->next;
        }

        T max_val = last->val;
        for (cur = first; cur != last; cur = cur->next) {
            if (cur->val > max_val) {
                Swap(cur->val, max_val);
            }
        }

        last->val = max_val;
    }


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, val;
    List<int> input_file;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> val;
        input_file.Add(val);
    }

    Sort(input_file.begin(), input_file.end());

    std::cout << input_file << "\n";
}
