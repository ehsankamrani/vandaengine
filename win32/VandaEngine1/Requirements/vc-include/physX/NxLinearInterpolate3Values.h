#ifndef NX_LINEAR_INTERPOLATE3_VALUES
#define NX_LINEAR_INTERPOLATE3_VALUES

class NxLinearInterpolate3Values {
	NxReal _left[3];
	NxReal _right[3];

public:
	void insert(NxReal* left, NxReal* right) {
		for (int i = 0; i < 3; i++) {
			int to = i;
			while (to > 0 && left[to] < _left[to-1]) {
				_left[to] = _left[to-1];
				_right[to] = _right[to-1];
				_left[to-1] = left[i];
			}
			_left[to] = left[i];
			_right[to] = right[i];
		}
	}
	NxReal getValue(NxReal v) {
		if (v > _left[1]) {
			if (v > _left[2])
				return _left[2];
			else {
				NxReal w1 = v - _left[1];
				NxReal w2 = _left[2] - v;
				return (_right[1] * w2 + _right[2] * w1) / (w1+w2);
			}
		} else {
			if (v < _left[0])
				return _left[0];
			else {
				NxReal w1 = v - _left[0];
				NxReal w2 = _left[1] - v;
				return (_right[0] * w2 + _right[1] * w1) / (w1+w2);
			}
		}
	}
};

#endif
