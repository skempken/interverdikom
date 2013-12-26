#ifndef GETTER_SETTER_MACROS_H_
#define GETTER_SETTER_MACROS_H_

// Simple get and set

#define GETTER(_MEMBER_NAME, _DATA_TYPE, _GET_FUNC_NAME) \
	_DATA_TYPE _GET_FUNC_NAME() const { return _MEMBER_NAME; }

#define SETTER(_MEMBER_NAME, _DATA_TYPE, _SET_FUNC_NAME) \
	void _SET_FUNC_NAME(_DATA_TYPE __newValue) { _MEMBER_NAME = __newValue; }

#define GETTER_SETTER(_MEMBER_NAME, _DATA_TYPE, _GET_FUNC_NAME, _SET_FUNC_NAME) \
	_DATA_TYPE _GET_FUNC_NAME() const { return _MEMBER_NAME; } \
	void _SET_FUNC_NAME(_DATA_TYPE __newValue) { _MEMBER_NAME = __newValue; }

// Get and set by reference

#define GETTER_R(_MEMBER_NAME, _DATA_TYPE, _GET_FUNC_NAME) \
	_DATA_TYPE & _GET_FUNC_NAME() { return _MEMBER_NAME; } \
	const _DATA_TYPE & _GET_FUNC_NAME() const { return _MEMBER_NAME; }

#define SETTER_R(_MEMBER_NAME, _DATA_TYPE, _SET_FUNC_NAME) \
	void _SET_FUNC_NAME(const _DATA_TYPE & __newValue) { _MEMBER_NAME = __newValue; }

#define GETTER_SETTER_R(_MEMBER_NAME, _DATA_TYPE, _GET_FUNC_NAME, _SET_FUNC_NAME) \
	_DATA_TYPE & _GET_FUNC_NAME() { return _MEMBER_NAME; } \
	const _DATA_TYPE & _GET_FUNC_NAME() const { return _MEMBER_NAME; } \
	void _SET_FUNC_NAME(const _DATA_TYPE & __newValue) { _MEMBER_NAME = __newValue; }

#endif
