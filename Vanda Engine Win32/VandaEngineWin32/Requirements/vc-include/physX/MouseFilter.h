#ifndef MOUSEFILTER_H
#define MOUSEFILTER_H

	class MouseFilter
	{
		public:
								MouseFilter();
								MouseFilter(NxU32 length, NxF32 weight_modifier);
								~MouseFilter();

		NX_INLINE	NxF32		GetWeightModifier()						const	{ return mWeightModifier;		}
		NX_INLINE	void		SetWeightModifier(NxF32 modifier)				{ mWeightModifier = modifier;	}

		NX_INLINE	NxU32		GetHistoryBufferLength()				const	{ return mHistoryBufferLength;	}
					bool		SetHistoryBufferLength(NxU32 length);

					void		Apply(NxF32& delta_mouse_x, NxF32& delta_mouse_y);
		private:
					NxF32		mWeightModifier;
					NxU32		mHistoryBufferLength;
					NxF32*		mHistoryBufferX;
					NxF32*		mHistoryBufferY;
	};

#endif
