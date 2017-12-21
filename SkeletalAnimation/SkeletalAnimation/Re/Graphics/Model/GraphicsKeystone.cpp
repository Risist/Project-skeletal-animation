#include <Re\Graphics\Model\GraphicsKeystone.h>

namespace Graphics
{
	ModelDef Keystone::countOffset(Step_t step, const Keystone& k1, const Keystone& k2)
	{
		assert(k1.time != k2.time);

		if (k1.time < k2.time)
		{
			return k1.def + (k2.def - k1.def) * 
				((step - k1.time) / (k2.time - k1.time));
		}
		else
		{
			return k2.def + (k1.def - k2.def) *
				((step - k2.time) / (k1.time - k2.time));
		}
	}
}