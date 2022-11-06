#ifndef LIST
#define LIST

#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cassert>

#include <iostream>

#include "logger.cpp"

#define ERR_VAL -1
#define MIN_LIST_SIZE 8

namespace {
	template <class T>
	void copy(const T * source, T * destination, int length) {
		assert(source != nullptr);
		assert(destination != nullptr);
		assert(length > 0);

		const void * src = static_cast<const void *>(source);
		void * dest = static_cast<void *>(destination);
		std::size_t count = length * sizeof(T);
		std::memcpy(dest, src, count);
	}

	int nth_fib(int n) {
		assert(n >= 0);

		float Phi = (1 + sqrt(5)) / 2;
		float phi = (1 - sqrt(5)) / 2;

		return (pow(Phi, n) - pow(phi, n)) / sqrt(5);
	}
	int fib_before(int n) {
		assert(n > 0);

		int fib=0, last_fib;
		for(int i=0; fib < n; i++) {
			last_fib = fib;
			fib = nth_fib(i);
		}

		return last_fib;
	}
	int fib_after(int n) {
		assert(n >= 0);

		int fib=0;
		for(int i=0; fib <= n; i++) {
			fib = nth_fib(i);
		}

		return fib;
	}
}

template <class T>
class List {
public:
	List(): List(0) {
		// hmmm
	}
	List(std::initializer_list<T> A): List(A.size()) {
		len = A.size();
		copy(A.begin(), array, A.size());
	}
	List(const T * A, int n): List(n) {
		assert(A != NULL);

		copy(A, array, n);
		len = n;
	}
	List(const List & other): List(other.cap) {
		//LOG("List(other)");
		assert(other.len >= 0);

		len = other.len;
		if (len != 0) {
			copy(other.array, array, len);
		}
	}
	List(const List && other): List(other.cap) {
		assert(0 == 1);
		len = other.len;

		if (len != 0) {
			assert(len > 0);
			copy(other.array, array, len);
		}
	}
	~List() {
		// LOG("~List()");
		std::free(array);
	}

	int get_len() const {
		return len;
	}
	int get_cap() const {
		return cap;
	}
	int is_empty() const {
		return len == 0;
	}

	friend void swap(List<T> & A, List<T> & B) {
		using std::swap; // enable ADL

		swap(A.array, B.array);
		swap(A.len, B.len);
		swap(A.cap, B.cap);
	}

	// now featuring the copy-and-swap idiom!
	List<T> & operator= (List<T> other) {
		swap(*this, other);
		return *this;
	}

	// element access
	T & operator[] (int index) {
		if(index < 0) {
			assert(0-index <= len);
			return array[len + index];
		}
		else {
			assert(index < len);
			return array[index];
		}
	}
	const T & operator[] (int index) const {
		if(index < 0) {
			assert(0-index <= len);
			return array[len + index];
		}
		else {
			assert(index < len);
			return array[index];
		}
	}
	const T * begin() const {
		return array;
	}
	const T * end() const {
		return array + len;
	}

	int find(T object) {
		return find(object, 0, len);
	}
	int find(T object, int start) {
		return find(object, start, len);
	}
	int find(T object, int start, int end) {
		assert(end <= len);
		for(int i = start; i < end; i++) {
			if (array[i] == object) return i;
		}
		return ERR_VAL;
	}

	void push(T object) {
		if (len == cap) {
			expand();
		}
		array[len++] = object;
	}
	T pop() {
		if (len < fib_before(cap)) {
			shrink();
		}
		return array[--len];
	}

	void operator+= (const List<T> & other) {
		if (cap < len + other.len) {
			expand_above(len + other.len);
		}
		copy(other.array, array+len, other.len);
		len += other.len;
	}

	List<T> operator* (int n) {
		assert(n > 0);

		List<T> product(len * n);
		product.len = len * n;

		for(int i=0; i<n; i++) {
			copy(array,
				product.array + (len * i), len);
		}
		return product;
	}

	template <typename x> // x is what T is made of (e.g. char, string)
	T join(x c);

	friend std::ostream & operator<< (std::ostream & stream,
						const List<T> & list) {
		int i;
		stream << '[';
		for(i=0; i<list.get_len()-1; i++) {
			stream << list[i] << ", ";
		}
		stream << list[i] << ']';
		return stream;
	}
protected:
	T* array;
	int len, cap;

	List(int n) {
		// LOG("List(n)");
		assert(n >= 0);
		n = std::max(n, MIN_LIST_SIZE);
		n = fib_after(n-1); // at least n

		len = 0;
		cap = n;
		array = static_cast<T *> (
			std::malloc(n * sizeof(T))
		);
	}

	void expand_above(int n) {
		assert(n >= cap);
		n = fib_after(n);

		cap = n;
		array = static_cast<T *> (
			std::realloc(array, n * sizeof(T))
		);
	}
	void expand() {
		expand_above(cap);
	}

	void shrink_below(int n) {
		assert(n <= cap);
		n = fib_before(n);
		assert(n >= len);

		cap = n;
		array = static_cast<T *> (
			std::realloc(array, n * sizeof(T))
		);
	}
	void shrink() {
		shrink_below(cap);
	}
};

// non-member function to allow copying left operand by value during function call
template <class T>
List<T> operator+ (List<T> left, const List<T> & right) {
	left += right;
	return left;
}

#endif
