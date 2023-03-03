#ifndef NX_LINEAR_INTERPOLATION_VALUES
#define NX_LINEAR_INTERPOLATION_VALUES

#include <stdio.h>

#include <map>

class NxLinearInterpolationValues {
	typedef std::map<NxF32, NxF32> MapType;
	typedef MapType::iterator MapIterator;
	typedef MapType::const_iterator ConstMapIterator;
	MapType _map;

	NxF32 _min, _max;
public:
	NxLinearInterpolationValues(): _min(0), _max(0), _map() { }
	
	void clear() { _map.clear(); }
	void insert(NxF32 index, NxF32 value) {
		if (_map.empty())
			_min = _max = index;
		else {
			_min = NxMath::min(_min, index);
			_max = NxMath::max(_max, index);
		}
		_map[index] = value;
	}

	void print() const {
		ConstMapIterator it = _map.begin();
		for (; it != _map.end(); ++it) {
			printf("%2.3f -> %2.3f\n", it->first, it->second);
		}
	}

	bool isValid(NxF32 number) const { return number>=_min && number<=_max; }

	NxF32 getValue(NxF32 number) const {
		ConstMapIterator lower = _map.begin();
		if (number < _min)
			return lower->second;
		ConstMapIterator upper = _map.end();
		upper--;
		if (number > _max)
			return upper->second;

		upper = _map.lower_bound(number);
		if (upper == lower)
			return (upper->second);
		lower = upper;
		lower--;
		
		//printf("- %2.3f %2.3f\n", lower->first, upper->first);
		NxF32 w1 = number - lower->first;
		NxF32 w2 = upper->first - number;
        return ((w2 * lower->second) + (w1 * upper->second)) / (w1 + w2);
	}

	NxF32 getValueAtIndex(NxI32 index) const {
		ConstMapIterator it = _map.begin();
		for (int i = 0; i < index; i++)
			++it;
		return it->second;
	}

	/*void operator=(const NxLinearInterpolationValues& other) {
		_map.insert(other._map.begin(), other._map.end());
		_max = other._max;
		_min = other._min;
	}*/

	NxU32 getSize() const { return (NxU32)_map.size(); }
};

#endif
