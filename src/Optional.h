#pragma once

#include <cassert>

template<typename T>
class Optional {
public:
	/**
	 * @brief Constructor. Create empty Optional.
	 */
	Optional() :
			hasValue_(false),
			value_() {
	}

	/**
	 * @brief Constructor. Create non empty Optional from value.
	 * @param arg value to create optional with.
	 */
	Optional(const T &arg) :
			hasValue_(true),
			value_(arg) {
	}

	/**
	 * @brief Copy constructor.
	 * @param other Optional object.
	 */
	Optional(const Optional<T> &other) :
			hasValue_(),
			value_() {
		*this = other;
	}

	/**
	 * @brief Destructor.
	 */
	~Optional() {
	}

	/**
	 * @brief Assignment operator.
	 * @param other Optional object.
	 */
	Optional &operator=(const Optional<T> &other) {
		if (this == &other) {
			return *this;
		}
		hasValue_ = other.hasValue();
		if (other.hasValue()) {
			value_ = other.value();
		}
		return *this;
	}

	/**
     * @brief Constant operator ->
     * Allows access to internal members of a value,
     * contained inside Optional
     * Assumes that Optional is not empty
     */
	const T *operator->() const {
		assert(hasValue());
		return value_.get();
	}

	/**
	 * @brief Operator ->
	 * allow to get the value from Optional.
	 * Assumes that optional is non empty.
	 */
	T *operator->() {
		assert(hasValue());
		return value_.get();
	}

	/**
	 * @brief Constant operator *
	 * Assumes that optional is non empty.
	 * @return constant link to inner value.
	 */
	const T &operator*() const {
		assert(hasValue());
		return value();
	}

	/**
	 * @brief Operator *
	 * Assumes that optional is non empty.
	 * @return constant link to inner value.
	 */
	T &operator*() {
		assert(hasValue());
		return value();
	}

	/**
	 * @brief Check whether optional has value
	 * @return true if Optional non empty, otherwise false
	 */
	bool hasValue() const {
		return hasValue_;
	}

	/**
	 * @brief Return constant link to value
	 * Assumes that optional is non empty.
	 */
	const T &value() const {
		assert(hasValue());
		return value_;
	}

	/**
	 * @brief Возвращает ссылку на значение внутри Optional
	 * Assumes that optional is non empty.
	 */
	T &value() {
		assert(hasValue());
		return value_;
	}

	/**
	 * @brief Return value if exists, otherwise
	 * return value given by argument,
	 */
	T valueOr(const T &v) const {
		return hasValue() ? value() : v;
	}

private:
	bool hasValue_; //!< Has value flag
	T value_; //!< Value Optional
};

/**
 * @brief Operator for comparing two Optionals for equality.
 * @return true if both are empty or both have the same value.
 * @return false if one is empty and the other is not, or the values are different.
 */
template<typename T, typename U>
inline bool operator==(const Optional<T> &lhs, const Optional<U> &rhs) {
	if (lhs.hasValue() != rhs.hasValue()) {
		return false;
	}
	if ((!lhs.hasValue()) && (!rhs.hasValue())) {
		return true;
	}
	return lhs.value() == rhs.value();
}

/**
 * @brief Operator for comparing two Optionals for inequality.
 * @return true if one is empty and the other is not, or the values are different.
 * @return false if both are empty or both have the same value.
 */
template<typename T, typename U>
inline bool operator!=(const Optional<T> &lhs, const Optional<U> &rhs) {
	return !(lhs == rhs);
}

/**
 * @brief Comparison operator Optional and values for equality.
 * @return true if Optional is not empty and its value is equal to the passed value.
 * @return false if Optional is empty or its value is not equal to the one passed.
 */
template<typename T>
inline bool operator==(const Optional<T> &lhs, const T &rhs) {
	return lhs.hasValue() && (lhs.value() == rhs);
}

/**
 * @brief Comparison operator Optional and values for inequality.
 * @return true if Optional is empty or its value is not equal to the one passed.
 * @return false if Optional is not empty and its value is equal to the passed value.
 */
template<typename T>
inline bool operator!=(const Optional<T> &lhs, const T &rhs) {
	return !(lhs == rhs);
}

/**
 * @brief Comparison operator Optional and values for equality.
 * @return true if Optional is not empty and its value is equal to the passed value.
 * @return false if Optional is empty or its value is not equal to the one passed.
 */
template<typename T>
inline bool operator==(const T &lhs, const Optional<T> &rhs) {
	return rhs.hasValue() && (rhs.value() == lhs);
}

/**
 * @brief Comparison operator Optional and values for inequality.
 * @return true if Optional is empty or its value is not equal to the one passed.
 * @return false if Optional is not empty and its value is equal to the passed value.
 */
template<typename T>
inline bool operator!=(const T &lhs, const Optional<T> &rhs) {
	return !(lhs == rhs);
}
