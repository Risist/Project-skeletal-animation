/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include<Re\Common\Control\ControlAxis.h>

namespace Control
{
	float32 AxisKey::getValue() const
	{
		assert(positiveKey && negativeKey);
		return (float)(positiveKey->isReady() - negativeKey->isReady());
	}
}